/**
 * @file chanvesecli.c
 * @brief Chan-Vese image segmentation IPOL demo
 * @author Pascal Getreuer <getreuer@gmail.com>
 * 
 * Copyright (c) 2011-2012, Pascal Getreuer
 * All rights reserved.
 * 
 * This program is free software: you can use, modify and/or 
 * redistribute it under the terms of the simplified BSD License. You 
 * should have received a copy of this license along this program. If 
 * not, see <http://www.opensource.org/licenses/bsd-license.html>.
 */

/**
 * @mainpage
 * @verbinclude readme.txt
 */

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "chanvese/cliio.h"
#include "chanvese/chanvese.h"
#include "chanvese/chanvesecli.h"

#define ROUNDCLAMP(x)   ((x < 0) ? 0 : \
    ((x > 1) ? 255 : (uint8_t)floor(255.0*(x) + 0.5)))

#ifdef __GNUC__
    /** @brief Macro for the unused attribue GNU extension */
    #define ATTRIBUTE_UNUSED __attribute__((unused))
#else
    #define ATTRIBUTE_UNUSED
#endif


int WriteBinary(image Phi, float *Temp)
{
    
    const int NumPixels = Phi.Width*Phi.Height;
    int i, Success;
    
    /*if(!(Temp = (float *)malloc(Phi.Width*Phi.Height)))
        return 0;*/
    
    for(i = 0; i < NumPixels; i++)
    {
         if (Phi.Data[i] >= 0  )
            {
                 Temp[i] = 255;
                 Phi.Data[i]=Phi.Data[i]*1;
               
            }
        if (Phi.Data[i]<0)
                {
             
                Temp[i]=0;
                Phi.Data[i]=Phi.Data[i]*1;
            }
    }
  
    
    
    return 1;
}



int SetParam(programparams *Param, float *Contour, image *input)
{
	/*useless*/
	Param->InputFile = NULL;
    Param->OutputFile = NULL;
    Param->OutputFile2 = NULL;
    Param->JpegQuality = 85;
     Param->IterPerFrame = 10;
    /*finish useless*/
    Param->Phi.Data=Contour;
    Param->Phi.Width=input->Width;
    Param->Phi.Height=input->Height;
    Param->Opt = NULL;
   
	
	 if(!(Param->Opt = ChanVeseNewOpt()))
    {
        fprintf(stderr, "Out of memory.\n");
        return 0;
    }
	
	
	
	return 1;
	
}

int ParseParam(programparams *Param, int argc, const char *argv[])
{
    const char *Option, *Value;
    float NumValue;
    char TokenBuf[256];
    int k, kread, Skip;
    
    
    /* Set parameter defaults */
    Param->InputFile = NULL;
    Param->OutputFile = NULL;
    Param->JpegQuality = 85;
    Param->Phi = NullImage;
    Param->Opt = NULL;
    Param->IterPerFrame = 10;
    
    if(!(Param->Opt = ChanVeseNewOpt()))
    {
        fprintf(stderr, "Out of memory.\n");
        return 0;
    }

    return 1;
}


/* If phi is read from an image file, this function is called to rescale
   it from the range [0,1] to [-10,10].  */
int PhiRescale(image *Phi)
{    
    const long NumEl = ((long)Phi->Width) * ((long)Phi->Height);
    float *Data = Phi->Data;
    long n;

    for(n = 0; n < NumEl; n++)
        Data[n] = 4*(2*Data[n] - 1);

    return 1;
}

