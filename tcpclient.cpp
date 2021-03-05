#include "tcpclient.h"
#include "QDebug"

tcpclient::tcpclient()
{

}

//отключение от сервера
void tcpclient::Discon()
{   abort();}

//подключение к серверу по адресу и порту
bool tcpclient::connect_to_server(QString ip, quint16 port)
{
    Discon();
    connectToHost(ip, port);
    tmr = new QTimer(this);
    connect(this, SIGNAL(readyRead()), this, SLOT(slotReadyRead()));
    connect(tmr, SIGNAL(timeout()), this, SLOT(prog()));
    return true;
}

void tcpclient::prog()
{    emit rec_prog(100*(double)recieved_data_size/(double)buffer_size);}

//Отправка данных на сервер
int tcpclient::sendToServer(QByteArray &data, quint8 command)
{
    if (state() == QAbstractSocket::ConnectedState)
    {
        write(conv.IntToArray(data.size() + 1));
        write(conv.Int8ToArray(command));
        int written_byte = write(data);
        waitForBytesWritten();
        return written_byte;
    }
    return 0;
}

int tcpclient::sendToServer(quint8 command)
{
    QByteArray data;
    data.append("NULL");
    return sendToServer(data, command);
}
bool tcpclient::sendToServer(QString str, quint8 command)
{
    QByteArray data;
    data = conv.StrToByte(str);
    return sendToServer(data, command);
}
bool tcpclient::sendToServer(const char*  str, quint8 command)
{
    QByteArray data;
    data = conv.StrToByte(QString(str));
    return sendToServer(data, command);
}

//чтение принятого сообщения
void tcpclient::slotReadyRead()
{ 
    int current_buf_size = 0;
    do
    {
        buffer.append(readAll());
        current_buf_size = buffer.size();
        do
        {
            if (f_r_flag == 0 && buffer_size == 0 && current_buf_size >= 5)
            {
                buffer_size = conv.ArrayToInt(buffer.mid(0, 4)) - 1;
                buffer.remove(0, 4);
                quint8 com;
                com = conv.ArrayToInt8(buffer.mid(0, 1));
                buffer.remove(0, 1);
                new_message.command = com;
                if(com == 17)
                {
                    f_r_flag = 1;
                    tmr->start(400);
                }
                else
                    f_r_flag = 0;
            }
            if (f_r_flag == 0 && buffer_size > 0 && current_buf_size >= buffer_size)
            {
                new_message.data = buffer.mid(0, buffer_size);
                buffer.remove(0, buffer_size);
                buffer_size = 0;
                emit dataRecieved(new_message);
            }
            current_buf_size = buffer.size();
        }
        while(f_r_flag == 0 && current_buf_size > 0);
        if (f_r_flag && current_buf_size <= buffer_size)
        {
            emit write_to_file(buffer);
            buffer.clear();
            recieved_data_size += current_buf_size;
            //qDebug()<<"Recived data are writting to file... Recieved data size is " <<recieved_data_size<<
            //          ", full file size is "<<buffer_size;
            if(recieved_data_size == buffer_size)
            {
                f_r_flag = 0;
                recieved_data_size = 0;
                buffer_size = 0;
                tmr->stop();
                emit finish_recieve();
                emit rec_prog(100);
            }
        }

    }
    while (bytesAvailable());
}


