//#include "circbuffer.h"

//template <class Type>
//CircBuffer<Type>::CircBuffer(int bufferSize,int blockSize):
//    sizeOfBuff(bufferSize), sizeOfBlock(blockSize)
//{
//    pointer    = new Type[sizeOfBuff];
//    if (pointer)
//        isAllocMem = true;
//    else
//        isAllocMem = false;

//    readCount  = 0;
//    writeCount = 0;
//}

//template <class Type>
//CircBuffer<Type>::~CircBuffer()
//{
//    if (isAllocMem)
//        delete [] pointer;
//}

//template <class Type>
//ErrorCode_m CircBuffer<Type>::writeBlock(const Type * block, int blockSize)
//{

//    if (!isAllocMem)
//    {
//        return AllocMemError;
//    }

//    if (blockSize <= 0 || blockSize%sizeof(Type) != 0)
//    {
//        return InvalidSize;
//    }

//    if (block == 0)
//    {
//        return InvalidData;
//    }

//    if (blockSize >= (sizeOfBuff - getQueueSize()))
//    {
//        return OverfullQueue;
//    }

//    uint64_t tempWriteCnt = writeCount.load();

//    int cntEnd = tempWriteCnt % uint64_t(sizeOfBuff);

//    if (sizeOfBuff - cntEnd >= blockSize)
//    {
//        memcpy(pointer + cntEnd,
//               block,
//               blockSize * sizeof(Type));
//    }
//    else
//    {
//        memcpy(pointer + cntEnd * sizeof(Type),
//               block,
//               (sizeOfBuff - cntEnd) * sizeof(Type));

//        memcpy(pointer,
//               block + (sizeOfBuff - cntEnd) * sizeof(Type),
//               (blockSize - sizeOfBuff + cntEnd) * sizeof(Type));
//    }
//    if (writeCount.testAndSetOrdered(tempWriteCnt, tempWriteCnt + sizeOfBlock))
//        return NoError;
//    else
//        return UnsuccessfulRead;
//}

//template <class Type>
//ErrorCode_m CircBuffer<Type>::readBlock(Type * block)
//{
//    if (!isAllocMem)
//    {
//        return AllocMemError;
//    }

//    uint64_t tempReadCnt = readCount.load();

//    if (getQueueSize() < 3 * sizeOfBlock)
//        return UndersizeQueue;

//    int cntBegin = tempReadCnt % sizeOfBuff;

//    if (sizeOfBuff - cntBegin - sizeOfBlock >= sizeOfBlock )
//    {
//        memcpy(block,
//               pointer + (cntBegin + sizeOfBlock) * sizeof(Type),
//               sizeOfBlock * sizeof(Type));
//    }
//    else
//    {
//        memcpy(block,
//               pointer + (cntBegin + sizeOfBlock) * sizeof(Type),
//               (sizeOfBuff   - cntBegin  - sizeOfBlock) * sizeof(Type));

//        memcpy(block + (sizeOfBuff - cntBegin   - sizeOfBlock) * sizeof(Type),
//               pointer,
//               (2*sizeOfBlock    - sizeOfBuff + cntBegin) * sizeof(Type));
//    }

//    if (readCount.testAndSetOrdered(tempReadCnt, tempReadCnt + sizeOfBlock))
//        return NoError;
//    else
//        return UnsuccessfulRead;
//}

//template <class Type>
//bool CircBuffer<Type>::isReadyToRead()
//{
//    if (isAllocMem && getQueueSize() < 3 * sizeOfBlock)
//        return false;
//    else
//        return true;
//}

//template <class Type>
//int CircBuffer<Type>::getQueueSize()
//{
//    int result = static_cast<int>(writeCount.load() - readCount.load());
//    return result;
//}

//template <class Type>
//uint64_t CircBuffer<Type>::getWriteCount()
//{
//    return writeCount.load();
//}


//template <class Type>
//uint64_t CircBuffer<Type>::getReadCount()
//{
//    return readCount.load();
//}


//template <class Type>
//void CircBuffer<Type>::clearBuffer()
//{
//    readCount.fetchAndStoreOrdered(0);
//    writeCount.fetchAndStoreOrdered(0);
//}
