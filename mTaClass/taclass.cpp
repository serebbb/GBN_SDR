#include "taclass.h"

#define ERROROUT qDebug() <<__FUNCTION__ << ": error code - "<<

/////////////////////////////////////////////////////////////////////////////////////
/*!
  \brief  Конструктор класса TaClass
  
  \param [in]  fname   полное имя файла записи анализируемого сигнала
  \param [in]  sform   формат отсчетов сигнала
  \param [in]  sfreq   частота дискретизации в герцах
  
*/
/////////////////////////////////////////////////////////////////////////////////////
TaClass::TaClass(QString fname,   InputFormats sform, float sfreq):
    filename(fname), format(sform),  sampleFreq(sfreq)
{
    posInFile  =  0;
    centerFreq = -1;
    bandwith   = -1;
    QFile file(filename);
    winsize = file.size();
    statusFun = NoError;
    isCancelled = false;
    leftWum  = 0;
    leftSig  = 0;
    rightWum = 0;
    rightSig = 0;
}

/////////////////////////////////////////////////////////////////////////////////////
/*!
  \brief  Конструктор класса TaClass по умолчанию
  
*/
/////////////////////////////////////////////////////////////////////////////////////
TaClass::TaClass()
{
    format     =  BIT16C;
    sampleFreq =  1;
    posInFile  =  0;
    centerFreq = -1;
    bandwith   = -1;
    statusFun = NoError;
    isCancelled = false;
    leftWum  = 0;
    leftSig  = 0;
    rightWum = 0;
    rightSig = 0;
}

/////////////////////////////////////////////////////////////////////////////////////
/*!
  \brief  Метод задания центарльной частоты обрабатываемого сигнала
  
  \param [in]  fc   центральная частота, Гц
*/
/////////////////////////////////////////////////////////////////////////////////////
void TaClass::setCenterFreq(float fc)
{
    centerFreq = fc;
}

/////////////////////////////////////////////////////////////////////////////////////
/*!
  \brief  Метод задания ширины полосы частот
  
  \param [in]  band   центральная частота, Гц
*/
/////////////////////////////////////////////////////////////////////////////////////
void TaClass::setBandwith(float band)
{
    bandwith = band;
}

void TaClass::setBandForSNR(float lwum, float rwum, float lsig, float rsig)
{
    leftWum  = lwum;
    leftSig  = lsig;
    rightWum = rwum;
    rightSig = rsig;
}
/////////////////////////////////////////////////////////////////////////////////////
/*!
  \brief  Метод задания позиции начала анализа в файле в байтах
  
  \param [in]  pos   позиция начала анализа в файле, байты
*/
/////////////////////////////////////////////////////////////////////////////////////
void TaClass::setPosInFile(qint64 pos)
{
    posInFile = pos;
}

/////////////////////////////////////////////////////////////////////////////////////
/*!
  \brief  Метод задания размера интервала анализа в файле в байтах
  
  \param [in]  win   размер итервала анализа в файле, байты
*/
/////////////////////////////////////////////////////////////////////////////////////
void TaClass::setWinSize(qint64 win)
{
    winsize = win;
}

/////////////////////////////////////////////////////////////////////////////////////
/*!
  \brief  Метод задания частоты дискретизации сигнала в герцах
  
  \param [in]  sfreq   частота дискретизации, герцы
*/
/////////////////////////////////////////////////////////////////////////////////////
void TaClass::setSampleFreq(float sfreq)
{
    sampleFreq = sfreq;
}

/////////////////////////////////////////////////////////////////////////////////////
/*!
  \brief  Метод задания имени файла записи анализируемого сигнала
  
  \param [in]  name  полное имя сигнала
*/
/////////////////////////////////////////////////////////////////////////////////////
void TaClass::setFileName(QString name)
{
    filename = name;
}

/////////////////////////////////////////////////////////////////////////////////////
/*!
  \brief  Метод задания формата отсчетов записи сигнала
  
  \param [in]  form  формат отсчетов типа InputFormats
*/
/////////////////////////////////////////////////////////////////////////////////////
void TaClass::setFormat(InputFormats form)
{
    format = form;
}

/////////////////////////////////////////////////////////////////////////////////////
/*!
  \brief  Метод возвращения центральной частоты обрабатываемого сигнала
*/
/////////////////////////////////////////////////////////////////////////////////////
float TaClass::getCenterFreq()
{
    return  centerFreq;
}

/////////////////////////////////////////////////////////////////////////////////////
/*!
  \brief  Метод возвращения ширины полосы частот
*/
/////////////////////////////////////////////////////////////////////////////////////
float TaClass::getBandWith()
{
    return  bandwith;
}

/////////////////////////////////////////////////////////////////////////////////////
/*!
  \brief  Метод возвращения начальной позиции анализа в файле в байтах
*/
/////////////////////////////////////////////////////////////////////////////////////
qint64 TaClass::getPosInFile()
{
    return posInFile;
}

/////////////////////////////////////////////////////////////////////////////////////
/*!
  \brief  Метод возвращения размера интервала анализа в файле в байтах
*/
/////////////////////////////////////////////////////////////////////////////////////
qint64 TaClass::getWinSize()
{
    return  winsize;
}

/////////////////////////////////////////////////////////////////////////////////////
/*!
  \brief  Метод возвращения частоты дискретизации сигнала в герцах
*/
/////////////////////////////////////////////////////////////////////////////////////
float TaClass::getSampleFreq()
{
    return  sampleFreq;
}

/////////////////////////////////////////////////////////////////////////////////////
/*!
  \brief  Метод возвращения имени файла записи анализируемого сигнала
*/
/////////////////////////////////////////////////////////////////////////////////////
QString  TaClass::getFileName()
{
    return  filename;
}

/////////////////////////////////////////////////////////////////////////////////////
/*!
  \brief  Метод возвращения формата отсчетов записи сигнала
*/
/////////////////////////////////////////////////////////////////////////////////////
InputFormats TaClass::getFormat()
{
    return  format;
}

/////////////////////////////////////////////////////////////////////////////////////
/*!
  \brief  Метод проверки корректности частотных параметров обработки
  
  Метод проверяет корректность заданных центральной частоты и полосы фильтрации
  относительно частоты дискретизации и возвращает код ошибки InvalidBandOrCentFreq
*/
/////////////////////////////////////////////////////////////////////////////////////
ErrorCode_Ta TaClass::isCorrectFreqPrms()
{
    if (format == BIT8C  ||
            format == BIT16C ||
            format == BIT32C ||
            format == BIT32CF)
    {
        if (((centerFreq - bandwith/2) < -sampleFreq/2) ||
                ((centerFreq + bandwith/2) >  sampleFreq/2) ||
                bandwith > 0.98*sampleFreq)
        {
            ERROROUT InvalidBandOrCentFreq;
            return  InvalidBandOrCentFreq;
        }
    }
    else
    {
        if (((centerFreq - bandwith/2) < 0)             ||
                ((centerFreq + bandwith/2) >  sampleFreq/2) ||
                bandwith > 0.98*sampleFreq/2)
        {
            ERROROUT InvalidBandOrCentFreq;
            return  InvalidBandOrCentFreq;
        }
    }
    
    return NoError;
}

/////////////////////////////////////////////////////////////////////////////////////
/*!
  \brief  Метод вычисления числа отсчетов в заданном блоке байтов
  
  Метод предназначен для определения числа отсчетов сигнала, помещаемых в заданном
  блоке из bytes байтов в зависимости от формата представления отсчетов format,
  характеризуемого типом InputFormats
  
  \param [in]  format   формат представления отсчетов сигнала InputFormats
  \param [in]  bytes    число байтов
*/
/////////////////////////////////////////////////////////////////////////////////////
int64_t TaClass::getSamplesCnt(InputFormats format, int64_t bytes)
{
    int64_t samplesCnt;
    switch (format)
    {
    case BIT8R:
        samplesCnt = bytes;
        break;
    case BIT8C:
        samplesCnt = bytes/2;
        break;
    case BIT16R:
        samplesCnt = bytes/2;
        break;
    case BIT16C:
        samplesCnt = bytes/2/2;
        break;
    case BIT32R:
        samplesCnt = bytes/4;
        break;
    case BIT32C:
        samplesCnt = bytes/4/2;
        break;
    case BIT32RF:
        samplesCnt = bytes/4;
        break;
    case BIT32CF:
        samplesCnt = bytes/4/2;
    }
    return samplesCnt;
}

/////////////////////////////////////////////////////////////////////////////////////
/*!
  \brief  Метод вычисления числа байтов в заданном блоке отсчетов сигнала
  
  Метод предназначен для определения числа байтов, соответствующих заданному
  блоку из samplsCnt отсчетов в зависимости от формата представления отсчетов format,
  характеризуемого типом InputFormats
  
  \param [in]  format       формат представления отсчетов сигнала InputFormats
  \param [in]  samplsCnt    число отсчетов сигнала
  
*/
/////////////////////////////////////////////////////////////////////////////////////
int64_t TaClass::getBytesCnt(InputFormats format, int64_t samplsCnt)
{
    int64_t blockSizeBytes;
    switch (format)
    {
    case BIT8R:
        blockSizeBytes = samplsCnt;
        break;
    case BIT8C:
        blockSizeBytes = samplsCnt*2;
        break;
    case BIT16R:
        blockSizeBytes = samplsCnt*2;
        break;
    case BIT16C:
        blockSizeBytes = samplsCnt*2*2;
        break;
    case BIT32R:
        blockSizeBytes = samplsCnt*4;
        break;
    case BIT32C:
        blockSizeBytes = samplsCnt*4*2;
        break;
    case BIT32RF:
        blockSizeBytes = samplsCnt*4;
        break;
    case BIT32CF:
        blockSizeBytes = samplsCnt*4*2;
    }
    return blockSizeBytes;
}

/////////////////////////////////////////////////////////////////////////////////////
/*!
  \brief  Метод определения степени двойки
  
  Метод возвращает значение степени, в которую нужно возвести число 2 для получения
  входного значения fftsize
  
  \param [in]  fftsize  число, получаемое в результате возведения числа 2 в искомую
                        степень
*/
/////////////////////////////////////////////////////////////////////////////////////
int TaClass::getOrder2(int fftsize)
{
    int ord = 0;
    for (int i = 1; i < 31; i++)
    {
        if (int(pow(2,i)) == fftsize)
        {
            ord = i;
            break;
        }
    }
    return ord;
}


/////////////////////////////////////////////////////////////////////////////////////
/*!
  \brief  Метод децимации цифровой записи сигнала
  
  Метод предназначен для понижения частоты дискретизации цифровой записи сигнала,
  хранящейся в файле, в целое число раз. Метод возвращает код ошибки типа ErrorCode_Ta.
  
  \param [in]  fileInputName  имя входного файла
  \param [in]  fileOutName    имя выходного файла
  \param [in]  koefDecim      коэффициент децимации
*/
/////////////////////////////////////////////////////////////////////////////////////
ErrorCode_Ta TaClass::decimSigOnFile(QString      fileInputName,
                                     QString      fileOutName,
                                     int          koefDecim,
                                     InputFormats formatIn)
{
    ErrorCode_Ta status = NoError;
    
    QElapsedTimer timest;
    timest.start();
    
    isCancelled = false;
    
    int blockSizeSamples = koefDecim*1024;
    int blockSizeBytes;
    
    //Создание файловых переменных
    QFile fileInput(fileInputName);
    QFile fileOutput(fileOutName);
    if (fileOutput.exists())
        fileOutput.remove();
    
    vector<int8_t>   blockInput8s;
    vector<int8_t>   blockOutput8s;
    vector<int16_t>  blockInput16s;
    vector<int16_t>  blockOutput16s;
    vector<int32_t>  blockInput32s;
    vector<int32_t>  blockOutput32s;
    vector<float>    blockInput32f;
    vector<float>    blockOutput32f;
    
    vector<complex <int8_t>  > blockInput8sc;
    vector<complex <int8_t>  > blockOutput8sc;
    vector<complex <int16_t> > blockInput16sc;
    vector<complex <int16_t> > blockOutput16sc;
    vector<complex <int32_t> > blockInput32sc;
    vector<complex <int32_t> > blockOutput32sc;
    vector<complex <float>   > blockInput32fc;
    vector<complex <float>   > blockOutput32fc;
    
    switch (format)
    {
    case BIT8R:
        blockSizeBytes = blockSizeSamples;
        blockInput8s.resize(blockSizeSamples);
        blockOutput8s.resize(blockSizeSamples/koefDecim);
        break;
    case BIT8C:
        blockSizeBytes = blockSizeSamples*2;
        blockInput8sc.resize(blockSizeSamples);
        blockOutput8sc.resize(blockSizeSamples/koefDecim);
        break;
    case BIT16R:
        blockSizeBytes = blockSizeSamples*2;
        blockInput16s.resize(blockSizeSamples);
        blockOutput16s.resize(blockSizeSamples/koefDecim);
        break;
    case BIT16C:
        blockSizeBytes = blockSizeSamples*2*2;
        blockInput16sc.resize(blockSizeSamples);
        blockOutput16sc.resize(blockSizeSamples/koefDecim);
        break;
    case BIT32R:
        blockSizeBytes = blockSizeSamples*4;
        blockInput32s.resize(blockSizeSamples);
        blockOutput32s.resize(blockSizeSamples/koefDecim);
        break;
    case BIT32C:
        blockSizeBytes = blockSizeSamples*4*2;
        blockInput32sc.resize(blockSizeSamples);
        blockOutput32sc.resize(blockSizeSamples/koefDecim);
        break;
    case BIT32RF:
        blockSizeBytes = blockSizeSamples*4;
        blockInput32f.resize(blockSizeSamples);
        blockOutput32f.resize(blockSizeSamples/koefDecim);
        break;
    case BIT32CF:
        blockSizeBytes = blockSizeSamples*4*2;
        blockInput32fc.resize(blockSizeSamples);
        blockOutput32fc.resize(blockSizeSamples/koefDecim);
    }
    
    if (fileInput.exists())
    {
        
        if (koefDecim < 1 || getSamplesCnt(formatIn,fileInput.size())/koefDecim < 2)
        {
            ERROROUT InvalidDecimKoef;
            return InvalidDecimKoef;
        }
        
        if (fileInput.open(QIODevice::ReadOnly) && fileOutput.open(QIODevice::WriteOnly))
        {
            
            while (!fileInput.atEnd())
            {
                
                switch (formatIn)
                {
                case BIT8R:
                    blockSizeBytes = blockSizeSamples;
                    fileInput.read((char*)blockInput8s.data(),blockSizeBytes);
                    for (int i = 0; i < blockSizeSamples;i+=koefDecim)
                    {
                        blockOutput8s[i/koefDecim] = blockInput8s[i];
                    }
                    fileOutput.write((char*)(blockOutput8s.data()),
                                     blockOutput8s.size()*sizeof(int8_t));
                    break;
                    
                case BIT8C:
                    blockSizeBytes = blockSizeSamples*2;
                    fileInput.read((char*)blockInput8sc.data(),blockSizeBytes);
                    for (int i = 0; i < blockSizeSamples;i+=koefDecim)
                    {
                        blockOutput8sc[i/koefDecim] = blockInput8sc[i];
                    }
                    fileOutput.write((char*)(blockOutput8sc.data()),
                                     blockOutput8sc.size()*sizeof(int8_t)*2);
                    break;
                    
                case BIT16R:
                    blockSizeBytes = blockSizeSamples*2;
                    fileInput.read((char*)blockInput16s.data(),blockSizeBytes);
                    for (int i = 0; i < blockSizeSamples;i+=koefDecim)
                    {
                        blockOutput16s[i/koefDecim] = blockInput16s[i];
                    }
                    fileOutput.write((char*)(blockOutput16s.data()),
                                     blockOutput16s.size()*sizeof(int16_t));
                    break;
                    
                case BIT16C:
                    blockSizeBytes = blockSizeSamples*2*2;
                    
                    fileInput.read((char*)blockInput16sc.data(),blockSizeBytes);
                    for (int i = 0; i < blockSizeSamples;i+=koefDecim)
                    {
                        blockOutput16sc[i/koefDecim] = blockInput16sc[i];
                    }
                    fileOutput.write((char*)(blockOutput16sc.data()),
                                     blockOutput16sc.size()*sizeof(int16_t)*2);
                    break;
                case BIT32R:
                    blockSizeBytes = blockSizeSamples*4;
                    
                    fileInput.read((char*)blockInput32s.data(),blockSizeBytes);
                    for (int i = 0; i < blockSizeSamples;i+=koefDecim)
                    {
                        blockOutput32s[i/koefDecim] = blockInput32s[i];
                    }
                    fileOutput.write((char*)(blockOutput32s.data()),
                                     blockOutput32s.size()*sizeof(int32_t));
                    break;
                case BIT32C:
                    
                    blockSizeBytes = blockSizeSamples*4*2;
                    
                    fileInput.read((char*)blockInput32sc.data(),blockSizeBytes);
                    for (int i = 0; i < blockSizeSamples;i+=koefDecim)
                    {
                        blockOutput32sc[i/koefDecim] = blockInput32sc[i];
                    }
                    fileOutput.write((char*)(blockOutput32sc.data()),
                                     blockOutput32sc.size()*sizeof(int32_t)*2);
                    
                    break;
                case BIT32RF:
                    blockSizeBytes = blockSizeSamples*4;
                    
                    fileInput.read((char*)blockInput32f.data(),blockSizeBytes);
                    for (int i = 0; i < blockSizeSamples;i+=koefDecim)
                    {
                        blockOutput32f[i/koefDecim] = blockInput32f[i];
                    }
                    fileOutput.write((char*)(blockOutput32f.data()),
                                     blockOutput32f.size()*sizeof(float));
                    break;
                case BIT32CF:
                    blockSizeBytes = blockSizeSamples*4*2;
                    
                    
                    fileInput.read((char*)blockInput32fc.data(),blockSizeBytes);
                    for (int i = 0; i < blockSizeSamples;i+=koefDecim)
                    {
                        blockOutput32fc[i/koefDecim] = blockInput32fc[i];
                    }
                    fileOutput.write((char*)(blockOutput32fc.data()),
                                     blockOutput32fc.size()*sizeof(float)*2);
                }
                
                
                //каждые полсекунды отправляем данные для отображения в
                //интерфейсе пользователя
                if (timest.elapsed() > 500)
                {
                    int progress = int(100.*float(fileInput.pos())/
                                       float(fileInput.size()));
                    emit sendProgress(progress);
                    
                    qDebug() << progress;
                    timest.restart();
                }
                if (isCancelled)
                {
                    isCancelled = false;
                    break;
                }
                
                
            }
            
            fileInput.close();
            fileOutput.close();
        }
        else
        {
            ERROROUT FileNotOpened;
            status = FileNotOpened;
        }
    }
    else
    {
        ERROROUT FileNotExist;
        status = FileNotExist;
    }
    
    return status;
}

/////////////////////////////////////////////////////////////////////////////////////
/*!
  \brief  Метод фильтрации цифровой записи сигналов
  
  Метод предназначен для частотной селекции сигнала, содержащегося в цифровой записи
  сигнала, которая хранится в файел. Метод возвращает код ошибки типа ErrorCode_Ta.
  
  \param [in]   fileOutName    имя выходного файла
  \param [in]   blocksize      размер блока фильтрации
  \param [out]  resSampleFreq  указатель на результирующию частоту дискретизации
                               при фильтрации с децимацией
  \param [in]   isDecim        индикатор необходимости децимации
*/
/////////////////////////////////////////////////////////////////////////////////////

ErrorCode_Ta TaClass::filterSigOnFile(QString fileOutName,
                                      int blocksize,
                                      float * resSampleFreq,
                                      bool isDecim)
{
    ErrorCode_Ta status;
    
    //проверка корректности входных параметров
    int ord = getOrder2(blocksize);
    if (ord < 6 || ord > 24)
    {
        ERROROUT InvalidFFTsize;
        return InvalidFFTsize;
    }
    
    if (sampleFreq < 1)
    {
        ERROROUT InvalidSampleRate;
        return  InvalidSampleRate;
    }
    
    if (bandwith < 0 || bandwith > sampleFreq*0.98)
    {
        ERROROUT InvalidBandOrCentFreq;
        return  InvalidBandOrCentFreq;
    }
    
    status = isCorrectFreqPrms();
    if (status != NoError)
        return status;
    
    isCancelled = false;
    
    //импульсная характеристика фильтра
    vector< complex<float> > imphar32fc;
    //АЧХ фильтра
    vector<complex <float> > achFilt;
    
    *resSampleFreq = sampleFreq;
    float sampleFreqDecim = sampleFreq;
    int coefDecim = 0;
    
    
    int implen = 0;
    
    
    //формируем комплексную импульсную характеристику
    imphar32fc = genRCosFIRLowpassOnSymbsCmplx(5, bandwith,
                                               sampleFreq, 0.35, true);
    
    implen = imphar32fc.size()+1;
    
    int s = imphar32fc.size();
    //если длина имп.хар-ки больше fftsize
    if (s > blocksize)
    {
        //уменьшаем длину имп. хар-ки
        imphar32fc = genRCosFIRLowpassOnSampsCmplx(blocksize-1,
                                                   bandwith/sampleFreq,
                                                   0.35, true);
    }
    else if (s < blocksize)
    {
        //добавляем нули к имп.хар-ки
        imphar32fc.resize(blocksize);
        memset((char*)(imphar32fc.data() + s ), 0 ,sizeof(float)*2);
    }
    
    float fimp = centerFreq/sampleFreq;
    qint64 tb = 0;
    //переносим центральную частоту АЧХ фильтра на частоту сигнала
    freqTranslate_32fc(imphar32fc.data(), fimp, blocksize, &tb);
    
    achFilt.resize(blocksize);
    
    //расчитываем АЧХ фильтра
    getFilterAFR_32fc(imphar32fc.data(),achFilt.data(), blocksize);
    
    coefDecim = sampleFreq/(4*bandwith);
    
    QFile file(filename);
    QFile fileOut(fileOutName);
    
    if (file.exists())
    {
        
        if (getSamplesCnt(format,file.size()) < blocksize)
        {
            ERROROUT InvalidFFTsize << " fftsize > size of file";
            status = InvalidFFTsize;
        }
        
        if (getSamplesCnt(format, winsize) < blocksize)
        {
            ERROROUT InvalidWinSize << " fftsize > winsize";
            status = InvalidWinSize;
        }
        
        if (winsize > file.size())
        {
            ERROROUT InvalidWinSize << " winsize > size of file";
            status = InvalidWinSize;
        }
        
        if (file.open(QIODevice::ReadOnly) && fileOut.open(QIODevice::WriteOnly))
        {
            if (winsize == 0)
                winsize = file.size();
            
            //implen = fftsize/2;
            
            //вектор входных данных, читаемых их файла
            vector<complex <float> > datain(blocksize);
            
            //текущий комплексный спектр
            vector<complex <float> > currSpecFilt(blocksize);
            
            //децимированные данные
            vector<complex <float> > dataiDecim(blocksize);
            
            //план прямого БПФ для фильтрации
            fftwf_plan planFow = fftwf_plan_dft_1d(blocksize,
                                                   (fftwf_complex*) datain.data(),
                                                   (fftwf_complex*) currSpecFilt.data(),
                                                   FFTW_FORWARD, FFTW_ESTIMATE);
            //план обратного БПФ для фильтрации
            fftwf_plan planInv = fftwf_plan_dft_1d(blocksize,
                                                   (fftwf_complex*) currSpecFilt.data(),
                                                   (fftwf_complex*) datain.data(),
                                                   FFTW_BACKWARD, FFTW_ESTIMATE);
            
            //таймер нужен для отправки сигналов через определенные интервалы времени,
            //а не постоянно
            QElapsedTimer timer;
            timer.start();
            
            qint64 fpos = posInFile;
            int ostatok = 0;
            qint64 tsample = 0;
            
            //Кольцевой буфер
            CircBuffer< complex<float> > circBuff(blocksize*16,blocksize);
            
            ErrorCode_Ta statusFile = NoError;
            
            while (!file.atEnd() && (fpos < (posInFile + winsize)) && statusFile != EndOfFile)
            {
                /* Чтение данных из файла и одновременная конвертация отчетов
                 * при необходимости*/
                statusFile = readAndConvert(file, datain , &fpos, format, implen);
                
                /* Начало фильтрации сигнала */
                
                //расчитываем спектр текущего фрагмента сигнала
                fftwf_execute(planFow);
                //перемножаем спектр сигнала на АЧХ фильтра
                multVec_32fc_I(achFilt.data(),currSpecFilt.data(),blocksize);
                //расчитываем ОБПФ результата перемножения
                fftwf_execute(planInv);
                //нормируем результат ОБПФ, поделив на размер, получив
                //т.о. результат фильтрации
                divVecC_32fc_I(float(blocksize),datain.data(),blocksize);
                
                if (isDecim)
                    coefDecim = sampleFreq/(4*bandwith);
                else
                    coefDecim = 1;
                sampleFreqDecim = sampleFreq/coefDecim;
                
                /* Конец фильтрации сигнала */
                //переносим сигнал на нулевую частоту
                freqTranslate_32fc(datain.data()+implen,-centerFreq/sampleFreq,
                                   blocksize-implen, &tsample);
                
                //если надо децимировать
                if (coefDecim > 1)
                {
                    //memset(dataiDecim.data(),0,sizeof (float)*2*fftsize);
                    for (int i = implen+ostatok, c = 0; i < blocksize; i+=coefDecim,c++)
                    {
                        
                        circBuff.writeBlock(datain.data()+i,1);
                        ostatok = i;
                    }
                    ostatok = coefDecim - (blocksize - ostatok);
                }
                else //если не надо децимировать
                {
                    circBuff.writeBlock(datain.data()+implen,blocksize-implen);
                }
                
                bool isEndRead = (fpos >= (posInFile + winsize)) || (statusFile == EndOfFile);
                
                if (isEndRead && !circBuff.getReadyToLastRead())
                {
                    int cnt  = circBuff.getQueueSize();
                    vector<complex<float> > zero(blocksize-cnt+1);
                    memset(zero.data(),0,zero.size()*sizeof (float)*2);
                    circBuff.writeBlock(zero.data(),zero.size());
                }
                
                while (circBuff.getReadyToLastRead())
                {
                    circBuff.readLastBlock(dataiDecim.data());
                    
                    fileOut.write((char*)dataiDecim.data(),dataiDecim.size()*sizeof (float)*2);
                }
                
                //каждые полсекунды отправляем данные для отображения в
                //интерфейсе пользователя
                if (timer.elapsed() > 500)
                {
                    int progress = int(100.*float(fpos-posInFile)/float(winsize));
                    emit sendProgress(progress);
                    
                    qDebug() << progress;
                    timer.restart();
                }
                if (isCancelled)
                {
                    isCancelled = false;
                    break;
                }
            }
            
            fftwf_destroy_plan(planFow);
            fftwf_destroy_plan(planInv);
            file.close();
            fileOut.close();
        }
        else
        {
            ERROROUT FileNotOpened;
            status = FileNotOpened;
        }
        
        emit sendProgress(0);
    }
    else
    {
        ERROROUT FileNotExist;
        status = FileNotExist;
    }
    
    *resSampleFreq = sampleFreqDecim;
    
    return status;
}


