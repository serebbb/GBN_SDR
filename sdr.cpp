#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_hackrf_controller.h"
using namespace std;

void MainWindow::openTuner()
{
    if(tuner_state->isOpen)
    {
        show_StB_msg("Приемник уже подключен!");
        TCPclient.sendToServer("Ошибка! Приемник уже подключен!", 3);
        return;
    }
    if (ui->cb_device->currentText().isEmpty())
    {
        qDebug()<<"Не удалось подключиться. Лист устройств пуст";
        show_StB_msg("Ошибка! Не удалось подключиться к устройству.");
        TCPclient.sendToServer("Ошибка! Проверьте подключение приемника!", 3);
        return;
    }
    qDebug()<<"Подключение к SDR...";
    QString str = ui->cb_device->currentText();
    QString driver = "driver+"+str;
    if (str == "hackrf")
    {
        tuner_state->dev_type = HackRF;
        connect(&hackrfSetWin, SIGNAL(lna_gain_changed(int)), this, SLOT(setLnaGain(int)));
        connect(&hackrfSetWin, SIGNAL(vga_gain_changed(int)), this, SLOT(setVgaGain(int)));
        connect(&hackrfSetWin, SIGNAL(amp_gain_stateChanged(bool)), this, SLOT(setAmpGain(bool)));
        connect(&hackrfSetWin, SIGNAL(sampleRate_changed(double)), this, SLOT(setSampleRate(double)));
    }

    if (str == "uhd")
    {
        str.append(", type=b200");
    }

    //make device
    SoapySDR::Device *sdr = SoapySDR::Device::make(driver.toStdString());
    if(sdr == NULL)
    {
        qDebug()<<"Ошибка! Не удалось подключиться к устройству.";
        show_StB_msg("Ошибка! Не удалось подключиться к устройству.");
        TCPclient.sendToServer("Ошибка! Проверьте подключение приемника!", 3);
        return;
    }
    tuner_state->device = sdr;
    tuner_state->isOpen = true;
    hackrfSetWin.setEnabled(true);


    vector<string> str_list;
    //	2.2 Усиления
    str_list = tuner_state->device->listGains(SOAPY_SDR_RX, 0);
    for(int i = 0; i < str_list.size(); ++i)
        qDebug()<<QString::fromStdString(str_list[i]);

    for(int i=0; i< str_list.size(); i++)
    {
        SoapySDR::Range range = tuner_state->device->getGainRange(SOAPY_SDR_RX, 0, str_list[i]);
        qDebug()<<range.minimum()<<" "<<range.maximum()<<" "<<range.step();
    }

    show_StB_msg("Приемник подключен!", 1000);
    TCPclient.sendToServer("Приемник подключен!", 3);
}


void MainWindow::start_read()
{
    if (!tuner_state->isOpen)
    {
        show_StB_msg("Устройство не подключено!");
        TCPclient.sendToServer("Ошибка! Устройство не подключено!",3);
        return;
    }
    else if (tuner_state->isRunning)
    {
        show_StB_msg("Запись уже идет! Сначала остановите предыдущий поток");
        TCPclient.sendToServer("Ошибка! Запись уже идет!",3);
        return;
    }
    packeg_cnt = 0;

    int err = setFreq(centFreqEdit->getNumber());
    err |= setSampleRate(hackrfSetWin.getSampleRateCurrentVal());
    err |= setGain(hackrfSetWin.getLnaGainCurrentVal(), hackrfSetWin.getVgaGainCurrentVal(), hackrfSetWin.getAmpCurStatus());
    if(err)
    {
        qDebug()<<"(start_read) Ошибка установки параметров приемника"<<err;
        return;
    }

    ProcThread->setSignalFileName(path_to_sig_file);
    ProcThread->setRunning(true);
    SdrThread->setRunning(true);
    thread_proc->start();
    thread_sdr->start();

    TCPclient.sendToServer("Запись начата", 3);
    show_StB_msg("Запись начата", 1000);
    circBuffer->setParams(tuner_state->adcBufSize * 500, tuner_state->adcBufSize);
    qDebug()<<"Размер буфера"<<circBuffer->sizeOfBuff;
    //    ui_set_enabled(false);

    //Таймер для показа статуса заполнения буфера
    if (!tmr->isActive())
        tmr->start(500);
}

