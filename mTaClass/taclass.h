#ifndef TACLASS_H
#define TACLASS_H
#pragma once
#include <QObject>
#include <QFile>
#include <complex>
#include "fftw3/fftw3.h"
#include <vector>
#include <QElapsedTimer>
#include <limits>
#include <float.h>
#include <QDebug>
#include <mTaClass/circbuffer.h>
#include <mTaClass/TaDefs.h>
#include <mTaClass/medFilter1d.h>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

/// < коды ошибок
enum ErrorCode_Ta
{
    NoError               = 0, /// < нет ошибок
    InvalidData           = 1, /// < в качестве массива передан нулевой укзатель
    InvalidSize           = 2, /// < некорректный размер массива
    FileNotExist          = 3, /// < файл не существует
    FileNotOpened         = 4, /// < файл не открывается
    InvalidFFTsize        = 5, /// < размер БПФ не корректен (отрицательный или не кратен двум)
    InvalidSampleRate     = 5, /// < некорректная частота дискретизации
    InvalidBandOrCentFreq = 6, /// < некорректная полоса частот или центральная частота
    InvalidTransformNum   = 7, /// < некорректный порядок преобразования (д.б. 1, 2, 4, 8)
    InvalidOverlap        = 8, /// < некорректное перекрытие (д.б. от 0  до fftsize-1);
    InvalidWinSize        = 9, /// < некорректный интервал анализа
    InvalidStep           = 10,/// < некорректный шаг
    InvalidDecimKoef      = 11,/// < некорректный коэффициент децимации
    EndOfFile             = 12,/// < конец файла
    UknownError           = 13 /// < неизвестная ошибка
};


/////////////////////////////////////////////////////////////////////////////////////
/*!
  \brief Класс додетекторного технического анализа и обработки сигналов

  Класс предназначен для реализации функций додетекторного технического анализа
  и цифрвой обработки сигналов.
*/
/////////////////////////////////////////////////////////////////////////////////////
class TaClass:public QObject
{
    Q_OBJECT

private:

    QString      filename;   /// < имя файла записи сигнала
    InputFormats format;     /// < формат отчетов
    qint64       posInFile;  /// < позиция начала анализа в файле, байты
    qint64       winsize;    /// < размер окна анализа в файле, байты
    float        sampleFreq; /// < частота дискретизации, герцы
    float        centerFreq; /// < центральная частота, герцы
    float        bandwith;   /// < полоса анализа, герцы
    ErrorCode_Ta statusFun;  /// < результат работы методов
    bool         isCancelled;/// < индикатор отмены обработки

    float leftWum;           /// < левая граница шума
    float rightWum;          /// < правая граница шума
    float leftSig;           /// < левая граница сигнала
    float rightSig;          /// < правая граница сигнала

    static int compare_64f(const void * x1, const void * x2);
public:

    //конструкторы класса
    TaClass(QString fname, InputFormats sform = BIT16C , float sfreq = 1);
    TaClass();

    void setCenterFreq(float fc);
    void setBandwith(float band);
    void setBandForSNR(float lwum, float rwum, float lsig, float rsig);
    void setPosInFile(qint64 pos);
    void setWinSize(qint64 win);
    void setSampleFreq(float sfreq);
    void setFileName(QString name);
    void setFormat(InputFormats form);

    float        getCenterFreq();
    float        getBandWith();
    qint64       getPosInFile();
    qint64       getWinSize();
    float        getSampleFreq();
    QString      getFileName();
    InputFormats getFormat();

    ErrorCode_Ta isCorrectFreqPrms();

    static int64_t  getSamplesCnt(InputFormats format, int64_t bytes);
    static int64_t  getBytesCnt(InputFormats format, int64_t samplsCnt);
    static int      getOrder2(int fftsize);

    ErrorCode_Ta decimSigOnFile(QString      fileInputName,
                                QString      fileOutName,
                                int          koefDecim,
                                InputFormats format);

    ErrorCode_Ta filterSigOnFile(QString fileOutName,
                                 int fftsize,
                                 float * resSampleFreq,
                                 bool isDecim);

    ErrorCode_Ta getMagnReImForm(vector<double> &timeOs64f,
                                 vector<double> &magn64f,
                                 vector<double> &real64f,
                                 vector<double> &imag64f,
                                 int maxSmpls,
                                 int * delta);

    ErrorCode_Ta sigDetection(QVector<double> &amft,
                              QVector<double> &amftBin,
                              QVector<double> &meanSpec,
                              int fftsize,
                              int med1WinPor,
                              int med1WinSpec,
                              int med2Win,
                              int porMin,
                              int porMax,
                              QVector<SignDetStruct> &massSigs);

