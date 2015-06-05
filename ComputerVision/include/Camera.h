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
	int device = 0;
	int width = 640;
	int height = 480;

	Camera(int device, int width, int height);
        void crop(float *contour, float *output);
        void OpenCamera();
        void Follow();
private:
	Mat frame;
	VideoCapture capture;
        void build_array(Mat M,float *out_arr);
        void build_Mat(Mat out,float *inp);
};

#endif