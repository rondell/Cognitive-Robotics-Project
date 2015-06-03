#include <stdio.h>
#include <string.h>
#include "chanvese/chanvese.h"

int ActiveContour (float *src, float *dst, float *contour , int width, int height)
{        
    num c1[3], c2[3];
    
    /* Perform the segmentation */
    if(!ChanVese(contour, src, width, height, 1, ChanVeseNewOpt()))
    {
        fprintf(stderr, "Error in ChanVese.");
        return 0;
    }

    /* Compute the final region averages */
    RegionAverages(c1, c2, contour, src, width, height, 1);
    
    printf("\nRegion averages\n");
    
    for(int i=0; i<width*height; i++) {
        contour[i] *= 0.0001;
        dst[i] = (contour[i] >= 0) ? 255 : 0;
    }
    return 1;
}

void InitContour(float *contour, int width, int height) {
    ChanVeseInitPhi(contour, width, height);
}
