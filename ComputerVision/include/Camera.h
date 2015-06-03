#ifndef CAMERA_H
#define	CAMERA_H

#include <iostream>
#include <vector>

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "chanvese/contour.h"

using namespace cv;
using namespace std;

class Camera
{
public:
	int device;
	int width;
	int height;

	Camera(int device, int width, int height);
        void crop(float *contour, float *output);
        void OpenCamera(int device, int width, int height);
        void init_active_con(float *contour,float *output);
private:
	Mat frame;
	VideoCapture capture;
        void build_array(Mat M,float *out_arr);
        void build_Mat(Mat out,float *inp);
};

#endif