    ErrorCode_Ta getMeanMaxMinSpec(vector<float>   &meanSpec,
                                   vector<float>   &minSpec,
                                   vector<float>   &maxSpec,
                                   QVector<double> &amft,
                                   vector<float>   &osf,
                                   int fftsize = 8192,
                                   int trNum = 15,
                                   int overLap = 0);

    ErrorCode_Ta getMeanSpec(vector<complex<float>> &datain,
                                   vector<float>   &meanSpec,
                                   QVector<double> &amft,
                                   vector<float>   &osf,
                                   float SampleFreq,
                                   int fftsize = 8192,
                                   int bpfCnt = 64,
                                   int overLap = 0);

    ErrorCode_Ta getCentFreqValue(fftwf_plan     &plan,
                                  complex<float> * data,
                                  complex<float> * spec,
                                  float * amplSpec,
                                  float * fc,
                                  int fftsize,
                                  int trNum);

    ErrorCode_Ta getCentFreqForPSK(vector<float> &values0,
                                   vector<float> &values2,
                                   vector<float> &values4,
                                   vector<float> &values8,
                                   vector<float> &ost,
                                   vector<float> &meanSpec1,
                                   vector<float> &meanSpec2,
                                   vector<float> &meanSpec4,
                                   vector<float> &meanSpec8,
                                   vector<float> &osf,
                                   int fftsize = 8192,
                                   int trNum = 15,
                                   int overLap = 0,
                                   int step = 1);

    ErrorCode_Ta getCentFreqForPSK(vector<float> &values0,
                                   vector<float> &values2,
                                   vector<float> &values4,
                                   vector<float> &values8,
                                   vector<float> &ost,
                                   int fftsize = 8192,
                                   int trNum = 15,
                                   int overLap = 0,
                                   int step = 1);

    ErrorCode_Ta getCentFreqForPSK(vector<float> &values0,
                                   vector<float> &values2,
                                   vector<float> &values4,
                                   vector<float> &values8,
                                   vector<float> &power,
                                   vector<float> &ost,
                                   int fftsize = 8192,
                                   int trNum = 15,
                                   int overLap = 0,
                                   int step = 1);

    ErrorCode_Ta getPowerSNR(vector<float> &SNR,
                             vector<float> &power,
                             vector<float> &ost,
                             int * delta,
                             int fftsize = 8192,
                             int maxSmpls = 8192);

    ErrorCode_Ta getSpecOfDet(vector<float> &meanSpecOgib,
                              vector<float> &meanSpecFreq,
                              vector<float> &meanSpecAcf,
                              vector<float> &osf,
                              int fftsize = 8192, uint8_t trInd = 7);

    ErrorCode_Ta getSpecOfSig(vector<float> &meanSpec1,
                              vector<float> &meanSpec2,
                              vector<float> &meanSpec4,
                              vector<float> &meanSpec8,
                              vector<float> &osf,
                              int fftsize = 8192, uint8_t trInd = 15);

    ErrorCode_Ta getMagnDetectOut(vector<float> &magn,
                                  vector<float> &ost,
                                  vector<float> &acf,
                                  vector<float> &ostacf,
                                  vector<float> &hist,
                                  vector<float> &osxhist,
                                  int fftsize = 8192,
                                  int trInd = 3);

    ErrorCode_Ta getFreqDetectOut(vector<float> &freq,
                                  vector<float> &ostfreq,
                                  vector<float> &acf,
                                  vector<float> &ostacf,
                                  vector<float> &hist,
                                  vector<float> &osxhist,
                                  int fftsize = 8192,
                                  int trInd = 3);

    // методы формирования импульсной характеристики
    static vector<complex<float> > genRCosFIRLowpassOnSymbsCmplx(int symbolsCnt,
                                                                 float Vmod,
                                                                 float Fs,
                                                                 float R,
                                                                 bool isSqrt);

    static vector<complex<float> > genRCosFIRLowpassOnSampsCmplx(int filtOrder,
                                                                 float F, float R,
                                                                 bool isSqrt);

    static vector<float> genRCosFIRLowpassOnSymbs(int symbolsCnt,
                                                  float Vmod,
                                                  float Fs,
                                                  float R,
                                                  bool isSqrt);

    static vector<float> genRCosFIRLowpassOnSamps(int filtOrder,
                                                  float F,
                                                  float R,
                                                  bool isSqrt);

    //метод чтения и конвертации из файла
    static ErrorCode_Ta readAndConvert(QFile &file,
                                       vector<complex <float> > &blockLine,
                                       qint64 *lastPos,
                                       InputFormats format,
                                       int overlap = 0);

