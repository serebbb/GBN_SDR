#ifndef CIRCBUFFER_H
#define CIRCBUFFER_H
#pragma once
#include <QAtomicInteger>
#include "QDebug"

/// < Коды ошибок
enum ErrorCode_m
{
    NoErrorCB           = 0,     /// < нет ошибок
    InvalidDataCB       = 1,     /// < в качестве входного массива передан нулевой укзатель
    InvalidSizeCB       = 2,     /// < размер входного массива меньше  одного
    InvalidShiftCB      = 3,     /// < некорректный сдвиг
    OverfullQueueCB     = 4,     /// < переполнение очереди
    UndersizeQueueCB    = 5,     /// < недостаточный размер очереди
    UnsuccessfulReadCB  = 6,     /// < безуспешное чтение
    UnsuccessfulWriteCB = 7,     /// < безуспешная запись
    AllocMemErrorCB     = 8,     /// < не выделена память для буфера
    UknownErrorCB       = 9      /// < неизвестная ошибка
};

template <class Type>
/*!
  \brief Шаблонный класс создания кольцевого буфера CircBuffer.

  Класс CircBuffer предназначен для создания безблокировочной очереди данных
  любого типа в виде кольцевого буфера с целью обеспечения передачи данных
  между двумяпотоками: "потока-писателя" и "потока-читателя".
*/
class CircBuffer
{
public:
    QAtomicInteger<uint64_t> writeCount;   /// < глобальный счетчик поступивших данных в элементах
    QAtomicInteger<uint64_t> readCount;    /// < глобальный счетчик cчитанных данных в элементах
    int sizeOfBuff;                        /// < размер буфера в элементах
    int sizeOfBlock;                       /// < размер блока чтения из буфера в элементах
    Type * pointer;                        /// < указатель на начало буффера
    int    shift;                          /// < текущий тактовый сдвиг относительно начала блока чтения
    bool isAllocMem;                       /// < индикатор успешного выделения памяти под буффер
    bool isWriteFinish;                    /// < индикатор окончания записи в буффер
public:

    CircBuffer(int bufferSize = 2048,int blockSize = 128);
    ~CircBuffer();

    ErrorCode_m writeBlock(const Type * block, int size);
    ErrorCode_m readMidBlock(Type * block, int * shift);
    ErrorCode_m readMidBlock(Type * block);
    ErrorCode_m readLastBlock(Type * block);

    int         getQueueSize();
    float       getFullness();
    bool        getReadyToMidRead();
    bool        getReadyToLastRead();
    bool        getWriteFinish();
    uint64_t    getWriteCount();
    uint64_t    getReadCount();

    void        clearBuffer();
    void        setWriteFinish();
    void        setParams(int bufSize, int blSize);

};
//extern template class CircBuffer<float>;


template <class Type>
/*!
  \brief Конструктор класса CircBuffer.

  В конструкторе класса CircBuffer инициализируются поля и выделяется
  динамическая память размером bufferSize, заданным в виде параметра

  \param [in]  bufferSize   размер буфера в элементах
  \param [in]  blockSize    размер блока чтения в элементах
*/
CircBuffer<Type>::CircBuffer(int bufferSize,int blockSize):
    sizeOfBuff(bufferSize), sizeOfBlock(blockSize)
{
    pointer    = new Type[sizeOfBuff];
    if (pointer)
        isAllocMem = true;
    else
        isAllocMem = false;
    isWriteFinish = false;

    readCount  = 0;
    writeCount = 0;
}

template <class Type>
/*!
  \brief Деструктор класса CircBuffer.

  В деструкторе освобождается динамическая память,
  выделенная для буффера.
*/
CircBuffer<Type>::~CircBuffer()
{
    if (isAllocMem)
        delete [] pointer;
}

template <class Type>
/*!
  \brief Метод записи данных в очередь.

  В методе осуществляется запись данных в очередь.
  Метод возвращает код ошибки типа ErrorCode_m.

  \param [in]  *block     указатель на блок данных, который нужно записать в очередь
  \param [in]  blockSize  размер блока данных в элементах
*/
ErrorCode_m CircBuffer<Type>::writeBlock(const Type * block, int blockSize)
{
    if (!isAllocMem)
    {
        return AllocMemErrorCB;
    }

    if (blockSize <= 0)
    {
        return InvalidSizeCB;
    }

    if (block == 0)
    {
        return InvalidDataCB;
    }

    if (blockSize >= (sizeOfBuff - getQueueSize()))
    {
        return OverfullQueueCB;
    }

    uint64_t tempWriteCnt = writeCount.load();

    int cntEnd = tempWriteCnt % uint64_t(sizeOfBuff);

    if (sizeOfBuff - cntEnd >= blockSize)
    {
        memcpy(pointer + cntEnd,
               block,
               blockSize * sizeof(Type));
    }
    else
    {
        memcpy(pointer + cntEnd,
               block,
               (sizeOfBuff - cntEnd) * sizeof(Type));

        memcpy(pointer,
               (block     + sizeOfBuff - cntEnd),
               (blockSize - sizeOfBuff + cntEnd) * sizeof(Type));
    }
    if (writeCount.testAndSetOrdered(tempWriteCnt, tempWriteCnt + blockSize))
        return NoErrorCB;
    else
        return UnsuccessfulReadCB;
}

