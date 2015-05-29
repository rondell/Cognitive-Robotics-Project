/**
 * @file chanvese.h
 * @brief Chan-Vese active contours without edges image segmentation
 * @author Pascal Getreuer <getreuer@gmail.com>
 */
#ifndef _CHANVESE_H_
#define _CHANVESE_H_


typedef struct chanvesestruct chanveseopt;

chanveseopt *ChanVeseNewOpt();
void ChanVeseFreeOpt(chanveseopt *Opt);
void ChanVeseSetMu(chanveseopt *Opt, float Mu);
void ChanVeseSetNu(chanveseopt *Opt, float Nu);
void ChanVeseSetLambda1(chanveseopt *Opt, float Lambda1);
void ChanVeseSetLambda2(chanveseopt *Opt, float Lambda2);
void ChanVeseSetTol(chanveseopt *Opt, float Tol);
void ChanVeseSetDt(chanveseopt *Opt, float dt);
void ChanVeseSetMaxIter(chanveseopt *Opt, int MaxIter);
void ChanVeseSetPlotFun(chanveseopt *Opt, 
    int (*PlotFun)(int, int, float, const float*, const float*, const float*, 
        int, int, int, void*), void *PlotParam);
void ChanVesePrintOpt(const chanveseopt *Opt);

int ChanVese(float *Phi, const float *f, 
    int Width, int Height, int NumChannels, const chanveseopt *Opt,int cont);

void ChanVeseInitPhi(float *Phi, int Width, int Height, int it);

void RegionAverages(float *c1, float *c2, const float *Phi, const float *f,
    int Width, int Height, int NumChannels);

#endif /* _CHANVESE_H_ */
