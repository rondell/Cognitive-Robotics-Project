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
#include "gifwrite.h"
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


int WriteBinary(image Phi, const char *File)
{
    unsigned char *Temp = NULL;
    const int NumPixels = Phi.Width*Phi.Height;
    int i, Success;
    
    if(!(Temp = (unsigned char *)malloc(Phi.Width*Phi.Height)))
        return 0;
    
    for(i = 0; i < NumPixels; i++)
        Temp[i] = (Phi.Data[i] >= 0) ? 255 : 0;
    
    Success = WriteImage(Temp, Phi.Width, Phi.Height, File, 
        IMAGEIO_U8 | IMAGEIO_GRAYSCALE, 0);
    
    free(Temp);
    return Success;
}

//MODIFIED BY GARO:input int vid_frame added
int WriteAnimation(plotparam *PlotParam, int Width, int Height,
    const char *OutputFile)
{
    const int NumPixels = Width*Height;
    unsigned char *PlotInd = NULL;
    unsigned char *Palette = NULL;
    unsigned char **PlotIndFrames = NULL;    
    int Frame, Success = 0;
    
    
    
    if(!(PlotInd = (unsigned char *)malloc(Width*Height*PlotParam->NumFrames))
        || !(Palette = (unsigned char *)calloc(3*256, 1))
        || !(PlotIndFrames = (unsigned char **)
            malloc(sizeof(unsigned char *)*PlotParam->NumFrames)))
        goto Catch;
    
    for(Frame = 0; Frame < PlotParam->NumFrames; Frame++)
        PlotIndFrames[Frame] = PlotInd + NumPixels*Frame;
    
    /* Quantize colors for GIF */
    if(!Rgb2Ind(PlotInd, Palette, 255, PlotParam->Plot, 
        Width*Height*PlotParam->NumFrames))
        goto Catch;
    
    /* Optimize animation */
    FrameDifference(PlotIndFrames, Width, Height, PlotParam->NumFrames, 255);
    
    /* Write the output animation */
    if(!GifWrite(PlotIndFrames, Width, Height, PlotParam->NumFrames,
        Palette, 256, 255, PlotParam->Delays, OutputFile))
    {
        fprintf(stderr, "Error writing \"%s\".\n", OutputFile);
        goto Catch;
    }
    else
        printf("Output written to \"%s\".\n", OutputFile);    
    
    Success = 1;
Catch:
    if(PlotIndFrames)
        free(PlotIndFrames);
    if(Palette)
        free(Palette);
    if(PlotInd)
        free(PlotInd);
    return Success;
}


