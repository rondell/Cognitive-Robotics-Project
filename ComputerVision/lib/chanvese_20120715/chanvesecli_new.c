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
#include "cliio.h"
#include "chanvese.h"

#include "rgb2ind.h"

#define ROUNDCLAMP(x)   ((x < 0) ? 0 : \
    ((x > 1) ? 255 : (uint8_t)floor(255.0*(x) + 0.5)))

#ifdef __GNUC__
    /** @brief Macro for the unused attribue GNU extension */
    #define ATTRIBUTE_UNUSED __attribute__((unused))
#else
    #define ATTRIBUTE_UNUSED
#endif

/** @brief Program parameters struct */
typedef struct
{
    /** @brief Input file name */
    //MODIFIED BY GARO: re-put a const
    char *InputFile;
    /** @brief Animation output file name */
    const char *OutputFile;
    /** @brief Binary output file name */
    const char *OutputFile2;
    /** @brief Quality for saving JPEG images (0 to 100) */
    int JpegQuality;
  
    /** @brief Level set */
    image Phi;
    /** @brief ChanVese options object */
    chanveseopt *Opt;
    
    int IterPerFrame;
} programparams;

/** @brief Plotting parameters struct */
typedef struct
{
    const num *Image;
    unsigned char *Plot;
    int *Delays;
    int IterPerFrame;
    int NumFrames;
} plotparam;


static void PrintHelpMessage()
{
    puts("chanvese, P. Getreuer 2011-2012\n"
    "Chan-Vese segmentation IPOL demo\n\n"
    "Usage: chanvese [param:value ...] input animation final \n\n"
    "where \"input\" and \"final\" are " 
    READIMAGE_FORMATS_SUPPORTED " files\n"
    "and \"animation\" is a GIF file.\n");
    puts("Parameters\n");
    puts("   mu:<number>           length penalty (default 0.25)");
    puts("   nu:<number>           area penalty (default 0.0)");
    puts("   lambda1:<number>      fit weight inside the cuve (default 1.0)");
    puts("   lambda2:<number>      fit weight outside the curve (default 1.0)");
    puts("   phi0:<file>           read initial level set from an image or text file");
    puts("   tol:<number>          convergence tolerance (default 1e-3)");
    puts("   maxiter:<number>      maximum number of iterations (default 500)");
    puts("   dt:<number>           time step (default 0.5)\n");
    puts("   iterperframe:<number> iterations per frame (default 10)\n");
#ifdef LIBJPEG_SUPPORT
    puts("   jpegquality:<number>  Quality for saving JPEG images (0 to 100)\n");
#endif
    puts("Example:\n"    
#ifdef LIBPNG_SUPPORT
    "   chanvese tol:1e-5 mu:0.5 input.png animation.gif final.png\n");
#else    
    "   chanvese tol:1e-5 mu:0.5 input.bmp animation.gif final.bmp\n");    
#endif    
}


static int PlotFun(int State, int Iter, num Delta,
    const num *c1, const num *c2, const num *Phi,
    int Width, int Height, int NumChannels, void *ParamPtr);
static int ParseParam(programparams *Param, int argc, const char *argv[]);
static int PhiRescale(image *Phi);


int WriteBinary(image Phi, num *Temp)
{
    
    const int NumPixels = Phi.Width*Phi.Height;
    int i, Success;
    
    if(!(Temp = (num *)malloc(Phi.Width*Phi.Height)))
        return 0;
    
    for(i = 0; i < NumPixels; i++)
         if (Phi->Data[i] > 0 || Phi->Data[i] < -1e-3 )
            {
                 Temp[i] = 255;
                 Phi->Data[i]=Phi->Data[i]*0.0001;
                 
            }else 
                {
                Temp[i]=0;
                Phi->Data[i]=Phi->Data[i]*0.0001;
            }
    
  
    
    
    return 1;
}



static int SetParam(programparams *Param, num *Contour, image *input)
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




/*Try to make a light main that take a stream of images as input and 
send a set of image as output*/

int Active_Contour (num *Contour, image *ImageInput,num *OutPut)/* Dopo chiederà in ingresso : num *Phi , num *InputImage , num *Output, int Width , int Height(last two are inside the Image output)*/
{
	
   
    
    
	programparams Param;
	image f = ImageInput;
	num c1,c2;/*only grayscale images*/
	int Status=1;
	FILE *fInputImg=fopen("test_image.txt","r");
	int cont = 0;
    int tmp=0;
	char Tmp_in_f[50];
	/*set the Param*/  	
	if (!SetParam(&Param, Contour, f))
		goto Catch;
	
   
    
	while( (fgets(Tmp_in_f,50,fInputImg)))/*sarà esterno*/
    {
        
     	Param.InputFile=Tmp_in_f;
		cont++;
        
        
		
        tmp=strlen(Param.InputFile)-1;
        
	 	Param.InputFile[tmp]='\0';
          
		/* Read the input image */
    	if(!ReadImageObj(&f, Param.InputFile))  /*f dovrà essere data, height e width */
        	goto Catch;

		 
		if(Param.Phi.Data && 
        (f.Width != Param.Phi.Width || f.Height != Param.Phi.Height))
   	 	{
        fprintf(stderr, "Size mismatch: "
            "phi0 (%dx%d) does not match image size (%dx%d).\n",
            Param.Phi.Width, Param.Phi.Height, f.Width, f.Height);
        goto Catch;
   		 } 
	 

         
		 
		  /* Perform the segmentation */
   	 	if(!ChanVese(Param.Phi.Data, f.Data, 
        	f.Width, f.Height, f.NumChannels, Param.Opt,cont))
    	{
        	fprintf(stderr, "Error in ChanVese.");
        	goto Catch;
    	}
		
		
		
		
		if( !WriteBinary(Param.Phi, OutPut))
        goto Catch;
	 
	}
	
	fclose(fInputImg);
	Status = 0;
Catch:
	 FreeImageObj(Param.Phi);
     FreeImageObj(f);
     ChanVeseFreeOpt(Param.Opt);
     return Status;
	
	
}


static int ParseParam(programparams *Param, int argc, const char *argv[])
{
    const char *Option, *Value;
    num NumValue;
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
        
    if(argc >1)
    {
        PrintHelpMessage();
        return 0;
    }

    return 1;
}


/* If phi is read from an image file, this function is called to rescale
   it from the range [0,1] to [-10,10].  */
static int PhiRescale(image *Phi)
{    
    const long NumEl = ((long)Phi->Width) * ((long)Phi->Height);
    num *Data = Phi->Data;
    long n;

    for(n = 0; n < NumEl; n++)
        Data[n] = 4*(2*Data[n] - 1);

    return 1;
}