/////////////////////////////////////////////////////////////////////////////////////
/*!
  \brief  Метод расчета абсолютных значеений и выделения реальной и мнимой частей
  массива комплесных значений, хранящихся в файле
  
  Метод расчета абсолютных значеений и выделения реальной и мнимой частей
  массива комплесных значений, хранящихся в файле. В случае, если в файле хранится
  больше отсчетов, чем заданно в параметре maxSmpls, при чтении осуществляется
  прореживание, т.е. пропуск *delta отсчетов. Метод возвращает код ошибки
  типа ErrorCode_Ta.
  
  \param [out]   timeOs64f    вектор отсчетов времени
  \param [out]   magn64f      вектор абсолютных значений осчетов сигнала
  \param [out]   real64f      вектор реальных значений осчетов сигнала
  \param [out]   imag64f      вектор мнимых значений осчетов сигнала
  \param [in]    maxSmpls     максимально допустимое число читаемых отсчетов
  \param [out]   delta        указатель на величину прореживания
*/
/////////////////////////////////////////////////////////////////////////////////////
ErrorCode_Ta TaClass::getMagnReImForm(vector<double> &timeOs64f,
                                      vector<double> &magn64f,
                                      vector<double> &real64f,
                                      vector<double> &imag64f,
                                      int maxSmpls,
                                      int * delta)
{
    ErrorCode_Ta status;
    
    //проверка корректности входных параметров
    
    
    if (sampleFreq < 1)
    {
        ERROROUT InvalidSampleRate;
        return  InvalidSampleRate;
    }
    
    if (maxSmpls < 512 || delta == 0)
    {
        ERROROUT InvalidData;
        return InvalidData;
    }
    
    isCancelled = false;
    
    timeOs64f.clear();
    magn64f.clear();
    real64f.clear();
    imag64f.clear();
    
    timeOs64f.reserve(maxSmpls*2);
    magn64f.reserve(maxSmpls*2);
    real64f.reserve(maxSmpls*2);
    imag64f.reserve(maxSmpls*2);
    
    QFile file(filename);
    if (file.exists())
    {
        
        if (winsize > file.size())
        {
            ERROROUT InvalidWinSize << " winsize > size of file";
            status = InvalidWinSize;
        }
        
        if (file.open(QIODevice::ReadOnly))
        {
            
            if (winsize == 0)
                winsize = file.size();
            
            //таймер нужен для отправки сигналов через определенные интервалы времени,
            //а не постоянно
            QElapsedTimer timer;
            timer.start();
            
            file.seek(posInFile);
            
            int smplsCntWin = getSamplesCnt(format,winsize);
            int bytesCntWin = getBytesCnt(format,smplsCntWin);
            
            if (smplsCntWin < maxSmpls)
            {
                timeOs64f.resize(smplsCntWin);
                real64f.resize(smplsCntWin);
                magn64f.resize(smplsCntWin);
                imag64f.resize(smplsCntWin);
                
                vector<int8_t> mass8;
                vector<complex <int8_t>> mass8c;
                vector<int16_t> mass16;
                vector<complex <int16_t>> mass16c;
                vector<int32_t> mass32;
                vector<complex <int32_t>> mass32c;
                vector<float> mass32f;
                vector<complex <float>> mass32fc;
                
                switch (format)
                {
                case BIT8R:
                    mass8.resize(smplsCntWin);
                    file.read((char*)mass8.data(),bytesCntWin);
                    convert_8s64f(mass8.data(),real64f.data(),smplsCntWin);
                    break;
                case BIT8C:
                    mass8c.resize(smplsCntWin);
                    file.read((char*)mass8c.data(),bytesCntWin);
                    magnitude_8c64f(mass8c.data(),magn64f.data(),smplsCntWin);
                    real_8c64f(mass8c.data(),real64f.data(),smplsCntWin);
                    imag_8c64f(mass8c.data(),imag64f.data(),smplsCntWin);
                    break;
                case BIT16R:
                    mass16.resize(smplsCntWin);
                    file.read((char*)mass16.data(),bytesCntWin);
                    convert_16s64f(mass16.data(),real64f.data(),smplsCntWin);
                    break;
                case BIT16C:
                    mass16c.resize(smplsCntWin);
                    file.read((char*)mass16c.data(),bytesCntWin);
                    magnitude_16c64f(mass16c.data(),magn64f.data(),smplsCntWin);
                    real_16c64f(mass16c.data(),real64f.data(),smplsCntWin);
                    imag_16c64f(mass16c.data(),imag64f.data(),smplsCntWin);
                    break;
                case BIT32R:
                    mass32.resize(smplsCntWin);
                    file.read((char*)mass32.data(),bytesCntWin);
                    convert_32s64f(mass32.data(),real64f.data(),smplsCntWin);
                    break;
                case BIT32C:
                    mass32c.resize(smplsCntWin);
                    file.read((char*)mass32c.data(),bytesCntWin);
                    magnitude_32c64f(mass32c.data(),magn64f.data(),smplsCntWin);
                    real_32c64f(mass32c.data(),real64f.data(),smplsCntWin);
                    imag_32c64f(mass32c.data(),imag64f.data(),smplsCntWin);
                    break;
                case BIT32RF:
                    mass32f.resize(smplsCntWin);
                    file.read((char*)mass32f.data(),bytesCntWin);
                    convert_32f64f(mass32f.data(),real64f.data(),smplsCntWin);
                    break;
                case BIT32CF:
                    mass32fc.resize(smplsCntWin);
                    file.read((char*)mass32fc.data(),bytesCntWin);
                    magnitude_32fc64f(mass32fc.data(),magn64f.data(),smplsCntWin);
                    real_32fc64f(mass32fc.data(),real64f.data(),smplsCntWin);
                    imag_32fc64f(mass32fc.data(),imag64f.data(),smplsCntWin);
                }
                
                qint64 beg = getSamplesCnt(format,posInFile);
                for (int i = 0; i < smplsCntWin; i++)
                {
                    timeOs64f[i] = double(i+beg)/sampleFreq;
                }
            }
            else
            {
                qint64 startSample = getSamplesCnt(format,posInFile);
                qint64 deltaSample = trunc(float(smplsCntWin)/float(maxSmpls));
                deltaSample = (deltaSample<1) ? 1 : deltaSample;
                *delta = deltaSample;
                
                int    smplSize = getBytesCnt(format,1);
                qint64 endSeek  = posInFile+winsize;
                
                int8_t            sample8;
                complex <int8_t>  sample8c;
                int16_t           sample16;
                complex <int16_t> sample16c;
                int32_t           sample32;
                complex <int32_t> sample32c;
                float             sample32f;
                complex <float>   sample32fc;
                
                double real = 0,imag = 0, magn = 0;
                for (qint64 i = startSample; i*smplSize < endSeek - smplSize; i+=deltaSample)
                {
                    file.seek(i*smplSize);
                    switch (format)
                    {
                    case BIT8R:
                        file.read((char*) (&sample8),sizeof(sample8));
                        real = double(sample8);
                        break;
                    case BIT8C:
                        file.read((char*) (&sample8c),sizeof(sample8c));
                        real = double(sample8c.real());
                        imag = double(sample8c.imag());
                        magn = double(abs(sample8c));
                        break;
                    case BIT16R:
                        file.read((char*) (&sample16),sizeof(sample16));
                        real = double(sample16);
                        break;
                    case BIT16C:
                        file.read((char*) (&sample16c),sizeof(sample16c));
                        real = double(sample16c.real());
                        imag = double(sample16c.imag());
                        magn = double(abs(sample16c));
                        break;
                    case BIT32R:
                        file.read((char*) (&sample32),sizeof(sample32));
                        real = double(sample32);
                        break;
                    case BIT32C:
                        file.read((char*) (&sample32c),sizeof(sample32c));
                        real = double(sample32c.real());
                        imag = double(sample32c.imag());
                        magn = double(abs(sample32c));
                        break;
                    case BIT32RF:
                        file.read((char*) (&sample32f),sizeof(sample32f));
                        real = double(sample32f);
                        break;
                    case BIT32CF:
                        file.read((char*) (&sample32fc),sizeof(sample32fc));
                        real = double(sample32fc.real());
                        imag = double(sample32fc.imag());
                        magn = double(abs(sample32fc));
                    }
                    
                    real64f.push_back(real);
                    imag64f.push_back(imag);
                    magn64f.push_back(magn);
                    timeOs64f.push_back(double(i)/sampleFreq*1000);
                    
                    //каждые полсекунды отправляем данные для отображения в интерфейсе
                    //пользователя
                    if (timer.elapsed() > 100)
                    {
                        int progress = int(100.*float(i*smplSize-posInFile)/float(winsize));
                        emit sendProgress(progress);
                        qDebug() << progress;
                        timer.restart();
                    }
                    
                    if (isCancelled)
                    {
                        isCancelled = false;
                        break;
                    }
                }
            }
            file.close();
        }
        else
        {
            ERROROUT FileNotOpened;
            status = FileNotOpened;
        }
    }
    else
    {
        ERROROUT FileNotExist;
        status = FileNotExist;
    }
    
    return status;
}




ErrorCode_Ta TaClass::sigDetection(QVector<double> &amft,
                                   QVector<double> &amftBin,
                                   QVector<double> &meanSpec,
                                   int fftsize,
                                   int med1WinPor,
                                   int med1WinSpec,
                                   int med2Win,
                                   int porMin,
                                   int porMax,
                                   QVector<SignDetStruct> &massSigs)
{
    if (float(amft.size())/float(fftsize) > 1 && amft.size()%fftsize == 0)
    {
        
        QVector<SignDetStruct> massSigsTemp;
        
        if (amftBin.size() != amft.size())
            amftBin.resize(amft.size());
        
        int count = amft.size()/fftsize;
        vector<double> porogMin(fftsize);
        vector<double> porogMax(fftsize);
        
        
        memcpy(porogMin.data(),meanSpec.data(),fftsize*sizeof (double));
        
        Mediator<double> mediator(fftsize);
        for (int k = 0;  k < fftsize; k++)
        {
            mediator.insert(porogMin[k]);
        }
        
        medFilter1d(porogMin.data(),porogMin.size(),med1WinPor);
        
        for (int k = 0;  k < fftsize; k++)
        {
            porogMax[k] = porogMin[k] + porMax;
            porogMin[k] = porogMin[k] + porMin;
        }
        
        emit sendGraficsSpec1os(porogMin.data(),  fftsize, 3);
        emit sendGraficsSpec1os(porogMax.data(),  fftsize, 4);
        
        for (int i = 0; i < count; i++)
        {
            
            
            
            
            medFilter1d(amft.data() + i*fftsize, fftsize, med1WinSpec);
            
            emit sendGraficsSpec1os(amft.data() + i*fftsize, fftsize, 2);
            
            
            bool indObn = false;
            for (int j = i * fftsize; j < i * fftsize + fftsize; j++)
            {
                int curind = j - i * fftsize;
                
                if (curind > med1WinPor/3*2  && curind < fftsize - med1WinPor/3*2)
                {
                    if (amft[j] > (porogMax[curind]) && indObn == false)
                    {
                        amftBin[j] = 1;
                        indObn = true;
                    }
                    
                    if (amft[j] < (porogMax[curind]) && indObn == false)
                    {
                        amftBin[j] = 0;
                        indObn = false;
                    }
                    
                    if (indObn == true && amft[j] >= (porogMin[curind]))
                    {
                        amftBin[j] = 1;
                        indObn = true;
                    }
                    
                    if (indObn == true && amft[j] < (porogMin[curind]))
                    {
                        amftBin[j] = 0;
                        indObn = false;
                    }
                    
                }
                else
                {
                    amftBin[j] = 0;
                }
                //
            }
            emit sendProgress(int(float(i)/float(count)*100.));
        }
        
        emit sendProgress(0);
        for (int i = 0; i < amftBin.size() - med2Win; i++)
        {
            int sum = 0;
            for (int j = 0 ; j < med2Win; j++)
                sum+=amftBin[i+j];
            if (sum>med2Win/2)
                amftBin[i] = 1;
            else
                amftBin[i] = 0;
            emit sendProgress(int(float(i)/float(amftBin.size() - med2Win)*100.));
            
        }
        
        emit sendProgress(0);
        massSigs.clear();
        
        
        for (int i = 0; i < count; i++)
        {
            for (int j = i * fftsize + 1; j < i * fftsize + fftsize - 3; j++)
            {
                if (amftBin[j-1]==0 && amftBin[j]==1 && amftBin[j+1]==1 && amftBin[j+2]==1)
                {
                    SignDetStruct sig;
                    sig.begt = i*fftsize;
                    sig.endt = i*fftsize+fftsize;
                    sig.lfreq = j%fftsize+med1WinSpec/2;
                    massSigsTemp.push_back(sig);
                    continue;
                    
                }
                
                if (amftBin[j-1]==1 && amftBin[j]==1 && amftBin[j+1]==0 && amftBin[j+2]==0 && amftBin[j+3]==0)
                {
                    if (massSigsTemp.size()>0)
                    {
                        massSigsTemp[massSigsTemp.size()-1].rfreq = j%fftsize+med1WinSpec/2;
                        massSigsTemp[massSigsTemp.size()-1].active = true;
                    }
                }
            }
            emit sendProgress(int(float(i)/float(count)*100.));
        }
        
        emit sendProgress(0);
        
        for ( int i = 0 ; i < massSigsTemp.size(); i++)
        {
            for ( int j = 0 ; j < massSigsTemp.size(); j++)
            {
                if (i!=j && massSigsTemp[i].endt >= massSigsTemp[j].begt   &&
                        massSigsTemp[i].begt <= massSigsTemp[j].begt   &&
                        massSigsTemp[i].endt <= massSigsTemp[j].endt   &&
                        massSigsTemp[j].active == true &&
                        massSigsTemp[i].active == true)
                {
                    int delta1 = massSigsTemp[j].rfreq - massSigsTemp[j].lfreq;
                    int delta2 = massSigsTemp[i].rfreq - massSigsTemp[i].lfreq;
                    
                    if (abs(delta1 - delta2) <= fftsize/30)
                    {
                        if (abs(massSigsTemp[j].lfreq - massSigsTemp[i].lfreq) <= fftsize/60 &&
                                abs(massSigsTemp[j].rfreq - massSigsTemp[i].rfreq) <= fftsize/60 )
                        {
                            massSigsTemp[j].begt = massSigsTemp[i].begt;
                            massSigsTemp[i].active = false;
                        }
                    }
                    
                    
                }
            }
            emit sendProgress(int(float(i)/float(massSigsTemp.size())*100.));
        }
        
        emit sendProgress(0);
        for ( int i = 0 ; i < massSigsTemp.size(); i++)
        {
            for ( int j = 0 ; j < massSigsTemp.size(); j++)
            {
                if (i!=j && abs(massSigsTemp[i].endt - massSigsTemp[j].begt) <=fftsize   &&
                        massSigsTemp[i].begt <= massSigsTemp[j].begt   &&
                        massSigsTemp[i].endt <= massSigsTemp[j].endt   &&
                        massSigsTemp[j].active == true &&
                        massSigsTemp[i].active == true)
                {
                    int delta1 = massSigsTemp[j].rfreq - massSigsTemp[j].lfreq;
                    int delta2 = massSigsTemp[i].rfreq - massSigsTemp[i].lfreq;
                    
                    if (abs(delta1 - delta2) <= fftsize/30)
                    {
                        if (abs(massSigsTemp[j].lfreq - massSigsTemp[i].lfreq) <= fftsize/60 &&
                                abs(massSigsTemp[j].rfreq - massSigsTemp[i].rfreq) <= fftsize/60 )
                        {
                            massSigsTemp[j].begt = massSigsTemp[i].begt;
                            massSigsTemp[i].active = false;
                        }
                    }
                }
            }
            emit sendProgress(int(float(i)/float(massSigsTemp.size())*100.));
        }
        
        emit sendProgress(0);
        for ( int i = 0 ; i < massSigsTemp.size(); i++)
        {
            for ( int j = 0 ; j < massSigsTemp.size(); j++)
            {
                if (i!=j   &&
                        massSigsTemp[j].active == true &&
                        massSigsTemp[i].active == true)
                {
                    
                    if (massSigsTemp[i].lfreq < massSigsTemp[j].lfreq  &&
                            massSigsTemp[i].rfreq > massSigsTemp[j].rfreq  &&
                            massSigsTemp[i].begt < massSigsTemp[j].begt    &&
                            massSigsTemp[i].endt > massSigsTemp[j].endt )
                    {
                        massSigsTemp[j].active = false;
                    }
                }
                
                
            }
            emit sendProgress(int(float(i)/float(massSigsTemp.size())*100.));
        }
        
        emit sendProgress(0);
        if (massSigsTemp.size()>0)
        {
            for ( int i = massSigsTemp.size()-1 ; i >= 0; i--)
            {
                if (massSigsTemp[i].active &&
                        massSigsTemp[i].endt!=0 &&
                        (massSigsTemp[i].endt -  massSigsTemp[i].begt) > 16*fftsize &&
                        (massSigsTemp[i].rfreq -  massSigsTemp[i].lfreq) > 128)
                {
                    if (massSigs.size() > 0)
                    {
                        
                        int sch = 0;
                        while (sch                  < massSigs.size()    &&
                               massSigsTemp[i].begt < massSigs[sch++].begt)
                        {};
                        
                        massSigs.insert(sch,massSigsTemp[i]);
                    }
                    else
                        massSigs.push_back(massSigsTemp[i]);
                }
                emit sendProgress(int(float(i)/float(massSigsTemp.size())*100.));
            }
        }
        emit sendDetectedSigs(massSigs);
        
        emit sendProgress(0);
    }
    return NoError;
}
ErrorCode_Ta TaClass::getMeanSpec(vector<complex<float> > &datain,
                                  vector<float> &meanSpec,
                                  QVector<double> &amft,
                                  vector<float> &osf,
                                  float SampleFreq,
                                  int fftsize,
                                  int bpfCnt,
                                  int overLap)
{
    ErrorCode_Ta status;
    
    //проверка корректности входных параметров
    int ord = getOrder2(fftsize);
    if (ord < 6 || ord > 24 || fftsize%2!=0)
    {
        ERROROUT InvalidFFTsize;
        return InvalidFFTsize;
    }
    
    if (overLap < 0 || overLap > fftsize-1)
    {
        ERROROUT InvalidOverlap;
        return InvalidOverlap;
    }
    
    
    meanSpec.clear();
    amft.clear();
    osf.clear();
    
    meanSpec.resize(fftsize);
    osf.resize(fftsize);
    memset(meanSpec.data(),0,sizeof(float)*fftsize);
    amft.reserve(bpfCnt*fftsize+10*fftsize);
    
    //текущий комплексный спектр
    vector<complex <float> > currSpec(fftsize);
    //амплитудный спектр
    vector<float>            currAmplSpec(fftsize);
    memset(currSpec.data(),0,sizeof(float)*2);
    
    //план прямого БПФ
    fftwf_plan planFow = fftwf_plan_dft_1d(fftsize,
                                           (fftwf_complex*) datain.data(),
                                           (fftwf_complex*) currSpec.data(),
                                           FFTW_FORWARD, FFTW_ESTIMATE);   
    qint64 sch = 0;

    fftwf_execute(planFow);

    magnitude_32fc(currSpec.data(),currAmplSpec.data(),fftsize);

    for (int i = 0; i < fftsize;i++)
    {
        if (currAmplSpec[i] == 0)
            currAmplSpec[i] =  1;
        if (std::isinf(currAmplSpec[i]))
            currAmplSpec[i] = std::numeric_limits<float>::max();
        if (std::isnan(currAmplSpec[i]))
            currAmplSpec[i] = std::numeric_limits<float>::min();
    }

    multVecC_32f_I(1./SampleFreq,currAmplSpec.data(),fftsize);

    fftShift_32f(currAmplSpec.data(),currAmplSpec.size());
    log10Vec(currAmplSpec.data(),currAmplSpec.data(),fftsize, 20.);

    addVec_32f_I(currAmplSpec.data(), meanSpec.data(), fftsize);
    
//    if (trNum&1)
//        divVecC_32f_I(sch,meanSpec.data(),meanSpec.size());
    
    fftwf_destroy_plan(planFow);
    
    osf.resize(fftsize);
    for (int i = 0; i < fftsize; i++)
        osf[i] = i*SampleFreq/fftsize - SampleFreq/2;
    
    return status;
}


ErrorCode_Ta TaClass::getMeanMaxMinSpec(vector<float>   &meanSpec,
                                        vector<float>   &minSpec,
                                        vector<float>   &maxSpec,
                                        QVector<double> &amft,
                                        vector<float>   &osf,
                                        int fftsize,
                                        int trNum,
                                        int overLap)
{
    
    ErrorCode_Ta status;
    
    //проверка корректности входных параметров
    int ord = getOrder2(fftsize);
    if (ord < 6 || ord > 24 || fftsize%2!=0)
    {
        ERROROUT InvalidFFTsize;
        return InvalidFFTsize;
    }
    
    if (sampleFreq < 1)
    {
        ERROROUT InvalidSampleRate;
        return  InvalidSampleRate;
    }
    
    if (overLap < 0 || overLap > fftsize-1)
    {
        ERROROUT InvalidOverlap;
        return InvalidOverlap;
    }
    
    
    if (trNum < 1 &&  trNum > 15)
    {
        ERROROUT InvalidTransformNum;
        return InvalidTransformNum;
    }
    
    
    isCancelled = false;
    
    meanSpec.clear();
    minSpec.clear();
    maxSpec.clear();
    amft.clear();
    osf.clear();
    
    
    int bpfCnt = getSamplesCnt(format,winsize)/fftsize;
    int deltaBpf = 1;
    
    int tempcnt = bpfCnt;
    while (bpfCnt>=1024)
    {
        deltaBpf++;
        bpfCnt = tempcnt/deltaBpf;
    }
    
    if (format == BIT8R  ||
            format == BIT16R ||
            format == BIT32R ||
            format == BIT32RF )
    {
        meanSpec.resize(fftsize/2);
        minSpec.resize(fftsize/2);
        maxSpec.resize(fftsize/2);
        osf.resize(fftsize/2);
        memset(meanSpec.data(),0,sizeof(float)*fftsize/2);
        amft.reserve(bpfCnt*fftsize/2+10*fftsize/2);
    }
    else
    {
        meanSpec.resize(fftsize);
        minSpec.resize(fftsize);
        maxSpec.resize(fftsize);
        osf.resize(fftsize);
        memset(meanSpec.data(),0,sizeof(float)*fftsize);
        amft.reserve(bpfCnt*fftsize+10*fftsize);
    }
    
    for (unsigned int i = 0; i < minSpec.size(); i++)
    {
        minSpec[i] =  std::numeric_limits<float>::max();
        maxSpec[i] = -std::numeric_limits<float>::max();
    }
    
    
    
    QFile file(filename);
    if (file.exists())
    {
        if (getSamplesCnt(format,file.size()) < fftsize)
        {
            ERROROUT InvalidFFTsize << " fftsize > size of file";
            status = InvalidFFTsize;
        }
        
        if (getSamplesCnt(format, winsize) < fftsize)
        {
            ERROROUT InvalidWinSize << " fftsize > winsize";
            status = InvalidWinSize;
        }
        
        if (winsize > file.size())
        {
            ERROROUT InvalidWinSize << " winsize > size of file";
            status = InvalidWinSize;
        }
        
        if (file.open(QIODevice::ReadOnly))
        {
            
            if (winsize == 0)
                winsize = file.size();
            
            //вектор входных данных, читаемых их файла
            vector<complex <float> > datain(fftsize);
            
            
            //текущий комплексный спектр
            vector<complex <float> > currSpec(fftsize);
            //амплитудный спектр
            vector<float>            currAmplSpec(fftsize);
            memset(currSpec.data(),0,sizeof(float)*2);
            
            //план прямого БПФ
            fftwf_plan planFow = fftwf_plan_dft_1d(fftsize,
                                                   (fftwf_complex*) datain.data(),
                                                   (fftwf_complex*) currSpec.data(),
                                                   FFTW_FORWARD, FFTW_ESTIMATE);
            
            //таймер нужен для отправки сигналов через определенные интервалы времени,
            //а не постоянно
            QElapsedTimer timer;
            timer.start();
            qint64 fpos = posInFile;
            
            qint64 sch = 0;
            
            ErrorCode_Ta ststusFile = NoError;
            
            while (!file.atEnd() && (fpos < (posInFile + winsize)) && ststusFile !=EndOfFile)
            {
                
                //текущее время относительно начала записи
                //float time = float(getSamplesCnt(format,fpos))/sampleFreq;
                
                /* Чтение данных из файла и одновременная конвертация отчетов
                 * при необходимости*/
                ststusFile = readAndConvert(file, datain, &fpos, format, overLap);
                
                normalizeToValue_32f((float*)datain.data(),1,fftsize*2);
                
                fftwf_execute(planFow);
                
                magnitude_32fc(currSpec.data(),currAmplSpec.data(),fftsize);
                
                
                for (int i = 0; i < fftsize;i++)
                {
                    if (currAmplSpec[i] == 0)
                        currAmplSpec[i] =  1;
                    if (std::isinf(currAmplSpec[i]))
                        currAmplSpec[i] = std::numeric_limits<float>::max();
                    if (std::isnan(currAmplSpec[i]))
                        currAmplSpec[i] = std::numeric_limits<float>::min();
                }
                
                multVecC_32f_I(1./sampleFreq,currAmplSpec.data(),fftsize);
                
                if (format == BIT8R  ||
                        format == BIT16R ||
                        format == BIT32R ||
                        format == BIT32RF)
                {
                    log10Vec(currAmplSpec.data(),currAmplSpec.data(),fftsize/2., 20.);
                    
                    if (trNum&1)
                    {
                        addVec_32f_I(currAmplSpec.data(), meanSpec.data(), fftsize/2.);
                    }
                    
                    if (trNum&2)
                    {
                        everyMax_32f(currAmplSpec.data(),maxSpec.data(),fftsize/2.);
                    }
                    
                    if (trNum&4)
                    {
                        everyMin_32f(currAmplSpec.data(),minSpec.data(),fftsize/2.);
                    }
                    
                    if (trNum&8 && sch%deltaBpf == 0)
                    {
                        amft.resize(amft.size()+fftsize/2);
                        convert_32f64f(currAmplSpec.data(),amft.data() + amft.size() - fftsize/2 ,fftsize/2);
                    }
                }
                
                if (format == BIT8C  ||
                        format == BIT16C ||
                        format == BIT32C ||
                        format == BIT32CF)
                {
                    fftShift_32f(currAmplSpec.data(),currAmplSpec.size());
                    log10Vec(currAmplSpec.data(),currAmplSpec.data(),fftsize, 20.);
                    
                    if (trNum&1)
                    {
                        addVec_32f_I(currAmplSpec.data(), meanSpec.data(), fftsize);
                    }
                    
                    if (trNum&2)
                    {
                        everyMax_32f(currAmplSpec.data(),maxSpec.data(),fftsize);
                    }
                    
                    if (trNum&4)
                    {
                        everyMin_32f(currAmplSpec.data(),minSpec.data(),fftsize);
                    }
                    
                    if (trNum&8 && sch%deltaBpf == 0)
                    {
                        amft.resize(amft.size()+fftsize);
                        convert_32f64f(currAmplSpec.data(),amft.data() + amft.size() - fftsize,fftsize);
                        
                    }
                }
                
                
                //каждые полсекунды отправляем данные для отображения в интерфейсе
                //пользователя
                if (timer.elapsed() > 100)
                {
                    int progress = int(100.*float(fpos-posInFile)/float(winsize));
                    emit sendProgress(progress);
                    qDebug() << progress;
                    timer.restart();
                }
                
                
                if (isCancelled)
                {
                    isCancelled = false;
                    break;
                }
                
                sch++;
            }
            
            if (trNum&1)
            {
                divVecC_32f_I(sch,meanSpec.data(),meanSpec.size());
            }
            
            fftwf_destroy_plan(planFow);
            
            if (format == BIT8R  ||
                    format == BIT16R ||
                    format == BIT32R ||
                    format == BIT32RF)
            {
                osf.resize(fftsize/2);
                
                for (int i = 0; i < fftsize/2; i++)
                {
                    osf[i] = i*sampleFreq/fftsize;
                }
            }
            else
            {
                osf.resize(fftsize);
                
                for (int i = 0; i < fftsize; i++)
                {
                    osf[i] = i*sampleFreq/fftsize - sampleFreq/2;
                }
            }
            
            file.close();
        }
        else
        {
            ERROROUT FileNotOpened;
            status = FileNotOpened;
        }
        emit sendProgress(0);
    }
    else
    {
        ERROROUT FileNotExist;
        status = FileNotExist;
    }
    
    
    return status;
    
}

/////////////////////////////////////////////////////////////////////////////////////
/*!
  \brief  Метод вычисления номинала частоты по максимуму амплитудного спектра
  
  Метод предназначен для овычисления номинала частоты по максимуму амплитудного
  спектра 1-й, 2-й, 4-й и 8-й степеней входного сигнала. Метод возращает код ошибки
  ErrorCode_Ta.
  
  \param [in]   plan      структура БПФ, созданная заранее
  \param [in]   data      указатель на массив входных комплексных отсчетов сигнала,
                          привязанный к структуре БПФ plan
  \param [in]   spec      указатель на массив спектральынйх комплексных отсчетов
                          сигнала,  привязанный к структуре БПФ plan
  \param [out]  amplSpec  указатель на массив амплитудного спектра
  \param [out]  fc        указатель на область памяти в которую должно быть сохранено
                          значение частоты типа float по результатам работы метда
  \param [in]   fftsize   размер массивов, кратный двум
  \param [in]   trNum     значение степени, в которую необходимо возвести входной
                          массив data для вычисления частоты
*/
/////////////////////////////////////////////////////////////////////////////////////
ErrorCode_Ta TaClass::getCentFreqValue(fftwf_plan &plan,
                                       complex<float> * data,
                                       complex<float> * spec,
                                       float * amplSpec,
                                       float * fc,
                                       int fftsize,
                                       int trNum)
{
    if (data == 0 || data == 0 || amplSpec == 0 || fc == 0)
    {
        ERROROUT InvalidData;
        return   InvalidData;
    }
    if (fftsize < 1)
    {
        ERROROUT InvalidSize;
        return   InvalidSize;
    }
    int ord = getOrder2(fftsize);
    if (ord < 6 || ord > 24 || fftsize % 2 != 0)
    {
        ERROROUT InvalidFFTsize;
        return   InvalidFFTsize;
    }
    if (trNum !=1 && trNum != 2  && trNum != 4 && trNum != 8)
    {
        ERROROUT InvalidTransformNum;
        return   InvalidTransformNum;
    }
    
    
    //возводим результат фильтрации в нужную степень trNum,
    //заданную в параметрах функции
    powVec_32fc_I(data,trNum,fftsize);
    constRemove_32f((float*)data,fftsize*2);
    
    //выполняем БПФ результата возведения в степень
    fftwf_execute(plan);
    //вычисляем амплитудный спектр
    magnitude_32fc(spec,amplSpec,fftsize);
    
    int index;
    float max;
    
    //определяем положение максимума
    maxIndex_32f(amplSpec,fftsize,&max,&index);
    vector<float> y(3);
    float dopval = 0;
    if (index > 0)
    {
        y[0] = amplSpec[index-1];
        y[1] = amplSpec[index+0];
        y[2] = amplSpec[index+1];
        dopval = interpMax(y);
    }
    
    if (trNum == 4)
        emit sendGraficsSpec1os(amplSpec, fftsize,2);
    
    if (trNum == 1)
    {
        
        if (format == BIT8C  ||
                format == BIT16C ||
                format == BIT32C ||
                format == BIT32CF)
        {
            *fc = (index+dopval)*sampleFreq/fftsize;
            if (*fc > sampleFreq/2.)
            {
                *fc -= sampleFreq;
            }
        }
        else
        {
            *fc = (index+dopval)*sampleFreq/fftsize;
        }
    }
    else
    {
        
        if (format == BIT8C  ||
                format == BIT16C ||
                format == BIT32C ||
                format == BIT32CF)
        {
            float cfreq = fmod(centerFreq+sampleFreq,sampleFreq);
            int   por   = cfreq  * float(trNum) / sampleFreq;
            *fc  = float(index+dopval)*sampleFreq/fftsize + por * sampleFreq;
            *fc /= float(trNum);
            
            if (*fc > sampleFreq/2.)
            {
                *fc -= sampleFreq;
            }
        }
        else
        {
            int  por = (centerFreq ) * float(trNum) / sampleFreq;
            *fc  = float(index+dopval) * sampleFreq /float(fftsize) ;
            *fc += por * sampleFreq;
            *fc /= float(trNum);
        }
    }
    return NoError;
}

