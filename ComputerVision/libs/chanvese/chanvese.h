/**
 * @file chanvese.h
 * @brief Chan-Vese active contours without edges image segmentation
 * @author Pascal Getreuer <getreuer@gmail.com>
 */
#ifndef _CHANVESE_H_
#define _CHANVESE_H_

typedef float num;

typedef struct chanvesestruct chanveseopt;

/** @brief struct representing an image */
typedef struct
{
    /** @brief Float image data */
    num *Data;
    /** @brief Image width */
    int Width;
    /** @brief Image height */
    int Height;
    /** @brief Number of channels */
    int NumChannels;
} image;

chanveseopt *ChanVeseNewOpt();
void ChanVeseFreeOpt(chanveseopt *Opt);
void ChanVeseSetMu(chanveseopt *Opt, num Mu);
void ChanVeseSetNu(chanveseopt *Opt, num Nu);
void ChanVeseSetLambda1(chanveseopt *Opt, num Lambda1);
void ChanVeseSetLambda2(chanveseopt *Opt, num Lambda2);
void ChanVeseSetTol(chanveseopt *Opt, num Tol);
void ChanVeseSetDt(chanveseopt *Opt, num dt);
void ChanVeseSetMaxIter(chanveseopt *Opt, int MaxIter);
void ChanVeseSetPlotFun(chanveseopt *Opt, 
    int (*PlotFun)(int, int, num, const num*, const num*, const num*, 
        int, int, int, void*), void *PlotParam);
void ChanVesePrintOpt(const chanveseopt *Opt);

int ChanVese(num *Phi, const num *f, 
    int Width, int Height, int NumChannels, const chanveseopt *Opt);

void ChanVeseInitPhi(num *Phi, int Width, int Height);

void RegionAverages(num *c1, num *c2, const num *Phi, const num *f,
    int Width, int Height, int NumChannels);

#endif /* _CHANVESE_H_ */
