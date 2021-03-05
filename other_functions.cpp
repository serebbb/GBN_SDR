#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_hackrf_controller.h"
using namespace std;

void MainWindow::show_StB_msg(QString str, int delay)
{
    QFont font;
    font.setPointSize(9);
    msg_status_bar->setFont(font);
    msg_status_bar->setText(str);
    QTimer::singleShot(delay, msg_status_bar, [this](){msg_status_bar->setText("");} );
}

void MainWindow::ui_set_enabled(bool state)
{
    //    ui->cb_sample_rate->setEnabled(state);
    ui->gb_save_signal->setEnabled(state);
    //    ui->cb_buffer_size->setEnabled(state);
    ui->cb_fftsize->setEnabled(state);
}

void MainWindow::write_to_file(QByteArray data)
{
    if(sig_file.isOpen())
        sig_file.write(data);
    else
        show_StB_msg("Запись в файл невозможна");
}

void MainWindow::close_file()
{
    sig_file.close();
    show_StB_msg("Получено файлов "+QString::number(++count_file));
    pprd_rec->hide();
}

void MainWindow::create_sig_file()
{
    path_to_sig_file = QDir::currentPath()+"/signal";
    ui->le_signal_filename->setText(path_to_sig_file);
    QFile sigfile(path_to_sig_file);
    if (!sigfile.exists())
        sigfile.open(QIODevice::WriteOnly);
    else
    {
        sigfile.remove();
        sigfile.open(QIODevice::WriteOnly);
    }
    sigfile.close();
    QDir cur_dir = QDir::currentPath();
    cur_dir.mkdir("Recieved_sig");
}