/////////////////////////////////////////////////////////////////////////////////////
/*!
  \brief  Метод поблочного оценивания несущей частоты ФМн-сиганлов
  
  Метод предназначена определения несущей частоты ФМн-сигналов на основе
  эффекта свертки спектра с фильтрацией. Функция возращает код ошибки ErrorCode_Ta.
  
  \param [out]  values1    значения частоты по максимуму спектра сигнала
  \param [out]  values2    значения частоты по максимуму спектра квадрата сигнала
  \param [out]  values4    значения частоты по максимуму спектра четвертой степени
                           сигнала
  \param [out]  values8    значения частоты по максимуму спектра восьмой степени
                           сигнала
  \param [out]  meanSpec0  усредненый амплитудный спектр сигнала
  \param [out]  meanSpec2  усредненый амплитудный спектр квадрата сигнала
  \param [out]  meanSpec4  усредненый амплитудный спектр четвертой степени сигнала
  \param [out]  meanSpec8  усредненый амплитудный спектр воьмой степени сигнала
  \param [out]  osf        вектор отсчетов оси частот
  \param [out]  ost        вектор временных отсчетов, соответствующих значениям частот
  \param [in]   fftsize    размер блока вычисления частоты (степень двоики)
  \param [in]   trNum      флаг, каждый из младших четырех разрядов которого
                           определяет необходимость вычисления спектра каждой
                           из 4-х степеней. Например, при trNum = 15, вычисляются все
                           спектры, при trNum = 8 - только спектр восьмой степени
                           сигнала
  \param [in]   overLap    размер перекрытия блоков вычисления (от 0 до fftsize-1)
  \param [in]   step       кратность шага движения по файлу в отсчетах, кратность 1
                           соответствует шагу в fftsize отсчетов, 2 - 2*fftsize и т.д.
                           при overLap > 0, step = 1, при step > 1, overLap  = 0
*/
/////////////////////////////////////////////////////////////////////////////////////
ErrorCode_Ta TaClass::getCentFreqForPSK(vector<float> &values1,
                                        vector<float> &values2,
                                        vector<float> &values4,
                                        vector<float> &values8,
                                        vector<float> &ost,
                                        vector<float> &meanSpec1,
                                        vector<float> &meanSpec2,
                                        vector<float> &meanSpec4,
                                        vector<float> &meanSpec8,
                                        vector<float> &osf,
                                        int fftsize,
                                        int trNum,
                                        int overLap,
                                        int step)
{
    ErrorCode_Ta status;
    
    //проверка корректности входных параметров
    int ord = getOrder2(fftsize);
    if (ord < 6 || ord > 24 || fftsize%2!=0)
    {
        ERROROUT InvalidFFTsize;
        return InvalidFFTsize;
    }
    
    if (sampleFreq < 1)
    {
        ERROROUT InvalidSampleRate;
        return  InvalidSampleRate;
    }
    
    if (overLap < 0 || overLap > fftsize-1)
    {
        ERROROUT InvalidOverlap;
        return InvalidOverlap;
    }
    
    if (step < 1 || step > 100)
    {
        ERROROUT InvalidStep;
        return InvalidStep;
    }
    
    if (step > 1 || overLap > 0)
    {
        ERROROUT InvalidOverlap;
        return InvalidOverlap;
    }
    
    if (trNum < 1 &&  trNum > 15)
    {
        ERROROUT InvalidTransformNum;
        return InvalidTransformNum;
    }
    
    if (step > 1)
        overLap = -step*fftsize;
    
    isCancelled = false;
    
    //импульсная характеристика фильтра
    vector< complex<float> > imphar32fc;
    //АЧХ фильтра
    vector<complex <float> > achFilt;
    
    /* для АПЧ фильтра
    //запоминаем частоту сигнала
    float fsig_old = centerFreq;
    float fsig_old_old = centerFreq;
    */
    
    
    values1.clear();
    values2.clear();
    values4.clear();
    values8.clear();
    ost.clear();
    
    meanSpec1.resize(fftsize);
    meanSpec2.resize(fftsize);
    meanSpec4.resize(fftsize);
    meanSpec8.resize(fftsize);
    memset(meanSpec1.data(),0,sizeof(float)*fftsize);
    memset(meanSpec2.data(),0,sizeof(float)*fftsize);
    memset(meanSpec4.data(),0,sizeof(float)*fftsize);
    memset(meanSpec8.data(),0,sizeof(float)*fftsize);
    
    //проверка необходимости фильтрации ///////////////////////////Вдругих функциях тоже
    if (bandwith > 0)
    {
        status = isCorrectFreqPrms();
        if (status != NoError)
            return status;
        
        //формируем комплексную импульсную характеристику
        imphar32fc = genRCosFIRLowpassOnSymbsCmplx(5, bandwith, sampleFreq,
                                                   0.35, true);
        
        
        int s = imphar32fc.size();
        //если длина имп.хар-ки больше fftsize
        if (s > fftsize)
        {
            //уменьшаем длину имп. хар-ки
            imphar32fc = genRCosFIRLowpassOnSampsCmplx(fftsize-1,
                                                       bandwith/sampleFreq,
                                                       0.35, true);
        }
        else if (s < fftsize)
        {
            //добавляем нули к имп.хар-ки
            imphar32fc.resize(fftsize);
            memset((char*)(imphar32fc.data() + s ), 0 ,sizeof(float)*2);
        }
        
        float fimp = centerFreq/sampleFreq;
        qint64 tb = 0;
        //переносим центральную частоту АЧХ фильтра на частоту сигнала
        freqTranslate_32fc(imphar32fc.data(), fimp, fftsize, &tb);
        
        achFilt.resize(fftsize);
        
        //расчитываем АЧХ фильтра
        getFilterAFR_32fc(imphar32fc.data(),achFilt.data(), fftsize);
    }
    
    QFile file(filename);
    if (file.exists())
    {
        if (getSamplesCnt(format,file.size()) < fftsize)
        {
            ERROROUT InvalidFFTsize << " fftsize > size of file";
            status = InvalidFFTsize;
        }
        
        if (getSamplesCnt(format, winsize) < fftsize)
        {
            ERROROUT InvalidWinSize << " fftsize > winsize";
            status = InvalidWinSize;
        }
        
        if (winsize > file.size())
        {
            ERROROUT InvalidWinSize << " winsize > size of file";
            status = InvalidWinSize;
        }
        
        if (file.open(QIODevice::ReadOnly))
        {
            if (winsize == 0)
                winsize = file.size();
            
            //вектор входных данных, читаемых их файла
            vector<complex <float> > datain1(fftsize);
            
            //вектор входных данных, читаемых их файла
            vector<complex <float> > datain2(fftsize);
            
            //вектор входных данных, читаемых их файла
            vector<complex <float> > datain4(fftsize);
            
            //вектор входных данных, читаемых их файла
            vector<complex <float> > datain8(fftsize);
            
            //текущий комплексный спектр
            vector<complex <float> > currSpec(fftsize);
            //амплитудный спектр
            vector<float>            currAmplSpec(fftsize);
            memset(currSpec.data(),0,sizeof(float)*2);
            
            //план прямого БПФ
            fftwf_plan planFow1 = fftwf_plan_dft_1d(fftsize,
                                                    (fftwf_complex*) datain1.data(),
                                                    (fftwf_complex*) currSpec.data(),
                                                    FFTW_FORWARD, FFTW_ESTIMATE);
            
            //план прямого БПФ
            fftwf_plan planFow2 = fftwf_plan_dft_1d(fftsize,
                                                    (fftwf_complex*) datain2.data(),
                                                    (fftwf_complex*) currSpec.data(),
                                                    FFTW_FORWARD, FFTW_ESTIMATE);
            
            //план прямого БПФ
            fftwf_plan planFow4 = fftwf_plan_dft_1d(fftsize,
                                                    (fftwf_complex*) datain4.data(),
                                                    (fftwf_complex*) currSpec.data(),
                                                    FFTW_FORWARD, FFTW_ESTIMATE);
            
            //план прямого БПФ
            fftwf_plan planFow8 = fftwf_plan_dft_1d(fftsize,
                                                    (fftwf_complex*) datain8.data(),
                                                    (fftwf_complex*) currSpec.data(),
                                                    FFTW_FORWARD, FFTW_ESTIMATE);
            
            //план обратного БПФ для фильтрации
            fftwf_plan planInv = fftwf_plan_dft_1d(fftsize,
                                                   (fftwf_complex*) currSpec.data(),
                                                   (fftwf_complex*) datain1.data(),
                                                   FFTW_BACKWARD, FFTW_ESTIMATE);
            
            //таймер нужен для отправки сигналов через определенные интервалы времени,
            //а не постоянно
            QElapsedTimer timer;
            timer.start();
            qint64 fpos = posInFile;
            
            /* для АПЧ фильтра
            qint64 ts = 0;
            float fc;
            */
            
            float  fc1, fc2, fc4, fc8;
            
            ErrorCode_Ta ststusFile = NoError;
            
            while (!file.atEnd() && (fpos < (posInFile + winsize)) && ststusFile !=EndOfFile)
            {
                //текущее время относительно начала записи
                float time = float(getSamplesCnt(format,fpos))/sampleFreq;
                
                /* Чтение данных из файла и одновременная конвертация отчетов
                 * при необходимости*/
                ststusFile = readAndConvert(file, datain1, &fpos, format, overLap);
                
                //если нужно фильтровать
                if (!imphar32fc.empty())
                {
                    
                    /* Начало фильтрации сигнала */
                    
                    //расчитываем спектр текущего фрагмента сигнала
                    fftwf_execute(planFow1);
                    //перемножаем спектр сигнала на АЧХ фильтра
                    multVec_32fc_I(achFilt.data(),currSpec.data(),fftsize);
                    //расчитываем ОБПФ результата перемножения
                    fftwf_execute(planInv);
                    //нормируем результат ОБПФ, поделив на размер, получив
                    //т.о. результат фильтрации
                    divVecC_32fc_I(float(fftsize),datain1.data(),fftsize);
                    memcpy(datain2.data(),datain1.data(),fftsize*2*sizeof (float));
                    memcpy(datain4.data(),datain2.data(),fftsize*2*sizeof (float));
                    memcpy(datain8.data(),datain4.data(),fftsize*2*sizeof (float));
                    
                    /* Конец фильтрации сигнала */
                    
                }
                else
                {
                    memcpy(datain2.data(),datain1.data(),fftsize*2*sizeof (float));
                    memcpy(datain4.data(),datain2.data(),fftsize*2*sizeof (float));
                    memcpy(datain8.data(),datain4.data(),fftsize*2*sizeof (float));
                }
                
                if (trNum&1)
                {
                    normalizeToValue_32f((float*)datain1.data(),1,fftsize*2);
                    getCentFreqValue(planFow1,
                                     datain1.data(),
                                     currSpec.data(),
                                     currAmplSpec.data(),
                                     &fc1,fftsize,1);
                    multVecC_32f_I(1./sampleFreq,currAmplSpec.data(),fftsize);
                    
                    addVec_32f_I(currAmplSpec.data(),
                                 meanSpec1.data(),
                                 fftsize);
                    //сохраняем значение частоты и время относительно начала записи
                    values1.push_back(fc1);
                }
                if (trNum&2)
                {
                    normalizeToValue_32f((float*)datain2.data(),1,fftsize*2);
                    getCentFreqValue(planFow2,
                                     datain2.data(),
                                     currSpec.data(),
                                     currAmplSpec.data(),
                                     &fc2,fftsize,2);
                    multVecC_32f_I(1./sampleFreq,currAmplSpec.data(),fftsize);
                    addVec_32f_I(currAmplSpec.data(),
                                 meanSpec2.data(),
                                 fftsize);
                    //сохраняем значение частоты и время относительно начала записи
                    values2.push_back(fc2);
                }
                if (trNum&4)
                {
                    normalizeToValue_32f((float*)datain4.data(),1,fftsize*2);
                    getCentFreqValue(planFow4,
                                     datain4.data(),
                                     currSpec.data(),
                                     currAmplSpec.data(),
                                     &fc4,fftsize,4);
                    multVecC_32f_I(1./sampleFreq,currAmplSpec.data(),fftsize);
                    addVec_32f_I(currAmplSpec.data(),
                                 meanSpec4.data(),
                                 fftsize);
                    //сохраняем значение частоты и время относительно начала записи
                    values4.push_back(fc4);
                    
                }
                if (trNum&8)
                {
                    normalizeToValue_32f((float*)datain8.data(),1,fftsize*2);
                    getCentFreqValue(planFow8,
                                     datain8.data(),
                                     currSpec.data(),
                                     currAmplSpec.data(),
                                     &fc8,fftsize,8);
                    multVecC_32f_I(1./sampleFreq,currAmplSpec.data(),fftsize);
                    addVec_32f_I(currAmplSpec.data(),
                                 meanSpec8.data(),
                                 fftsize);
                    //сохраняем значение частоты и время относительно начала записи
                    values8.push_back(fc8);
                }
                
                ost.push_back(time);
                
                /* В РАЗРАБОТКЕ. НЕПОНЯТНА РЕАЛИЗАЦИЯ ИТЕРФЕЙСА ПОЛЬЗОВАТЕЛЯ ДЛЯ ЭТОЙ ФУНКЦИИИ*/
                /* Корректировка АЧХ фильтра по значению частоты */
                
                /*
                if (fc != fsig_old)
                {
                    float delta = (fc - fsig_old)/16. - (fsig_old - fsig_old_old)/32.;//!!!!!!!!!!!!!!
                    //переносим центральную частоту АЧХ фильтра на частоту сигнала
                    
                    freqTranslate_32fc(imphar32fc.data(), delta, fftsize, &ts);
                    //расчитываем АЧХ фильтра
                    getFilterAFR_32fc(imphar32fc.data(),achFilt.data(), fftsize);
                }
                fsig_old_old = fsig_old;
                fsig_old = fc;*/
                
                /* Конец корректировки АЧХ фильтра */
                
                
                //каждые полсекунды отправляем данные для отображения в интерфейсе
                //пользователя
                if (timer.elapsed() > 100)
                {
                    int progress = int(100.*float(fpos-posInFile)/float(winsize));
                    emit sendProgress(progress);
                    
                    //                    emit sendGraficsTime2os(ost.data(),values1.data(), values1.size(),7);
                    //                    emit sendGraficsTime2os(ost.data(),values2.data(), values2.size(),2);
                    //                    emit sendGraficsTime2os(ost.data(),values4.data(), values4.size(),3);
                    //                    emit sendGraficsTime2os(ost.data(),values8.data(), values8.size(),5);
                    qDebug() << progress;
                    timer.restart();
                }
                
                
                if (isCancelled)
                {
                    isCancelled = false;
                    break;
                }
                
            }
            
            fftwf_destroy_plan(planFow1);
            fftwf_destroy_plan(planFow2);
            fftwf_destroy_plan(planFow4);
            fftwf_destroy_plan(planFow8);
            fftwf_destroy_plan(planInv);
            
            osf.resize(fftsize);
            
            for (int i = 0; i < fftsize; i++)
            {
                osf[i] = i*sampleFreq/fftsize - sampleFreq/2;
            }
            
            fftShift_32f(meanSpec1.data(),meanSpec1.size());
            fftShift_32f(meanSpec2.data(),meanSpec2.size());
            fftShift_32f(meanSpec4.data(),meanSpec4.size());
            fftShift_32f(meanSpec8.data(),meanSpec8.size());
            
            file.close();
        }
        else
        {
            ERROROUT FileNotOpened;
            status = FileNotOpened;
        }
        emit sendProgress(0);
    }
    else
    {
        ERROROUT FileNotExist;
        status = FileNotExist;
    }
    
    return status;
    
}

/////////////////////////////////////////////////////////////////////////////////////
/*!
  \brief  Метод поблочного оценивания несущей частоты ФМн-сиганлов
  
  Метод предназначена определения несущей частоты ФМн-сигналов на основе
  эффекта свертки спектра с фильтрацией. Функция возращает код ошибки ErrorCode_Ta.
  
  \param [out]  values1    значения частоты по максимуму спектра сигнала
  \param [out]  values2    значения частоты по максимуму спектра квадрата сигнала
  \param [out]  values4    значения частоты по максимуму спектра четвертой степени
                           сигнала
  \param [out]  values8    значения частоты по максимуму спектра восьмой степени
                           сигнала
  \param [out]  ost        вектор временных отсчетов, соответствующих значениям частот
  \param [in]   fftsize    размер блока вычисления частоты (степень двоики)
  \param [in]   trNum      флаг, каждый из младших четырех разрядов которого
                           определяет необходимость вычисления спектра каждой
                           из 4-х степеней. Например, при trNum = 15, вычисляются все
                           спектры, при trNum = 8 - только спектр восьмой степени
                           сигнала
  \param [in]   overLap    размер перекрытия блоков вычисления (от 0 до fftsize-1)
  \param [in]   step       кратность шага движения по файлу в отсчетах, кратность 1
                           соответствует шагу в fftsize отсчетов, 2 - 2*fftsize и т.д.
                           при overLap > 0, step = 1, при step > 1, overLap  = 0
*/
/////////////////////////////////////////////////////////////////////////////////////
ErrorCode_Ta TaClass::getCentFreqForPSK(vector<float> &values1,
                                        vector<float> &values2,
                                        vector<float> &values4,
                                        vector<float> &values8,
                                        vector<float> &ost,
                                        int fftsize,
                                        int trNum,
                                        int overLap,
                                        int step)
{
    ErrorCode_Ta status;
    
    //проверка корректности входных параметров
    int ord = getOrder2(fftsize);
    if (ord < 6 || ord > 24 || fftsize%2!=0)
    {
        ERROROUT InvalidFFTsize;
        return InvalidFFTsize;
    }
    
    if (sampleFreq < 1)
    {
        ERROROUT InvalidSampleRate;
        return  InvalidSampleRate;
    }
    
    if (overLap < 0 || overLap > fftsize-1)
    {
        ERROROUT InvalidOverlap;
        return InvalidOverlap;
    }
    
    
    if (step < 1 || step > 100)
    {
        ERROROUT InvalidStep;
        return InvalidStep;
    }
    
    if (step > 1 || overLap > 0)
    {
        ERROROUT InvalidOverlap;
        return InvalidOverlap;
    }
    
    if (trNum < 1 &&  trNum > 15)
    {
        ERROROUT InvalidTransformNum;
        return InvalidTransformNum;
    }
    
    if (step > 1)
        overLap = -step*fftsize;
    
    isCancelled = false;
    
    //импульсная характеристика фильтра
    vector< complex<float> > imphar32fc;
    //АЧХ фильтра
    vector<complex <float> > achFilt;
    
    /* для АПЧ фильтра
    //запоминаем частоту сигнала
    float fsig_old = centerFreq;
    float fsig_old_old = centerFreq;
    */
    
    values1.clear();
    values2.clear();
    values4.clear();
    values8.clear();
    ost.clear();
    
    //проверка необходимости фильтрации ///////////////////////////Вдругих функциях тоже
    if (bandwith > 0)
    {
        status = isCorrectFreqPrms();
        if (status != NoError)
            return status;
        
        //формируем комплексную импульсную характеристику
        imphar32fc = genRCosFIRLowpassOnSymbsCmplx(5, bandwith, sampleFreq,
                                                   0.35, true);
        
        
        int s = imphar32fc.size();
        //если длина имп.хар-ки больше fftsize
        if (s > fftsize)
        {
            //уменьшаем длину имп. хар-ки
            imphar32fc = genRCosFIRLowpassOnSampsCmplx(fftsize-1,
                                                       bandwith/sampleFreq,
                                                       0.35, true);
        }
        else if (s < fftsize)
        {
            //добавляем нули к имп.хар-ки
            imphar32fc.resize(fftsize);
            memset((char*)(imphar32fc.data() + s ), 0 ,sizeof(float)*2);
        }
        
        float fimp = centerFreq/sampleFreq;
        qint64 tb = 0;
        //переносим центральную частоту АЧХ фильтра на частоту сигнала
        freqTranslate_32fc(imphar32fc.data(), fimp, fftsize, &tb);
        
        achFilt.resize(fftsize);
        
        //расчитываем АЧХ фильтра
        getFilterAFR_32fc(imphar32fc.data(),achFilt.data(), fftsize);
    }
    
    QFile file(filename);
    if (file.exists())
    {
        if (getSamplesCnt(format,file.size()) < fftsize)
        {
            ERROROUT InvalidFFTsize << " fftsize > size of file";
            status = InvalidFFTsize;
        }
        
        if (getSamplesCnt(format, winsize) < fftsize)
        {
            ERROROUT InvalidWinSize << " fftsize > winsize";
            status = InvalidWinSize;
        }
        
        if (winsize > file.size())
        {
            ERROROUT InvalidWinSize << " winsize > size of file";
            status = InvalidWinSize;
        }
        
        if (file.open(QIODevice::ReadOnly))
        {
            if (winsize == 0)
                winsize = file.size();
            
            //вектор входных данных, читаемых их файла
            vector<complex <float> > datain1(fftsize);
            
            //вектор входных данных, читаемых их файла
            vector<complex <float> > datain2(fftsize);
            
            //вектор входных данных, читаемых их файла
            vector<complex <float> > datain4(fftsize);
            
            //вектор входных данных, читаемых их файла
            vector<complex <float> > datain8(fftsize);
            
            //текущий комплексный спектр
            vector<complex <float> > currSpec(fftsize);
            //амплитудный спектр
            vector<float>            currAmplSpec(fftsize);
            memset(currSpec.data(),0,sizeof(float)*2);
            
            //план прямого БПФ
            fftwf_plan planFow1 = fftwf_plan_dft_1d(fftsize,
                                                    (fftwf_complex*) datain1.data(),
                                                    (fftwf_complex*) currSpec.data(),
                                                    FFTW_FORWARD, FFTW_ESTIMATE);
            
            //план прямого БПФ
            fftwf_plan planFow2 = fftwf_plan_dft_1d(fftsize,
                                                    (fftwf_complex*) datain2.data(),
                                                    (fftwf_complex*) currSpec.data(),
                                                    FFTW_FORWARD, FFTW_ESTIMATE);
            
            //план прямого БПФ
            fftwf_plan planFow4 = fftwf_plan_dft_1d(fftsize,
                                                    (fftwf_complex*) datain4.data(),
                                                    (fftwf_complex*) currSpec.data(),
                                                    FFTW_FORWARD, FFTW_ESTIMATE);
            
            //план прямого БПФ
            fftwf_plan planFow8 = fftwf_plan_dft_1d(fftsize,
                                                    (fftwf_complex*) datain8.data(),
                                                    (fftwf_complex*) currSpec.data(),
                                                    FFTW_FORWARD, FFTW_ESTIMATE);
            
            //план обратного БПФ для фильтрации
            fftwf_plan planInv = fftwf_plan_dft_1d(fftsize,
                                                   (fftwf_complex*) currSpec.data(),
                                                   (fftwf_complex*) datain1.data(),
                                                   FFTW_BACKWARD, FFTW_ESTIMATE);
            
            //таймер нужен для отправки сигналов через определенные интервалы времени,
            //а не постоянно
            QElapsedTimer timer;
            timer.start();
            qint64 fpos = posInFile;
            
            /* для АПЧ фильтра
            qint64 ts = 0;
            float fc;
            */
            
            float  fc1, fc2, fc4, fc8;
            
            ErrorCode_Ta ststusFile = NoError;
            
            while (!file.atEnd() && (fpos < (posInFile + winsize)) && ststusFile !=EndOfFile)
            {
                //текущее время относительно начала записи
                float time = float(getSamplesCnt(format,fpos))/sampleFreq;
                
                /* Чтение данных из файла и одновременная конвертация отчетов
                 * при необходимости*/
                ststusFile = readAndConvert(file, datain1, &fpos, format, overLap);
                
                //если нужно фильтровать
                if (!imphar32fc.empty())
                {
                    
                    /* Начало фильтрации сигнала */
                    
                    //расчитываем спектр текущего фрагмента сигнала
                    fftwf_execute(planFow1);
                    //перемножаем спектр сигнала на АЧХ фильтра
                    multVec_32fc_I(achFilt.data(),currSpec.data(),fftsize);
                    //расчитываем ОБПФ результата перемножения
                    fftwf_execute(planInv);
                    //нормируем результат ОБПФ, поделив на размер, получив
                    //т.о. результат фильтрации
                    divVecC_32fc_I(float(fftsize),datain1.data(),fftsize);
                    memcpy(datain2.data(),datain1.data(),fftsize*2*sizeof (float));
                    memcpy(datain4.data(),datain2.data(),fftsize*2*sizeof (float));
                    memcpy(datain8.data(),datain4.data(),fftsize*2*sizeof (float));
                    
                    /* Конец фильтрации сигнала */
                    
                }
                else
                {
                    memcpy(datain2.data(),datain1.data(),fftsize*2*sizeof (float));
                    memcpy(datain4.data(),datain2.data(),fftsize*2*sizeof (float));
                    memcpy(datain8.data(),datain4.data(),fftsize*2*sizeof (float));
                }
                
                if (trNum&1)
                {
                    normalizeToValue_32f((float*)datain1.data(),1,fftsize*2);
                    getCentFreqValue(planFow1,
                                     datain1.data(),
                                     currSpec.data(),
                                     currAmplSpec.data(),
                                     &fc1,fftsize,1);
                    
                    //сохраняем значение частоты и время относительно начала записи
                    values1.push_back(fc1);
                }
                if (trNum&2)
                {
                    normalizeToValue_32f((float*)datain2.data(),1,fftsize*2);
                    getCentFreqValue(planFow2,
                                     datain2.data(),
                                     currSpec.data(),
                                     currAmplSpec.data(),
                                     &fc2,fftsize,2);
                    
                    //сохраняем значение частоты и время относительно начала записи
                    values2.push_back(fc2);
                }
                if (trNum&4)
                {
                    normalizeToValue_32f((float*)datain4.data(),1,fftsize*2);
                    getCentFreqValue(planFow4,
                                     datain4.data(),
                                     currSpec.data(),
                                     currAmplSpec.data(),
                                     &fc4,fftsize,4);
                    
                    //сохраняем значение частоты и время относительно начала записи
                    values4.push_back(fc4);
                    
                }
                if (trNum&8)
                {
                    normalizeToValue_32f((float*)datain8.data(),1,fftsize*2);
                    getCentFreqValue(planFow8,
                                     datain8.data(),
                                     currSpec.data(),
                                     currAmplSpec.data(),
                                     &fc8,fftsize,8);
                    
                    //сохраняем значение частоты и время относительно начала записи
                    values8.push_back(fc8);
                }
                
                ost.push_back(time);
                
                /* В РАЗРАБОТКЕ. НЕПОНЯТНА РЕАЛИЗАЦИЯ ИТЕРФЕЙСА ПОЛЬЗОВАТЕЛЯ ДЛЯ ЭТОЙ ФУНКЦИИИ*/
                /* Корректировка АЧХ фильтра по значению частоты */
                
                /*
                if (fc != fsig_old)
                {
                    float delta = (fc - fsig_old)/16. - (fsig_old - fsig_old_old)/32.;//!!!!!!!!!!!!!!
                    //переносим центральную частоту АЧХ фильтра на частоту сигнала
                    
                    freqTranslate_32fc(imphar32fc.data(), delta, fftsize, &ts);
                    //расчитываем АЧХ фильтра
                    getFilterAFR_32fc(imphar32fc.data(),achFilt.data(), fftsize);
                }
                fsig_old_old = fsig_old;
                fsig_old = fc;*/
                
                /* Конец корректировки АЧХ фильтра */
                
                
                //каждые полсекунды отправляем данные для отображения в
                //интерфейсе пользователя
                if (timer.elapsed() > 500)
                {
                    int progress = int(100.*float(fpos-posInFile)/float(winsize));
                    emit sendProgress(progress);
                    
                    qDebug() << progress;
                    timer.restart();
                }
                
                
                
                if (isCancelled)
                {
                    isCancelled = false;
                    break;
                }
                
            }
            
            fftwf_destroy_plan(planFow1);
            fftwf_destroy_plan(planFow2);
            fftwf_destroy_plan(planFow4);
            fftwf_destroy_plan(planFow8);
            fftwf_destroy_plan(planInv);
            
            file.close();
        }
        else
        {
            ERROROUT FileNotOpened;
            status = FileNotOpened;
        }
        emit sendProgress(0);
    }
    else
    {
        ERROROUT FileNotExist;
        status = FileNotExist;
    }
    
    return status;
}


