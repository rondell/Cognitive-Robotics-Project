#include <stdio.h>
#include <string.h>
#include "chanvese/cliio.h"
#include "chanvese/chanvese.h"
#include "chanvese/chanvesecli.h"

int ActiveContour (float *Contour, image *ImageInput,float *OutPut)
{    


	programparams Param;
	image f = *ImageInput;
        
        fprintf(stdout, "[CONTOUR.C] First elements of image struct\n");
        for(int i=0; i<10; i++)
            fprintf(stdout, "%f ", f.Data[i]);
        
        fprintf(stdout, "\nwidth = %d height = %d channels = %d\n\n", f.Width, f.Height, f.NumChannels);
        
        
	float c1,c2;/*only grayscale images*/
	int Status=1;
	int cont = 0;
    int tmp=0;
	char Tmp_in_f[50];
	/*set the Param*/  	
	if (!SetParam(&Param, Contour, &f))
		goto Catch;
	
   
    

        
     	Param.InputFile=Tmp_in_f;
		cont++;
        
        
		
        tmp=strlen(Param.InputFile)-1;
        
	 	Param.InputFile[tmp]='\0';
       

		 
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
	 
	
	Status = 0;
Catch:
	 FreeImageObj(Param.Phi);
     FreeImageObj(f);
     ChanVeseFreeOpt(Param.Opt);
     return Status;
	
	
}