template <class Type>
/*!
  \brief Метод чтения данных из очереди со сдвигом.

  В методе осуществляется чтение блока данных размером blockSize,
  заданным в конструкторе, из очереди с позиции blockSize+shift относительно
  начала очереди (первого элемента). В случае, если модуль значения сдвига
  превышает величину 3/4*blockSize, то величина сдвига меняется внутри функции
  следующему по правилу:
  shift+=blockSize при shift <-3/4*blockSize;
  shift-=blockSize при shift > 3/4*blockSize.
  Метод возвращает код ошибки типа ErrorCode_m.

  \param [in]  *block     указатель на блок данных, в который нужно записать
                          извлеченные из очереди данные
  \param [in]  *shift     указатель на свиг относительно blockSize
*/
ErrorCode_m CircBuffer<Type>::readMidBlock(Type * block, int * shift)
{
    if (!isAllocMem)
    {
        return AllocMemErrorCB;
    }

    if (getQueueSize() < 3*sizeOfBlock)
    {
        return UndersizeQueueCB;
    }

    if (block == 0)
    {
        return InvalidDataCB;
    }

    if (*shift > sizeOfBlock || *shift < -sizeOfBlock)
    {
        return InvalidShiftCB;
    }

    uint64_t tempReadCnt = readCount.load();

    int cntBegin = tempReadCnt % sizeOfBuff;

    if (sizeOfBuff - cntBegin - sizeOfBlock - *shift >= sizeOfBlock )
    {

        memcpy(block,
               pointer + cntBegin + sizeOfBlock + *shift,
               sizeOfBlock * sizeof(Type));
    }
    else
    {
        memcpy(block,
               pointer       + cntBegin + sizeOfBlock + *shift,
               (sizeOfBuff   - cntBegin - sizeOfBlock - *shift) * sizeof(Type));

        memcpy(block + sizeOfBuff - cntBegin  - sizeOfBlock - *shift,
               pointer,
               (2*sizeOfBlock - sizeOfBuff + cntBegin + *shift) * sizeof(Type));
    }

    int addBlocksize = sizeOfBlock;

    if (*shift < -sizeOfBlock + sizeOfBlock/4)
    {
        addBlocksize = 0;
        *shift += sizeOfBlock;
    }

    if (*shift >  sizeOfBlock - sizeOfBlock/4)
    {
        addBlocksize = 2 * sizeOfBlock;
        *shift -= sizeOfBlock;
    }

    if (readCount.testAndSetOrdered(tempReadCnt, tempReadCnt + addBlocksize))
        return NoErrorCB;
    else
        return UnsuccessfulReadCB;
}

template <class Type>
void CircBuffer<Type>::setParams(int bufSize, int blSize)
{
    sizeOfBuff = bufSize;
    sizeOfBlock = blSize;

    pointer    = new Type[sizeOfBuff];
    if (pointer)
        isAllocMem = true;
    else
        isAllocMem = false;
    isWriteFinish = false;

    readCount  = 0;
    writeCount = 0;
}

template <class Type>
/*!
  \brief Метод чтения данных из очереди.

  В методе осуществляется чтение блока данных размером blockSize,
  заданным в конструкторе, из очереди с позиции blockSize относительно
  начала очереди (первого элемента).
  Метод возвращает код ошибки типа ErrorCode_m.

  \param [in]  *block     указатель на блок данных, в который нужно записать
                          извлеченные из очереди данные
*/
ErrorCode_m CircBuffer<Type>::readMidBlock(Type * block)
{
    if (!isAllocMem)
    {
        return AllocMemErrorCB;
    }

    if (getQueueSize() < 3*sizeOfBlock)
    {
        return UndersizeQueueCB;
    }

    if (block == 0)
    {
        return InvalidDataCB;
    }

    uint64_t tempReadCnt = readCount.load();

    int cntBegin = tempReadCnt % sizeOfBuff;

    if (sizeOfBuff - cntBegin - sizeOfBlock >= sizeOfBlock )
    {

        memcpy(block,
               pointer + cntBegin + sizeOfBlock,
               sizeOfBlock * sizeof(Type));
    }
    else
    {
        memcpy(block,
               pointer     + cntBegin + sizeOfBlock,
               (sizeOfBuff - cntBegin - sizeOfBlock) * sizeof(Type));

        memcpy(block + sizeOfBuff - cntBegin  - sizeOfBlock,
               pointer,
               (2*sizeOfBlock - sizeOfBuff + cntBegin) * sizeof(Type));
    }

    if (readCount.testAndSetOrdered(tempReadCnt, tempReadCnt + sizeOfBlock))
        return NoErrorCB;
    else
        return UnsuccessfulReadCB;
}