/////////////////////////////////////////////////////////////////////////////////////
/*!
  \brief  Метод поблочного оценивания несущей частоты ФМн-сиганлов
  
  Метод предназначена определения несущей частоты ФМн-сигналов на основе
  эффекта свертки спектра с фильтрацией. Функция возращает код ошибки ErrorCode_Ta.
  
  \param [out]  values1    значения частоты по максимуму спектра сигнала
  \param [out]  values2    значения частоты по максимуму спектра квадрата сигнала
  \param [out]  values4    значения частоты по максимуму спектра четвертой степени
                           сигнала
  \param [out]  values8    значения частоты по максимуму спектра восьмой степени
                           сигнала
  \param [out]  ost        вектор временных отсчетов, соответствующих значениям частот
  \param [in]   fftsize    размер блока вычисления частоты (степень двоики)
  \param [in]   trNum      флаг, каждый из младших четырех разрядов которого
                           определяет необходимость вычисления спектра каждой
                           из 4-х степеней. Например, при trNum = 15, вычисляются все
                           спектры, при trNum = 8 - только спектр восьмой степени
                           сигнала
  \param [in]   overLap    размер перекрытия блоков вычисления (от 0 до fftsize-1)
  \param [in]   step       кратность шага движения по файлу в отсчетах, кратность 1
                           соответствует шагу в fftsize отсчетов, 2 - 2*fftsize и т.д.
                           при overLap > 0, step = 1, при step > 1, overLap  = 0
*/
/////////////////////////////////////////////////////////////////////////////////////
ErrorCode_Ta TaClass::getCentFreqForPSK(vector<float> &values1,
                                        vector<float> &values2,
                                        vector<float> &values4,
                                        vector<float> &values8,
                                        vector<float> &power,
                                        vector<float> &ost,
                                        int fftsize,
                                        int trNum,
                                        int overLap,
                                        int step)
{
    ErrorCode_Ta status;
    
    //проверка корректности входных параметров
    int ord = getOrder2(fftsize);
    if (ord < 6 || ord > 24 || fftsize%2!=0)
    {
        ERROROUT InvalidFFTsize;
        return InvalidFFTsize;
    }
    
    if (sampleFreq < 1)
    {
        ERROROUT InvalidSampleRate;
        return  InvalidSampleRate;
    }
    
    if (overLap < 0 || overLap > fftsize-1)
    {
        ERROROUT InvalidOverlap;
        return InvalidOverlap;
    }
    
    
    if (step < 1 || step > 100)
    {
        ERROROUT InvalidStep;
        return InvalidStep;
    }
    
    if (step > 1 || overLap > 0)
    {
        ERROROUT InvalidOverlap;
        return InvalidOverlap;
    }
    
    if (trNum < 1 &&  trNum > 15)
    {
        ERROROUT InvalidTransformNum;
        return InvalidTransformNum;
    }
    
    if (step > 1)
        overLap = -step*fftsize;
    
    isCancelled = false;
    
    //импульсная характеристика фильтра
    vector< complex<float> > imphar32fc;
    //АЧХ фильтра
    vector<complex <float> > achFilt;
    
    /* для АПЧ фильтра
    //запоминаем частоту сигнала
    float fsig_old = centerFreq;
    float fsig_old_old = centerFreq;
    */
    
    values1.clear();
    values2.clear();
    values4.clear();
    values8.clear();
    power.clear();
    ost.clear();
    
    int indexLeft = 0;
    int indexRight = 0;
    
    //проверка необходимости фильтрации ///////////////////////////Вдругих функциях тоже
    if (bandwith > 0)
    {
        status = isCorrectFreqPrms();
        if (status != NoError)
            return status;
        
        //формируем комплексную импульсную характеристику
        imphar32fc = genRCosFIRLowpassOnSymbsCmplx(5, bandwith, sampleFreq,
                                                   0.35, true);
        
        
        int s = imphar32fc.size();
        //если длина имп.хар-ки больше fftsize
        if (s > fftsize)
        {
            //уменьшаем длину имп. хар-ки
            imphar32fc = genRCosFIRLowpassOnSampsCmplx(fftsize-1,
                                                       bandwith/sampleFreq,
                                                       0.35, true);
        }
        else if (s < fftsize)
        {
            //добавляем нули к имп.хар-ки
            imphar32fc.resize(fftsize);
            memset((char*)(imphar32fc.data() + s ), 0 ,sizeof(float)*2);
        }
        
        float fimp = centerFreq/sampleFreq;
        qint64 tb = 0;
        //переносим центральную частоту АЧХ фильтра на частоту сигнала
        freqTranslate_32fc(imphar32fc.data(), fimp, fftsize, &tb);
        
        achFilt.resize(fftsize);
        
        //расчитываем АЧХ фильтра
        getFilterAFR_32fc(imphar32fc.data(),achFilt.data(), fftsize);
        
        
        if (format == BIT8C  ||
                format == BIT16C ||
                format == BIT32C ||
                format == BIT32CF)
        {
            indexLeft = round((centerFreq-bandwith/2.)/sampleFreq*fftsize)+fftsize/2;
            indexRight = round((centerFreq+bandwith/2.)/sampleFreq*fftsize)+fftsize/2;
        }
        else
        {
            indexLeft = round((centerFreq-bandwith/2.)/sampleFreq*fftsize);
            indexRight = round((centerFreq+bandwith/2.)/sampleFreq*fftsize);
        }
        
        
    }
    else
    {
        indexLeft = 0;
        if (format == BIT8C  ||
                format == BIT16C ||
                format == BIT32C ||
                format == BIT32CF)
        {
            indexRight = fftsize-1;
        }
        else
        {
            indexRight = fftsize/2-1;
        }
    }
    
    QFile file(filename);
    if (file.exists())
    {
        if (getSamplesCnt(format,file.size()) < fftsize)
        {
            ERROROUT InvalidFFTsize << " fftsize > size of file";
            status = InvalidFFTsize;
        }
        
        if (getSamplesCnt(format, winsize) < fftsize)
        {
            ERROROUT InvalidWinSize << " fftsize > winsize";
            status = InvalidWinSize;
        }
        
        if (winsize > file.size())
        {
            ERROROUT InvalidWinSize << " winsize > size of file";
            status = InvalidWinSize;
        }
        
        if (file.open(QIODevice::ReadOnly))
        {
            if (winsize == 0)
                winsize = file.size();
            
            //вектор входных данных, читаемых их файла
            vector<complex <float> > datain1(fftsize);
            
            //вектор входных данных, читаемых их файла
            vector<complex <float> > datain2(fftsize);
            
            //вектор входных данных, читаемых их файла
            vector<complex <float> > datain4(fftsize);
            
            //вектор входных данных, читаемых их файла
            vector<complex <float> > datain8(fftsize);
            
            //текущий комплексный спектр
            vector<complex <float> > currSpec(fftsize);
            //амплитудный спектр
            vector<float>            currAmplSpec(fftsize);
            memset(currSpec.data(),0,sizeof(float)*2);
            
            //план прямого БПФ
            fftwf_plan planFow1 = fftwf_plan_dft_1d(fftsize,
                                                    (fftwf_complex*) datain1.data(),
                                                    (fftwf_complex*) currSpec.data(),
                                                    FFTW_FORWARD, FFTW_ESTIMATE);
            
            //план прямого БПФ
            fftwf_plan planFow2 = fftwf_plan_dft_1d(fftsize,
                                                    (fftwf_complex*) datain2.data(),
                                                    (fftwf_complex*) currSpec.data(),
                                                    FFTW_FORWARD, FFTW_ESTIMATE);
            
            //план прямого БПФ
            fftwf_plan planFow4 = fftwf_plan_dft_1d(fftsize,
                                                    (fftwf_complex*) datain4.data(),
                                                    (fftwf_complex*) currSpec.data(),
                                                    FFTW_FORWARD, FFTW_ESTIMATE);
            
            //план прямого БПФ
            fftwf_plan planFow8 = fftwf_plan_dft_1d(fftsize,
                                                    (fftwf_complex*) datain8.data(),
                                                    (fftwf_complex*) currSpec.data(),
                                                    FFTW_FORWARD, FFTW_ESTIMATE);
            
            //план обратного БПФ для фильтрации
            fftwf_plan planInv = fftwf_plan_dft_1d(fftsize,
                                                   (fftwf_complex*) currSpec.data(),
                                                   (fftwf_complex*) datain1.data(),
                                                   FFTW_BACKWARD, FFTW_ESTIMATE);
            
            //таймер нужен для отправки сигналов через определенные интервалы времени,
            //а не постоянно
            QElapsedTimer timer;
            timer.start();
            qint64 fpos = posInFile;
            
            /* для АПЧ фильтра
            qint64 ts = 0;
            float fc;
            */
            
            float  fc1, fc2, fc4, fc8;
            
            ErrorCode_Ta ststusFile = NoError;
            
            while (!file.atEnd() && (fpos < (posInFile + winsize)) && ststusFile !=EndOfFile)
            {
                //текущее время относительно начала записи
                float time = float(getSamplesCnt(format,fpos))/sampleFreq;
                
                /* Чтение данных из файла и одновременная конвертация отчетов
                 * при необходимости*/
                ststusFile = readAndConvert(file, datain1, &fpos, format, overLap);
                
                //если нужно фильтровать
                if (!imphar32fc.empty())
                {
                    
                    /* Начало фильтрации сигнала */
                    
                    //расчитываем спектр текущего фрагмента сигнала
                    fftwf_execute(planFow1);
                    //перемножаем спектр сигнала на АЧХ фильтра
                    multVec_32fc_I(achFilt.data(),currSpec.data(),fftsize);
                    //расчитываем ОБПФ результата перемножения
                    fftwf_execute(planInv);
                    //нормируем результат ОБПФ, поделив на размер, получив
                    //т.о. результат фильтрации
                    divVecC_32fc_I(float(fftsize),datain1.data(),fftsize);
                    memcpy(datain2.data(),datain1.data(),fftsize*2*sizeof (float));
                    memcpy(datain4.data(),datain2.data(),fftsize*2*sizeof (float));
                    memcpy(datain8.data(),datain4.data(),fftsize*2*sizeof (float));
                    
                    /* Конец фильтрации сигнала */
                    
                }
                else
                {
                    memcpy(datain2.data(),datain1.data(),fftsize*2*sizeof (float));
                    memcpy(datain4.data(),datain2.data(),fftsize*2*sizeof (float));
                    memcpy(datain8.data(),datain4.data(),fftsize*2*sizeof (float));
                }
                
                if (trNum&1)
                {
                    normalizeToValue_32f((float*)datain1.data(),1,fftsize*2);
                    getCentFreqValue(planFow1,
                                     datain1.data(),
                                     currSpec.data(),
                                     currAmplSpec.data(),
                                     &fc1,fftsize,1);
                    multVecC_32f_I(1./sampleFreq,currAmplSpec.data(),fftsize);
                    
                    float pow = 0;
                    for (int i = indexLeft; i <= indexRight; i++)
                    {
                        pow+=currAmplSpec[i]*currAmplSpec[i];
                    }
                    float dF  = sampleFreq/fftsize;
                    float dT  = fftsize/sampleFreq;
                    pow = pow * dF / dT;
                    power.push_back(10.*log10(pow));
                    
                    //сохраняем значение частоты и время относительно начала записи
                    values1.push_back(fc1);
                }
                if (trNum&2)
                {
                    normalizeToValue_32f((float*)datain2.data(),1,fftsize*2);
                    getCentFreqValue(planFow2,
                                     datain2.data(),
                                     currSpec.data(),
                                     currAmplSpec.data(),
                                     &fc2,fftsize,2);
                    
                    //сохраняем значение частоты и время относительно начала записи
                    values2.push_back(fc2);
                }
                if (trNum&4)
                {
                    normalizeToValue_32f((float*)datain4.data(),1,fftsize*2);
                    getCentFreqValue(planFow4,
                                     datain4.data(),
                                     currSpec.data(),
                                     currAmplSpec.data(),
                                     &fc4,fftsize,4);
                    
                    //сохраняем значение частоты и время относительно начала записи
                    values4.push_back(fc4);
                    
                }
                if (trNum&8)
                {
                    normalizeToValue_32f((float*)datain8.data(),1,fftsize*2);
                    getCentFreqValue(planFow8,
                                     datain8.data(),
                                     currSpec.data(),
                                     currAmplSpec.data(),
                                     &fc8,fftsize,8);
                    
                    //сохраняем значение частоты и время относительно начала записи
                    values8.push_back(fc8);
                }
                
                ost.push_back(time);
                
                /* В РАЗРАБОТКЕ. НЕПОНЯТНА РЕАЛИЗАЦИЯ ИТЕРФЕЙСА ПОЛЬЗОВАТЕЛЯ ДЛЯ ЭТОЙ ФУНКЦИИИ*/
                /* Корректировка АЧХ фильтра по значению частоты */
                
                /*
                if (fc != fsig_old)
                {
                    float delta = (fc - fsig_old)/16. - (fsig_old - fsig_old_old)/32.;//!!!!!!!!!!!!!!
                    //переносим центральную частоту АЧХ фильтра на частоту сигнала
                    
                    freqTranslate_32fc(imphar32fc.data(), delta, fftsize, &ts);
                    //расчитываем АЧХ фильтра
                    getFilterAFR_32fc(imphar32fc.data(),achFilt.data(), fftsize);
                }
                fsig_old_old = fsig_old;
                fsig_old = fc;*/
                
                /* Конец корректировки АЧХ фильтра */
                
                
                //каждые полсекунды отправляем данные для отображения в
                //интерфейсе пользователя
                if (timer.elapsed() > 500)
                {
                    int progress = int(100.*float(fpos-posInFile)/float(winsize));
                    emit sendProgress(progress);
                    
                    qDebug() << progress;
                    timer.restart();
                }
                
                
                
                if (isCancelled)
                {
                    isCancelled = false;
                    break;
                }
                
            }
            
            fftwf_destroy_plan(planFow1);
            fftwf_destroy_plan(planFow2);
            fftwf_destroy_plan(planFow4);
            fftwf_destroy_plan(planFow8);
            fftwf_destroy_plan(planInv);
            
            file.close();
        }
        else
        {
            ERROROUT FileNotOpened;
            status = FileNotOpened;
        }
        emit sendProgress(0);
    }
    else
    {
        ERROROUT FileNotExist;
        status = FileNotExist;
    }
    
    return status;
}

ErrorCode_Ta TaClass::getPowerSNR(vector<float> &SNR,
                                  vector<float> &power,
                                  vector<float> &ost,
                                  int * delta,
                                  int fftsize ,
                                  int maxSmpls )
{
    ErrorCode_Ta status;
    
    //проверка корректности входных параметров
    int ord = getOrder2(fftsize);
    if (ord < 6 || ord > 24 || fftsize%2!=0)
    {
        ERROROUT InvalidFFTsize;
        return InvalidFFTsize;
    }
    
    if (sampleFreq < 1)
    {
        ERROROUT InvalidSampleRate;
        return  InvalidSampleRate;
    }
    
    
    if (maxSmpls < 512 || delta==0)
    {
        ERROROUT InvalidData;
        return  InvalidData;
    }
    
    isCancelled = false;
    
    SNR.clear();
    power.clear();
    ost.clear();
    
    SNR.reserve(maxSmpls*3);
    power.reserve(maxSmpls*3);
    ost.reserve(maxSmpls*3);
    
    int indexLeftWum = 0;
    int indexRightWum = 0;
    
    int indexLeftSig = 0;
    int indexRightSig = 0;
    
    
    if (format == BIT8C  ||
            format == BIT16C ||
            format == BIT32C ||
            format == BIT32CF)
    {
        indexLeftWum = round(leftWum/sampleFreq*fftsize)+fftsize/2;
        indexRightWum = round(rightWum/sampleFreq*fftsize)+fftsize/2;
        
        indexLeftSig = round(leftSig/sampleFreq*fftsize)+fftsize/2;
        indexRightSig = round(rightSig/sampleFreq*fftsize)+fftsize/2;
    }
    else
    {
        indexLeftWum = round(leftWum/sampleFreq*fftsize);
        indexRightWum = round(rightWum/sampleFreq*fftsize);
        
        indexLeftSig = round(leftSig/sampleFreq*fftsize);
        indexRightSig = round(rightSig/sampleFreq*fftsize);
    }
    
    
    QFile file(filename);
    if (file.exists())
    {
        if (getSamplesCnt(format,file.size()) < fftsize)
        {
            ERROROUT InvalidFFTsize << " fftsize > size of file";
            status = InvalidFFTsize;
        }
        
        if (getSamplesCnt(format, winsize) < fftsize)
        {
            ERROROUT InvalidWinSize << " fftsize > winsize";
            status = InvalidWinSize;
        }
        
        if (winsize > file.size())
        {
            ERROROUT InvalidWinSize << " winsize > size of file";
            status = InvalidWinSize;
        }
        
        if (file.open(QIODevice::ReadOnly))
        {
            if (winsize == 0)
                winsize = file.size();
            
            //вектор входных данных, читаемых их файла
            vector<complex <float> > datain(fftsize);
            
            
            //текущий комплексный спектр
            vector<complex <float> > currSpec(fftsize);
            //амплитудный спектр
            vector<float>            currAmplSpec(fftsize);
            memset(currSpec.data(),0,sizeof(float)*2);
            
            //план прямого БПФ
            fftwf_plan plan = fftwf_plan_dft_1d(fftsize,
                                                (fftwf_complex*) datain.data(),
                                                (fftwf_complex*) currSpec.data(),
                                                FFTW_FORWARD, FFTW_ESTIMATE);
            
            //таймер нужен для отправки сигналов через определенные интервалы времени,
            //а не постоянно
            QElapsedTimer timer;
            timer.start();
            qint64 fpos = posInFile;
            
            ErrorCode_Ta ststusFile = NoError;
            
            qint64 smplsCntWin = getSamplesCnt(format,winsize)/fftsize;
            qint64 deltaSample = trunc(float(smplsCntWin)/float(maxSmpls));
            deltaSample = (deltaSample<1) ? 1 : deltaSample;
            *delta = deltaSample;
            
            while (!file.atEnd() && (fpos < (posInFile + winsize)) && ststusFile !=EndOfFile)
            {
                //текущее время относительно начала записи
                float time = float(getSamplesCnt(format,fpos))/sampleFreq;
                
                /* Чтение данных из файла и одновременная конвертация отчетов
                 * при необходимости*/
                ststusFile = readAndConvert(file, datain, &fpos, format, 0);
                qint64 step = getBytesCnt(format,(deltaSample-1)*fftsize);
                fpos+=step;
                
                //выполняем БПФ результата возведения в степень
                fftwf_execute(plan);
                //вычисляем амплитудный спектр
                magnitude_32fc(currSpec.data(),currAmplSpec.data(),fftsize);
                multVecC_32f_I(1./sampleFreq,currAmplSpec.data(),fftsize);
                
                fftShift_32f(currAmplSpec.data(),fftsize);
                
                
                float dF  = sampleFreq/fftsize;
                float dT  = fftsize/sampleFreq;
                
                float powSig = 0;
                for (int i = indexLeftSig; i <= indexRightSig; i++)
                {
                    powSig+=currAmplSpec[i]*currAmplSpec[i];
                }
                powSig = powSig * dF / dT;
                
                float powWum = 0;
                for (int i = indexLeftWum; i <= indexRightWum; i++)
                {
                    powWum+=currAmplSpec[i]*currAmplSpec[i];
                }
                powWum = powWum * dF / dT;
                
                power.push_back(10*log10(powSig));
                SNR.push_back(10*log10(powSig/powWum));
                ost.push_back(time);
                
                //каждые полсекунды отправляем данные для отображения в
                //интерфейсе пользователя
                if (timer.elapsed() > 500)
                {
                    int progress = int(100.*float(fpos-posInFile)/float(winsize));
                    emit sendProgress(progress);
                    
                    qDebug() << progress;
                    timer.restart();
                }
                
                if (isCancelled)
                {
                    isCancelled = false;
                    break;
                }
                
            }
            
            fftwf_destroy_plan(plan);
            file.close();
        }
        else
        {
            ERROROUT FileNotOpened;
            status = FileNotOpened;
        }
        emit sendProgress(0);
    }
    else
    {
        ERROROUT FileNotExist;
        status = FileNotExist;
    }
    
    return status;
}




/////////////////////////////////////////////////////////////////////////////////////
/*!
  \brief  Метод поблочного вычисления индикаторных функции модуляционной скорости
  
  Метод предназначена для поблочного  вычисления индикаторных функции модуляционной
  скорости: амплитудного спектра огибающей, амплитудного спектра модуля мгновенной
  частоты и амплитудного спект производной автокорреляции сигнала. Функция возращает
  код ошибки ErrorCode_Ta.
  
  \param [out]  meanSpecOgib  усредненный амплитудный спектр огибающей сигнала
  \param [out]  meanSpecOgib  усредненный амплитудный спектр модуля мгновенной частоты
  \param [out]  meanSpecAcf   усредненый амплитудный спектр производной автокорреляции
  \param [out]  osf           вектор отсчетов оси частот
  \param [in]   fftsize       размер блока обработки, размер БПФ (степень двоики)
  \param [in]   trInd         флаг, каждый из младших четырех разрядов которого
                              определяет необходимость вычисления каждого из идикаторных
                              преобразований.Например, при trInd = 7, вычисляются все
                              индикаторные функции, при trNum = 4 - только спектр
                              производной автокорреляции и т.д.
*/
/////////////////////////////////////////////////////////////////////////////////////

ErrorCode_Ta TaClass::getSpecOfDet(vector<float> &meanSpecOgib,
                                   vector<float> &meanSpecFreq,
                                   vector<float> &meanSpecAcf,
                                   vector<float> &osf,
                                   int fftsize, uint8_t trInd)
{
    
    ErrorCode_Ta status;
    
    //проверка корректности входных параметров
    int ord = getOrder2(fftsize);
    if (ord < 6 || ord > 24)
    {
        ERROROUT InvalidFFTsize;
        return InvalidFFTsize;
    }
    
    if (sampleFreq < 1)
    {
        ERROROUT InvalidSampleRate;
        return  InvalidSampleRate;
    }
    
    if (trInd < 1 || trInd > 15)
    {
        ERROROUT InvalidTransformNum;
        return InvalidTransformNum;
    }
    
    
    isCancelled = false;
    
    //импульсная характеристика фильтра
    vector< complex<float> > imphar32fc;
    //АЧХ фильтра
    vector<complex <float> > achFilt;
    
    float sampleFreqDecim = sampleFreq;
    
    meanSpecOgib.resize(fftsize/2);
    meanSpecFreq.resize(fftsize/2);
    meanSpecAcf.resize(fftsize/2);
    memset(meanSpecOgib.data(),0,sizeof(float)*fftsize/2);
    memset(meanSpecFreq.data(),0,sizeof(float)*fftsize/2);
    memset(meanSpecAcf.data(),0,sizeof(float)*fftsize/2);
    
    int implen = 0;
    
    //проверка необходимости фильтрации
    if (bandwith > 0)
    {
        status = isCorrectFreqPrms();
        if (status != NoError)
            return status;
        
        //формируем комплексную импульсную характеристику
        imphar32fc = genRCosFIRLowpassOnSymbsCmplx(5, bandwith,
                                                   sampleFreq, 0.35, true);
        
        implen = imphar32fc.size();
        
        int s = imphar32fc.size();
        //если длина имп.хар-ки больше fftsize
        if (s > fftsize)
        {
            //уменьшаем длину имп. хар-ки
            imphar32fc = genRCosFIRLowpassOnSampsCmplx(fftsize-1,
                                                       bandwith/sampleFreq,
                                                       0.35, true);
        }
        else if (s < fftsize)
        {
            //добавляем нули к имп.хар-ки
            imphar32fc.resize(fftsize);
            memset((char*)(imphar32fc.data() + s ), 0 ,sizeof(float)*2);
        }
        
        float fimp = centerFreq/sampleFreq;
        qint64 tb = 0;
        //переносим центральную частоту АЧХ фильтра на частоту сигнала
        freqTranslate_32fc(imphar32fc.data(), fimp, fftsize, &tb);
        
        achFilt.resize(fftsize);
        
        //расчитываем АЧХ фильтра
        getFilterAFR_32fc(imphar32fc.data(),achFilt.data(), fftsize);
    }
    
    QFile file(filename);
    if (file.exists())
    {
        
        if (getSamplesCnt(format,file.size()) < fftsize)
        {
            ERROROUT InvalidFFTsize << " fftsize > size of file";
            status = InvalidFFTsize;
        }
        
        if (getSamplesCnt(format, winsize) < fftsize)
        {
            ERROROUT InvalidWinSize << " fftsize > winsize";
            status = InvalidWinSize;
        }
        
        if (winsize > file.size())
        {
            ERROROUT InvalidWinSize << " winsize > size of file";
            status = InvalidWinSize;
        }
        
        if (file.open(QIODevice::ReadOnly))
        {
            if (winsize == 0)
                winsize = file.size();
            
            //implen = fftsize/2;
            
            //вектор входных данных, читаемых их файла
            vector<complex <float> > datain(fftsize);
            
            //текущий комплексный спектр
            vector<complex <float> > currSpecFilt(fftsize);
            
            //децимированные данные
            vector<complex <float> > dataiDecim(fftsize);
            
            //Огибающая сигнала
            vector<float> dataOgib(fftsize);
            
            //Мгновенная частота сигнала
            vector<float>  dataFreqDet(fftsize);
            
            //производная АКФ сигнала
            vector<float> dataAcf(fftsize);
            vector<float> dataAcfDiff(fftsize);
            
            
            //текущий комплексный спектр
            vector<complex <float> > currSpec(fftsize);
            
            
            //план прямого БПФ для фильтрации
            fftwf_plan planFow = fftwf_plan_dft_1d(fftsize,
                                                   (fftwf_complex*) datain.data(),
                                                   (fftwf_complex*) currSpecFilt.data(),
                                                   FFTW_FORWARD, FFTW_ESTIMATE);
            //план обратного БПФ для фильтрации
            fftwf_plan planInv = fftwf_plan_dft_1d(fftsize,
                                                   (fftwf_complex*) currSpecFilt.data(),
                                                   (fftwf_complex*) datain.data(),
                                                   FFTW_BACKWARD, FFTW_ESTIMATE);
            
            
            fftwf_plan planOgib = fftwf_plan_dft_r2c_1d(fftsize,
                                                        dataOgib.data(),
                                                        (fftwf_complex*) currSpec.data(),
                                                        FFTW_ESTIMATE);
            
            fftwf_plan planFreq = fftwf_plan_dft_r2c_1d(fftsize,
                                                        dataFreqDet.data(),
                                                        (fftwf_complex*) currSpec.data(),
                                                        FFTW_ESTIMATE);
            
            fftwf_plan planAcf = fftwf_plan_dft_r2c_1d(fftsize,
                                                       dataAcf.data(),
                                                       (fftwf_complex*) currSpec.data(),
                                                       FFTW_ESTIMATE);
            
            //таймер нужен для отправки сигналов через определенные интервалы времени,
            //а не постоянно
            QElapsedTimer timer;
            timer.start();
            
            qint64 fpos = posInFile;
            int ostatok = 0;
            qint64 tsample = 0;
            
            //Кольцевой буфер
            CircBuffer< complex<float> > circBuff(fftsize*16,fftsize);
            
            ErrorCode_Ta statusFile = NoError;
            
            while (!file.atEnd() && (fpos < (posInFile + winsize)) && statusFile != EndOfFile)
            {
                
                /* Чтение данных из файла и одновременная конвертация отчетов
                 * при необходимости*/
                statusFile = readAndConvert(file, datain , &fpos, format, implen);
                
                int coefDecim = 0;
                
                //если нужно фильтровать
                if (!imphar32fc.empty())
                {
                    /* Начало фильтрации сигнала */
                    
                    //расчитываем спектр текущего фрагмента сигнала
                    fftwf_execute(planFow);
                    //перемножаем спектр сигнала на АЧХ фильтра
                    multVec_32fc_I(achFilt.data(),currSpecFilt.data(),fftsize);
                    //расчитываем ОБПФ результата перемножения
                    fftwf_execute(planInv);
                    //нормируем результат ОБПФ, поделив на размер, получив
                    //т.о. результат фильтрации
                    divVecC_32fc_I(float(fftsize),datain.data(),fftsize);
                    
                    coefDecim = sampleFreq/(4*bandwith);
                    sampleFreqDecim = sampleFreq/coefDecim;
                    
                    /* Конец фильтрации сигнала */
                    //переносим сигнал на нулевую частоту
                    freqTranslate_32fc(datain.data()+implen,-centerFreq/sampleFreq,
                                       fftsize-implen, &tsample);
                    
                }
                
                //если надо децимировать
                if (coefDecim > 1)
                {
                    //memset(dataiDecim.data(),0,sizeof (float)*2*fftsize);
                    for (int i = implen+ostatok, c = 0; i < fftsize; i+=coefDecim,c++)
                    {
                        
                        circBuff.writeBlock(datain.data()+i,1);
                        ostatok = i;
                    }
                    ostatok = coefDecim - (fftsize - ostatok);
                }
                else //если не надо децимировать
                {
                    circBuff.writeBlock(datain.data()+implen,fftsize-implen);
                    sampleFreqDecim = sampleFreq;
                }
                
                
                bool isEndRead = (fpos >= (posInFile + winsize)) || (statusFile == EndOfFile);
                
                if (isEndRead && !circBuff.getReadyToLastRead())
                {
                    int cnt  = circBuff.getQueueSize();
                    vector<complex<float> > zero(fftsize-cnt+1);
                    memset(zero.data(),0,zero.size()*sizeof (float)*2);
                    circBuff.writeBlock(zero.data(),zero.size());
                }
                
                while (circBuff.getReadyToLastRead())
                {
                    circBuff.readLastBlock(dataiDecim.data());
                    
                    if (trInd&1 || trInd&4)
                    {
                        //расчет огибающей
                        magnitude_32fc(dataiDecim.data(),dataOgib.data(),fftsize);
                        //устраняем постоянную составляющую
                        constRemove_32f(dataOgib.data(), fftsize);
                    }
                    // 0
                    if (trInd&1)
                    {
                        //выполняем БПФ огибающей
                        fftwf_execute(planOgib);
                        //вычисляем амплитудный спектр огибающей
                        magnAddVec_32fc(currSpec.data(),meanSpecOgib.data(),fftsize/2);
                    }
                    
                    if (trInd&2)
                    {
                        //вычисляем модуль мгновенной частоты
                        freqDiscriminator32f(dataiDecim.data(),
                                             dataFreqDet.data(),
                                             fftsize,
                                             sampleFreqDecim,true);
                        
                        //устраняем постоянную составляющую
                        constRemove_32f(dataFreqDet.data(), fftsize);
                        //выполняем БПФ результата возведения в степень
                        fftwf_execute(planFreq);
                        //вычисляем амплитудный спектр
                        magnAddVec_32fc(currSpec.data(),meanSpecFreq.data(),fftsize/2);
                    }
                    
                    if (trInd&4)
                    {
                        //рассчет АКФ огибающей
                        acf_32f(dataOgib.data(),dataAcf.data(),fftsize);
                        //рачет производной АКФ
                        diffVec_32f(dataAcf.data(),dataAcfDiff.data(),fftsize);
                        //устраняем постоянную составляющую
                        constRemove_32f(dataAcfDiff.data(), fftsize);
                        //выполняем БПФ результата возведения в степень
                        fftwf_execute(planAcf);
                        //вычисляем амплитудный спектр производной АКФ
                        magnAddVec_32fc(currSpec.data(),meanSpecAcf.data(),fftsize/2);
                    }
                    
                    
                    //каждые полсекунды отправляем данные для отображения в
                    //интерфейсе пользователя
                    if (timer.elapsed() > 500)
                    {
                        int progress = int(100.*float(fpos-posInFile)/float(winsize));
                        emit sendProgress(progress);
                        
                        // emit sendGraficsTime1os(dataOgib.data(), fftsize/2, 0);
                        
                        emit sendGraficsTime1os(meanSpecAcf.data(), fftsize/2, 1);
                        
                        qDebug() << progress;
                        timer.restart();
                    }
                }
                
                
                
                if (isCancelled)
                {
                    isCancelled = false;
                    break;
                }
            }
            
            //нормируем амплитудный спектр поделив его на сумму амплитуд
            //спектральных составляющих
            
            if (trInd&1)
            {
                //нормируем по площади
                normalizeToSum_32f(meanSpecOgib.data(),
                                   sampleFreqDecim/fftsize,
                                   fftsize/2);
            }
            if (trInd&2)
            {
                //нормируем по площади
                normalizeToSum_32f(meanSpecFreq.data(),
                                   sampleFreqDecim/fftsize,
                                   fftsize/2);
            }
            if (trInd&4)
            {
                //нормируем по площади
                normalizeToSum_32f(meanSpecAcf.data(),
                                   sampleFreqDecim/fftsize,
                                   fftsize/2);
            }
            
            fftwf_destroy_plan(planFow);
            fftwf_destroy_plan(planInv);
            fftwf_destroy_plan(planOgib);
            fftwf_destroy_plan(planFreq);
            fftwf_destroy_plan(planAcf);
            
            file.close();
        }
        else
        {
            ERROROUT FileNotOpened;
            status = FileNotOpened;
        }
        
        osf.resize(fftsize/2);
        
        for (int i = 0; i < fftsize/2; i++)
        {
            osf[i] = i*sampleFreqDecim/fftsize;
        }
        
        emit sendProgress(0);
        
        if (trInd&1)
        {
            
            emit sendGraficsSpec2os(osf.data(),meanSpecOgib.data(), fftsize/2, 0);
        }
        if (trInd&2)
        {
            
            emit sendGraficsSpec2os(osf.data(),meanSpecFreq.data(), fftsize/2, 1);
        }
        if (trInd&4)
        {
            
            emit sendGraficsSpec2os(osf.data(),meanSpecAcf.data(), fftsize/2, 2);
        }
        
        
    }
    else
    {
        ERROROUT FileNotExist;
        status = FileNotExist;
    }
    
    
    return status;
    
}

