#ifndef MEDFILTER1D_H
#define MEDFILTER1D_H
#pragma once
#include "mTaClass/mediator.h"

void medFilter1d( double* array, int n, int filterSize );
void medFilter1d( float* array, int n, int filterSize );
void medFilter1d( long* array, int n, int filterSize );
void filterEachRow( double* array, int m, int n, int filterSize );
void filterEachRow( long* array, int m, int n, int filterSize );

#endif