template <class Type>
/*!
  \brief Метод чтения данных из начала очереди.

  В методе осуществляется чтение блока данных размером blockSize,
  заданным в конструкторе, из очереди начиная с первого элемента.
  Метод возвращает код ошибки типа ErrorCode_m.

  \param [in]  *block     указатель на блок данных, в который нужно записать
                          извлеченные из очереди данные.
*/
ErrorCode_m CircBuffer<Type>::readLastBlock(Type * block)
{
    if (!isAllocMem)
    {
        return AllocMemErrorCB;
    }

//    if (block == 0)
//    {
//        return InvalidDataCB;
//    }

    uint64_t tempReadCnt = readCount.load();

    int cntBegin = tempReadCnt % sizeOfBuff;

    memcpy(block,
           pointer + cntBegin,
           sizeOfBlock * sizeof(Type));

    if (readCount.testAndSetOrdered(tempReadCnt, tempReadCnt + sizeOfBlock))
        return NoErrorCB;
    else
        return UnsuccessfulReadCB;
}


template <class Type>
/*!
  \brief Метод определения готовности очереди для чтения методом readMidBlock().

  Метод определяет, готова ли очередь для получени из нее данных
  методом readMidBlock(). Возвращается true, если читать можно, и false
  в противном случае. Готовность определяется наличием не менее трех
  блоков чтения в очереди.
*/
bool CircBuffer<Type>::getReadyToMidRead()
{
    if (isAllocMem && getQueueSize() < 3*sizeOfBlock)
        return false;
    else
        return true;
}

template <class Type>
/*!
  \brief Метод определения готовности очереди для чтения методом readLastBlock().

  Метод определяет, готова ли очередь для получени из нее данных
  методом readLastBlock(). Возвращается true, если читать можно, и false
  в противном случае. Готовность определяется наличием не менее одного
  блока чтения в очереди.
*/
bool CircBuffer<Type>::getReadyToLastRead()
{
    if (isAllocMem && getQueueSize() < sizeOfBlock)
        return false;
    else
        return true;
}

template <class Type>
/*!
  \brief Метод определения числа элементов в очереди.

  Метод определяет, сколько элементов содержится в очереди.
*/
int CircBuffer<Type>::getQueueSize()
{
    int result = static_cast<int>(writeCount.load() - readCount.load());
    return result;
}

template <class Type>
/*!
  \brief Метод определения числа переданных элементов в очередь.

  Метод определяет, сколько элементов передано в очередь.
*/
uint64_t CircBuffer<Type>::getWriteCount()
{
    return writeCount.load();
}

template <class Type>
/*!
  \brief Метод определения числа полученных элементов из очереди.

  Метод определяет, сколько элементов получено из очереди.
*/
uint64_t CircBuffer<Type>::getReadCount()
{
    return readCount.load();
}

template <class Type>
/*!
  \brief Метод очищения очереди.

  Метод определяет очищает очередь путем обнуления счетчиков.
*/
void CircBuffer<Type>::clearBuffer()
{
    readCount.fetchAndStoreOrdered(0);
    writeCount.fetchAndStoreOrdered(0);
    isWriteFinish = false;
}

template <class Type>
/*!
  \brief Метод сигнализации о конце передаваемых данных.

  Метод устанавливает индикатор того, что передаваемых данные закончились.
*/
void CircBuffer<Type>::setWriteFinish()
{
    isWriteFinish = true;
}

template <class Type>
/*!
  \brief Метод определения завершенности передаваемых данных.

  Метод устанавливает читает значение индикатора того,
  что передаваемых данные закончились.
*/
bool CircBuffer<Type>::getWriteFinish()
{
    return isWriteFinish;
}

template <class Type>
/*!
  \brief Метод определения степени заполненности очереди в процентах.

  Метод определяет, насколько закончена очередь, в процентах.
*/
float CircBuffer<Type>::getFullness()
{
    return float(getQueueSize())/float(sizeOfBuff)*100.;
}

#endif // CIRCBUFFER_H
