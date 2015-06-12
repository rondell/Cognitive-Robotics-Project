#include <stdio.h>
#include <string.h>
#include "chanvese.h"

num c1[3], c2[3];
chanveseopt opt = {(num)1e-3, 1, (num)0.25, 0, 1, 1, (num)0.5, NULL, NULL};

int ActiveContour (float *src, float *contour, float* mask, int width, int height)
{        
    if(!ChanVese(contour, src, mask, width, height, 1, &opt))
    {
        fprintf(stderr, "Error in ChanVese.");
        return 0;
    }

    RegionAverages(c1, c2, contour, src, width, height, 1);
        
    return 1;
}

void InitContour(float *contour, int width, int height) {
    ChanVeseInitPhi(contour, width, height);
}