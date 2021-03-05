#include "sdr_thread.h"
using namespace std;

sdr_thread::sdr_thread(Tuner_state *t_s, CircBuffer<char> *cB, QObject *parent) : m_running(0)
{
    tuner_state = t_s;
    circBuffer = cB;
}

bool sdr_thread::running()
{
    return m_running;
}

void sdr_thread::setRunning(bool running)
{
    if (m_running == running)
        return;

    m_running = running;
    emit runningChanged(running);
}

void sdr_thread::run()
{
    int direction = tuner_state->direction;
    int chanNum = tuner_state->channelsNum;
    //создание потока чтения
    double fullScale(0.0);
    tuner_state->format = tuner_state->device->getNativeStreamFormat(direction, chanNum, fullScale);
    const size_t elemSize = SoapySDR::formatToSize(tuner_state->format); //Сколько бит на отсчет
    auto stream = tuner_state->device->setupStream(direction, tuner_state->format);
    qDebug()<<"Stream format:"<<QString::fromStdString(tuner_state->format); //CS8 - complex signed 8bit

    const size_t numElems = tuner_state->device->getStreamMTU(stream);
    qDebug()<<"numElems:"<<numElems;

    vector<char> buffMem(elemSize*numElems);
    void * buffs = buffMem.data();

    tuner_state->device->activateStream(stream);

    unsigned int overflows(0);
    unsigned int underflows(0);
    unsigned long long totalSamples(0);
    const auto startTime = chrono::high_resolution_clock::now();
    while(m_running)
    {

         //   packeg_cnt++;
            int ret(0);
            int flags(0);
            long long timeNs(0);
            ret = tuner_state->device->readStream(stream, &buffs, numElems, flags, timeNs);
            //if (ret == SOAPY_SDR_TIMEOUT) continue;
            if (ret == SOAPY_SDR_OVERFLOW)
            {
                overflows++;
                continue;
            }
            if (ret == SOAPY_SDR_UNDERFLOW)
            {
                underflows++;
                continue;
            }
            if (ret < 0)
            {
                qDebug()<<"Unexpected stream error"<< SoapySDR::errToStr(ret);
                break;
            }
            totalSamples += ret;
            circBuffer->writeBlock(buffMem.data(),tuner_state->adcBufSize);
    }
    auto now = chrono::high_resolution_clock::now();
    auto timePassed = chrono::duration_cast<chrono::microseconds>(now - startTime);
    double FactSampleRate = double(totalSamples)/timePassed.count();
    qDebug()<<FactSampleRate<<"Msps";
    if(overflows != 0) qDebug()<<"Overflows:"<<overflows;
    if(underflows != 0) qDebug()<<"Underflows:"<<underflows;
    tuner_state->device->deactivateStream(stream);
    tuner_state->device->closeStream(stream);
    qDebug()<<"(sdr_thread::run()) Поток чтения остановлен. Принято"<<totalSamples*elemSize<<"бит";
    emit finished();
}
