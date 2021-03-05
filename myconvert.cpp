#include "myconvert.h"

MyConvert::MyConvert()
{

}

QByteArray MyConvert::Int8ToArray(quint8 source)
{
    QByteArray temp;
    QDataStream data(&temp, QIODevice::ReadWrite);
    data << source;
    return temp;
}
QByteArray MyConvert::IntToArray(int source)
{
    QByteArray temp;
    QDataStream data(&temp, QIODevice::ReadWrite);
    data << source;
    return temp;
}
quint8 MyConvert::ArrayToInt8(QByteArray source)
{
    quint8 temp;
    QDataStream data(&source, QIODevice::ReadWrite);
    data >> temp;
    return temp;
}
int MyConvert::ArrayToInt(QByteArray source)
{
    int temp;
    QDataStream data(&source, QIODevice::ReadWrite);
    data >> temp;
    return temp;
}
QByteArray MyConvert::StrToByte(QString str)
{
    QByteArray byte;
    byte.resize(str.size()*2);
    memcpy(byte.data(), str.data(), str.size()*2);
    return byte;
}
QString MyConvert::ByteToStr(QByteArray byte)
{
    QString str;
    str.resize(byte.size()/2);
    memcpy(str.data(), byte.data(), byte.size());
    return str;
}

//преобразование tuner_state в массив байтов
QByteArray MyConvert::TSToByte(Tuner_state *tuner_state)
{
    QByteArray byte;
    byte.resize(sizeof(Tuner_state));
    memcpy(byte.data(), tuner_state, sizeof(Tuner_state));
    return byte;
}
//преобразование массива байтов в tuner_state
Tuner_state* MyConvert::ByteToTS(QByteArray &byte)
{
    Tuner_state *t_s = new Tuner_state;
    memcpy(&t_s, byte.data(), byte.size());
    return t_s;
}