void MainWindow::stop_read()
{
    ProcThread->setRunning(false);
    SdrThread->setRunning(false);
    tmr->stop();
    bar_buf_fullness->setValue(0);
    //    ui_set_enabled(true);
    circBuffer->clearBuffer();
    show_StB_msg("Запись остановлена", 2000);
    TCPclient.sendToServer("Запись остановлена", 3);
    //        ui->lb_dropped_buffer->setText(QString("Потеряно пакетов: %1").arg(packeg_cnt - tuner_state->packeg_cnt));
    //    TCPclient.sendToServer(QString("Потеряно пакетов: %1").arg(packeg_cnt - tuner_state->packeg_cnt),3);
}

//Обнаружение подключенных приемников
void MainWindow::init_sdr()
{
    size_t maxPathLen(0);
    const auto searchPaths = SoapySDR::listSearchPaths();
    const auto modules = SoapySDR::listModules();
    for (const auto &path : searchPaths) maxPathLen = std::max(maxPathLen, path.size());
    for (const auto &mod : modules) maxPathLen = std::max(maxPathLen, mod.size());

    //print search path information
    for (const auto &path : searchPaths)
    {
        struct stat info;
        const bool missing = (stat(path.c_str(), &info) != 0);
        cout << "Search path:  " << path;
        if (missing) cout << std::string(maxPathLen-path.size(), ' ') << " (missing)";
        cout << endl;
    }

    //load each module and print information
    for (const auto &mod : modules)
    {
        cout << "Module found: " << mod;
        const auto &errMsg = SoapySDR::loadModule(mod);
        if (not errMsg.empty()) cout << "\n  " << errMsg;
        const auto version = SoapySDR::getModuleVersion(mod);
        if (not version.empty()) cout << std::string(maxPathLen-mod.size(), ' ') << " (" << version << ")";
        cout << endl;
    }
    if (modules.empty()) std::cout << "No modules found!" << std::endl;

    // 0. enumerate devices (list all devices' information)
    SoapySDR::KwargsList results = SoapySDR::Device::enumerate();
    SoapySDR::Kwargs::iterator it;
    qDebug()<<results.size();
    for( int i = 0; i < results.size(); ++i)
    {
        for(it = results[i].begin(); it != results[i].end(); ++it)
        {
            qDebug()<<QString::fromStdString(it->first)<<" "<<QString::fromStdString(it->second);
            if(QString::fromStdString(it->first) == "driver")
                ui->cb_device->addItem(QString::fromStdString(it->second));
        }
    }
}

void MainWindow::set_tuner_state(Tuner_state *ts)
{
    TCPclient.sendToServer("Параметры получены", 3);
    centFreqEdit->setNumber(ts->centFreq);
    on_pb_set_cent_freq_clicked();
    //    ui->cb_sample_rate->setCurrentText(QString::number((int)ts.sampleRate));
    //    ui->cb_buffer_size->setCurrentText(QString::number(ts.adcBufSize));
    //    ui->chb_auto_gain_mode->setChecked(ts.agcMode);
    //    ui->cb_gain->setCurrentText(QString::number(ts.gainLevel));
    //    for (int i = 0; i < tuner_state->fftSize; i++)
    //        osx[i] = (-tuner_state->sampleRate/2 + (tuner_state->sampleRate/tuner_state->fftSize)*i + tuner_state->centFreq)/1000000.;
}

int MainWindow::setSampleRate(double val)
{
    if (tuner_state->isOpen)
    {
        tuner_state->device->setSampleRate(SOAPY_SDR_RX, 1, val);
        double sdr_val = tuner_state->device->getSampleRate(SOAPY_SDR_RX, 1);
        if(val != sdr_val)
            return OTHER_ERROR;
        tuner_state->sampleRate = val;
        qDebug()<<"Частота дискретизации:"<<val<<"Гц";
        return ALL_RIGHT;
    }
    else
        return DEVICE_NOT_OPEN;
}

int MainWindow::setFreq(double val)
{
    if (tuner_state->isOpen)
    {
        tuner_state->device->setFrequency(SOAPY_SDR_RX, 0, val);
        double sdr_val = tuner_state->device->getFrequency(SOAPY_SDR_RX, 0);
        if (val != sdr_val)
            return OTHER_ERROR;
        tuner_state->centFreq = val;
        qDebug()<<"Центральная частота:"<<val<<"Гц";
        return ALL_RIGHT;
    }
    else
        return DEVICE_NOT_OPEN;
}

int MainWindow::setLnaGain(int val)
{
    if (tuner_state->isOpen)
    {
        tuner_state->device->setGain(SOAPY_SDR_RX, 1, "LNA", val);
        int sdr_val = tuner_state->device->getGain(SOAPY_SDR_RX, 1, "LNA");
        if (val != sdr_val)
            return OTHER_ERROR;
        tuner_state->lna_gainLevel = val;
        qDebug()<<"LNA усиление:"<<val;
        return ALL_RIGHT;
    }
    else
        return DEVICE_NOT_OPEN;
}

