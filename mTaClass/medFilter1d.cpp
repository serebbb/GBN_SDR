﻿#include "mTaClass/medFilter1d.h"

void medFilter1d( double* array, int n, int filterSize )
{
  Mediator<double> mediator( filterSize );
  for (int i = 0; i < filterSize/2; i++)
  {
    mediator.insert( array[0] );
    array[i] = mediator.getMedian();
  }
  int offset = filterSize/2 + (filterSize % 2);
  for (int i = 0; i < offset; i++)
  {
    mediator.insert( array[i] );
  }
  for (int i = 0; i < n - offset; i++)
  {
    array[i] = mediator.getMedian();
    mediator.insert( array[i + offset] );
  }
  for (int i = n - offset; i < n; i++)
  {
    array[i] = mediator.getMedian();
    mediator.insert( array[n - 1] );
  }
}

void medFilter1d( float* array, int n, int filterSize )
{
  Mediator<float> mediator( filterSize );
  for (int i = 0; i < filterSize/2; i++)
  {
    mediator.insert( array[0] );
    array[i] = mediator.getMedian();
  }
  int offset = filterSize/2 + (filterSize % 2);
  for (int i = 0; i < offset; i++)
  {
    mediator.insert( array[i] );
  }
  for (int i = 0; i < n - offset; i++)
  {
    array[i] = mediator.getMedian();
    mediator.insert( array[i + offset] );
  }
  for (int i = n - offset; i < n; i++)
  {
    array[i] = mediator.getMedian();
    mediator.insert( array[n - 1] );
  }
}
void medFilter1d( long* array, int n, int filterSize )
{ 
  Mediator<long> mediator( filterSize );
  for (int i = 0; i < filterSize/2; i++)
  {
    mediator.insert( array[0] );
    array[i] = mediator.getMedian();
  }
  int offset = filterSize/2 + (filterSize % 2);
  for (int i = 0; i < offset; i++)
  {
    mediator.insert( array[i] );
  }
  for (int i = 0; i < n - offset; i++)
  {
    array[i] = mediator.getMedian();
    mediator.insert( array[i + offset] );
  }
  for (int i = n - offset; i < n; i++)
  {
    array[i] = mediator.getMedian();
    mediator.insert( array[n - 1] );
  }
}

void filterEachRow( double* array, int m, int n, int filterSize )
{
  for (int i = 0; i < m; i++)
  {
    medFilter1d( array + i*n, n, filterSize );
  }
}

void filterEachRow( long* array, int m, int n, int filterSize )
{
  for (int i = 0; i < m; i++)
  {
    medFilter1d( array + i*n, n, filterSize );
  }
}
