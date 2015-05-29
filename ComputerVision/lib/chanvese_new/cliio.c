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
#include "cliio.h"


const image NullImage = {NULL, 0, 0, 0};




void FreeImageObj(image f)
{
    if(f.Data)
        free(f.Data);
}


int ReadImageObj(image *f, const char *FileName)
{
    
    if(!f || !(f->Data = (num *)ReadImage(&f->Width, &f->Height, FileName,
         IMAGEIO_NUM | IMAGEIO_RGB | IMAGEIO_PLANAR)))
    {
        *f = NullImage;
        return 0;
    }
    
    f->NumChannels = (IsGrayscale(f->Data, f->Width, f->Height)) ? 1:3;
    return 1;
}


int ReadImageObjGrayscale(image *f, const char *FileName)
{
    if(!f || !(f->Data = (num *)ReadImage(&f->Width, &f->Height, FileName,
         IMAGEIO_NUM | IMAGEIO_GRAYSCALE | IMAGEIO_PLANAR)))
    {
        *f = NullImage;
        return 0;
    }
    
    f->NumChannels = 1;
    return 1;
}




/** @brief Check whether all three channels in a color image are the same */
int IsGrayscale(num *Data, int Width, int Height)
{    
    const long NumPixels = ((long)Width) * ((long)Height);
    const num *Red = Data;
    const num *Green = Data + NumPixels;
    const num *Blue = Data + 2*NumPixels;
    long n;
    
    for(n = 0; n < NumPixels; n++)
        if(Red[n] != Green[n] || Red[n] != Blue[n])
            return 0;
    
    return 1;
}











