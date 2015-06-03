#include <iostream>
#include <opencv2/opencv.hpp>

#include "Camera.h"

using namespace std;
/*
 * 
 */
int main() {
    cout << "OpenCV version: " << CV_VERSION << endl;
    int height=480;
    int width=640;
    
    float* contour=new float[height*width]();
    float* output=new float[height*width]();
    Camera camera(0, width, height);
    camera.init_active_con(contour,output);
    camera.OpenCamera(0,width,height);
    camera.crop(contour,output);
    
    while (1);
}

