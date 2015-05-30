/**
 * @file cliio.c
 * @brief Utilities for creating a command line interface
 * @author Pascal Getreuer <getreuer@gmail.com>
 */
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "chanvese/cliio.h"
#include "chanvese/chanvese.h"
#include "chanvese/chanvesecli.h"


const image NullImage = {NULL, 0, 0, 0};




void FreeImageObj(image f)
{
    if(f.Data)
        free(f.Data);
}

/** @brief Check whether all three channels in a color image are the same */
int IsGrayscale(float *Data, int Width, int Height)
{    
    const long NumPixels = ((long)Width) * ((long)Height);
    const float *Red = Data;
    const float *Green = Data + NumPixels;
    const float *Blue = Data + 2*NumPixels;
    long n;
    
    for(n = 0; n < NumPixels; n++)
        if(Red[n] != Green[n] || Red[n] != Blue[n])
            return 0;
    
    return 1;
}