    //методы конвертации отсчетов
    static ErrorCode_Ta convert_32s64f(const int32_t * pSrc, double * pDst, int size);
    static ErrorCode_Ta convert_16s64f(const int16_t * pSrc, double * pDst, int size);
    static ErrorCode_Ta convert_32s32f(const int     * pSrc, float  * pDst, int size);
    static ErrorCode_Ta convert_16s32f(const int16_t * pSrc, float  * pDst, int size);
    static ErrorCode_Ta convert_8s64f (const int8_t  * pSrc, double * pDst, int size);
    static ErrorCode_Ta convert_8s32f (const int8_t  * pSrc, float  * pDst, int size);
    static ErrorCode_Ta convert_32f64f(const float   * pSrc, double * pDst, int size);

    //методы арифметических действий над массивами
    static ErrorCode_Ta everyMax_32f(const float   * pSrc,
                                     float * pDst,
                                     int size);
    static ErrorCode_Ta everyMin_32f(const float   * pSrc,
                                     float * pDst,
                                     int size);
    static ErrorCode_Ta sum2Vec_32f( float * sum,
                                     float * pSrc,
                                     int size);
    static ErrorCode_Ta sumVec_32f(float * sum,
                                   const float * pSrc,
                                   int size);
    static ErrorCode_Ta sumVec_64f(double * sum,
                                   const double * pSrc,
                                   int size);
    static ErrorCode_Ta addVec_32fc(const complex<float>  * pSrc1,
                                    const complex<float> * pSrc2,
                                    complex<float> * pDst,
                                    int size);
    static ErrorCode_Ta addVec_32f(const float  * pSrc1,
                                   const float * pSrc2,
                                   float * pDst,
                                   int size);
    static ErrorCode_Ta addVec_16s(const int16_t  * pSrc1,
                                   const int16_t * pSrc2,
                                   int16_t * pDst,
                                   int size);
    static ErrorCode_Ta addVec_32f_I(const float * pSrc,
                                     float * pSrcDst,
                                     int size);
    static ErrorCode_Ta multVecC_32f_I(const float Val,
                                       float * pSrcDst,
                                       int size);
    static ErrorCode_Ta multVecC_32fc_I(const float Val,
                                        complex<float> * pSrcDst,
                                        int size);
    static ErrorCode_Ta divVecC_32f_I(const float Val,
                                      float * pSrcDst,
                                      int size);
    static ErrorCode_Ta subVecC_32f_I(const float Val,
                                      float * pSrcDst,
                                      int size);
    static ErrorCode_Ta divVecC_32fc_I(const float Val,
                                       complex<float> * pSrcDst,
                                       int size);
    static ErrorCode_Ta multVec_32f_I(const float  * pSrc,
                                      float * pSrcDst,
                                      int size);
    static ErrorCode_Ta multVec_32fc_I(const complex<float>  * pSrc,
                                       complex<float> * pSrcDst,
                                       int size);
    static ErrorCode_Ta powVec_32fc_I(complex<float> * pSrcDst,
                                      int pow2,
                                      int size);
    static ErrorCode_Ta maxIndex_32f(const float   * pSrc,
                                     int size,
                                     float * max,
                                     int * index);
    static ErrorCode_Ta minIndex_32f(const float   * pSrc,
                                     int size,
                                     float * min,
                                     int * index);

