#ifndef TADEFS_H
#define TADEFS_H
#pragma once
#include <QString>

/// < форматы представления отсчетов
enum InputFormats {
    BIT8R   = 0, /// < целый, 8 бит
    BIT8C   = 1, /// < целый, комплексный, 8 бит
    BIT16R  = 2, /// < целый, 16 бит
    BIT16C  = 3, /// < целый, комлексный, 16 бит
    BIT32R  = 4, /// < целый, 32 бита
    BIT32C  = 5, /// < целый, комплексный, 32 бита
    BIT32RF = 6, /// < с плавающей точкой, 32 бита
    BIT32CF = 7  /// < с плавающей точкой, комплексный, 32 бита
};


/// < Виды модуляций
enum ModeType
{
    FSK2       = 0, /// < ЧМ-2
    PSK2       = 1, /// < ФМ-2
    PSK4       = 2, /// < ФМ-4
    PSK8       = 3, /// < ФМ-8
    MSK        = 4, /// < ММС
    PSK_FM     = 5, /// < КИМ-ФМ-ЧМ
    PSK_PM     = 6, /// < КИМ-ФМ-ФМ
    UnknownMod = 7  /// < Неизвестный вид модуляции
};

/// < Параметры анализируемого сигнала
struct SignalParams
{
    ModeType modType;        /// < Модуляционная скорость
    float    carrierFreq;    /// < Несущая частота в герцах
    float    subCarrierFreq; /// < Поднесущая частота в герцах
    float    tactFreq;       /// < Модуляционная скорость в герцах
    float    deltaFreq;      /// < Полоса сигнала
    bool     isDemoded;      /// < Индикатор, принимающий значение
    /// < true если сигнал демодулирован
    float    SNR;            /// < Отношение сигнал/шум после демодуляции

    /*!
      \brief  Метод опеределения названия вида модуляции
    */
    QString getModTypeStr()
    {
        QString rez;
        switch (modType)
        {
            case UnknownMod:
                rez = "Не определена";
                break;
            case FSK2:
                rez =  "ЧМ-2";
                break;
            case PSK2:
                rez =  "ФМ-2";
                break;
            case PSK4:
                rez =  "ФМ-4";
                break;
            case PSK8:
                rez =  "ФМ-8";
                break;
            case MSK:
                return "ММС";
                break;
            case PSK_FM:
                rez =  "КИМ-ФМ-ЧМ";
                break;
            case PSK_PM:
                rez =  "КИМ-ФМ-ФМ";
        }
        return  rez;
    }

    void resetparam()
    {
        modType        = UnknownMod; // Вид модуляции
        carrierFreq    = 0;       // Несущая частота
        subCarrierFreq = 0;       // Поднесущая частота
        tactFreq       = 0;       // Тактовая частота
        deltaFreq      = 0;       // Полоса сигнала
    }
};

struct SignDetStruct
{
    float lfreq;
    float rfreq;
    float begt;
    float endt;
    bool active;
};
#endif // TADEFS_H
