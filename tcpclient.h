#ifndef TCPCLIENT_H
#define TCPCLIENT_H
#pragma once
#include <QTcpSocket>
#include "QTcpServer"
#include "QNetworkInterface"
#include <QAbstractSocket>
#include <QObject>
#include "myconvert.h"
#include "QTimer"

struct Message
{
    quint8 command;
    QByteArray data;
};

class tcpclient : public QTcpSocket
{
    Q_OBJECT

public:
    tcpclient();
    MyConvert conv;
    int sendToServer(QByteArray &data, quint8 command);
    int sendToServer(quint8 command);
    bool sendToServer(QString str, quint8 command);
    bool sendToServer(const char* str, quint8 command);
    void Discon();
    bool connect_to_server(QString ip, quint16 port);

    Message new_message;
    QByteArray buffer;
    int buffer_size = 0;
    bool f_r_flag = 0;
    int recieved_data_size = 0;
    QTimer *tmr;

    public slots:
        void slotReadyRead();
        void prog();
    signals:
        void dataRecieved(Message mes);
        void finish_recieve();
        void write_to_file(QByteArray dat);
        void rec_prog(int pr);
};

#endif // TCPCLIENT_H
