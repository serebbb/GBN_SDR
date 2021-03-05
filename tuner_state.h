#ifndef TUNER_STATE_H
#define TUNER_STATE_H

#include "SoapySDR/Device.hpp"
#include "QtGlobal"
#include "QString"

enum device_type
{
    HackRF,
    RTL_SDR
};

struct Tuner_state
{
    SoapySDR::Device *device;
    int dev_type = -1;
    bool isOpen = false;
    std::string format;
    int  centFreq = 100000000;
    size_t channelsNum = 1;
    int direction = SOAPY_SDR_RX;
    double  sampleRate = 8000000;
    int lna_gainLevel = -1;
    int vga_gainLevel = -1;
    int amp_gainLevel = -1;
    bool autoGainMode = 0;
    int  gainLevel = -1;
    uint32_t  adcBufSize = 131072;
    bool isNeedToExit = false; //индикатор необходимости выхода
    bool isRunning = false; //передача отсчетов запущена
    bool LogSpec = false;
    int  fftSize = 2048;
    int accumCnt = 64;
    int accumSono = 75;
    int packeg_cnt = 0;
    uint32_t bytesToRead = 0; //число байтов для чтения с выхода АЦП
};

struct SigParam
{
    quint64 bloksCnt;
    int sampFreq;
    int blockSize;
    int centFreq;
    int fftsize;
    int order;
    int impCountDelta;
};

#endif // TUNER_STATE_H
