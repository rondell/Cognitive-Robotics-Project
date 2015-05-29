/**
 * @file cliio.h
 * @brief Utilities for creating a command line interface
 * @author Pascal Getreuer <getreuer@gmail.com>
 */
#ifndef _CLIIO_H_
#define _CLIIO_H_

#include "num.h"


#ifdef NUM_SINGLE
#define IMAGEIO_NUM           (IMAGEIO_SINGLE)
#else
#define IMAGEIO_NUM           (IMAGEIO_DOUBLE)
#endif

/** @brief struct representing an image */
typedef struct
{
    /** @brief Float image data */
    num *Data;
    /** @brief Image width */
    int Width;
    /** @brief Image height */
    int Height;
    /** @brief Number of channels */
    int NumChannels;
} image;



void FreeImageObj(image f);/*mi serve*/


int IsGrayscale(num *Data, int Width, int Height);/*mi serve*/


extern const image NullImage;

#endif /* _CLIIO_H_ */
