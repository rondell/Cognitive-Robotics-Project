#include <iostream>
#include <opencv2/opencv.hpp>

#include "Camera.h"

using namespace std;
/*
 * 
 */
int main() {
    cout << "OpenCV version: " << CV_VERSION << endl;
    
    Camera camera(0, 640, 480);
    camera.crop();
    
    while (1);
}