int MainWindow::setVgaGain(int val)
{
    if (tuner_state->isOpen)
    {
        tuner_state->device->setGain(SOAPY_SDR_RX, 1, "VGA", val);
        int sdr_val = tuner_state->device->getGain(SOAPY_SDR_RX, 1, "VGA");
        if (val != sdr_val)
            return OTHER_ERROR;
        tuner_state->vga_gainLevel = val;
        qDebug()<<"VGA усиление:"<<val;
        return ALL_RIGHT;
    }
    else
        return DEVICE_NOT_OPEN;
}

int MainWindow::setAmpGain(bool val)
{
    if (tuner_state->isOpen)
    {
        //qDebug()<<val;
        int gain;
        if(val) gain=14;
        else gain=0;
        tuner_state->device->setGain(SOAPY_SDR_RX, 1, "AMP", gain);
        int sdr_val = tuner_state->device->getGain(SOAPY_SDR_RX, 1, "AMP");
        if(sdr_val != gain)
            return OTHER_ERROR;
        tuner_state->amp_gainLevel = sdr_val;
        qDebug()<<"Постоянное усиление (14 дБ) "+ (val?QString("включено"):QString("отключено"));
        return ALL_RIGHT;
    }
    else
        return DEVICE_NOT_OPEN;
}

void MainWindow::setGain(int val)
{

}

int MainWindow::setGain(int lnagain, int vgagain, bool ampgain)
{
    int err = setLnaGain(lnagain);
    err |= setVgaGain(vgagain);
    err |= setAmpGain(ampgain);
    return err;
}


//    vector<double> double_list = tuner_state->device->listSampleRates(SOAPY_SDR_RX, 0);
//    for(int i=double_list.size()-1; i>=0; i--)
//    {
//        if(tuner_state->dev_type == HackRF)
//            hackrfSetWin.addItemToSampleRateList(double_list[i]);
//    }

// 2. query device info
// vector<string> str_list;
//	2.2 Усиления
//    str_list = tuner_state->device->listGains(SOAPY_SDR_RX, 0);
//    for(int i = 0; i < str_list.size(); ++i)
//        ui->cb_gain->addItem(QString::fromStdString(str_list[i]));

//    for(int i=0; i< str_list.size(); i++)
//    {
//        SoapySDR::Range range = tuner_state->device->getGainRange(SOAPY_SDR_RX, 1, str_list[i]);
//        qDebug()<<range.minimum()<<" "<<range.maximum()<<" "<<range.step();
//    }
//    //	2.3. ranges(frequency ranges)
//    SoapySDR::RangeList ranges = sdr->getFrequencyRange( SOAPY_SDR_RX, 0);
//    printf("Rx freq ranges: ");
//    for(int i = 0; i < ranges.size(); ++i)
//        printf("[%g Hz -> %g Hz], ", ranges[i].minimum(), ranges[i].maximum());
//    printf("\n");

//    // 3. apply settings
//    sdr->setSampleRate( SOAPY_SDR_RX, 0, 10e6);

//    sdr->setFrequency( SOAPY_SDR_RX, 0, 433e6);

//    // 4. setup a stream (complex floats)
//    SoapySDR::Stream *rx_stream = sdr->setupStream( SOAPY_SDR_RX, SOAPY_SDR_CF32);
//    if( rx_stream == NULL)
//    {
//        fprintf( stderr, "Failed\n");
//        SoapySDR::Device::unmake( sdr );
//        return EXIT_FAILURE;
//    }
//    sdr->activateStream( rx_stream, 0, 0, 0);

//    // 5. create a re-usable buffer for rx samples
//    std::complex<float> buff[1024];

//    // 6. receive some samples
//    for( int i = 0; i < 10; ++i)
//    {
//        void *buffs[] = {buff};
//        int flags;
//        long long time_ns;
//        int ret = sdr->readStream( rx_stream, buffs, 1024, flags, time_ns, 1e5);
//        printf("ret = %d, flags = %d, time_ns = %lld\n", ret, flags, time_ns);
//    }

//    // 7. shutdown the stream
//    sdr->deactivateStream( rx_stream, 0, 0);	//stop streaming
//    sdr->closeStream( rx_stream );

//    // 8. cleanup device handle
//    SoapySDR::Device::unmake( sdr );
