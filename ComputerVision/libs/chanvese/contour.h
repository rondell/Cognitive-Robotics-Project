
#ifndef CONTOUR_H
#define	CONTOUR_H

#ifdef	__cplusplus
extern "C" {
#endif

int ActiveContour (float *src, float *dst, float *contour, float* mask, int width, int height);

void InitContour(float *contour, int Width, int Height);

#ifdef	__cplusplus
}
#endif

#endif	/* CONTOUR_H */