/////////////////////////////////////////////////////////////////////////////////////
/*!
  \brief  Метод поблочного вычисления амплитудного  спектра 1, 2, 4 и 8 степеней
          сигнала
          
  Метод предназначена для поблочного  вычисления усредненного амплитудного  спектра
  1, 2, 4 и 8 степеньй сигнала с децимирующей фильтрацией. Функция возращает код
  ошибки ErrorCode_Ta.
  
  \param [out]  meanSpec1  усредненый амплитудный спектр сигнала
  \param [out]  meanSpec2  усредненый амплитудный спектр квадрата сигнала
  \param [out]  meanSpec4  усредненый амплитудный спектр четвертой степени сигнала
  \param [out]  meanSpec8  усредненый амплитудный спектр воьмой степени сигнала
  \param [out]  osf        вектор отсчетов оси частот
  \param [in]   fftsize    размер блока обработки, размер БПФ (степень двоики)
  \param [in]   trNum      флаг, каждый из младших четырех разрядов которого
                           определяет необходимость вычисления спектра каждой
                           из 4-х степеней. При trNum = 15, вычисляются все
                           спектры, при trNum = 8 - только спектр восьмой степени
                           сигнала
*/
/////////////////////////////////////////////////////////////////////////////////////

ErrorCode_Ta TaClass::getSpecOfSig(vector<float> &meanSpec1,
                                   vector<float> &meanSpec2,
                                   vector<float> &meanSpec4,
                                   vector<float> &meanSpec8,
                                   vector<float> &osf,
                                   int fftsize, uint8_t trInd)
{
    ErrorCode_Ta status;
    
    //проверка корректности входных параметров
    int ord = getOrder2(fftsize);
    if (ord < 6 || ord > 24)
    {
        ERROROUT InvalidFFTsize;
        return InvalidFFTsize;
    }
    
    if (sampleFreq < 1)
    {
        ERROROUT InvalidSampleRate;
        return  InvalidSampleRate;
    }
    
    if (trInd < 1 || trInd > 15)
    {
        ERROROUT InvalidTransformNum;
        return InvalidTransformNum;
    }
    
    isCancelled = false;
    
    //импульсная характеристика фильтра
    vector< complex<float> > imphar32fc;
    //АЧХ фильтра
    vector<complex <float> > achFilt;
    
    float sampleFreqDecim = sampleFreq;
    
    meanSpec1.resize(fftsize);
    meanSpec2.resize(fftsize);
    meanSpec4.resize(fftsize);
    meanSpec8.resize(fftsize);
    memset(meanSpec1.data(),0,sizeof(float)*fftsize);
    memset(meanSpec2.data(),0,sizeof(float)*fftsize);
    memset(meanSpec4.data(),0,sizeof(float)*fftsize);
    memset(meanSpec8.data(),0,sizeof(float)*fftsize);
    
    int implen = 0;
    
    //проверка необходимости фильтрации
    if (bandwith > 0)
    {
        status = isCorrectFreqPrms();
        if (status != NoError)
            return status;
        
        //формируем комплексную импульсную характеристику
        imphar32fc = genRCosFIRLowpassOnSymbsCmplx(5, bandwith,
                                                   sampleFreq, 0.35, true);
        
        implen = imphar32fc.size();
        
        int s = imphar32fc.size();
        //если длина имп.хар-ки больше fftsize
        if (s > fftsize)
        {
            //уменьшаем длину имп. хар-ки
            imphar32fc = genRCosFIRLowpassOnSampsCmplx(fftsize-1,
                                                       bandwith/sampleFreq,
                                                       0.35, true);
        }
        else if (s < fftsize)
        {
            //добавляем нули к имп.хар-ки
            imphar32fc.resize(fftsize);
            memset((char*)(imphar32fc.data() + s ), 0 ,sizeof(float)*2);
        }
        
        float fimp = centerFreq/sampleFreq;
        qint64 tb = 0;
        //переносим центральную частоту АЧХ фильтра на частоту сигнала
        freqTranslate_32fc(imphar32fc.data(), fimp, fftsize, &tb);
        
        achFilt.resize(fftsize);
        
        //расчитываем АЧХ фильтра
        getFilterAFR_32fc(imphar32fc.data(),achFilt.data(), fftsize);
    }
    
    QFile file(filename);
    if (file.exists())
    {
        if (getSamplesCnt(format,file.size()) < fftsize)
        {
            ERROROUT InvalidFFTsize << " fftsize > size of file";
            status = InvalidFFTsize;
        }
        
        if (getSamplesCnt(format, winsize) < fftsize)
        {
            ERROROUT InvalidWinSize << " fftsize > winsize";
            status = InvalidWinSize;
        }
        
        if (winsize > file.size())
        {
            ERROROUT InvalidWinSize << " winsize > size of file";
            status = InvalidWinSize;
        }
        
        
        if (file.open(QIODevice::ReadOnly))
        {
            if (winsize == 0)
                winsize = file.size();
            
            //implen = fftsize/2;
            
            //вектор входных данных, читаемых их файла
            vector<complex <float> > datain(fftsize);
            
            //текущий комплексный спектр
            vector<complex <float> > currSpecFilt(fftsize);
            
            //децимированные данные
            vector<complex <float> > dataiDecim(fftsize);
            
            //текущий комплексный спектр
            vector<complex <float> > currSpec(fftsize);
            
            //план прямого БПФ
            fftwf_plan planFow = fftwf_plan_dft_1d(fftsize,
                                                   (fftwf_complex*) datain.data(),
                                                   (fftwf_complex*) currSpecFilt.data(),
                                                   FFTW_FORWARD, FFTW_ESTIMATE);
            //план обратного БПФ для фильтрации
            fftwf_plan planInv = fftwf_plan_dft_1d(fftsize,
                                                   (fftwf_complex*) currSpecFilt.data(),
                                                   (fftwf_complex*) datain.data(),
                                                   FFTW_BACKWARD, FFTW_ESTIMATE);
            
            //план прямого БПФ
            fftwf_plan planFowDec = fftwf_plan_dft_1d(fftsize,
                                                      (fftwf_complex*) dataiDecim.data(),
                                                      (fftwf_complex*) currSpec.data(),
                                                      FFTW_FORWARD, FFTW_ESTIMATE);
            
            //таймер нужен для отправки сигналов через определенные интервалы времени,
            //а не постоянно
            QElapsedTimer timer;
            timer.start();
            
            qint64 fpos = posInFile;
            int ostatok = 0;
            qint64 tsample = 0;
            
            //Кольцевой буфер
            CircBuffer< complex<float> > circBuff(fftsize*16,fftsize);
            
            
            ErrorCode_Ta statusFile = NoError;
            
            while (!file.atEnd() && (fpos < (posInFile + winsize)) && statusFile != EndOfFile)
            {
                
                /* Чтение данных из файла и одновременная конвертация отчетов
                 * при необходимости*/
                statusFile = readAndConvert(file, datain , &fpos,
                                            format, implen);//,
                
                int coefDecim = 0;
                
                //если нужно фильтровать
                if (!imphar32fc.empty())
                {
                    /* Начало фильтрации сигнала */
                    
                    //расчитываем спектр текущего фрагмента сигнала
                    fftwf_execute(planFow);
                    //перемножаем спектр сигнала на АЧХ фильтра
                    multVec_32fc_I(achFilt.data(),currSpecFilt.data(),fftsize);
                    //расчитываем ОБПФ результата перемножения
                    fftwf_execute(planInv);
                    //нормируем результат ОБПФ, поделив на размер, получив
                    //т.о. результат фильтрации
                    divVecC_32fc_I(float(fftsize),datain.data(),fftsize);
                    
                    coefDecim = sampleFreq/(4*bandwith);
                    
                    
                    /* Конец фильтрации сигнала */
                }
                
                //переносим сигнал на нулевую частоту
                freqTranslate_32fc(datain.data()+implen,-centerFreq/sampleFreq,
                                   fftsize-implen, &tsample);
                
                
                //если надо децимировать
                if (coefDecim > 1)
                {
                    //memset(dataiDecim.data(),0,sizeof (float)*2*fftsize);
                    for (int i = implen+ostatok, c = 0; i < fftsize; i+=coefDecim,c++)
                    {
                        
                        circBuff.writeBlock(datain.data()+i,1);
                        ostatok = i;
                    }
                    ostatok = coefDecim - (fftsize - ostatok);
                    sampleFreqDecim = sampleFreq/coefDecim;
                }
                else //если не надо децимировать
                {
                    circBuff.writeBlock(datain.data()+implen,fftsize-implen);
                    sampleFreqDecim = sampleFreq;
                }
                
                
                bool isEndRead = (fpos >= (posInFile + winsize)) || (statusFile == EndOfFile);
                
                if (isEndRead && !circBuff.getReadyToLastRead())
                {
                    int cnt  = circBuff.getQueueSize();
                    vector<complex<float> > zero(fftsize-cnt+1);
                    memset(zero.data(),0,zero.size()*sizeof (float)*2);
                    circBuff.writeBlock(zero.data(),zero.size());
                }
                
                while (circBuff.getReadyToLastRead())
                {
                    circBuff.readLastBlock(dataiDecim.data());
                    
                    // 0
                    if (trInd&1)
                    {
                        //выполняем БПФ результата возведения в степень
                        fftwf_execute(planFowDec);
                        //вычисляем амплитудный спектр
                        magnAddVec_32fc(currSpec.data(),meanSpec1.data(),fftsize);
                    }
                    
                    // 2
                    if (trInd&2 || trInd&4 || trInd&8)
                    {
                        powVec_32fc_I(dataiDecim.data(),2,fftsize);
                        normalizeToValue_32f((float*)dataiDecim.data(),32768/2,fftsize*2);
                    }
                    if (trInd&2)
                    {
                        //выполняем БПФ результата возведения в степень
                        fftwf_execute(planFowDec);
                        //вычисляем амплитудный спектр
                        magnAddVec_32fc(currSpec.data(),meanSpec2.data(),fftsize);
                    }
                    
                    // 4
                    if (trInd&4 || trInd&8)
                    {
                        powVec_32fc_I(dataiDecim.data(),2,fftsize);
                        normalizeToValue_32f((float*)dataiDecim.data(),32768/2,fftsize*2);
                    }
                    if (trInd&4)
                    {
                        //выполняем БПФ результата возведения в степень
                        fftwf_execute(planFowDec);
                        //вычисляем амплитудный спектр
                        magnAddVec_32fc(currSpec.data(),meanSpec4.data(),fftsize);
                    }
                    
                    // 8
                    if (trInd&8)
                    {
                        powVec_32fc_I(dataiDecim.data(),2,fftsize);
                        normalizeToValue_32f((float*)dataiDecim.data(),32768/2,fftsize*2);
                        //выполняем БПФ результата возведения в степень
                        fftwf_execute(planFowDec);
                        //вычисляем амплитудный спектр
                        magnAddVec_32fc(currSpec.data(),meanSpec8.data(),fftsize);
                    }
                    
                    
                    //каждые полсекунды отправляем данные для отображения в
                    //интерфейсе пользователя
                    if (timer.elapsed() > 1000)
                    {
                        int progress = int(100.*float(fpos-posInFile)/float(winsize));
                        emit sendProgress(progress);
                        
                        qDebug() << progress;
                        timer.restart();
                    }
                }
            }
            
            //нормируем амплитудный спектр поделив его на сумму амплитуд
            //спектральных составляющих
            
            if (trInd&1)
            {
                normalizeToSum_32f(meanSpec1.data(),
                                   sampleFreqDecim/fftsize,
                                   fftsize);
            }
            if (trInd&2)
            {
                normalizeToSum_32f(meanSpec2.data(),
                                   sampleFreqDecim/fftsize,
                                   fftsize);
            }
            if (trInd&4)
            {
                normalizeToSum_32f(meanSpec4.data(),
                                   sampleFreqDecim/fftsize,
                                   fftsize);
            }
            if (trInd&8)
            {
                normalizeToSum_32f(meanSpec8.data(),
                                   sampleFreqDecim/fftsize,
                                   fftsize);
            }
            
            fftwf_destroy_plan(planFow);
            fftwf_destroy_plan(planInv);
            fftwf_destroy_plan(planFowDec);
            
            file.close();
            
            osf.resize(fftsize);
            
            for (int i = 0; i < fftsize; i++)
            {
                osf[i] = i*sampleFreqDecim/fftsize - sampleFreqDecim/2;
            }
            
            emit sendProgress(0);
            
            
            if (trInd&1)
            {
                fftShift_32f(meanSpec1.data(), fftsize);
                emit sendGraficsSpec2os(osf.data(),meanSpec1.data(), fftsize, 0);
            }
            if (trInd&2)
            {
                fftShift_32f(meanSpec2.data(), fftsize);
                emit sendGraficsSpec2os(osf.data(),meanSpec2.data(), fftsize, 1);
            }
            if (trInd&4)
            {
                fftShift_32f(meanSpec4.data(), fftsize);
                emit sendGraficsSpec2os(osf.data(),meanSpec4.data(), fftsize, 2);
            }
            if (trInd&8)
            {
                fftShift_32f(meanSpec8.data(), fftsize);
                emit sendGraficsSpec2os(osf.data(),meanSpec8.data(), fftsize, 3);
            }
        }
        else
        {
            ERROROUT FileNotOpened;
            status = FileNotOpened;
        }
        
    }
    else
    {
        ERROROUT FileNotExist;
        status = FileNotExist;
    }
    
    
    return status;
}

/////////////////////////////////////////////////////////////////////////////////////
/*!
  \brief  Метод поблочного вычисления амплитудного  спектра 1, 2, 4 и 8 степеней
          сигнала
          
  Метод предназначена для поблочного  вычисления усредненного амплитудного  спектра
  1, 2, 4 и 8 степеньй сигнала с децимирующей фильтрацией. Функция возращает код
  ошибки ErrorCode_Ta.
  
  \param [out]  1111  усредненый амплитудный спектр сигнала
  \param [out]  11111  усредненый амплитудный спектр квадрата сигнала
  \param [out]  1111222  усредненый амплитудный спектр четвертой степени сигнала
  \param [out]  55555555555555555  усредненый амплитудный спектр воьмой степени сигнала
  \param [out]  5555555555555555555        вектор отсчетов оси частот
  \param [in]   55555555555    размер блока обработки, размер БПФ (степень двоики)
  \param [in]   555555555555      флаг, каждый из младших четырех разрядов которого
                           определяет необходимость вычисления спектра каждой
                           из 4-х степеней. При trNum = 15, вычисляются все
                           спектры, при trNum = 8 - только спектр восьмой степени
                           сигнала
*/
/////////////////////////////////////////////////////////////////////////////////////
ErrorCode_Ta TaClass::getMagnDetectOut(vector<float> &magn,
                                       vector<float> &ost,
                                       vector<float> &acf,
                                       vector<float> &ostacf,
                                       vector<float> &hist,
                                       vector<float> &osxhist,
                                       int fftsize,
                                       int trInd)
{
    ErrorCode_Ta status;
    
    //проверка корректности входных параметров
    int ord = getOrder2(fftsize);
    if (ord < 6 || ord > 24)
    {
        ERROROUT InvalidFFTsize;
        return InvalidFFTsize;
    }
    
    if (sampleFreq < 1)
    {
        ERROROUT InvalidSampleRate;
        return  InvalidSampleRate;
    }
    
    if (trInd < 0 || trInd > 3)
    {
        ERROROUT InvalidTransformNum;
        return InvalidTransformNum;
    }
    
    
    isCancelled = false;
    
    //импульсная характеристика фильтра
    vector< complex<float> > imphar32fc;
    //АЧХ фильтра
    vector<complex <float> > achFilt;
    
    float sampleFreqDecim = sampleFreq;
    
    int coefDecim = 0;
    
    
    magn.clear();
    ost.clear();
    acf.clear();
    ostacf.clear();
    hist.clear();
    osxhist.clear();
    
    magn.shrink_to_fit();
    ost.shrink_to_fit();
    acf.shrink_to_fit();
    ostacf.shrink_to_fit();
    hist.shrink_to_fit();
    osxhist.shrink_to_fit();
    
    
    
    int implen = 0;
    uint32_t capacitySize = 0;
    
    //проверка необходимости фильтрации
    if (bandwith > 0)
    {
        status = isCorrectFreqPrms();
        if (status != NoError)
            return status;
        
        //формируем комплексную импульсную характеристику
        imphar32fc = genRCosFIRLowpassOnSymbsCmplx(5, bandwith,
                                                   sampleFreq, 0.35, true);
        
        implen = imphar32fc.size()+1;
        
        int s = imphar32fc.size();
        //если длина имп.хар-ки больше fftsize
        if (s > fftsize)
        {
            //уменьшаем длину имп. хар-ки
            imphar32fc = genRCosFIRLowpassOnSampsCmplx(fftsize-1,
                                                       bandwith/sampleFreq,
                                                       0.35, true);
        }
        else if (s < fftsize)
        {
            //добавляем нули к имп.хар-ки
            imphar32fc.resize(fftsize);
            memset((char*)(imphar32fc.data() + s ), 0 ,sizeof(float)*2);
        }
        
        float fimp = centerFreq/sampleFreq;
        qint64 tb = 0;
        //переносим центральную частоту АЧХ фильтра на частоту сигнала
        freqTranslate_32fc(imphar32fc.data(), fimp, fftsize, &tb);
        
        achFilt.resize(fftsize);
        
        //расчитываем АЧХ фильтра
        getFilterAFR_32fc(imphar32fc.data(),achFilt.data(), fftsize);
        
        int coefDecim = sampleFreq/(4*bandwith);
        if (coefDecim < 1)
            coefDecim = 1;
        
        qint64 needcnt = getSamplesCnt(format,winsize)/coefDecim;
        if (needcnt > magn.max_size())
            needcnt = magn.max_size();
        if (needcnt < fftsize)
            needcnt = fftsize;
        capacitySize = uint32_t(needcnt);
        
        qDebug() << "needcnt " << needcnt;
        
        rezerveMemoryForVec(magn,&capacitySize);
        rezerveMemoryForVec(ost,&capacitySize);
        rezerveMemoryForVec(acf,&capacitySize);
        rezerveMemoryForVec(ostacf,&capacitySize);
    }
    else
    {
        qint64 needcnt = getSamplesCnt(format,winsize);
        
        qDebug() << "needcnt " << needcnt;
        
        if (needcnt > magn.max_size())
            needcnt = magn.max_size();
        if (needcnt < fftsize)
            needcnt = fftsize;
        capacitySize = uint32_t(needcnt);
        
        rezerveMemoryForVec(magn,&capacitySize);
        rezerveMemoryForVec(ost,&capacitySize);
        rezerveMemoryForVec(acf,&capacitySize);
        rezerveMemoryForVec(ostacf,&capacitySize);
    }
    
    qDebug() << "capacitySize " << capacitySize;
    qDebug() << "freqs.capacity " << magn.capacity();
    
    
    QFile file(filename);
    if (file.exists())
    {
        
        if (getSamplesCnt(format,file.size()) < fftsize)
        {
            ERROROUT InvalidFFTsize << " fftsize > size of file";
            status = InvalidFFTsize;
        }
        
        if (getSamplesCnt(format, winsize) < fftsize)
        {
            ERROROUT InvalidWinSize << " fftsize > winsize";
            status = InvalidWinSize;
        }
        
        if (winsize > file.size())
        {
            ERROROUT InvalidWinSize << " winsize > size of file";
            status = InvalidWinSize;
        }
        
        if (file.open(QIODevice::ReadOnly))
        {
            if (winsize == 0)
                winsize = file.size();
            
            //implen = fftsize/2;
            
            //вектор входных данных, читаемых их файла
            vector<complex <float> > datain(fftsize);
            
            //текущий комплексный спектр
            vector<complex <float> > currSpecFilt(fftsize);
            
            //децимированные данные
            vector<complex <float> > dataiDecim(fftsize);
            
            
            //Огибающая  сигнала
            vector<float>  dataMagnDet(fftsize);
            
            
            //план прямого БПФ для фильтрации
            fftwf_plan planFow = fftwf_plan_dft_1d(fftsize,
                                                   (fftwf_complex*) datain.data(),
                                                   (fftwf_complex*) currSpecFilt.data(),
                                                   FFTW_FORWARD, FFTW_ESTIMATE);
            //план обратного БПФ для фильтрации
            fftwf_plan planInv = fftwf_plan_dft_1d(fftsize,
                                                   (fftwf_complex*) currSpecFilt.data(),
                                                   (fftwf_complex*) datain.data(),
                                                   FFTW_BACKWARD, FFTW_ESTIMATE);
            
            //таймер нужен для отправки сигналов через определенные интервалы времени,
            //а не постоянно
            QElapsedTimer timer;
            timer.start();
            
            qint64 fpos = posInFile;
            int ostatok = 0;
            qint64 tsample = 0;
            
            int zerosCnt = 0;
            
            //Кольцевой буфер
            CircBuffer< complex<float> > circBuff(fftsize*16,fftsize);
            
            ErrorCode_Ta statusFile = NoError;
            
            while (!file.atEnd() && (fpos < (posInFile + winsize)) && statusFile != EndOfFile)
            {
                
                /* Чтение данных из файла и одновременная конвертация отчетов
                 * при необходимости*/
                statusFile = readAndConvert(file, datain , &fpos, format, implen);
                
                
                
                //если нужно фильтровать
                if (!imphar32fc.empty())
                {
                    /* Начало фильтрации сигнала */
                    
                    //расчитываем спектр текущего фрагмента сигнала
                    fftwf_execute(planFow);
                    //перемножаем спектр сигнала на АЧХ фильтра
                    multVec_32fc_I(achFilt.data(),currSpecFilt.data(),fftsize);
                    //расчитываем ОБПФ результата перемножения
                    fftwf_execute(planInv);
                    //нормируем результат ОБПФ, поделив на размер, получив
                    //т.о. результат фильтрации
                    divVecC_32fc_I(float(fftsize),datain.data(),fftsize);
                    
                    coefDecim = sampleFreq/(4*bandwith);
                    sampleFreqDecim = sampleFreq/coefDecim;
                    
                    /* Конец фильтрации сигнала */
                    //переносим сигнал на нулевую частоту
                    freqTranslate_32fc(datain.data()+implen,-centerFreq/sampleFreq,
                                       fftsize-implen, &tsample);
                    
                }
                
                //если надо децимировать
                if (coefDecim > 1)
                {
                    //memset(dataiDecim.data(),0,sizeof (float)*2*fftsize);
                    for (int i = implen+ostatok, c = 0; i < fftsize; i+=coefDecim,c++)
                    {
                        
                        circBuff.writeBlock(datain.data()+i,1);
                        ostatok = i;
                    }
                    ostatok = coefDecim - (fftsize - ostatok);
                }
                else //если не надо децимировать
                {
                    circBuff.writeBlock(datain.data()+implen,fftsize-implen);
                    sampleFreqDecim = sampleFreq;
                }
                
                
                bool isEndRead = (fpos >= (posInFile + winsize)) || (statusFile == EndOfFile);
                
                
                if (isEndRead && !circBuff.getReadyToLastRead())
                {
                    int cnt  = circBuff.getQueueSize();
                    vector<complex<float> > zero(fftsize-cnt+1);
                    zerosCnt = fftsize-cnt+1;
                    memset(zero.data(),0,zero.size()*sizeof (float)*2);
                    circBuff.writeBlock(zero.data(),zero.size());
                }
                
                uint32_t newsize = 0;
                while (circBuff.getReadyToLastRead())
                {
                    circBuff.readLastBlock(dataiDecim.data());
                    
                    //вычисляем огибающую
                    magnitude_32fc(dataiDecim.data(),
                                   dataMagnDet.data(),
                                   fftsize);
                    
                    float lastTime = 0;
                    int   sch = 0;
                    if (!ost.empty())
                    {
                        lastTime = ost[ost.size()-1];
                        sch = magn.size();
                    }
                    newsize = magn.size() + dataMagnDet.size();
                    if (newsize > capacitySize)
                    {
                        qDebug() << "Переполнение вектора...";
                        qDebug() << "newsize " << newsize;
                        qDebug() << "capacitySize " << capacitySize;
                        break;
                    }
                    magn.resize(newsize);
                    ost.resize(newsize);
                    
                    memcpy(magn.data() + newsize - fftsize,
                           dataMagnDet.data(),fftsize*sizeof (float));
                    for (int i = 0; i < fftsize; i++)
                    {
                        ost[sch + i] = lastTime + float(i)/sampleFreqDecim;
                    }
                    
                    
                    //каждые полсекунды отправляем данные для отображения в
                    //интерфейсе пользователя
                    if (timer.elapsed() > 500)
                    {
                        int progress = int(100.*float(fpos-posInFile)/float(winsize));
                        emit sendProgress(progress);
                        
                        qDebug() << progress;
                        timer.restart();
                    }
                }
                
                if (newsize > capacitySize)
                    break;
                
                if (isCancelled)
                {
                    isCancelled = false;
                    break;
                }
            }
            
            //нормируем амплитудный спектр поделив его на сумму амплитуд
            //спектральных составляющих
            
            
            magn[0] = magn[1];
            if (zerosCnt)
                magn.resize(magn.size() - zerosCnt);
            
            
            if (trInd&1)
            {
                qDebug() << "Расчет АКФ мгновенной частоты";
                int size = magn.size();
                if (size%2 != 0)
                    size = (size/2)*2;
                acf.resize(size);
                ostacf.resize(size);
                //рассчет АКФ мгновенной частоты
                qDebug() << "Размер вектора " << size;
                acf_32f(magn.data(),acf.data(),size);
                normalizeToValue_32f(acf.data(),1,acf.size());
                fftShift_32f(acf.data(),acf.size());
                
                for (int i = 0; i < int(size); i++)
                {
                    ostacf[i] = float(i)/sampleFreqDecim - float(magn.size())/sampleFreqDecim/2.;
                }
            }
            
            if (trInd&2)
            {
                qDebug() << "Расчет гистограммы мгновенной частоты";
                float maxv, minv;
                int index;
                maxIndex_32f(magn.data(),magn.size(),&maxv,&index);
                minIndex_32f(magn.data(),magn.size(),&minv,&index);
                float delta = (maxv-minv)/100.;
                int histsize = int((maxv-minv+delta)/delta);
                hist.resize(histsize);
                for (float x = minv; x <= maxv;  x+=delta)
                    osxhist.push_back(x);
                
                histDeltaOpt(hist.data(),magn.data(), magn.size(),
                             minv, delta, maxv);
            }
            
            
            fftwf_destroy_plan(planFow);
            fftwf_destroy_plan(planInv);
            file.close();
        }
        else
        {
            ERROROUT FileNotOpened;
            status = FileNotOpened;
        }
        
        emit sendProgress(0);
        
    }
    else
    {
        ERROROUT FileNotExist;
        status = FileNotExist;
    }
    
    return status;
}

