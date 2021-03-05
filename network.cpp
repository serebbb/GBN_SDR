#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_hackrf_controller.h"
using namespace std;

void MainWindow::discon()
{
    admin_enable = false;
    ui->le_msg->setEnabled(false);
    ui->gb_server->setEnabled(false);
    QMessageBox::information(this, "Подключение", "Подключение разорвано");
}

void MainWindow::on_act_admin_connect_triggered()
{
    bool bOk;
    QString password = QInputDialog::getText(this, "Подключение к серверу", "Введите пароль"
                                             ,QLineEdit::Password, "", &bOk);
    if(!bOk)
        return;
    else if(password!=admin_password)
    {
        QMessageBox::information(this ,"Подключение", "Вход не выполнен. Неверный пароль");
        return;
    }
    user_name = "admin";
    TCPclient.connect_to_server(ui->act_local_host->isChecked()? "127.0.0.1" : IP, port.toInt());
}

void MainWindow::on_act_client_connect_triggered()
{
    bool bOk;
    QString client_name = QInputDialog::getText(this, "Подключение к серверу", "Введите имя клиента"
                                                ,QLineEdit::Normal, "Client", &bOk);
    if(!bOk)
        return;
    user_name = client_name;
    if (!user_name.isEmpty() && user_name!="admin")
        TCPclient.connect_to_server(ui->act_local_host->isChecked()? "127.0.0.1" : IP, port.toInt());
    else
        QMessageBox::information(this ,"Подключение", "Вход не выполнен. Введите имя");
}

//Ошибка связанная с соединением с сервером
void MainWindow::slotError(QAbstractSocket::SocketError err)
{
    QString strError = "Error: " + (err == QAbstractSocket::HostNotFoundError ? "Не удалось подключиться к серверу. Проверьте IP адрес и порт" : err == QAbstractSocket::ConnectionRefusedError ? "Подключение разорвано" : QString(TCPclient.errorString()));
    ui->te_server_info->append(strError);
    QMessageBox::information(this, "Ошибка подключения", strError);
}

void MainWindow::show_connect_message()
{
    QMessageBox::information(this, "Подключение", "Подключение выполнено успешно");
    if(user_name == "admin")
    {
        admin_enable = true;
    }
    ui->le_msg->setEnabled(true);
    ui->gb_server->setEnabled(true);
    QByteArray name = conv.StrToByte(user_name);
    TCPclient.sendToServer(name, 1);
}

void MainWindow::get_signals()
{
    if(TCPclient.isOpen() && admin_enable)
    {
        count_file = 0;
        TCPclient.sendToServer(18);
        pprd_rec->setLabelText("Принято " + QString::number(count_file));
        pprd_rec->setValue(0);
    }
    else if (!TCPclient.isOpen())
        QMessageBox::warning(this,"Внимание", "Вы не подключены к серверу!", QMessageBox::Ok);
    else if (!admin_enable)
        QMessageBox::warning(this,"Внимание", "Вы не администратор сети!", QMessageBox::Ok);
}

void MainWindow::send_sig()
{
    QFile sig(path_to_sig_file);
    if(!sig.exists())
    {
        show_StB_msg("Файл сигнала не существует!");
        return;
    }
    int size_of_message = 4096;
    TCPclient.sendToServer(19);

    if(sig.open(QIODevice::ReadOnly))
    {
        ui->pb_send_msg->setEnabled(false);
        pprd_send->show();
        tmr_2->start(150);
        file_size = sig.size();
        send_byte = 0;
        show_StB_msg("Отправка файла");
        TCPclient.write(conv.IntToArray(file_size + 1));
        TCPclient.write(conv.Int8ToArray(17));
        while(!sig.atEnd())
        {
            send_byte += TCPclient.write(sig.read(size_of_message));
            TCPclient.waitForBytesWritten();
            QApplication::processEvents(); //приложение не лагает, но передаются файлы долго
        }
        show_StB_msg("Файл передан!", 3000);
        pprd_send->setValue(100);
        tmr_2->stop();
        pprd_send->hide();
        sig.close();
        ui->pb_send_msg->setEnabled(true);
    }
}

void MainWindow::set_network_ts()
{
    if(admin_enable)
    {
        qDebug()<<tuner_state->sampleRate;
        tuner_state->centFreq = centFreqEdit->getNumber();
        QByteArray data = conv.TSToByte(tuner_state);
        TCPclient.sendToServer(data , 6);
        show_StB_msg("Установка параметров сети");
    }
    else
        QMessageBox::warning(this, "Внимание", "Вы не администратор сети!", QMessageBox::Ok);
}
