#include <iostream>
#include <opencv2/opencv.hpp>

#include "Camera.h"

using namespace std;
/*
 * 
 */
int main() {
    cout << "OpenCV version: " << CV_VERSION << endl;
    int height=300;
    int width=300;
    
    Camera camera(0, width, height);
    camera.OpenCamera();
    camera.Follow();
    
    return 0;
}