/////////////////////////////////////////////////////////////////////////////////////
/*!
  \brief  Метод поблочного вычисления амплитудного  спектра 1, 2, 4 и 8 степеней
          сигнала
          
  Метод предназначена для поблочного  вычисления усредненного амплитудного  спектра
  1, 2, 4 и 8 степеньй сигнала с децимирующей фильтрацией. Функция возращает код
  ошибки ErrorCode_Ta.
  
  \param [out]  1111  усредненый амплитудный спектр сигнала
  \param [out]  11111  усредненый амплитудный спектр квадрата сигнала
  \param [out]  1111222  усредненый амплитудный спектр четвертой степени сигнала
  \param [out]  55555555555555555  усредненый амплитудный спектр воьмой степени сигнала
  \param [out]  5555555555555555555        вектор отсчетов оси частот
  \param [in]   55555555555    размер блока обработки, размер БПФ (степень двоики)
  \param [in]   555555555555      флаг, каждый из младших четырех разрядов которого
                           определяет необходимость вычисления спектра каждой
                           из 4-х степеней. При trNum = 15, вычисляются все
                           спектры, при trNum = 8 - только спектр восьмой степени
                           сигнала
*/
/////////////////////////////////////////////////////////////////////////////////////
ErrorCode_Ta TaClass::getFreqDetectOut(vector<float> &freqs,
                                       vector<float> &ostfreq,
                                       vector<float> &acf,
                                       vector<float> &ostacf,
                                       vector<float> &hist,
                                       vector<float> &osxhist,
                                       int fftsize,
                                       int trInd)
{
    ErrorCode_Ta status;
    
    //проверка корректности входных параметров
    int ord = getOrder2(fftsize);
    if (ord < 6 || ord > 24)
    {
        ERROROUT InvalidFFTsize;
        return InvalidFFTsize;
    }
    
    if (sampleFreq < 1)
    {
        ERROROUT InvalidSampleRate;
        return  InvalidSampleRate;
    }
    
    if (trInd < 0 || trInd > 3)
    {
        ERROROUT InvalidTransformNum;
        return InvalidTransformNum;
    }
    
    
    isCancelled = false;
    
    //импульсная характеристика фильтра
    vector< complex<float> > imphar32fc;
    //АЧХ фильтра
    vector<complex <float> > achFilt;
    
    float sampleFreqDecim = sampleFreq;
    int coefDecim = 0;
    
    
    freqs.clear();
    ostfreq.clear();
    acf.clear();
    ostacf.clear();
    hist.clear();
    osxhist.clear();
    
    freqs.shrink_to_fit();
    ostfreq.shrink_to_fit();
    acf.shrink_to_fit();
    ostacf.shrink_to_fit();
    hist.shrink_to_fit();
    osxhist.shrink_to_fit();
    
    int implen = 0;
    uint32_t capacitySize = 0;
    
    //проверка необходимости фильтрации
    if (bandwith > 0)
    {
        status = isCorrectFreqPrms();
        if (status != NoError)
            return status;
        
        //формируем комплексную импульсную характеристику
        imphar32fc = genRCosFIRLowpassOnSymbsCmplx(5, bandwith,
                                                   sampleFreq, 0.35, true);
        
        implen = imphar32fc.size()+1;
        
        int s = imphar32fc.size();
        //если длина имп.хар-ки больше fftsize
        if (s > fftsize)
        {
            //уменьшаем длину имп. хар-ки
            imphar32fc = genRCosFIRLowpassOnSampsCmplx(fftsize-1,
                                                       bandwith/sampleFreq,
                                                       0.35, true);
        }
        else if (s < fftsize)
        {
            //добавляем нули к имп.хар-ки
            imphar32fc.resize(fftsize);
            memset((char*)(imphar32fc.data() + s ), 0 ,sizeof(float)*2);
        }
        
        float fimp = centerFreq/sampleFreq;
        qint64 tb = 0;
        //переносим центральную частоту АЧХ фильтра на частоту сигнала
        freqTranslate_32fc(imphar32fc.data(), fimp, fftsize, &tb);
        
        achFilt.resize(fftsize);
        
        //расчитываем АЧХ фильтра
        getFilterAFR_32fc(imphar32fc.data(),achFilt.data(), fftsize);
        
        
        int coefDecim = sampleFreq/(4*bandwith);
        if (coefDecim < 1)
            coefDecim = 1;
        
        qint64 needcnt = getSamplesCnt(format,winsize)/coefDecim;
        if (needcnt > freqs.max_size())
            needcnt = freqs.max_size();
        if (needcnt < fftsize)
            needcnt = fftsize;
        
        capacitySize = uint32_t(needcnt);
        
        qDebug() << "needcnt " << needcnt;
        
        rezerveMemoryForVec(freqs,&capacitySize);
        rezerveMemoryForVec(ostfreq,&capacitySize);
        rezerveMemoryForVec(acf,&capacitySize);
        rezerveMemoryForVec(ostacf,&capacitySize);
        
    }
    else
    {
        qint64 needcnt = getSamplesCnt(format,winsize);
        
        qDebug() << "needcnt " << needcnt;
        
        if (needcnt > freqs.max_size())
            needcnt = freqs.max_size();
        if (needcnt < fftsize)
            needcnt = fftsize;
        
        capacitySize = uint32_t(needcnt);
        
        rezerveMemoryForVec(freqs,&capacitySize);
        rezerveMemoryForVec(ostfreq,&capacitySize);
        rezerveMemoryForVec(acf,&capacitySize);
        rezerveMemoryForVec(ostacf,&capacitySize);
    }
    qDebug() << "capacitySize " << capacitySize;
    qDebug() << "freqs.capacity " << freqs.capacity();
    
    QFile file(filename);
    if (file.exists())
    {
        
        if (getSamplesCnt(format,file.size()) < fftsize)
        {
            ERROROUT InvalidFFTsize << " fftsize > size of file";
            status = InvalidFFTsize;
        }
        
        if (getSamplesCnt(format, winsize) < fftsize)
        {
            ERROROUT InvalidWinSize << " fftsize > winsize";
            status = InvalidWinSize;
        }
        
        if (winsize > file.size())
        {
            ERROROUT InvalidWinSize << " winsize > size of file";
            status = InvalidWinSize;
        }
        
        if (file.open(QIODevice::ReadOnly))
        {
            if (winsize == 0)
                winsize = file.size();
            
            //implen = fftsize/2;
            
            //вектор входных данных, читаемых их файла
            vector<complex <float> > datain(fftsize);
            
            //текущий комплексный спектр
            vector<complex <float> > currSpecFilt(fftsize);
            
            //децимированные данные
            vector<complex <float> > dataiDecim(fftsize);
            
            
            //Мгновенная частота сигнала
            vector<float>  dataFreqDet(fftsize);
            
            
            //план прямого БПФ для фильтрации
            fftwf_plan planFow = fftwf_plan_dft_1d(fftsize,
                                                   (fftwf_complex*) datain.data(),
                                                   (fftwf_complex*) currSpecFilt.data(),
                                                   FFTW_FORWARD, FFTW_ESTIMATE);
            //план обратного БПФ для фильтрации
            fftwf_plan planInv = fftwf_plan_dft_1d(fftsize,
                                                   (fftwf_complex*) currSpecFilt.data(),
                                                   (fftwf_complex*) datain.data(),
                                                   FFTW_BACKWARD, FFTW_ESTIMATE);
            
            //таймер нужен для отправки сигналов через определенные интервалы времени,
            //а не постоянно
            QElapsedTimer timer;
            timer.start();
            
            qint64 fpos = posInFile;
            int ostatok = 0;
            qint64 tsample = 0;
            float lastPhase = 0;
            int zerosCnt = 0;
            
            //Кольцевой буфер
            CircBuffer< complex<float> > circBuff(fftsize*16,fftsize);
            
            ErrorCode_Ta statusFile = NoError;
            
            while (!file.atEnd() && (fpos < (posInFile + winsize)) && statusFile != EndOfFile)
            {
                
                /* Чтение данных из файла и одновременная конвертация отчетов
                 * при необходимости*/
                statusFile = readAndConvert(file, datain , &fpos, format, implen);
                
                //если нужно фильтровать
                if (!imphar32fc.empty())
                {
                    /* Начало фильтрации сигнала */
                    
                    //расчитываем спектр текущего фрагмента сигнала
                    fftwf_execute(planFow);
                    //перемножаем спектр сигнала на АЧХ фильтра
                    multVec_32fc_I(achFilt.data(),currSpecFilt.data(),fftsize);
                    //расчитываем ОБПФ результата перемножения
                    fftwf_execute(planInv);
                    //нормируем результат ОБПФ, поделив на размер, получив
                    //т.о. результат фильтрации
                    divVecC_32fc_I(float(fftsize),datain.data(),fftsize);
                    
                    coefDecim = sampleFreq/(4*bandwith);
                    sampleFreqDecim = sampleFreq/coefDecim;
                    
                    /* Конец фильтрации сигнала */
                    //переносим сигнал на нулевую частоту
                    freqTranslate_32fc(datain.data()+implen,-centerFreq/sampleFreq,
                                       fftsize-implen, &tsample);
                    
                }
                
                
                //если надо децимировать
                if (coefDecim > 1)
                {
                    //memset(dataiDecim.data(),0,sizeof (float)*2*fftsize);
                    for (int i = implen+ostatok, c = 0; i < fftsize; i+=coefDecim,c++)
                    {
                        
                        circBuff.writeBlock(datain.data()+i,1);
                        ostatok = i;
                    }
                    ostatok = coefDecim - (fftsize - ostatok);
                }
                else //если не надо децимировать
                {
                    circBuff.writeBlock(datain.data()+implen,fftsize-implen);
                    sampleFreqDecim = sampleFreq;
                }
                
                
                bool isEndRead = (fpos >= (posInFile + winsize)) || (statusFile == EndOfFile);
                
                
                if (isEndRead && !circBuff.getReadyToLastRead())
                {
                    int cnt  = circBuff.getQueueSize();
                    vector<complex<float> > zero(fftsize-cnt+1);
                    zerosCnt = fftsize-cnt+1;
                    memset(zero.data(),0,zero.size()*sizeof (float)*2);
                    circBuff.writeBlock(zero.data(),zero.size());
                }
                
                uint32_t newsize = 0;
                while (circBuff.getReadyToLastRead())
                {
                    circBuff.readLastBlock(dataiDecim.data());
                    
                    //вычисляем модуль мгновенной частоты
                    freqDiscriminator32f(dataiDecim.data(),
                                         dataFreqDet.data(),
                                         fftsize,
                                         sampleFreqDecim,false, &lastPhase);
                    
                    float lastTime = 0;
                    int   sch = 0;
                    if (!ostfreq.empty())
                    {
                        lastTime = ostfreq[ostfreq.size()-1];
                        sch = freqs.size();
                    }
                    newsize = freqs.size() + dataFreqDet.size();
                    if (newsize > capacitySize)
                    {
                        qDebug() << "Переполнение вектора...";
                        qDebug() << "newsize " << newsize;
                        qDebug() << "capacitySize " << capacitySize;
                        break;
                    }
                    
                    
                    freqs.resize(newsize);
                    ostfreq.resize(newsize);
                    
                    memcpy(freqs.data() + newsize - fftsize,
                           dataFreqDet.data(),fftsize*sizeof (float));
                    for (int i = 0; i < fftsize; i++)
                    {
                        ostfreq[sch + i] = lastTime + float(i)/sampleFreqDecim;
                    }
                    
                    
                    //каждые полсекунды отправляем данные для отображения в
                    //интерфейсе пользователя
                    if (timer.elapsed() > 500)
                    {
                        int progress = int(100.*float(fpos-posInFile)/float(winsize));
                        emit sendProgress(progress);
                        qDebug() << progress;
                        timer.restart();
                    }
                }
                if (newsize > capacitySize)
                    break;
                
                if (isCancelled)
                {
                    isCancelled = false;
                    break;
                }
            }
            
            //нормируем амплитудный спектр поделив его на сумму амплитуд
            //спектральных составляющих
            
            
            freqs[0] = freqs[1];
            if (zerosCnt)
                freqs.resize(freqs.size() - zerosCnt);
            freqs[freqs.size()-1] = freqs[freqs.size()-2];
            
            if (trInd&1)
            {
                qDebug() << "Расчет АКФ мгновенной частоты";
                int size = freqs.size();
                if (size%2 != 0)
                    size = (size/2)*2;
                acf.resize(size);
                ostacf.resize(size);
                //рассчет АКФ мгновенной частоты
                qDebug() << "Размер вектора " << size;
                acf_32f(freqs.data(),acf.data(),size);
                normalizeToValue_32f(acf.data(),1,acf.size());
                fftShift_32f(acf.data(),acf.size());
                
                for (int i = 0; i < int(size); i++)
                {
                    ostacf[i] = float(i)/sampleFreqDecim - float(freqs.size())/sampleFreqDecim/2.;
                }
            }
            
            
            if (trInd&2)
            {
                qDebug() << "Расчет гистограммы мгновенной частоты";
                float maxv, minv;
                int index;
                maxIndex_32f(freqs.data(),freqs.size(),&maxv,&index);
                minIndex_32f(freqs.data(),freqs.size(),&minv,&index);
                float delta = (maxv-minv)/100.;
                int histsize = int((maxv-minv+delta)/delta);
                hist.resize(histsize);
                for (float x = minv; x <= maxv;  x+=delta)
                    osxhist.push_back(x);
                
                histDeltaOpt(hist.data(),freqs.data(), freqs.size(),
                             minv, delta, maxv);
            }
            
            fftwf_destroy_plan(planFow);
            fftwf_destroy_plan(planInv);
            file.close();
        }
        else
        {
            ERROROUT FileNotOpened;
            status = FileNotOpened;
        }
        
        emit sendProgress(0);
        
    }
    else
    {
        ERROROUT FileNotExist;
        status = FileNotExist;
    }
    
    return status;
}


/////////////////////////////////////////////////////////////////////////////////////
/*!
  \brief  Функция формирования комплексной импульсной характеристики по порядку
          фильтра
          
  Функция предназначена для формирования отсчетов импульсной характеристики
  НЧ-фильтра типа "приподнятый косинус"   или "корень из приподнятого косинуса"
  по заданию порядка фильтра. Возращает вектор комплексных отсчетов типа float
  
  \param [in]  filtOrder   порядок фильтра (не должен быть меньше 5)
  \param [in]  F           частота среза фильтра относительно частоты дискретизации
                           в пределах (0;5)
  \param [in]  R           коэффициент скругления фильтра в пределах [0;1]
  \param [in]  isSqrt      индикатор выбора типа НЧ-фильтра из "приподнятого
                           косинуса" (isSqrt = false) и "корня из приподнятого
                           косинуса"(isSqrt = true)
*/
/////////////////////////////////////////////////////////////////////////////////////
vector<complex<float> > TaClass::genRCosFIRLowpassOnSampsCmplx(int filtOrder, float F,
                                                               float R, bool isSqrt)
{
    //Генерируем импульсную харатеристику НЧ-фильтра в вещественном формате
    vector<float>  imphar32f = genRCosFIRLowpassOnSamps(filtOrder, F, R, isSqrt);
    
    //Импульсная харатеристика НЧ-фильтра в комплексном формате
    vector<complex<float> > imphar32fc(imphar32f.size());
    //Преобразуем импульсную характеристику в комплексный вид
    for (int i = 0; i < int(imphar32f.size()) ; i++)
    {
        imphar32fc[i].imag(0);//imphar32f[i];
        imphar32fc[i].real(imphar32f[i]);
    }
    return imphar32fc;
}

/////////////////////////////////////////////////////////////////////////////////////
/*!
  \brief  Функция формирования комплексно импульсной характеристики по числу символов
  
  Функция предназначена для формирования отсчетов импульсной характеристики
  НЧ-фильтра типа "приподнятый косинус"   или "корень из приподнятого косинуса"
  по заданию количества символов. Возращает вектор комплексных отсчетов типа float
  
  \param [in]  symbolsCnt  длина импольсной характеристики по числу модуляционных
               символов
  \param [in]  Vmod        модуляционная скорость сигнала (частота среза)
  \param [in]  R           коэффициент скругления фильтра в пределах [0;1];
  \param [in]  isSqrt      индикатор выбора типа НЧ-фильтра из "приподнятого
                           косинуса" (isSqrt = false) и "корня из приподнятого
косинуса"(isSqrt = true)
*/
/////////////////////////////////////////////////////////////////////////////////////
vector<complex<float> > TaClass::genRCosFIRLowpassOnSymbsCmplx(int symbolsCnt, float
                                                               Vmod, float Fs,
                                                               float R, bool isSqrt)
{
    //Генерируем импульсную харатеристику НЧ-фильтра в вещественном формате
    vector<float>  imphar32f = genRCosFIRLowpassOnSymbs(symbolsCnt, Vmod, Fs, R, isSqrt);
    
    //Импульсная харатеристика НЧ-фильтра в комплексном формате
    vector<complex<float> > imphar32fc(imphar32f.size());
    //Преобразуем импульсную характеристику в комплексный вид
    for (int i = 0; i < int(imphar32f.size()) ; i++)
    {
        imphar32fc[i].imag(0);//imphar32f[i];
        imphar32fc[i].real(imphar32f[i]);
    }
    return imphar32fc;
}

/////////////////////////////////////////////////////////////////////////////////////
/*!
  \brief  Функция формирования импульсной характеристики по числу символов
  
  Функция предназначена для формирования отсчетов импульсной характеристики
  НЧ-фильтра типа "приподнятый косинус"   или "корень из приподнятого косинуса"
  по заданию количества символов. Возращает вектор отсчетов типа float
  
  \param [in]  symbolsCnt  длина импольсной характеристики по числу модуляционных
               символов
  \param [in]  Vmod        модуляционная скорость сигнала (частота среза)
  \param [in]  R           коэффициент скругления фильтра в пределах [0;1];
  \param [in]  isSqrt      индикатор выбора типа НЧ-фильтра из "приподнятого
                           косинуса" (isSqrt = false) и "корня из приподнятого
косинуса"(isSqrt = true)
*/
/////////////////////////////////////////////////////////////////////////////////////
vector<float> TaClass::genRCosFIRLowpassOnSymbs(int symbolsCnt, float Vmod, float Fs,
                                                float R, bool isSqrt)
{
    vector<float> imp_res;
    float F = Vmod/Fs;
    int   filtOrder = round(Fs/Vmod)*symbolsCnt-1;
    imp_res = genRCosFIRLowpassOnSamps(filtOrder, F, R, isSqrt);
    return imp_res;
}

/////////////////////////////////////////////////////////////////////////////////////
/*!
  \brief  Функция формирования импульсной характеристики
  
  Функция предназначена для формирования отсчетов импульсной характеристики
  НЧ-фильтра типа "приподнятый косинус"   или "корень из приподнятого косинуса"
  по заданию количества символов. Функкция вычисляет импульсную
  характеристику по формулам, используемым функцией firrcos в Матлабе
  
  \param [in]  filtOrder   порядок фильтра (не должен быть меньше 5)
  \param [in]  F           частота среза фильтра относительно частоты дискретизации
                           в пределах (0;5)!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
  \param [in]  R           коэффициент скругления фильтра в пределах [0;1]
  \param [in]  isSqrt      индикатор выбора типа НЧ-фильтра из "приподнятого
                           косинуса" (isSqrt = false) и "корня из приподнятого
                           косинуса"(isSqrt = true)
*/
/////////////////////////////////////////////////////////////////////////////////////
vector<float> TaClass::genRCosFIRLowpassOnSamps(int filtOrder, float F, float R,
                                                bool isSqrt)
{
    //вектор выходной импульсной характеристики
    vector<float> imp_res;
    
    //проверка корректности введенных параметров
    //проверка частоты среза
    if (F <= 0 || F >= 0.98)
    {
        ERROROUT InvalidBandOrCentFreq;
        return imp_res;
    }
    //проверка коэффициента скругления
    if (R < 0 || R >1)
    {
        ERROROUT InvalidBandOrCentFreq;
        return imp_res;
    }
    //проверка частоты среза с учетом коэффициента скругления
    if ((F+R*F)>=1)
    {
        ERROROUT InvalidBandOrCentFreq;
        return imp_res;
    }
    
    //число отсчетов имульсной характеристики
    int L = filtOrder+1;
    
    //величина сдвига временной оси влево
    int delay = 0;
    if (L%2!=0)
        delay = (L-1)/2;
    else
        delay = L/2;
    
    //коэффициент скругления типа double
    double Rd = double(R);
    //частота среза типа double
    double Fd = double(F);
    
    //создание вектора временной оси
    vector<double> t(L);
    //формирование временной оси
    for (int i = 0; i < L; i ++)
        t[i] = i-delay;
    
    //минимальное число типа double, на которое можно делить
    double doubleMin = 2.225073858507201e-308;
    //погрешность чисел с плавающей точкой типа double
    double eps       = 2.220446049250313e-16;
    
    if (Rd == 0)
        Rd =  doubleMin;
    
    imp_res.resize(L);
    
    //если генерируем характеристику фильтра типа корень из приподнятого косинуса
    if (isSqrt)
    {
        for (int i = 0; i < int(t.size()); i ++)
        {
            double rez = 0;
            if(t[i]==0)
            {
                rez = -sqrt(Fd)/M_PI*(M_PI*(Rd-1)-4*Rd);;
            }
            else if  (pow(fabs(fabs(4.*double(Rd)*double(t[i])*Fd-1.0)),2.) < eps)
            {
                double c = sqrt(Fd)/(2*M_PI);
                double d = M_PI*(Rd+1.)*sin(M_PI*(Rd+1.)/(4.*Rd));
                double f = -4.*Rd*sin(M_PI*(Rd-1.)/(4.*Rd));
                double e = M_PI*(Rd-1.)*cos(M_PI*(Rd-1.)/(4.*Rd));
                rez = c *(d+f+e);
            }
            else
            {
                double g = -4.*Rd;
                double k = cos((1+Rd)*M_PI*Fd*t[i]);
                double m = sin((1-Rd)*M_PI*Fd*t[i])/4./Rd/Fd/t[i];
                double r = M_PI*sqrt(1./Fd)*(pow(4.*Rd*Fd*t[i],2.)-1);
                rez = g*(k+m)/r;
            }
            imp_res[i] = float(rez*sqrt(Fd));
        }
    }
    //иначе генерируем характеристику фильтра типа приподнятый косинус
    else
    {
        for (int i = 0; i < int(t.size()); i ++)
        {
            double rez = 0;
            if (t[i]==0)
            {
                rez = 1;
            }
            else if  (pow(fabs(fabs(4.*double(Rd)*double(t[i])*Fd-1.0)),2.) < eps)
            {
                rez = Rd * sin(M_PI / (2.*Rd));
            }
            else
            {
                double sinc = sin(M_PI*Fd*t[i])/(M_PI*Fd*t[i]);
                double chis = cos(M_PI*Fd*Rd*t[i]);
                double znam = 1.0 - pow(2.*Rd*Fd*t[i],2.);
                rez = sinc*chis/znam;
            }
            imp_res[i] = float(rez*Fd);
        }
    }
    return imp_res;
}

/////////////////////////////////////////////////////////////////////////////////////
/*!
  \brief  Метод чтения и конвертации отсчетов сигнала из файла
  
  Метод реализует чтение и, при необходимости, конвертацию блока отсчетов из
  заданного файла и возвращает блок считанных отчетов в формате "комплексные
  с плавающей точкой типа float". Если отсчеты записи сиганла, хранящейся
  в заданном файле, изначально представлены в таком формате, конвертация не
  производится. Если отсчеты в записи представлены в некомлексном виде.
  дополнительно производится расчет мнимой составляющей с помощью преобразования
  Гильберта. Метод возвращает код ошибки ErrorCode_Ta
  
  \param [in]      file         файловая переменная, в которой храниться запись сигнала
  \param [out]     blockLine    выходной блок считанных отсчетов в комплексном формате
  \param [in/out]  lastPos      указатель на позицию в файле в байтах, с которой
                                необходимо начать чтение, по завершению функции *lastPos
                                смещается на длину считанного блока в байтах
  \param [in]      format       формат представления отсчетов сигнала InputFormats
  
*/
/////////////////////////////////////////////////////////////////////////////////////
ErrorCode_Ta TaClass::readAndConvert(QFile &file, vector<complex <float> > &blockLine,
                                     qint64 *lastPos,
                                     InputFormats format,
                                     int overlap)
{
    ErrorCode_Ta status = NoError;
    
    int blockSizeSamples = blockLine.size();
    int blockSizeBytes = getBytesCnt(format,blockSizeSamples);
    int overBytes = getBytesCnt(format,overlap);
    
    if (file.isOpen())
    {
        //текущий считываемый из файла блок отсчетов
        vector<char>   currBlockChar(blockSizeBytes); //!! нужно вынести из функции выделение памяти
        memset(currBlockChar.data(),0,currBlockChar.size());
        vector<float>  temp32f(blockSizeSamples);     //!! нужно вынести из функции выделение памяти
        
        file.seek(*lastPos);
        
        //чтение блока отсчетов в промежуточный массив
        qint64 nread = file.read(currBlockChar.data(),blockSizeBytes);
        
        if (nread < blockSizeBytes)
            status = EndOfFile;
        
        //Конвертация отсчетов в вещественные комплексные типа 32fc в зависимости
        //от исходного формата
        switch (format)
        {
        case BIT8R:
            //конвертация из целого в вещественный  вид
            convert_8s32f(reinterpret_cast<int8_t*>(currBlockChar.data()),
                          temp32f.data(),
                          blockSizeSamples);
            //преобразование Гильберта
            hilbertTransform_32f32fc(temp32f.data(),blockLine.data(),blockSizeSamples);
            break;
        case BIT8C:
            //конвертация из целого комплексного в вещественный комплексный вид
            convert_8s32f(reinterpret_cast<int8_t*>(currBlockChar.data()),
                          reinterpret_cast<float*> (blockLine.data()),
                          blockSizeSamples*2);
            break;
        case BIT16R:
            //конвертация из целого в вещественный  вид
            convert_16s32f(reinterpret_cast<int16_t*>(currBlockChar.data()),
                           (temp32f.data()),
                           blockSizeSamples);
            //преобразование Гильберта
            hilbertTransform_32f32fc(temp32f.data(),blockLine.data(),blockSizeSamples);
            break;
        case BIT16C:
            //конвертация из целого комплексного в вещественный комплексный вид
            convert_16s32f(reinterpret_cast<int16_t*>(currBlockChar.data()),
                           reinterpret_cast<float*>(blockLine.data()),
                           blockSizeSamples*2);
            break;
        case BIT32R:
            //конвертация из целого в вещественный  вид
            convert_32s32f(reinterpret_cast<int*>(currBlockChar.data()),
                           temp32f.data(),
                           blockSizeSamples);
            //преобразование Гильберта
            hilbertTransform_32f32fc(temp32f.data(),blockLine.data(),blockSizeSamples);
            break;
        case BIT32C:
            //конвертация из целого комплексного в вещественный комплексный вид
            convert_32s32f(reinterpret_cast<int*>(currBlockChar.data()),
                           reinterpret_cast<float*>(blockLine.data()),
                           blockSizeSamples*2);
            break;
        case BIT32RF:
            //преобразование Гильберта
            hilbertTransform_32f32fc((float*)currBlockChar.data(),blockLine.data(),
                                     blockSizeSamples);
            break;
        case BIT32CF:
            //просто запись считанного из файлов блока отсчетов в последний блок очереди
            memcpy(blockLine.data(),currBlockChar.data(),blockSizeBytes);
            
        }
        if (nread < blockSizeBytes)
            constRemove_32f((float*)blockLine.data(),getSamplesCnt(format, nread)*2);
        
        qint64 ps = file.pos() - overBytes;
        
        file.seek(ps);
        *lastPos = ps;
    }
    else
    {
        ERROROUT FileNotOpened;
        return FileNotOpened;
    }
    
    
    return status;
}

ErrorCode_Ta TaClass::convert_32s64f(const int32_t * pSrc, double * pDst, int size)
{
    if (pSrc == 0 || pDst == 0)
    {
        ERROROUT InvalidData;
        return InvalidData;
    }
    if (size < 1)
    {
        ERROROUT InvalidSize;
        return InvalidSize;
    }
    
    for (int i = 0; i < size; i++)
    {
        pDst[i] = double(pSrc[i]);
    }
    
    return NoError;
}

ErrorCode_Ta TaClass::convert_16s64f(const int16_t * pSrc, double * pDst, int size)
{
    if (pSrc == 0 || pDst == 0)
    {
        ERROROUT InvalidData;
        return InvalidData;
    }
    if (size < 1)
    {
        ERROROUT InvalidSize;
        return InvalidSize;
    }
    
    for (int i = 0; i < size; i++)
    {
        pDst[i] = double(pSrc[i]);
    }
    
    return NoError;
}

/////////////////////////////////////////////////////////////////////////////////////
/*!
  \brief  Метод преобразования массива целых чисел типа int в вещественные типа float
  
  Метод предназначен для перобразования массива целых чисел типа int в
  вещественные типа float. Метод возвращает код ошибки ErrorCode_Ta
  
  \param [in]   pSrc    указатель на массив целых чисел па int
  \param [out]  pDst    указатель на массив вещественных чисел па float
  \param [in]   size    размер входного и выходного массивов
  
*/
/////////////////////////////////////////////////////////////////////////////////////
ErrorCode_Ta TaClass::convert_32s32f(const int * pSrc, float * pDst, int size)
{
    if (pSrc == 0 || pDst == 0)
    {
        ERROROUT InvalidData;
        return InvalidData;
    }
    if (size < 1)
    {
        ERROROUT InvalidSize;
        return InvalidSize;
    }
    
    for (int i = 0; i < size; i++)
    {
        pDst[i] = float(pSrc[i]);
    }
    
    return NoError;
}

/////////////////////////////////////////////////////////////////////////////////////
/*!
  \brief  Метод преобразования массива целых чисел типа int16_t в вещественные float
  
  Метод предназначен для перобразования массива целых чисел типа int16_t
  в вещественные типа float. Метод возвращает код ошибки ErrorCode_Ta
  
  \param [in]   pSrc    указатель на массив целых чисел па int16_t
  \param [out]  pDst    указатель на массив вещественных чисел па float
  \param [in]   size    размер входного и выходного массивов
*/
/////////////////////////////////////////////////////////////////////////////////////
ErrorCode_Ta TaClass::convert_16s32f(const int16_t * pSrc, float * pDst, int size)
{
    if (pSrc == 0 || pDst == 0)
    {
        ERROROUT InvalidData;
        return InvalidData;
    }
    if (size < 1)
    {
        ERROROUT InvalidSize;
        return InvalidSize;
    }
    
    for (int i = 0; i < size; i++)
    {
        pDst[i] = float(pSrc[i]);
    }
    
    return NoError;
}



ErrorCode_Ta TaClass::convert_8s64f(const int8_t * pSrc, double * pDst, int size)
{
    if (pSrc == 0 || pDst == 0)
    {
        ERROROUT InvalidData;
        return InvalidData;
    }
    if (size < 1)
    {
        ERROROUT InvalidSize;
        return InvalidSize;
    }
    
    for (int i = 0; i < size; i++)
    {
        pDst[i] = double(pSrc[i]);
    }
    
    return NoError;
}

