#include <stdio.h>
#include <string.h>
#include "chanvese/cliio.h"
#include "chanvese/chanvese.h"
#include "chanvese/chanvesecli.h"

int ActiveContour (float *Contour, image *ImageInput,float *OutPut , int init)
{    
	programparams Param;
	image f = *ImageInput;        
	float c1,c2;/*only grayscale images*/
	int Status=1;
	int cont = 2;
    int tmp=0;
	
	/*set the Param*/  	
	if (!SetParam(&Param, Contour, &f))
		goto Catch;
	
    if (init==1){
        
        ChanVeseInitPhi(Param.Phi.Data, f.Width, f.Height, 0 );
        
    }
    

        
     	
		

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
        	f.Width, f.Height, f.NumChannels, Param.Opt,init))
    	{
        	fprintf(stderr, "Error in ChanVese.");
        	goto Catch;
    	}
		
		
		
		
		if( !WriteBinary(Param.Phi, OutPut))
        goto Catch;
	 
    
    
    
                return 1;
	Status = 0;
Catch:
     
    FreeImageObj(Param.Phi);
    FreeImageObj(f);
    ChanVeseFreeOpt(Param.Opt);
     return Status;
	
	
}
