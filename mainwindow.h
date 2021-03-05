#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#pragma once

#include <QMainWindow>
#include <QApplication>
#include "Ui/spinWidget.h"
#include "QProgressBar"
#include <QQueue>
#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>
#include "math.h"
#include "QDir"
#include "QTimer"
#include "mysettings.h"
#include "mTaClass/circbuffer.h"
#include "libhackrf/hackrf.h"
#include "proc_thread.h"
#include "sdr_thread.h"
#include <myconvert.h>
#include "tcpclient.h"
#include "QDataStream"
#include "QTime"
#include "QInputDialog"
#include "QProgressDialog"
#include "tuner_state.h"
#include "QThread"
#include <SoapySDR/Device.hpp>
#include <SoapySDR/Types.hpp>
#include <SoapySDR/Formats.hpp>
#include <SoapySDR/Modules.hpp>
#include <SoapySDR/Version.hpp>
#include <SoapySDR/Errors.hpp>
#include <string>
#include <vector>
#include <map>
#include <UI/hackrf_controller.h>
#include "QProgressBar"
#include "iostream"
#include "qwt_plot_spectrogram.h"


namespace Ui {
class MainWindow;
}

enum Errors
{
    ALL_RIGHT = 0,
    DEVICE_NOT_OPEN = -1,
    OTHER_ERROR = -2
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QwtPlotSpectrogram *spectrogram;

    HackRF_Controller hackrfSetWin;
    //структура, в которой хранятся данные о текущем состоянии используемого устройства
    Tuner_state *tuner_state;
    Tuner_state tuner_state_network;
    //кольцевой буфер (очередь) для передачи данных в поток обработки
    CircBuffer<char> *circBuffer;
    QQueue<double> sono;

    SpinWidget *centFreqEdit;
    QProgressBar *bar_buf_fullness;
    QLabel *lb_buf_fullness;

    QString admin_password = "admin1";
    bool admin_enable = false;
    QString user_name;
    QString IP;
    QString port;
    tcpclient TCPclient;
    MyConvert conv;
    void set_tuner_state(Tuner_state *ts);

    //работа с принятыми данными
    QThread *thread_proc;
    QThread *thread_sdr;
    proc_thread *ProcThread;
    sdr_thread *SdrThread;
    int packeg_cnt;
    QFile sig_file;
    QTimer *tmr_2;
    int file_size = 0;
    int send_byte = 0;
    int count_file = 0;
    void send_sig();
    QProgressDialog* pprd_rec;
    QProgressDialog* pprd_send;

    void create_plot();
    int sonoWindow = 100 * 2048;
    void show_StB_msg(QString str, int delay = 3000);
    void ui_set_enabled(bool state);
    void create_sig_file();
    QString path_to_sig_file;
    QTimer *tmr;

    //сохрание настроек
    QSettings *st;
    void write_settings();
    void read_settings();

    int setFreq(double val);
    void setGain(int val);
    int setGain(int lnagain, int vgagain, bool ampgain);

public slots:
    void start_read();
    void stop_read();
    void pb_start_clicked();
    void pb_stop_clicked();
    void pb_open_tuner_clicked();
    void get_signals();
    void open_settings_window();
    void init_sdr();
    void showSpecData(float *xData, float *yData, int size, int garmonicId);
    void slotError(QAbstractSocket::SocketError err);
    void show_connect_message();
    void parsing(Message message);
    void discon();
    void write_to_file(QByteArray data);
    void close_file();
    void set_send_progress();
    void set_network_ts();

    //SDR
    void refreshProg();
    void openTuner();
    int setSampleRate(double val);
    int setLnaGain(int val);
    int setVgaGain(int val);
    int setAmpGain(bool val);

private slots:
    void on_le_signal_filename_textChanged(const QString &arg1);
    void on_bp_set_signal_filename_clicked();
    void on_spb_accum_sono_valueChanged(int arg1);
    void on_pb_set_cent_freq_clicked();
    void on_cb_fftsize_currentTextChanged(const QString &arg1);
    void on_chb_log_spec_stateChanged(int arg1);
    void on_act_admin_connect_triggered();
    void on_act_client_connect_triggered();
    void on_act_set_ip_triggered();
    void on_act_set_port_triggered();
    void on_cb_accum_spec_currentTextChanged(const QString &arg1);
    void on_act_local_host_toggled(bool arg1);
    void on_act_disconnect_triggered();
    void on_pb_send_msg_clicked();

private:
    Ui::MainWindow *ui;
    QLabel *msg_status_bar;
};

#endif // MAINWINDOW_H
