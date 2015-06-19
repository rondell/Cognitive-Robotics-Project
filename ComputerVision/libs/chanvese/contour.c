#include <stdio.h>
#include <string.h>
#include "chanvese/chanvese.h"

int ActiveContour (float *src, float *dst, float *contour, float* mask, int width, int height)
{        
    num c1[3], c2[3];
    int cu,cd,cl,cr;
    chanveseopt* opt = ChanVeseNewOpt();
    opt->MaxIter = 1;
    /* Perform the segmentation */

        if(!ChanVese(contour, src, mask, width, height, 1, opt))
        {
            fprintf(stderr, "Error in ChanVese.");
            return 0;
        }

    /* Compute the final region averages */
    RegionAverages(c1, c2, contour, src, width, height, 1);
    
    //printf("\nRegion averages\n");
    
    for(int i=0; i<width*height; i++) {
        //contour[i]=(contour[i]>=0) ? 1 : -1;
        
        /*
        cl=i%width==0 ? i : i-1;
        cr=i%width== width-1 ? i : i+1;
        cd=i/width>height-2? i : i+width ;
        cu=i/width<1? i : i-width;
        cl=contour[cl]<0;
        cr=contour[cr]<0;
        cd=contour[cd]<0;
        cu=contour[cu]<0;
        dst[i] = (contour[i] < 0 && cl+cr+cd+cu<4) ? 255 : 0;*/
        dst[i] = (contour[i] >= 0) ? 255 : 0;
        contour[i] *= 0.001;
    }

    return 1;
}

void InitContour(float *contour, int width, int height) {
    ChanVeseInitPhi(contour, width, height);
}