    static ErrorCode_Ta imag_32fc64f(const complex<float> * pSrc,
                                     double * pDst,
                                     int size);
    static ErrorCode_Ta imag_32c64f(const complex<int32_t> * pSrc,
                                    double * pDst,
                                    int size);
    static ErrorCode_Ta imag_16c64f(const complex<int16_t> * pSrc,
                                    double * pDst,
                                    int size);
    static ErrorCode_Ta imag_8c64f(const complex<int8_t> * pSrc,
                                   double * pDst,
                                   int size);
    static ErrorCode_Ta imag_32fc(const complex<float>   * pSrc,
                                  float * pDst,
                                  int size);
    static ErrorCode_Ta real_32fc64f(const complex<float> * pSrc,
                                     double * pDst,
                                     int size);
    static ErrorCode_Ta real_32c64f(const complex<int32_t> * pSrc,
                                    double * pDst,
                                    int size);
    static ErrorCode_Ta real_16c64f(const complex<int16_t> * pSrc,
                                    double * pDst,
                                    int size);
    static ErrorCode_Ta real_8c64f(const complex<int8_t> * pSrc,
                                   double * pDst,
                                   int size);
    static ErrorCode_Ta real_32fc(const complex<float>   * pSrc,
                                  float * pDst,
                                  int size);
    static ErrorCode_Ta magnitude_32fc64f(const complex<float> * pSrc,
                                          double * pDst,
                                          int size);
    static ErrorCode_Ta magnitude_32c64f(const complex<int32_t> * pSrc,
                                         double * pDst,
                                         int size);
    static ErrorCode_Ta magnitude_16c64f(const complex<int16_t> * pSrc,
                                         double * pDst,
                                         int size);
    static ErrorCode_Ta magnitude_8c64f(const complex<int8_t> * pSrc,
                                        double * pDst,
                                        int size);
    static ErrorCode_Ta magnitude_32fc(const complex<float>   * pSrc,
                                       float * pDst,
                                       int size);
    static ErrorCode_Ta phase_32fc(const complex<float>   * pSrc,
                                   float * pDst,
                                   int size);
    static ErrorCode_Ta magnAddVec_32fc(const complex<float>   * pSrc,
                                        float * pSrcDst,
                                        int size);
    static ErrorCode_Ta normalizeToValue_32f(float * pSrcDst,
                                             int toVal,
                                             int size);
    static ErrorCode_Ta normalizeToSum_32f(float * pSrcDst,
                                           float deltax,
                                           int size);
    static ErrorCode_Ta conj_32fc(const complex<float> * pSrc,
                                  complex<float> * pDst,
                                  int size);
    static ErrorCode_Ta diffVec_32f(const float * pSrc,
                                    float * pDst,
                                    int size);
    static ErrorCode_Ta meanVec_32f(const float * pSrc,
                                    float * mean,
                                    int size);
    static ErrorCode_Ta constRemove_32f(float * pSrcDst,
                                        int size);
    //фомрирвоание комплексного сигнала на основе преобразования Гильберта
    static ErrorCode_Ta hilbertTransform_32f32fc(float * pSrc,
                                                 complex<float> * pDst,
                                                 int size);
    static ErrorCode_Ta freqTranslate_32fc(complex<float> * pSrcDst,
                                           float fdelta,
                                           int size,
                                           qint64 * ts);
    static ErrorCode_Ta getFilterAFR_32fc(const complex<float> * pSrc,
                                          complex<float>       * pDst,
                                          int                    size);
    static ErrorCode_Ta fftShift_32f(float * pSrcDst,
                                     int     size);
    static ErrorCode_Ta phaseDiscriminator32fc(const complex<float> * sigVec,
                                               float * phaseVec,
                                               int size);
    static ErrorCode_Ta phaseDiscriminator32fc(const complex<float> * sigVec,
                                               float * phaseVec,
                                               int size,
                                               float * lastPhase);
    static ErrorCode_Ta freqDiscriminator32f(const complex<float> * sigVec,
                                             float * freqVec,
                                             int   size,
                                             float Fs,
                                             bool  isAbs,
                                             float * lastPhase);
    static ErrorCode_Ta freqDiscriminator32f(const complex<float> * sigVec,
                                             float * freqVec,
                                             int   size,
                                             float Fs,
                                             bool  isAbs);
    static ErrorCode_Ta acf_32f(float * sigVec,
                                float * acfVec,
                                int     size);
    static ErrorCode_Ta acf_32fc(complex<float> * sigVec,
                                 float          * acfVec,
                                 int              size);
    static ErrorCode_Ta histDeltaOpt(float * histOut,
                                     float * input,
                                     int     size,
                                     float   min,
                                     float   delta,
                                     float   max);
    static ErrorCode_Ta log10Vec(float * pSrc,
                                 float * pDst,
                                 int     size,
                                 float   multKoef = 1.);
    static ErrorCode_Ta medFilt1_64f(double * pSrc,
                                     double * pDst,
                                     int      size,
                                     int      windSize);

    static ErrorCode_Ta sort_64f(double * pSrc,
                                 double * pDst,
                                 int size);
    static float interpMax(vector<float> & y);

    static vector<vector<float> > transposeMatrix32f(vector<vector<float> > &matrix);

    static void rezerveMemoryForVec(vector<float> & vec,
                                    uint32_t * wantedCap);
    static bool pushBackToVec(vector<float> & vec,
                              float val);
signals:

    void sendGraficsSpec2os(float * ost, float * values, int size, int grNum);
    void sendGraficsSpec1os(float * values, int size, int grNum);

    void sendGraficsTime2os(const float * ost, const float * values, int size, int grNum);
    void sendGraficsTime1os(const float * values, int size, int grNum);

    void sendProgress(int progress);

    void sendGraficsSpec1os(double * values, int size, int grNum);

    void sendDetectedSigs(QVector<SignDetStruct> sigList);

public slots:
    void cancelProc();
};

#endif // TACLASS_H
