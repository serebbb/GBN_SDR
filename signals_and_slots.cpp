#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_hackrf_controller.h"
using namespace std;

void MainWindow::pb_open_tuner_clicked()
{
    if(admin_enable)
        TCPclient.sendToServer(14);
    openTuner();
}

void MainWindow::on_bp_set_signal_filename_clicked()
{    ui->le_signal_filename->setText(QFileDialog::getOpenFileName(this, "Выберите путь для записи файла", "","*.*"));}

void MainWindow::on_spb_accum_sono_valueChanged(int arg1)
{
    tuner_state->accumSono = arg1;
    sonoWindow = arg1 * ui->cb_fftsize->currentText().toInt();
    //    ui->widSonogramBottom->plot->specData->matrix.resize(sonoWindow);
}

//Установка центральной частоты по нажатию
void MainWindow::on_pb_set_cent_freq_clicked()
{    setFreq(centFreqEdit->getNumber());}

void MainWindow::on_cb_fftsize_currentTextChanged(const QString &arg1)
{    tuner_state->fftSize = arg1.toInt();}

void MainWindow::on_chb_log_spec_stateChanged(int arg1)
{    tuner_state->LogSpec = arg1;}

void MainWindow::on_cb_accum_spec_currentTextChanged(const QString &arg1)
{    tuner_state->accumCnt = arg1.toInt();}

void MainWindow::on_le_signal_filename_textChanged(const QString &arg1)
{    path_to_sig_file = arg1;}

void MainWindow::on_act_set_ip_triggered()
{
    bool bOk;
    QString new_ip;
    new_ip = QInputDialog::getText(this, "Настройка подключения", "Укажите IP адрес сервера"
                                   ,QLineEdit::Normal, IP, &bOk);
    if(bOk)
        IP = new_ip;
}

void MainWindow::on_act_set_port_triggered()
{
    bool bOk;
    QString new_port;
    new_port = QInputDialog::getText(this, "Настройка подключения", "Укажите порт сервера"
                                     ,QLineEdit::Normal, port, &bOk);
    if(bOk)
        port=new_port;
}

void MainWindow::on_act_local_host_toggled(bool arg1)
{     ui->act_set_ip->setEnabled(!arg1);}

void MainWindow::on_act_disconnect_triggered()
{    TCPclient.Discon();}

void MainWindow::on_pb_send_msg_clicked()
{
    QString str;
    str = ui->le_msg->text();
    if(!str.isEmpty())
    {
        ui->le_msg->clear();
        QByteArray data;
        data = conv.StrToByte(str);
        TCPclient.sendToServer(data, 3);
    }
}

void MainWindow::set_send_progress()
{    pprd_send->setValue(100*(double)send_byte/(double)file_size);}

void MainWindow::refreshProg()
{
    int BufFul = circBuffer->getFullness();
    bar_buf_fullness->setValue(BufFul);
    if(BufFul <= 20)
        bar_buf_fullness->setStyleSheet("QProgressBar::chunk {background-color: rgb(0, 255, 0)}");
    else if(BufFul >= 20 && BufFul <= 70)
        bar_buf_fullness->setStyleSheet("QProgressBar::chunk {background-color: rgb(255, 255, 0)}");
    else if(BufFul >= 70)
        bar_buf_fullness->setStyleSheet("QProgressBar::chunk {background-color: rgb(255, 0, 0)}");
}

void MainWindow::pb_start_clicked()
{
    if(admin_enable)
    {
        TCPclient.sendToServer(15);
        return;
    }
    else
        start_read();
}

void MainWindow::pb_stop_clicked()
{
    if(admin_enable)
    {
        TCPclient.sendToServer(16);
        return;
    }
    else
        stop_read();
}

void MainWindow::open_settings_window()
{    hackrfSetWin.show();}
