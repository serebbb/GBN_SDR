#include "proc_thread.h"

proc_thread::proc_thread(Tuner_state *t_s, CircBuffer<char> *cB, QObject *parent) : m_running(0)
{
    tuner_state = t_s;
    circBuffer = cB;
}

void proc_thread::run()
{
    int BlockSize = tuner_state->adcBufSize;
    int CompBlockSize = BlockSize/2;
    int FFTSize = tuner_state->fftSize;
    int sampleRate = tuner_state->sampleRate;
    int centFreq = tuner_state->centFreq;
    int bpfCnt = tuner_state->accumCnt;
    int cnt = 0;
    tuner_state->packeg_cnt = 0;

    qDebug()<<BlockSize;
    qDebug()<<FFTSize;

    vector<float> meanSpec(FFTSize);
    memset(meanSpec.data(),0,sizeof(float)*FFTSize);
    vector<float> meanSpecToShow(FFTSize);

    vector<float> osf(FFTSize);
    for (int i = 0; i < FFTSize; i++)
        osf[i] = (-sampleRate/2 + (sampleRate/FFTSize)*i + centFreq)/1000000.;

    if (!fileACDout.fileName().isNull() && !fileACDout.isOpen())
        fileACDout.open(QIODevice::Append);

    char * ptrBuf = new char[BlockSize];
    vector<complex<float>> tempBlock(CompBlockSize);

    //текущий комплексный спектр
    vector<complex <float> > currSpec(FFTSize);
    //амплитудный спектр
    vector<float>            currAmplSpec(FFTSize);

    //план прямого БПФ
    fftwf_plan planFow = fftwf_plan_dft_1d(FFTSize,
                                           (fftwf_complex*) tempBlock.data(),
                                           (fftwf_complex*) currSpec.data(),
                                           FFTW_FORWARD, FFTW_ESTIMATE);
    while (m_running)
    {
        if (circBuffer->getReadyToLastRead())
        {
            if(bpfCnt != tuner_state->accumCnt)
                bpfCnt = tuner_state->accumCnt;
            circBuffer->readLastBlock(ptrBuf);
            vector<int8_t> rec_sign(BlockSize);

            for(int i=0; i<BlockSize; i++)
                //                    rec_sign[i] = ptrBuf[i]-127;
                rec_sign[i]=ptrBuf[i];

            if(fileACDout.isOpen())
            {
                fileACDout.write((char*)rec_sign.data(), BlockSize);
                fileACDout.flush();
            }

            for(int i=0, j=0; j<CompBlockSize; i=i+2, j++)
            {
                tempBlock[j].real(rec_sign[i]);
                tempBlock[j].imag(rec_sign[i+1]);
            }

            fftwf_execute(planFow);
            TaClass::magnitude_32fc(currSpec.data(),currAmplSpec.data(),FFTSize);
            //TaClass::multVecC_32f_I(1./sampleRate,currAmplSpec.data(),FFTSize);
            TaClass::fftShift_32f(currAmplSpec.data(),currAmplSpec.size());
            TaClass::addVec_32f_I(currAmplSpec.data(), meanSpec.data(), FFTSize);

            cnt++;
            if(cnt >= bpfCnt)
            {
                if (centFreq != tuner_state->centFreq)
                {
                    centFreq = tuner_state->centFreq;
                    for (int i = 0; i < FFTSize; i++)
                        osf[i] = (- sampleRate/2 + (sampleRate/FFTSize)*i + centFreq)/1000000.;//деление на 1000000 чтобы были МГц
                }
                TaClass::multVecC_32f_I(1./sampleRate,meanSpec.data(),FFTSize);
                TaClass::divVecC_32f_I(bpfCnt,meanSpec.data(),FFTSize);
                if (tuner_state->LogSpec)
                    TaClass::log10Vec(meanSpec.data(),meanSpec.data(),FFTSize, 20.);
                for(int i=0; i<FFTSize; i++)
                    meanSpecToShow[i]=meanSpec[i];
                emit sendSpecData(osf.data(), meanSpecToShow.data(), FFTSize, 1);
                memset(meanSpec.data(),0,sizeof(float)*FFTSize);
                cnt = 0;
            }
        }
        //            else
        //                _sleep(1000);
    }
    fftwf_destroy_plan(planFow);
    fileACDout.waitForBytesWritten(2500);
    tuner_state->packeg_cnt = fileACDout.size()/BlockSize;
    fileACDout.close();
    qDebug() << "(proc_thread::run()) Поток обработки остановлен";
}

void proc_thread::setSignalFileName(QString str)
{
    fileACDout.setFileName(str);
    if (fileACDout.exists())
        qDebug()<<"Файл " << (fileACDout.remove()? "успешно перезаписан":"не удалось перезаписать!");
}

void proc_thread::setWriteToFile(bool flag)
{
    m_write_flag = flag;
}


bool proc_thread::running()
{
    return m_running;
}

void proc_thread::setRunning(bool running)
{
    if (m_running == running)
        return;

    m_running = running;
    emit runningChanged(running);
}

void byteToBit(char * bytesIn, qint64 bytesInCount, char * bitsOut)
{
    for (qint64 i = 0; i < bytesInCount; i++)
    {
        for (int j = 0; j < 8; j++)
            bitsOut[i*8+j] = ((bytesIn[i]>>j) & 1) ? 1 : 0;
    }
}

void bitToByte(char * bitsIn, qint64 bitsInCount, char * bytesOut)
{
    for (qint64 i = 0; i < bitsInCount/8; i++)
        bytesOut[i] = ( (bitsIn[i*8+0] << 0) |
                (bitsIn[i*8+1] << 1) |
                (bitsIn[i*8+2] << 2) |
                (bitsIn[i*8+3] << 3) |
                (bitsIn[i*8+4] << 4) |
                (bitsIn[i*8+5] << 5) |
                (bitsIn[i*8+6] << 6) |
                (bitsIn[i*8+7] << 7) );
}
