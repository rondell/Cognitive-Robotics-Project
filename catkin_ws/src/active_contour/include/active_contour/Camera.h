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
        void GetFrame(Mat imm);
        vector<Point> Follow();
private:
	Mat frame;
	VideoCapture capture;
        vector<float> ToArray(Mat src);
        Mat ToMat(float *src, int rows, int cols);
        static void onMouse( int event, int x, int y, int d, void *ptr );
        void draw_box( Mat* img, Rect rect );
};

#endif