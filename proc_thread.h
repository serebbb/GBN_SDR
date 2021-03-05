#ifndef PROC_THREAD_H
#define PROC_THREAD_H

#include <QObject>
#include <tuner_state.h>
#include "mTaClass/circbuffer.h"
#include <complex>
#include <QVector>
#include <QFile>
#include "mTaClass/taclass.h"
#include <complex>
#include <float.h>
#include "fftw3/fftw3.h"
#include "tuner_state.h"



class proc_thread:public QObject
{
    Q_OBJECT

    // Свойство, управляющее работой потока
    Q_PROPERTY(bool running READ running WRITE setRunning NOTIFY runningChanged)
    Q_PROPERTY(bool write_flag WRITE setWriteToFile)
    bool m_running;
    bool m_write_flag;

public:
    explicit proc_thread(Tuner_state *t_s, CircBuffer<char> *cB, QObject *parent = 0);
    bool running();
    void setSignalFileName(QString str);
    void setWriteToFile(bool flag);

    SigParam sigP;
    TaClass mTaObject;
    CircBuffer<char> *circBuffer;
    QFile fileACDout;
    Tuner_state *tuner_state;

public slots:
    void run();
    void setRunning(bool running);

signals:
    void finished();    // Сигнал, по которому будем завершать поток, после завершения метода run
    void runningChanged(bool running);
    void sendSpecData(float *xData, float *yData, int size, int garmonicId);
};

#endif // PROC_THREAD_H
