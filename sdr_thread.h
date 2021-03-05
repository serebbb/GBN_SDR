#ifndef SDR_THREAD_H
#define SDR_THREAD_H

#include <QObject>
#include "SoapySDR/Errors.hpp"
#include "SoapySDR/Device.hpp"
#include <SoapySDR/Types.hpp>
#include <SoapySDR/Formats.hpp>
#include <SoapySDR/Modules.hpp>
#include <SoapySDR/Version.hpp>
#include "tuner_state.h"
#include "mTaClass/circbuffer.h"
#include <limits>
#include <vector>

class sdr_thread:public QObject
{
    Q_OBJECT
    // Свойство, управляющее работой потока
    Q_PROPERTY(bool running READ running WRITE setRunning NOTIFY runningChanged)
    bool m_running;

public:
    explicit sdr_thread(Tuner_state *t_s, CircBuffer<char> *cB, QObject *parent = 0);
    bool running();
    CircBuffer<char> *circBuffer;
    Tuner_state *tuner_state;

public slots:
    void run();
    void setRunning(bool running);

signals:
    void finished();    // Сигнал, по которому будем завершать поток, после завершения метода run
    void runningChanged(bool running);
};

#endif // SDR_THREAD_H