/////////////////////////////////////////////////////////////////////////////////////
/*!
  \brief  Метод преобразования массива целых чисел типа int8_t в вещественные  float
  
  Метод предназначен для перобразования массива целых чисел типа int8_t
  в вещественные типа float. Метод возвращает код ошибки ErrorCode_Ta
  
  \param [in]   pSrc    указатель на массив целых чисел па int8_t
  \param [out]  pDst    указатель на массив вещественных чисел па float
  \param [in]   size    размер входного и выходного массивов
*/
/////////////////////////////////////////////////////////////////////////////////////
ErrorCode_Ta TaClass::convert_8s32f(const int8_t * pSrc, float * pDst, int size)
{
    if (pSrc == 0 || pDst == 0)
    {
        ERROROUT InvalidData;
        return InvalidData;
    }
    if (size < 1)
    {
        ERROROUT InvalidSize;
        return InvalidSize;
    }
    
    for (int i = 0; i < size; i++)
    {
        pDst[i] = float(pSrc[i]);
    }
    
    return NoError;
}
/////////////////////////////////////////////////////////////////////////////////////
/*!
  \brief  Метод преобразования массива чисел типа float в тип  double
  
  Метод предназначен для перобразования массива чисел типа float
  в вещественные типа double. Метод возвращает код ошибки ErrorCode_Ta
  
  \param [in]   pSrc    указатель на массив чисел типа float
  \param [out]  pDst    указатель на массив чисел па вщиду
  \param [in]   size    размер входного и выходного массивов
*/
/////////////////////////////////////////////////////////////////////////////////////
ErrorCode_Ta TaClass::convert_32f64f(const float   * pSrc, double * pDst, int size)
{
    if (pSrc == 0 || pDst == 0)
    {
        ERROROUT InvalidData;
        return InvalidData;
    }
    if (size < 1)
    {
        ERROROUT InvalidSize;
        return InvalidSize;
    }
    
    for (int i = 0; i < size; i++)
    {
        pDst[i] = double(pSrc[i]);
    }
    
    return NoError;
}
/////////////////////////////////////////////////////////////////////////////////////
/*!
  \brief  Метод поэлементого выбора максимального из значений двух массивов
  
  Метод предназначен для поэлементного сравнения двух массивов, выбора и записи
  максимального элемента в один из массивов. Метод возвращает код ошибки ErrorCode_Ta
  
  \param [in]      pSrc       указатель на входной массив чисел типа float
  \param [in/out]  pSrcDst    указатель на входной массив чисел типа float, в
                   который будут записаны максимальные значения
  \param [in]      size       размер входного и выходного массивов
*/
/////////////////////////////////////////////////////////////////////////////////////
ErrorCode_Ta TaClass::everyMax_32f(const float   * pSrc, float * pSrcDst, int size)
{
    if (pSrc == 0 || pSrcDst == 0)
    {
        ERROROUT InvalidData;
        return InvalidData;
    }
    if (size < 1)
    {
        ERROROUT InvalidSize;
        return InvalidSize;
    }
    
    for (int i = 0; i < size; i++)
    {
        pSrcDst[i] = pSrcDst[i] > pSrc[i] ? pSrcDst[i] : pSrc[i];
    }
    
    return NoError;
}

/////////////////////////////////////////////////////////////////////////////////////
/*!
  \brief  Метод поэлементого выбора минимального из значений двух массивов
  
  Метод предназначен для поэлементного сравнения двух массивов, выбора и записи
  минимального элемента в один из массивов. Метод возвращает код ошибки ErrorCode_Ta
  
  \param [in]      pSrc       указатель на входной массив чисел типа float
  \param [in/out]  pSrcDst    указатель на входной массив чисел типа float, в
                   который будут записаны минимальные значения
  \param [in]      size       размер входного и выходного массивов
*/
/////////////////////////////////////////////////////////////////////////////////////
ErrorCode_Ta TaClass::everyMin_32f(const float   * pSrc, float * pSrcDst, int size)
{
    if (pSrc == 0 || pSrcDst == 0)
    {
        ERROROUT InvalidData;
        return InvalidData;
    }
    if (size < 1)
    {
        ERROROUT InvalidSize;
        return InvalidSize;
    }
    
    for (int i = 0; i < size; i++)
    {
        pSrcDst[i] = pSrcDst[i] < pSrc[i] ? pSrcDst[i] : pSrc[i];
    }
    
    return NoError;
}

/////////////////////////////////////////////////////////////////////////////////////
/*!
  \brief  Метод рассчета суммы значений элементов массива вещественных чисел  float
  
  Метод предназначен для рассчета суммы значений элементов массива
  вещественных чисел типа float. Метод возвращает код ошибки ErrorCode_Ta
  
  \param [in]   pSrc    указатель на массив целых чисел типа float
  \param [out]  sum     указатель на место в памяти, куда будет сохранен результат
  \param [in]   size    размер входного и выходного массивов
*/
/////////////////////////////////////////////////////////////////////////////////////
ErrorCode_Ta TaClass::sumVec_32f(float * sum, const float * pSrc, int size)
{
    if (pSrc == 0 || sum == 0)
    {
        ERROROUT InvalidData;
        return InvalidData;
    }
    
    if (size < 1)
    {
        ERROROUT InvalidSize;
        return InvalidSize;
    }
    
    *sum = 0;
    for (int i = 0; i < size; i++)
    {
        *sum+=pSrc[i];
    }
    
    return NoError;
}


/////////////////////////////////////////////////////////////////////////////////////
/*!
  \brief  Метод рассчета суммы значений элементов массива вещественных чисел double
  
  Метод предназначен для рассчета суммы значений элементов массива
  вещественных чисел типа double. Метод возвращает код ошибки ErrorCode_Ta
  
  \param [in]   pSrc    указатель на массив целых чисел типа double
  \param [out]  sum     указатель на место в памяти, куда будет сохранен результат
  \param [in]   size    размер входного и выходного массивов
*/
/////////////////////////////////////////////////////////////////////////////////////
ErrorCode_Ta TaClass::sumVec_64f(double * sum, const double * pSrc, int size)
{
    if (pSrc == 0 || sum == 0)
    {
        ERROROUT InvalidData;
        return InvalidData;
    }
    
    if (size < 1)
    {
        ERROROUT InvalidSize;
        return InvalidSize;
    }
    
    *sum = 0;
    for (int i = 0; i < size; i++)
    {
        *sum+=pSrc[i];
    }
    
    return NoError;
}

/////////////////////////////////////////////////////////////////////////////////////
/*!
  \brief  Метод рассчета суммы квадратов элементов массива вещественных чисел  float
  
  Метод предназначен для рассчета суммы квадратов элементов массива
  вещественных чисел типа float. Метод возвращает код ошибки ErrorCode_Ta
  
  \param [in]   pSrc    указатель на массив целых чисел типа float
  \param [out]  sum     указатель на место в памяти, куда будет сохранен результат
  \param [in]   size    размер входного и выходного массивов
*/
/////////////////////////////////////////////////////////////////////////////////////
ErrorCode_Ta TaClass::sum2Vec_32f(float * sum, float * pSrc, int size)
{
    if (pSrc == 0 || sum == 0)
    {
        ERROROUT InvalidData;
        return InvalidData;
    }
    
    if (size < 1)
    {
        ERROROUT InvalidSize;
        return InvalidSize;
    }
    
    *sum = 0;
    for (int i = 0; i < size; i++)
    {
        *sum+=pSrc[i]*pSrc[i];
    }
    
    return NoError;
}

ErrorCode_Ta TaClass::addVec_32fc(const complex<float>  * pSrc1,
                                  const complex<float>  * pSrc2,
                                  complex<float> * pDst,
                                  int size)
{
    if (pSrc1 == 0 || pSrc1 == 0 || pDst == 0)
    {
        ERROROUT InvalidData;
        return InvalidData;
    }
    
    if (size < 1)
    {
        ERROROUT InvalidSize;
        return InvalidSize;
    }
    
    for (int i = 0; i < size; i++)
    {
        pDst[i] = pSrc1[i] + pSrc2[i];
    }
    return NoError;
}

ErrorCode_Ta TaClass::addVec_32f(const float  * pSrc1,
                                 const float * pSrc2,
                                 float * pDst,
                                 int size)
{
    if (pSrc1 == 0 || pSrc1 == 0 || pDst == 0)
    {
        ERROROUT InvalidData;
        return InvalidData;
    }
    
    if (size < 1)
    {
        ERROROUT InvalidSize;
        return InvalidSize;
    }
    
    for (int i = 0; i < size; i++)
    {
        pDst[i] = pSrc1[i] + pSrc2[i];
    }
    return NoError;
}

ErrorCode_Ta TaClass::addVec_16s(const int16_t  * pSrc1,
                                 const int16_t * pSrc2,
                                 int16_t * pDst,
                                 int size)
{
    if (pSrc1 == 0 || pSrc1 == 0 || pDst == 0)
    {
        ERROROUT InvalidData;
        return InvalidData;
    }
    
    if (size < 1)
    {
        ERROROUT InvalidSize;
        return InvalidSize;
    }
    
    for (int i = 0; i < size; i++)
    {
        pDst[i] = pSrc1[i] + pSrc2[i];
    }
    return NoError;
}


/////////////////////////////////////////////////////////////////////////////////////
/*!
  \brief  Метод поэлементного сложения двух массивов типа float
  
  Метод предназначен для поэлементного сложения двух массивов типа float.
  Метод возвращает код ошибки ErrorCode_Ta
  
  \param [in]      pSrc      указатель на первый массив
  \param [in/out]  pSrcDst   указатель на второй массив, в
                             который будут записаны результаты
  \param [in]      size      размер входного и выходного массивов
*/
/////////////////////////////////////////////////////////////////////////////////////
ErrorCode_Ta TaClass::addVec_32f_I(const float  * pSrc, float * pSrcDst, int size)
{
    if (pSrcDst == 0 || pSrc == 0)
    {
        ERROROUT InvalidData;
        return InvalidData;
    }
    
    if (size < 1)
    {
        ERROROUT InvalidSize;
        return InvalidSize;
    }
    
    for (int i = 0; i < size; i++)
    {
        pSrcDst[i] = pSrcDst[i] + pSrc[i];
    }
    return NoError;
}


/////////////////////////////////////////////////////////////////////////////////////
/*!
  \brief  Метод умножения элементов массива чисел типа float на заданное число
  
  Метод предназначен для умножения элементов массива чисел типа float на заданное число.
  Метод возвращает код ошибки ErrorCode_Ta
  
  \param [in]      Val       число, на которое нужно умножить элементы массива
  \param [in/out]  pSrcDst   указатель на входной массив чисел типа float, в
                             который будут записаны результаты
  \param [in]      size      размер входного и выходного массивов
*/
/////////////////////////////////////////////////////////////////////////////////////
ErrorCode_Ta TaClass::multVecC_32f_I(const float Val, float * pSrcDst, int size)
{
    if (pSrcDst == 0)
    {
        ERROROUT InvalidData;
        return InvalidData;
    }
    
    if (size < 1)
    {
        ERROROUT InvalidSize;
        return InvalidSize;
    }
    
    for (int i = 0; i < size; i++)
    {
        pSrcDst[i] = pSrcDst[i] * Val;
    }
    
    return NoError;
}

/////////////////////////////////////////////////////////////////////////////////////
/*!
  \brief  Метод умножения элементов массива комплексных чисел типа float на заданное
          число
          
  Метод предназначен для умножения элементов массива комплексных чисел типа float на
  заданное число. Метод возвращает код ошибки ErrorCode_Ta
  
  \param [in]      Val       число, на которое нужно умножить элементы массива
  \param [in/out]  pSrcDst   указатель на входной массив комплексных чисел типа float,
                             в который будут записаны результаты
  \param [in]      size      размер входного  массива
*/
/////////////////////////////////////////////////////////////////////////////////////
ErrorCode_Ta TaClass::multVecC_32fc_I(const float Val, complex<float> * pSrcDst, int size)
{
    
    if (pSrcDst == 0)
    {
        ERROROUT InvalidData;
        return InvalidData;
    }
    
    if (size < 1)
    {
        ERROROUT InvalidSize;
        return InvalidSize;
    }
    
    for (int i = 0; i < size; i++)
    {
        pSrcDst[i].real(pSrcDst[i].real() * Val);
        pSrcDst[i].imag(pSrcDst[i].imag() * Val);
    }
    
    return NoError;
}

/////////////////////////////////////////////////////////////////////////////////////
/*!
  \brief  Метод деления элементов массива чисел типа float на заданное число
  
  Метод предназначен для деления элементов массива чисел типа float на заданное число.
  Метод возвращает код ошибки ErrorCode_Ta
  
  \param [in]      Val       число, на которое нужно разделить элементы массива
  \param [in/out]  pSrcDst   указатель на входной массив чисел типа float, в
                             который будут записаны результаты
  \param [in]      size      размер входного  массива
*/
/////////////////////////////////////////////////////////////////////////////////////
ErrorCode_Ta TaClass::divVecC_32f_I( const float Val, float * pSrcDst, int size)
{
    
    if (pSrcDst == 0)
    {
        ERROROUT InvalidData;
        return InvalidData;
    }
    
    if (size < 1)
    {
        ERROROUT InvalidSize;
        return InvalidSize;
    }
    
    for (int i = 0; i < size; i++)
    {
        pSrcDst[i] = pSrcDst[i] / Val;
    }
    
    return NoError;
}

/////////////////////////////////////////////////////////////////////////////////////
/*!
  \brief  Метод вычитания из элементов массива чисел типа float на заданного числа
  
  Метод предназначен для вычитания их элементов массива чисел типа float заданного числа.
  Метод возвращает код ошибки ErrorCode_Ta
  
  \param [in]      Val       число, на которое нужно вычесть из элементов массива
  \param [in/out]  pSrcDst   указатель на входной массив чисел типа float, в
                             который будут записаны результаты
  \param [in]      size      размер входного  массива
*/
/////////////////////////////////////////////////////////////////////////////////////
ErrorCode_Ta TaClass::subVecC_32f_I( const float Val, float * pSrcDst, int size)
{
    if (pSrcDst == 0)
    {
        ERROROUT InvalidData;
        return InvalidData;
    }
    
    if (size < 1)
    {
        ERROROUT InvalidSize;
        return InvalidSize;
    }
    
    for (int i = 0; i < size; i++)
    {
        pSrcDst[i] = pSrcDst[i] - Val;
    }
    
    return NoError;
}

/////////////////////////////////////////////////////////////////////////////////////
/*!
  \brief  Метод деления элементов массива комплексных чисел типа float на заданное
          число
          
  Метод предназначен для деления элементов массива комплексных чисел типа float на
  заданное число.Метод возвращает код ошибки ErrorCode_Ta
  
  \param [in]      Val       число, на которое нужно разделить элементы массива
  \param [in/out]  pSrcDst   указатель на входной массив комплексных чисел типа float,
                             в который будут записаны результаты
  \param [in]      size      размер входного и выходного массивов
*/
/////////////////////////////////////////////////////////////////////////////////////
ErrorCode_Ta TaClass::divVecC_32fc_I(const float Val, complex<float> * pSrcDst,
                                     int size)
{
    
    if (pSrcDst == 0)
    {
        ERROROUT InvalidData;
        return InvalidData;
    }
    
    if (size < 1)
    {
        ERROROUT InvalidSize;
        return InvalidSize;
    }
    
    for (int i = 0; i < size; i++)
    {
        pSrcDst[i].real(pSrcDst[i].real() / Val);
        pSrcDst[i].imag(pSrcDst[i].imag() / Val);
    }
    
    return NoError;
}

/////////////////////////////////////////////////////////////////////////////////////
/*!
  \brief  Метод поэлементного умножения двух массивов типа float
  
  Метод предназначен для поэлементного умножения двух массивов типа float.
  Метод возвращает код ошибки ErrorCode_Ta
  
  \param [in]      pSrc      указатель на первый массив
  \param [in/out]  pSrcDst   указатель на второй массив, в
                             который будут записаны результаты
  \param [in]      size      размер входного и выходного массивов
*/
/////////////////////////////////////////////////////////////////////////////////////
ErrorCode_Ta TaClass::multVec_32f_I(const float  * pSrc, float * pSrcDst, int size)
{
    if (pSrcDst == 0 || pSrc == 0)
    {
        ERROROUT InvalidData;
        return InvalidData;
    }
    
    if (size < 1)
    {
        ERROROUT InvalidSize;
        return InvalidSize;
    }
    
    for (int i = 0; i < size; i++)
    {
        pSrcDst[i] = pSrcDst[i] * pSrc[i];
    }
    return NoError;
}

/////////////////////////////////////////////////////////////////////////////////////
/*!
  \brief  Метод поэлементного умножения двух массивов компелксных значений типа float
  
  Метод предназначен для поэлементного умножения двух массивов комплексных
  значенийтипа float. Метод возвращает код ошибки ErrorCode_Ta
  
  \param [in]      pSrc      указатель на первый массив
  \param [in/out]  pSrcDst   указатель на второй массив, в
                             который будут записаны результаты
  \param [in]      size      размер входного и выходного массивов
*/
/////////////////////////////////////////////////////////////////////////////////////
ErrorCode_Ta TaClass::multVec_32fc_I(const complex<float> * pSrc,
                                     complex<float> * pSrcDst, int size)
{
    if (pSrcDst == 0 || pSrc == 0)
    {
        ERROROUT InvalidData;
        return InvalidData;
    }
    
    if (size < 1)
    {
        ERROROUT InvalidSize;
        return InvalidSize;
    }
    
    for (int i = 0; i < size; i++)
    {
        pSrcDst[i] = pSrcDst[i] * pSrc[i];
    }
    return NoError;
}

/////////////////////////////////////////////////////////////////////////////////////
/*!
  \brief  Функция возведение вектора в степени 2, 4, 8
  
  Функция предназначена для возведения вектора комплексных чисел типа
  float в степени 2, 4, 8.
  
  \param [in/out]  pSrcDst     указатель на вектор входных комплексных значений
  \param [in]      pow2        степень (1, 2, 4, 8)
  \param [in]      size        размер вектора
*/
/////////////////////////////////////////////////////////////////////////////////////
ErrorCode_Ta TaClass::powVec_32fc_I(complex<float> * pSrcDst, int pow2, int size)
{
    if (pSrcDst == 0)
    {
        ERROROUT InvalidData;
        return InvalidData;
    }
    
    if (size < 1)
    {
        ERROROUT InvalidSize;
        return InvalidSize;
    }
    
    for (int i = 0; i < size; i++)
    {
        switch (pow2)
        {
        case 1:
            return NoError;
        case 2:
            pSrcDst[i] = pSrcDst[i] * pSrcDst[i];
            break;
        case 4:
            pSrcDst[i] = pSrcDst[i] * pSrcDst[i]*
                    pSrcDst[i] * pSrcDst[i];
            break;
        case 8:
            pSrcDst[i] = pSrcDst[i] * pSrcDst[i]*
                    pSrcDst[i] * pSrcDst[i]*
                    pSrcDst[i] * pSrcDst[i]*
                    pSrcDst[i] * pSrcDst[i];
        }
    }
    return NoError;
}

/////////////////////////////////////////////////////////////////////////////////////
/*!
  \brief  Метод определения максимального значения и его индекса в массиве типа float
  
  Метод предназначен для определения максимального значения и его индекса в массиве
  типа float. Метод возвращает код ошибки ErrorCode_Ta
  
  \param [in]      pSrc      указатель на входной массив
  \param [in]      size      размер входного и выходного массивов
  \param [out]     max       указатель на область памяти, в которую будет сохранено
                             значение максимума
  \param [out]     index     указатель на область памяти, в которую будет сохранено
                             значение индекса максимального значения в массиве
*/
/////////////////////////////////////////////////////////////////////////////////////
ErrorCode_Ta TaClass::maxIndex_32f(const float   * pSrc, int size, float * max,
                                   int * index)
{
    *max = -FLT_MIN;
    if (pSrc == 0 || max == 0 || index == 0)
    {
        ERROROUT InvalidData;
        return InvalidData;
    }
    
    if (size < 1)
    {
        ERROROUT InvalidSize;
        return InvalidSize;
    }
    
    for (int i = 0; i < size; i++)
    {
        if (*max < pSrc[i])
        {
            *max   = pSrc[i];
            *index = i;
        }
    }
    return NoError;
}

/////////////////////////////////////////////////////////////////////////////////////
/*!
  \brief  Метод определения минимального значения и его индекса в массиве типа float
  
  Метод предназначен для определения минимального значения и его индекса в массиве
  типа float. Метод возвращает код ошибки ErrorCode_Ta
  
  \param [in]      pSrc      указатель на входной массив
  \param [in]      size      размер входного и выходного массивов
  \param [out]     min       указатель на область памяти, в которую будет сохранено
                             значение минимума
  \param [out]     index     указатель на область памяти, в которую будет сохранено
                             значение индекса минимального значения в массиве
*/
/////////////////////////////////////////////////////////////////////////////////////
ErrorCode_Ta TaClass::minIndex_32f(const float   * pSrc, int size, float * min,
                                   int * index)
{
    *min = FLT_MAX;
    if (pSrc == 0 || min == 0 || index == 0)
    {
        ERROROUT InvalidData;
        return InvalidData;
    }
    
    if (size < 1)
    {
        ERROROUT InvalidSize;
        return InvalidSize;
    }
    
    for (int i = 0; i < size; i++)
    {
        if (*min > pSrc[i])
        {
            *min   = pSrc[i];
            *index = i;
        }
    }
    return NoError;
}







ErrorCode_Ta TaClass::imag_32fc64f(const complex<float> * pSrc,
                                   double * pDst,
                                   int size)
{
    if (pSrc == 0 || pDst == 0)
    {
        ERROROUT InvalidData;
        return InvalidData;
    }
    if (size < 1)
    {
        ERROROUT InvalidSize;
        return InvalidSize;
    }
    
    for (int i = 0; i < size; i++)
    {
        pDst[i] = pSrc[i].imag();
    }
    
    return NoError;
}

ErrorCode_Ta TaClass::imag_32c64f(const complex<int32_t> * pSrc,
                                  double * pDst,
                                  int size)
{
    if (pSrc == 0 || pDst == 0)
    {
        ERROROUT InvalidData;
        return InvalidData;
    }
    if (size < 1)
    {
        ERROROUT InvalidSize;
        return InvalidSize;
    }
    
    for (int i = 0; i < size; i++)
    {
        pDst[i] = pSrc[i].imag();
    }
    
    return NoError;
}

ErrorCode_Ta TaClass::imag_16c64f(const complex<int16_t> * pSrc,
                                  double * pDst,
                                  int size)
{
    if (pSrc == 0 || pDst == 0)
    {
        ERROROUT InvalidData;
        return InvalidData;
    }
    if (size < 1)
    {
        ERROROUT InvalidSize;
        return InvalidSize;
    }
    
    for (int i = 0; i < size; i++)
    {
        pDst[i] = pSrc[i].imag();
    }
    
    return NoError;
}

ErrorCode_Ta TaClass::imag_8c64f(const complex<int8_t> * pSrc,
                                 double * pDst,
                                 int size)
{
    if (pSrc == 0 || pDst == 0)
    {
        ERROROUT InvalidData;
        return InvalidData;
    }
    if (size < 1)
    {
        ERROROUT InvalidSize;
        return InvalidSize;
    }
    
    for (int i = 0; i < size; i++)
    {
        pDst[i] = pSrc[i].imag();
    }
    
    return NoError;
}





ErrorCode_Ta TaClass::real_32fc64f(const complex<float> * pSrc,
                                   double * pDst,
                                   int size)
{
    if (pSrc == 0 || pDst == 0)
    {
        ERROROUT InvalidData;
        return InvalidData;
    }
    if (size < 1)
    {
        ERROROUT InvalidSize;
        return InvalidSize;
    }
    
    for (int i = 0; i < size; i++)
    {
        pDst[i] = pSrc[i].real();
    }
    
    return NoError;
}

ErrorCode_Ta TaClass::real_32c64f(const complex<int32_t> * pSrc,
                                  double * pDst,
                                  int size)
{
    if (pSrc == 0 || pDst == 0)
    {
        ERROROUT InvalidData;
        return InvalidData;
    }
    if (size < 1)
    {
        ERROROUT InvalidSize;
        return InvalidSize;
    }
    
    for (int i = 0; i < size; i++)
    {
        pDst[i] = pSrc[i].real();
    }
    
    return NoError;
}

ErrorCode_Ta TaClass::real_16c64f(const complex<int16_t> * pSrc,
                                  double * pDst,
                                  int size)
{
    if (pSrc == 0 || pDst == 0)
    {
        ERROROUT InvalidData;
        return InvalidData;
    }
    if (size < 1)
    {
        ERROROUT InvalidSize;
        return InvalidSize;
    }
    
    for (int i = 0; i < size; i++)
    {
        pDst[i] = pSrc[i].real();
    }
    
    return NoError;
}

ErrorCode_Ta TaClass::real_8c64f(const complex<int8_t> * pSrc,
                                 double * pDst,
                                 int size)
{
    if (pSrc == 0 || pDst == 0)
    {
        ERROROUT InvalidData;
        return InvalidData;
    }
    if (size < 1)
    {
        ERROROUT InvalidSize;
        return InvalidSize;
    }
    
    for (int i = 0; i < size; i++)
    {
        pDst[i] = pSrc[i].real();
    }
    
    return NoError;
}


ErrorCode_Ta TaClass::real_32fc(const complex<float> * pSrc, float * pDst,
                                int size)
{
    if (pSrc == 0 || pDst == 0)
    {
        ERROROUT InvalidData;
        return InvalidData;
    }
    if (size < 1)
    {
        ERROROUT InvalidSize;
        return InvalidSize;
    }
    
    for (int i = 0; i < size; i++)
    {
        pDst[i] = pSrc[i].real();
    }
    
    return NoError;
}










ErrorCode_Ta TaClass::magnitude_32fc64f(const complex<float> * pSrc,
                                        double * pDst,
                                        int size)
{
    if (pSrc == 0 || pDst == 0)
    {
        ERROROUT InvalidData;
        return InvalidData;
    }
    if (size < 1)
    {
        ERROROUT InvalidSize;
        return InvalidSize;
    }
    
    for (int i = 0; i < size; i++)
    {
        pDst[i] = double(sqrtf(pSrc[i].real()*pSrc[i].real()+
                               pSrc[i].imag()*pSrc[i].imag()));
    }
    
    return NoError;
}

ErrorCode_Ta TaClass::magnitude_32c64f(const complex<int32_t> * pSrc,
                                       double * pDst,
                                       int size)
{
    if (pSrc == 0 || pDst == 0)
    {
        ERROROUT InvalidData;
        return InvalidData;
    }
    if (size < 1)
    {
        ERROROUT InvalidSize;
        return InvalidSize;
    }
    
    for (int i = 0; i < size; i++)
    {
        pDst[i] = double(sqrtf(pSrc[i].real()*pSrc[i].real()+
                               pSrc[i].imag()*pSrc[i].imag()));
    }
    
    return NoError;
}

ErrorCode_Ta TaClass::magnitude_16c64f(const complex<int16_t> * pSrc,
                                       double * pDst,
                                       int size)
{
    if (pSrc == 0 || pDst == 0)
    {
        ERROROUT InvalidData;
        return InvalidData;
    }
    if (size < 1)
    {
        ERROROUT InvalidSize;
        return InvalidSize;
    }
    
    for (int i = 0; i < size; i++)
    {
        pDst[i] = double(sqrtf(pSrc[i].real()*pSrc[i].real()+
                               pSrc[i].imag()*pSrc[i].imag()));
    }
    
    return NoError;
}

ErrorCode_Ta TaClass::magnitude_8c64f(const complex<int8_t> * pSrc,
                                      double * pDst,
                                      int size)
{
    if (pSrc == 0 || pDst == 0)
    {
        ERROROUT InvalidData;
        return InvalidData;
    }
    if (size < 1)
    {
        ERROROUT InvalidSize;
        return InvalidSize;
    }
    
    for (int i = 0; i < size; i++)
    {
        pDst[i] = double(sqrtf(pSrc[i].real()*pSrc[i].real()+
                               pSrc[i].imag()*pSrc[i].imag()));
    }
    
    return NoError;
}




/////////////////////////////////////////////////////////////////////////////////////
/*!
  \brief  Метод вычисления амплитуды комплексных отсчетов типа float
  
  Метод предназначен для вычисления амплитуды комплексных отсчетов типа float.
  Значение амплитуды рассчитывается как корень из суммы квадратов реальной и мнимой
  частей отсчетов входного массива. Метод возвращает код ошибки ErrorCode_Ta
  
  \param [in]      pSrc   указатель на входной массив комплексных отсчетов типа float
  \param [out]     pDst   указатель на выходной массив амплитуд входных отсчетов
  \param [in]      size   размер входного и выходного массивов
  
*/
/////////////////////////////////////////////////////////////////////////////////////
ErrorCode_Ta TaClass::magnitude_32fc(const complex<float> * pSrc, float * pDst,
                                     int size)
{
    if (pSrc == 0 || pDst == 0)
    {
        ERROROUT InvalidData;
        return InvalidData;
    }
    if (size < 1)
    {
        ERROROUT InvalidSize;
        return InvalidSize;
    }
    
    for (int i = 0; i < size; i++)
    {
        pDst[i] = sqrtf(pSrc[i].real()*pSrc[i].real()+
                        pSrc[i].imag()*pSrc[i].imag());
    }
    
    return NoError;
}

/////////////////////////////////////////////////////////////////////////////////////
/*!
  \brief  Метод вычисления фазы комплексных отсчетов типа float
  
  Метод предназначен для вычисления фазы комплексных отсчетов типа float.
  Значение амплитуды рассчитывается как арктангенс отношения реальной к мнимой
  частей отсчетов входного массива. Метод возвращает код ошибки ErrorCode_Ta
  
  \param [in]      pSrc   указатель на входной массив комплексных отсчетов типа float
  \param [out]     pDst   указатель на выходной массив амплитуд входных отсчетов
  \param [in]      size   размер входного и выходного массивов
  
*/
/////////////////////////////////////////////////////////////////////////////////////
ErrorCode_Ta TaClass::phase_32fc(const complex<float>   * pSrc,
                                 float * pDst,
                                 int size)
{
    if (pSrc == 0 || pDst == 0)
    {
        ERROROUT InvalidData;
        return InvalidData;
    }
    if (size < 1)
    {
        ERROROUT InvalidSize;
        return InvalidSize;
    }
    
    for (int i = 0; i < size; i++)
    {
        pDst[i] = atan2(pSrc[i].imag(),pSrc[i].real());
    }
    
    return NoError;
}

/////////////////////////////////////////////////////////////////////////////////////
/*!
  \brief  Метод вычисления амплитуды комплексных отсчетов типа float с накоплением
  
  Метод предназначен для вычисления амплитуды комплексных отсчетов типа float.
  Значение амплитуды рассчитывается как корень из суммы квадратов реальной и мнимой
  частей отсчетов входного массива. Результат вычисления амлитуды каждого элемента
  входного массива прибавляется к соответсвующим элементам выходного массива(!).
  Мод возвращает код ошибки ErrorCode_Ta
  
  \param [in]      pSrc      указатель на входной массив комплексных отсчетов типа float
  \param [out]     pSrcDst   указатель на выходной массив амплитуд
  \param [in]      size      размер входного и выходного массивов
  
*/
/////////////////////////////////////////////////////////////////////////////////////
ErrorCode_Ta TaClass::magnAddVec_32fc(const complex<float>   * pSrc,
                                      float * pSrcDst, int size)
{
    if (pSrc == 0 || pSrcDst == 0)
    {
        ERROROUT InvalidData;
        return InvalidData;
    }
    if (size < 1)
    {
        ERROROUT InvalidSize;
        return InvalidSize;
    }
    
    for (int i = 0; i < size; i++)
    {
        pSrcDst[i] += sqrtf(pSrc[i].real()*pSrc[i].real()+
                            pSrc[i].imag()*pSrc[i].imag());
    }
    
    return NoError;
}

