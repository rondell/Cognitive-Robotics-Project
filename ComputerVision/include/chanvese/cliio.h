/**
 * @file cliio.h
 * @brief Utilities for creating a command line interface
 * @author Pascal Getreuer <getreuer@gmail.com>
 */
#ifndef _CLIIO_H_
#define _CLIIO_H_

/** @brief struct representing an image */
typedef struct
{
    /** @brief Float image data */
    float *Data;
    /** @brief Image width */
    int Width;
    /** @brief Image height */
    int Height;
    /** @brief Number of channels */
    int NumChannels;
} image;



void FreeImageObj(image f);/*mi serve*/


int IsGrayscale(float *Data, int Width, int Height);/*mi serve*/


extern const image NullImage;

#endif /* _CLIIO_H_ */
