#ifndef MYCONVERT_H
#define MYCONVERT_H
#pragma once
#include "QByteArray"
#include "QDataStream"
#include "tuner_state.h"

class MyConvert
{
public:
    MyConvert();

    QByteArray StrToByte(QString str);
    QString ByteToStr(QByteArray byte);
    quint8 ArrayToInt8(QByteArray source);
    int ArrayToInt(QByteArray source);
    QByteArray IntToArray(int source);
    QByteArray Int8ToArray(quint8 source);
    QByteArray TSToByte(Tuner_state *tuner_state);
    Tuner_state* ByteToTS(QByteArray &byte);
};

#endif // MYCONVERT_H