/////////////////////////////////////////////////////////////////////////////////////
/*!
  \brief  Метод нормировки входной функции по максимуму
  
  Метод предназначен для нормировки массива по максимуму (toVal = 1) или приведения
  максимума фукнции к заданному значению toVal. Метод возвращает код ошибки ErrorCode_Ta
  
  \param [in/щге]   pSrcDst  указатель на нормируемый массив
  \param [in]       toVal    желаемое значения максимума на выходе
  \param [in]       size     размер входного  массива
*/
/////////////////////////////////////////////////////////////////////////////////////
ErrorCode_Ta TaClass::normalizeToValue_32f(float * pSrcDst, int toVal, int size)
{
    if (pSrcDst == 0)
    {
        ERROROUT InvalidData;
        return InvalidData;
    }
    if (size < 1)
    {
        ERROROUT InvalidSize;
        return InvalidSize;
    }
    
    int index;
    float max;
    maxIndex_32f(pSrcDst,size,&max,&index);
    max/=toVal;
    divVecC_32f_I(max,pSrcDst,size);
    
    return NoError;
}

/////////////////////////////////////////////////////////////////////////////////////
/*!
  \brief  Метод нормировки входной функции по площади
  
  Метод предназначен для нормировки массива по площащи, вычисляемой как сумма
  значений массива, перемноженная на цену деления по оси абсцисс.
  Метод возвращает код ошибки ErrorCode_Ta
  
  \param [in/щге]   pSrcDst  указатель на нормируемый массив
  \param [in]       deltax   цена деления по оси абсцисс
  \param [in]       size     размер входного  массива
*/
/////////////////////////////////////////////////////////////////////////////////////
ErrorCode_Ta TaClass::normalizeToSum_32f(float * pSrcDst, float deltax, int size)
{
    if (pSrcDst == 0)
    {
        ERROROUT InvalidData;
        return InvalidData;
    }
    if (size < 1)
    {
        ERROROUT InvalidSize;
        return InvalidSize;
    }
    
    float sum = 0;
    sumVec_32f(&sum,pSrcDst,size);
    sum*=deltax;
    divVecC_32f_I(sum,pSrcDst,size);
    
    return NoError;
}

/////////////////////////////////////////////////////////////////////////////////////
/*!
  \brief  Метод вычисления комплексно сопряженного вектора
  
  Метод предназначен для комплексно сопряженного массива комплексных чисел.
  Метод возвращает код ошибки ErrorCode_Ta
  
  \param [in]   pSrc  указатель на входной массив комплексных отсчетов
  \param [out]  pDst  указатель на выходной массив комплексных отсчетов
  \param [in]   size  размер входного и выходного массивов
*/
/////////////////////////////////////////////////////////////////////////////////////
ErrorCode_Ta TaClass::conj_32fc(const complex<float> * pSrc,
                                complex<float> * pDst,
                                int size)
{
    if (pSrc == 0 || pDst == 0)
    {
        ERROROUT InvalidData;
        return InvalidData;
    }
    if (size < 1)
    {
        ERROROUT InvalidSize;
        return InvalidSize;
    }
    
    for (int i = 0 ; i < size; i++)
    {
        pDst[i].real(pSrc[i].real());
        pDst[i].imag(-pSrc[i].imag());
    }
    
    return NoError;
}


/////////////////////////////////////////////////////////////////////////////////////
/*!
  \brief  Метод вычисления производной
  
  Метод предназначен для вычисления производной функции, содержащейся во входном
  массиве. Метод возвращает код ошибки ErrorCode_Ta
  
  \param [in]   pSrc  указатель на входной массив отсчетов
  \param [out]  pDst  указатель на выходной массив
  \param [in]   size  размер входного и выходного массивов
*/
/////////////////////////////////////////////////////////////////////////////////////
ErrorCode_Ta TaClass::diffVec_32f(const float * pSrc,
                                  float * pDst,
                                  int size)
{
    if (pSrc == 0 || pDst == 0)
    {
        ERROROUT InvalidData;
        return InvalidData;
    }
    if (size < 1)
    {
        ERROROUT InvalidSize;
        return InvalidSize;
    }
    
    for (int i = 0 ; i < size-1; i++)
    {
        pDst[i] = pSrc[i+1]-pSrc[i];
    }
    pDst[size-1] = 0;
    
    return NoError;
}

/////////////////////////////////////////////////////////////////////////////////////
/*!
  \brief  Метод вычисления сренего арифметического
  
  Метод предназначен для вычисления среднего арифметического массива входных данных.
  Метод возвращает код ошибки ErrorCode_Ta
  
  \param [in]   pSrc  указатель на входной массив отсчетов
  \param [out]  mean  указатель на размещение вычисленного среднего
  \param [in]   size  размер входного  массива
*/
/////////////////////////////////////////////////////////////////////////////////////
ErrorCode_Ta TaClass::meanVec_32f(const float * pSrc,
                                  float * mean,
                                  int size)
{
    if (pSrc == 0)
    {
        ERROROUT InvalidData;
        return InvalidData;
    }
    if (size < 1)
    {
        ERROROUT InvalidSize;
        return InvalidSize;
    }
    
    *mean = 0;
    sumVec_32f(mean, pSrc ,size);
    *mean /= float(size);
    
    return NoError;
}

/////////////////////////////////////////////////////////////////////////////////////
/*!
  \brief  Метод устранения постоянной составляющей
  
  Метод предназначен для устранения постоянной составляющей в сигнале путем
  вычисления среднего и вычитания его из напряжения сигнала.
  Метод возвращает код ошибки ErrorCode_Ta
  
  \param [in/out]  pSrcDst  указатель на входной массив отсчетов
  \param [in]      size  размер входного и выходного массивов
*/
/////////////////////////////////////////////////////////////////////////////////////
ErrorCode_Ta TaClass::constRemove_32f(float * pSrcDst, int size)
{
    if (pSrcDst == 0)
    {
        ERROROUT InvalidData;
        return InvalidData;
    }
    if (size < 1)
    {
        ERROROUT InvalidSize;
        return InvalidSize;
    }
    
    float mean = 0;
    meanVec_32f(pSrcDst, &mean, size);
    subVecC_32f_I(mean,pSrcDst,size);
    
    return NoError;
}
/////////////////////////////////////////////////////////////////////////////////////
/*!
  \brief  Метод формирования аналитического (комплесного) сигнала
  
  Метод предназначен для расчета мнимой части по реальной и формирования аналитического
  (комплексного) представления сигнала на основе преобразования Гильберта.
  Метод возвращает код ошибки ErrorCode_Ta
  
  \param [in]    pSrc  указатель на входной массив реальных отсчетов типа float
  \param [out]   pDst  указатель на выходной массив комплексных отсчетов типа float
  \param [in]    size  размер входного и выходного массивов
*/
/////////////////////////////////////////////////////////////////////////////////////
ErrorCode_Ta TaClass::hilbertTransform_32f32fc(float  * pSrc, complex<float> * pDst,
                                               int size)
{
    if (pSrc == 0 || pDst == 0)
    {
        ERROROUT InvalidData;
        return InvalidData;
    }
    if (size < 1)
    {
        ERROROUT InvalidSize;
        return InvalidSize;
    }
    vector <complex <float>> temp32fc(size); //!! вынести за пределы метода выделение памяти
    
    memset(temp32fc.data(),0,sizeof(float)*2);
    fftwf_plan plan_r2c;
    
    plan_r2c = fftwf_plan_dft_r2c_1d(size,  pSrc, (fftwf_complex*) temp32fc.data(),
                                     FFTW_ESTIMATE); //!! вынести за пределы метода выделение памяти
    fftwf_execute(plan_r2c);
    fftwf_destroy_plan(plan_r2c);
    
    int n = 0;
    if (size%2==0)
    {
        n = size/2-1;
    }
    else
    {
        n = (size+1)/2-1;
    }
    
    temp32fc[0] = temp32fc[0];
    for (int i = 1 ; i < size; i++)
    {
        if (i<=n)
        {
            temp32fc[i].real(temp32fc[i].real()*2);
            temp32fc[i].imag(temp32fc[i].imag()*2);
        }
        else
        {
            if (size%2==0 && i==n+1)
            {
                temp32fc[i].real(temp32fc[i].real());
                temp32fc[i].imag(temp32fc[i].imag());
            }
            else
            {
                temp32fc[i].real(0);
                temp32fc[i].imag(0);
            }
        }
    }
    
    fftwf_plan plan_c2c;
    plan_c2c = fftwf_plan_dft_1d(size,(fftwf_complex*) temp32fc.data(),
                                 (fftwf_complex*) pDst,
                                 FFTW_BACKWARD, FFTW_ESTIMATE); //!! вынести за пределы метода выделение памяти
    fftwf_execute(plan_c2c);
    divVecC_32fc_I(float(size),pDst,size);
    fftwf_destroy_plan(plan_c2c);
    
    return NoError;
}


/////////////////////////////////////////////////////////////////////////////////////
/*!
  \brief  Метод переноса частоты сигнала
  
  Метод предназначен для переноса несущей (центральной) частоты сигнала путем
  перемножения на опорное колебание. Частота дискретизации принята равной 1.
  Метод возвращает код ошибки ErrorCode_Ta
  
  \param [in/out]   pSrcDst  указатель на массив комплексных отсчетов сигнала типа float
  \param [in]       fdelta   значение частоты, на которое нужно изменить частоту сигнала
                             относительно частоты дискретизации, т.е. [0,1]
  \param [in]       size     размер массивов отсчетов сигнала
  \param [in]       ts       размер массивов отсчетов сигнала
*/
/////////////////////////////////////////////////////////////////////////////////////
ErrorCode_Ta TaClass::freqTranslate_32fc(complex<float> * pSrcDst, float fdelta,
                                         int size,
                                         qint64 * ts)
{
    if (pSrcDst == 0 || ts == 0)
    {
        ERROROUT InvalidData;
        return InvalidData;
    }
    if (size < 1)
    {
        ERROROUT InvalidSize;
        return InvalidSize;
    }
    if (fdelta < -1 || fdelta > 1)
    {
        ERROROUT InvalidBandOrCentFreq;
        return InvalidBandOrCentFreq;
    }
    
    complex<float> ops;
    qint64 beg = *ts;
    double t = 0;
    for (qint64 i = 0; i < size; i++)
    {
        t = double(beg + i);
        //формируем отсчет опорного колебания
        ops.real(cos(2. * M_PI * double(fdelta) * t));
        ops.imag(sin(2. * M_PI * double(fdelta) * t));
        //Умножаем на опорное колебание
        pSrcDst[i] = pSrcDst[i]*ops;
    }
    *ts = t+1;
    
    return NoError;
}

/////////////////////////////////////////////////////////////////////////////////////
/*!
  \brief  Метод расчета АЧХ фильтра
  
  Метод предназначен для вычисления АЧХ фильтра по его импульсной характеристике с
  помощью БПФ. Метод возвращает код ошибки ErrorCode_Ta
  
  \param [out]    pDst  указатель на массив комплексных отсчетов АЧХ
  \param [in]     pSrc  указатель на массив комплексных коэффициентов
                        импульсной характеристики
  \param [in]     size  размер входного и выходноо массивов
  \param [in/out] ts    указатель на начальный и конечный отсчеты времени для
                        обеспечения непрерывности опорного колебания при поблочном
                        перемножении
*/
/////////////////////////////////////////////////////////////////////////////////////
ErrorCode_Ta TaClass::getFilterAFR_32fc(const complex<float> * pSrc,
                                        complex<float> * pDst,
                                        int size)
{
    if (pDst == 0 || pDst == 0)
    {
        ERROROUT InvalidData;
        return InvalidData;
    }
    if (size < 1)
    {
        ERROROUT InvalidSize;
        return InvalidSize;
    }
    
    //план прямого БПФ для вичисления АЧХ фильтра
    fftwf_plan planAch = fftwf_plan_dft_1d(size,(fftwf_complex*) pSrc,
                                           (fftwf_complex*) pDst,
                                           FFTW_FORWARD, FFTW_ESTIMATE);
    //вычисляем АЧХ фильтра
    fftwf_execute(planAch);
    //очищаем план прямого БПФ
    fftwf_destroy_plan(planAch);
    
    return NoError;
}

/////////////////////////////////////////////////////////////////////////////////////
/*!
  \brief  Метод половинного смещения амплитудного спектра комплексного сигнала
  
  Метод предназначен для половинного смещения амплитудного спектра комплексного
  сигнала. Входной массив делится пополам, полученные половины меняются местами.
  Метод возвращает код ошибки ErrorCode_Ta
  
  \param [in/out]    pSrcDst  массив отсчетов амплитудного спектра
  \param [in]     size  размер входного и выходноо массивов
*/
/////////////////////////////////////////////////////////////////////////////////////
ErrorCode_Ta TaClass::fftShift_32f(float * pSrcDst, int size)
{
    if (pSrcDst == 0)
    {
        ERROROUT InvalidData;
        return InvalidData;
    }
    if (size < 1)
    {
        ERROROUT InvalidSize;
        return InvalidSize;
    }
    
    float * buf = new float[size/2];
    memcpy(buf,                   pSrcDst,                sizeof(float)*size/2);
    memcpy(pSrcDst,               (char*)(pSrcDst+size/2),sizeof(float)*size/2);
    memcpy((char*)(pSrcDst+size/2),buf,                   sizeof(float)*size/2);
    delete[] buf;
    
    return NoError;
}


/////////////////////////////////////////////////////////////////////////////////////
/*!
  \brief Функция вычисления полной фазы сигнала (фазовый детектор)
  
  \param [in] sigVec   - указатель на массив отсчетов входного
                         сигнала сигнала размером не менее 5;
  \param [in] phaseVec - указатель на массив отсчетов с выхода
                         фазового детектора;
  \param [in] size     - размер массивов
*/
/////////////////////////////////////////////////////////////////////////////////////
ErrorCode_Ta TaClass::phaseDiscriminator32fc(const complex<float> * sigVec,
                                             float * phaseVec, int size)
{
    ErrorCode_Ta statusSFun = NoError;
    
    if (sigVec == 0 || phaseVec == 0)
    {
        ERROROUT InvalidData;
        return InvalidData;
    }
    if (size < 5)
    {
        ERROROUT InvalidSize;
        return InvalidSize;
    }
    
    //Вычисление полной фазы сигнала с разрывами фаз
    phase_32fc(sigVec, phaseVec, size);
    
    //устранение разрывов фаз (phase unwrap)
    float cumsum = 0.;
    float phaseOld = phaseVec[0];
    for (int i = 1; i < size; i++)
    {
        float dp  = phaseVec[i]-phaseOld;
        phaseOld  = phaseVec[i];
        float cel = floor((dp+M_PI)/2./M_PI);
        float dps = dp - 2.*M_PI*cel;
        if (dps == -M_PI && dp > 0)
        {
            dps = M_PI;
        }
        float dp_corr = dps - dp;
        if (abs(dp) < M_PI)
        {
            dp_corr = 0;
        }
        cumsum = cumsum + dp_corr;
        phaseVec[i] = phaseVec[i] + cumsum;
    }
    
    return statusSFun;
}


/////////////////////////////////////////////////////////////////////////////////////
/*!
  \brief Функция вычисления полной фазы сигнала (фазовый детектор)
  
  \param [in]    sigVec      указатель на массив отсчетов входного
                             сигнала сигнала размером не менее 5;
  \param [in]     phaseVec   указатель на массив отсчетов с выхода
                             фазового детектора;
  \param [in]     size       размер массивов
  \param [in/out] lastPhase  указатель на место хранения последнего
                             значения фазы при потоковой обработке
*/
/////////////////////////////////////////////////////////////////////////////////////
ErrorCode_Ta TaClass::phaseDiscriminator32fc(const complex<float> * sigVec,
                                             float * phaseVec, int size,
                                             float * lastPhase)
{
    ErrorCode_Ta statusSFun = NoError;
    
    if (sigVec == 0 || phaseVec == 0)
    {
        ERROROUT InvalidData;
        return InvalidData;
    }
    if (size < 5)
    {
        ERROROUT InvalidSize;
        return InvalidSize;
    }
    
    //Вычисление полной фазы сигнала с разрывами фаз
    phase_32fc(sigVec, phaseVec, size);
    
    //устранение разрывов фаз (phase unwrap)
    float cumsum = 0.;
    float phaseOld = *lastPhase;
    for (int i = 0; i < size; i++)
    {
        float dp  = phaseVec[i]-phaseOld;
        phaseOld  = phaseVec[i];
        float cel = floor((dp+M_PI)/2./M_PI);
        float dps = dp - 2.*M_PI*cel;
        if (dps == -M_PI && dp > 0)
        {
            dps = M_PI;
        }
        float dp_corr = dps - dp;
        if (abs(dp) < M_PI)
        {
            dp_corr = 0;
        }
        cumsum = cumsum + dp_corr;
        phaseVec[i] = phaseVec[i] + cumsum ;
    }
    
    *lastPhase = phaseVec[size-1];
    
    return statusSFun;
}

/////////////////////////////////////////////////////////////////////////////////////
/*!
  \brief Функция вычисления мгновенной частоты сигнала (частотный детектор)
  
  \param [in]     sigVec     указатель на массив отсчетов входного сигнала размером не
                             менее 5;
  \param [out]    freqVec    указатель на массив отсчетов с выхода частотного детектора;
  \param [in]     size       размер массивов;
  \param [in]     Fs         частота дискретизации
  \param [in/out] lastPhase  указатель на место хранения последнего значения фазы
                             в блоке для потоковой обработки
                             
*/
/////////////////////////////////////////////////////////////////////////////////////
ErrorCode_Ta TaClass::freqDiscriminator32f(const complex<float> * sigVec,
                                           float * freqVec,
                                           int   size,
                                           float Fs,
                                           bool  isAbs,
                                           float *lastPhase)
{
    ErrorCode_Ta statusSFun = NoError;
    
    if (Fs <= 0)
    {
        ERROROUT InvalidSampleRate;
        return InvalidSampleRate;
    }
    if (sigVec == 0 || freqVec == 0)
    {
        ERROROUT InvalidData;
        return InvalidData;
    }
    if (size < 5)
    {
        ERROROUT InvalidSize;
        return InvalidSize;
    }
    
    float firstsample = *lastPhase;
    
    //вектор полной фазы сигнала (с выхода фазового детектора)
    vector<float> phaseVec(size); //!!!!Вынести выделение памяти за пределы метода
    
    //фазовый детектор
    phaseDiscriminator32fc(sigVec, phaseVec.data(),size, lastPhase);
    
    //интервал дискретизации
    float   dt  = 1./float(Fs);
    
    
    if (isAbs)
        freqVec[0] = abs((phaseVec[0] - firstsample)/(2.*M_PI*dt));
    else
        freqVec[0] = (phaseVec[0] - firstsample)/(2.*M_PI*dt);
    
    *lastPhase = phaseVec[size-1];
    
    //вычисление производной полной фазы сигнала
    for (int i = 1; i < size; i++)
    {
        if (isAbs)
            freqVec[i] = abs((phaseVec[i]-phaseVec[i-1])/(2.*M_PI*dt));
        else
            freqVec[i] = (phaseVec[i]-phaseVec[i-1])/(2.*M_PI*dt);
    }
    
    return statusSFun;
}


/////////////////////////////////////////////////////////////////////////////////////
/*!
  \brief Функция вычисления мгновенной частоты сигнала (частотный детектор)
  
  \param [in]  sigVec   указатель на массив отсчетов входного сигнала размером не
                         менее 5;
  \param [out] freqVec  указатель на массив отсчетов с выхода частотного детектора;
  \param [in]  size     размер массивов;
  \param [in]  Fs       частота дискретизации
  
*/
/////////////////////////////////////////////////////////////////////////////////////
ErrorCode_Ta TaClass::freqDiscriminator32f(const complex<float> * sigVec,
                                           float * freqVec,
                                           int   size,
                                           float Fs,
                                           bool isAbs)
{
    ErrorCode_Ta statusSFun = NoError;
    
    if (Fs <= 0)
    {
        ERROROUT InvalidSampleRate;
        return InvalidSampleRate;
    }
    if (sigVec == 0 || freqVec == 0)
    {
        ERROROUT InvalidData;
        return InvalidData;
    }
    if (size < 5)
    {
        ERROROUT InvalidSize;
        return InvalidSize;
    }
    
    
    //вектор полной фазы сигнала (с выхода фазового детектора)
    vector<float> phaseVec(size); //!!!!Вынести выделение памяти за пределы метода
    
    //фазовый детектор
    phaseDiscriminator32fc(sigVec, phaseVec.data(),size);
    
    //интервал дискретизации
    float   dt  = 1./float(Fs);
    
    //вычисление производной полной фазы сигнала
    for (int i = 0; i < size-1; i++)
    {
        if (isAbs)
            freqVec[i] = abs((phaseVec[i+1]-phaseVec[i])/(2.*M_PI*dt));
        else
            freqVec[i] = (phaseVec[i+1]-phaseVec[i])/(2.*M_PI*dt);
    }
    
    //По-хорошему крайние отчеты легко можно вычислить
    //с помощью линейного интерполятора но пока это не принципиально
    freqVec[0] = freqVec[1];
    freqVec[size-1] = freqVec[size-2];
    
    
    return statusSFun;
}

/////////////////////////////////////////////////////////////////////////////////////
/*!
  \brief Метод вычисления автокорреляционной функции
  
  \param [in]  sigVec   указатель на массив отсчетов входного сигнала размером не
                         менее 5;
  \param [out] freqVec  указатель на массив отсчетов с выхода частотного детектора;
  \param [in]  size     размер массивов;
  \param [in]  Fs       частота дискретизации
  
*/
/////////////////////////////////////////////////////////////////////////////////////
ErrorCode_Ta TaClass::acf_32fc(complex<float> * sigVec,
                               float * acfVec,
                               int size)
{
    
    if (sigVec == 0 || acfVec == 0)
    {
        ERROROUT InvalidData;
        return InvalidData;
    }
    if (size < 1)
    {
        ERROROUT InvalidSize;
        return InvalidSize;
    }
    
    vector<complex<float>> spec1(size);
    vector<complex<float>> spec2(size);
    vector<complex<float>> acf_c(size);
    memset(spec1.data(),0,size*2*sizeof (float));
    memset(spec2.data(),0,size*2*sizeof (float));
    
    
    fftwf_plan  plan_c2c = fftwf_plan_dft_1d(size,
                                             (fftwf_complex*)sigVec,
                                             (fftwf_complex*) spec1.data(),
                                             FFTW_FORWARD, FFTW_ESTIMATE); //!! вынести за пределы метода выделение памяти
    fftwf_execute(plan_c2c);
    fftwf_destroy_plan(plan_c2c);
    
    conj_32fc(spec1.data(), spec2.data(),size);
    multVec_32fc_I(spec1.data(), spec2.data(), size);
    
    
    fftwf_plan  plan_c2cInv = fftwf_plan_dft_1d(size,
                                                (fftwf_complex*) spec2.data(),
                                                (fftwf_complex*) acf_c.data(),
                                                FFTW_BACKWARD, FFTW_ESTIMATE); //!! вынести за пределы метода выделение памяти
    fftwf_execute(plan_c2cInv);
    divVecC_32fc_I(float(size),acf_c.data(),size);
    
    fftwf_destroy_plan(plan_c2cInv);
    magnitude_32fc(acf_c.data(),acfVec,size);
    
    return NoError;
}

ErrorCode_Ta TaClass::acf_32f(float * sigVec,
                              float * acfVec,
                              int size)
{
    
    if (sigVec == 0 || acfVec == 0)
    {
        ERROROUT InvalidData;
        return InvalidData;
    }
    if (size < 1)
    {
        ERROROUT InvalidSize;
        return InvalidSize;
    }
    
    vector<complex<float>> spec1(size); //!! вынести за пределы метода выделение памяти
    vector<complex<float>> spec2(size); // Что-то с этим надо делать :(
    memset(spec1.data(),0,size*2*sizeof (float));
    memset(spec2.data(),0,size*2*sizeof (float));
    
    
    fftwf_plan plan_r2c = fftwf_plan_dft_r2c_1d(size,
                                                sigVec,
                                                (fftwf_complex*) spec1.data(),
                                                FFTW_ESTIMATE); //!! вынести за пределы метода выделение памяти
    fftwf_execute(plan_r2c);
    fftwf_destroy_plan(plan_r2c);
    
    conj_32fc(spec1.data(), spec2.data(),size);
    multVec_32fc_I(spec1.data(), spec2.data(), size);
    
    fftwf_plan plan_c2r = fftwf_plan_dft_c2r_1d(size,
                                                (fftwf_complex*) spec2.data(),
                                                acfVec,
                                                FFTW_ESTIMATE); //!! вынести за пределы метода выделение памяти
    fftwf_execute(plan_c2r);
    divVecC_32f_I(float(size),acfVec,size);
    fftwf_destroy_plan(plan_c2r);
    
    return NoError;
    
}



ErrorCode_Ta TaClass::histDeltaOpt(float * histOut, float * input, int size,
                                   float min, float delta, float max)
{
    if (histOut == 0 || input == 0)
    {
        ERROROUT InvalidData;
        return   InvalidData;
    }
    if (size < 1)
    {
        ERROROUT InvalidSize;
        return   InvalidSize;
    }
    
    if (min>max || max-min < 2*delta)
    {
        ERROROUT InvalidSize;
        return   InvalidSize;
    }
    
    
    int sizeHist = int((max-min+delta)/delta);
    memset(histOut,0,sizeHist*sizeof(float));
    for (int i=0;i<size;i++)
    {
        int histIndex = ceil((input[i]-delta/2.-min)/delta);
        histOut[histIndex]+=1;
    }
    
    return NoError;
}


ErrorCode_Ta TaClass::log10Vec(float * pSrc, float * pDst, int size, float multKoef)
{
    if (pSrc == 0 || pDst == 0)
    {
        ERROROUT InvalidData;
        return   InvalidData;
    }
    if (size < 1)
    {
        ERROROUT InvalidSize;
        return   InvalidSize;
    }
    
    
    for (int i = 0; i < size; i++)
    {
        pDst[i] = log10(pSrc[i])*multKoef;
    }
    
    return NoError;
}

ErrorCode_Ta TaClass::medFilt1_64f(double * pSrc, double * pDst, int size, int windSize)
{
    if (pSrc == 0 || pDst == 0)
    {
        ERROROUT InvalidData;
        return   InvalidData;
    }
    if (size < 1)
    {
        ERROROUT InvalidSize;
        return   InvalidSize;
    }
    
    vector<double> window(windSize);
    
    int index;
    if (windSize%2 == 0)
        index = windSize/2 - 1;
    else
        index = (windSize-1)/2;
    
    for (int i = 0; i < size; i++)
    {
        if ( i <= size - windSize)
        {
            sort_64f(pSrc+i, window.data(), windSize);
            pDst[i] = window[index];
        }
        else
        {
            int  cnt0 = windSize - size + i;
            int  cntN = size - i;
            memset((window.data() + cntN), 0 , cnt0 * sizeof (double));
            memcpy( window.data(), pSrc + i, cntN);
            sort_64f(window.data(), window.data(), windSize);
            pDst[i] = window[index];
        }
    }
    
    return NoError;
}


int TaClass::compare_64f(const void * x1, const void * x2)   // функция сравнения элементов массива
{
    return int(( *(double*)x1 - *(double*)x2 ) * 10.);              // если результат вычитания равен 0, то числа равны, < 0: x1 < x2; > 0: x1 > x2
}


ErrorCode_Ta TaClass::sort_64f(double * pSrc, double * pDst, int size)
{
    if (pSrc == 0 || pDst == 0)
    {
        ERROROUT InvalidData;
        return   InvalidData;
    }
    if (size < 1)
    {
        ERROROUT InvalidSize;
        return   InvalidSize;
    }
    
    memcpy(pDst, pSrc, size * sizeof (double));
    qsort(pDst, size, sizeof(double), compare_64f);
    
    return NoError;
}

float TaClass::interpMax(vector<float> & y)
{
    vector<float> x(3);
    x[0] = -1; x[1] = 0; x[2] = 1;
    float a=(y[2]-(x[2]*(y[1]-y[0])+x[1]*y[0]-x[0]*y[1])/(x[1]-x[0]))/(x[2]*(x[2]-x[0]-x[1])+x[0]*x[1]);
    float b=(y[1]-y[0])/(x[1]-x[0])-a*(x[0]+x[1]);
    return -b/(2*a);
}

vector<vector<float> > TaClass::transposeMatrix32f(vector<vector<float> > &matrix)
{
    vector<vector<float> > matrix_t;
    int rowCount = matrix.size();
    int colCount = matrix[0].size();
    matrix_t.resize(colCount);
    for (int i = 0; i < colCount; i++)
    {
        for (int j = 0; j<rowCount;j++ )
            matrix_t[i].push_back(matrix[j][i]);
    }
    return matrix_t;
}

void TaClass::rezerveMemoryForVec(vector<float> & vec, uint32_t * wantedCap)
{
    uint32_t need = * wantedCap;
    while (vec.capacity() == 0)
    {
        try
        {
            vec.reserve(need);
        }
        catch (const bad_alloc& ba)
        {
            qDebug() <<"ERROR: ";
            qDebug() << ba.what() << endl;
        }
        
        need -= (need/10);
    }
    *wantedCap = vec.capacity();
}

bool TaClass::pushBackToVec(vector<float> & vec, float val)
{
    bool ind = true;
    try
    {
        vec.push_back(val);
    }
    catch (const bad_alloc& ba)
    {
        qDebug() <<"ERROR: ";
        qDebug() << ba.what() << endl;
        ind = false;
    }
    return ind;
}

void TaClass::cancelProc()
{
    isCancelled = true;
}