static int SetParam(programparams *Param)
{
	
	Param->InputFile = NULL;
    Param->OutputFile = NULL;
    Param->OutputFile2 = NULL;
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




/*Try to make a light main that take a stream of images as input and 
send a set of image as output*/

int main (int argc,char *argv[])
{
	
   
    printf("prova");
    
	programparams Param;
	image f = NullImage;
	num c1,c2;/*only grayscale images*/
	int Status=1;
	FILE *fInputImg=fopen("test_image.txt","r");
	int cont = 0;
    int tmp=0;
	char Tmp_in_f[50];
	/*set the Param*/  	
	if (!SetParam(&Param))
		goto Catch;
	
   
    
	while( (fgets(Tmp_in_f,50,fInputImg)))
    {
        
     	Param.InputFile=Tmp_in_f;
		cont++;
        
        
		
        tmp=strlen(Param.InputFile)-1;
        
	 	Param.InputFile[tmp]='\0';
          
		/* Read the input image */
    	if(!ReadImageObj(&f, Param.InputFile))
        	goto Catch;

		 
		if(Param.Phi.Data && 
        (f.Width != Param.Phi.Width || f.Height != Param.Phi.Height))
   	 	{
        fprintf(stderr, "Size mismatch: "
            "phi0 (%dx%d) does not match image size (%dx%d).\n",
            Param.Phi.Width, Param.Phi.Height, f.Width, f.Height);
        goto Catch;
   		 } 
	 
	 	if(!Param.Phi.Data)
   		{
        	if(!AllocImageObj(&Param.Phi, f.Width, f.Height, 1))
        	{
            fprintf(stderr, "Out of memory.");
            goto Catch;
      	  	}
			ChanVeseInitPhi(Param.Phi.Data, Param.Phi.Width, Param.Phi.Height);
    	 }
         
         
         
		 
		  /* Perform the segmentation */
   	 	if(!ChanVese(Param.Phi.Data, f.Data, 
        	f.Width, f.Height, f.NumChannels, Param.Opt,cont))
    	{
        	fprintf(stderr, "Error in ChanVese.");
        	goto Catch;
    	}
		
		
		Param.OutputFile2="Out.jpg";
		
		if(Param.OutputFile2 && !WriteBinary(Param.Phi, Param.OutputFile2))
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

/* Plot callback function */
static int PlotFun(int State, int Iter, ATTRIBUTE_UNUSED num Delta,
    ATTRIBUTE_UNUSED const num *c1, ATTRIBUTE_UNUSED const num *c2, 
    const num *Phi, int Width, int Height, 
    ATTRIBUTE_UNUSED int NumChannels, void *ParamPtr)
{
    const int NumPixels = Width*Height;
    plotparam *PlotParam = (plotparam *)ParamPtr;
    unsigned char *Plot, *Temp = NULL;    
    int *Delays = NULL;
    num Red, Green, Blue, Alpha;
    long i;
    int x, y, Edge, NumFrames = PlotParam->NumFrames, Success = 0;
    int il, ir, iu, id;
    
    switch(State)
    {
    case 0:
        /* We print to stderr so that messages are displayed on the console
           immediately, during the TvRestore computation.  If we use stdout,
           messages might be buffered and not displayed until after TvRestore
           completes, which would defeat the point of having this real-time 
           plot callback. */
        if(NumChannels == 1)
            fprintf(stderr, "   Iteration %4d     Delta %7.4f     c1 = %6.4f     c2 = %6.4f\r", 
                Iter, Delta, *c1, *c2);
        else
            fprintf(stderr, "   Iteration %4d     Delta %7.4f\r", Iter, Delta);
        break;
    case 1: /* Converged successfully */
        fprintf(stderr, "Converged in %d iterations.                                            \n", 
            Iter);
        break;
    case 2: /* Maximum iterations exceeded */
        fprintf(stderr, "Maximum number of iterations exceeded.                                 \n");
        break;
    }
    
    if(State == 0 && (Iter % PlotParam->IterPerFrame) > 0)
        return 1;
    
    if(!(Plot = (unsigned char *)realloc(PlotParam->Plot, 
        3*Width*Height*(PlotParam->NumFrames + 1)))
        || !(Delays = (int *)realloc(PlotParam->Delays, 
        sizeof(int)*(PlotParam->NumFrames + 1)))
        || !(Temp = (unsigned char *)malloc(Width*Height)))
    {
        fprintf(stderr, "Out of memory.\n");
        goto Catch;
    }
    
    PlotParam->Plot = Plot;
    PlotParam->Delays = Delays;
    Plot += 3*NumPixels*PlotParam->NumFrames;
    
    for(y = 0, i = 0; y < Height; y++)
        for(x = 0; x < Width; x++, i++)
        {
            if(Phi[i] >= 0 &&    
                ((x > 0          && Phi[i - 1] < 0)
                    || (x + 1 < Width  && Phi[i + 1] < 0)
                    || (y > 0          && Phi[i - Width] < 0)
                    || (y + 1 < Height && Phi[i + Width] < 0)))
                Edge = 1;       /* Inside the curve, on the edge */
            else
                Edge = 0;                
            
            Temp[i] = Edge;
        }
        
    for(y = 0, i = 0; y < Height; y++)
    {
        iu = (y == 0) ? 0 : -Width;
        id = (y == Height - 1) ? 0 : Width;
            
        for(x = 0; x < Width; x++, i++)
        {
            il = (x == 0) ? 0 : -1;
            ir = (x == Width - 1) ? 0 : 1;
            
            Red = PlotParam->Image[i];
            Green = PlotParam->Image[i + NumPixels];
            Blue = PlotParam->Image[i + 2*NumPixels];
            
            Red = 0.95f*Red;
            Green = 0.95f*Green;
            Blue = 0.95f*Blue;
            
            i = x + Width*y;
            Alpha = (4*Temp[i]
                + Temp[i + ir] + Temp[i + il] 
                + Temp[i + id] + Temp[i + iu])/4.0f;
                
            if(Alpha > 1)
                Alpha = 1;
            
            Red = (1 - Alpha)*Red;
            Green = (1 - Alpha)*Green;
            Blue = (1 - Alpha)*Blue + Alpha;
            
            Plot[3*i + 0] = ROUNDCLAMP(Red);
            Plot[3*i + 1] = ROUNDCLAMP(Green);
            Plot[3*i + 2] = ROUNDCLAMP(Blue);
        }
    }
    
    PlotParam->Delays[NumFrames] = (State == 0) ? 12 : 120;
    PlotParam->NumFrames++;
    
    Success = 1;
Catch:
    if(Temp)
        free(Temp);
    return Success;
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

