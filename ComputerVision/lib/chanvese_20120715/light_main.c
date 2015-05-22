
static int SetParam(programparams *Param)
{
	
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




/*Try to make a light main that take a stream of images as input and 
send a set of image as output*/

int main ()
{
	
	programparams Param;
	image f = NullImage;
	num c1,c2;/*only grayscale images*/
	int Status=1;
	FILE *fInputImg=fopen("test_images.txt","r");
	int cont = 0;
	char outputfile_name[10];
	
	/*set the Param*/
	if (!SetParam(&Param))
		goto Catch;
	
	while(fgets(Param.InputFile,50,fInputImg))
    {
     	
		cont++;
		
	 	Param.InputFile[strlen(Param.InputFile)-1]='\0';
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
        	f.Width, f.Height, f.NumChannels, Param.Opt))
    	{
        	fprintf(stderr, "Error in ChanVese.");
        	goto Catch;
    	}
		
		itoa(cont,outputfile_name,10);
		Param.OutputFile2=strcat(outputfile_name,".jpg");
		
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