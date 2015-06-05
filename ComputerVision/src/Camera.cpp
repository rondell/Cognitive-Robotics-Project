#include "Camera.h"
#include<unistd.h>
Camera::Camera(int device, int width, int height) {
	this->device = device;
	this->width = width;
	this->height = height;
	cout << "Camera " << this->device << " [" << this->width << "x" << this->height << "]" << endl;
}

void Camera::OpenCamera()
{
	cout << "Opening camera ... ";
	capture.open(device);
	capture.set(CAP_PROP_FRAME_WIDTH, width);
	capture.set(CAP_PROP_FRAME_HEIGHT, height);

	if (capture.isOpened() == false) {
		cout << "[ERROR] camera already used" << endl;
	}
	else {
		cout << "[OK]" << endl << endl;
	}
}

void Camera::Follow()
{
    float* contour=new float[height*width]();
    float* output=new float[height*width]();

    cout << "[START] Active Contour " << endl;
    
    // Initialize the reference frame
    cout << "Initializing the reference frame ...";
    Mat refFrame = imread("./train/test_image.jpg",1);
    cvtColor(refFrame, refFrame, COLOR_RGB2GRAY);
    vector<float> refArray = ToArray(refFrame);
    
    InitContour(contour, width, height);
    for (int i = 0 ; i<25; i++)
    {
          ActiveContour(&refArray[0], output, contour, width, height,0);
    }
    
    imshow("Output", ToMat(output, height, width));
    
    cout << "[OK]" << endl;
    		
    while (waitKey(10) == -1);

    /*
    // Follow the 2nd reference frame
    cout << "Follow the 2nd reference frame ...";
    refFrame = imread("./train/test_image2.jpg",1);
    cvtColor(refFrame, refFrame, COLOR_RGB2GRAY);
    refArray = ToArray(refFrame);
    
    for (int i = 0 ; i<25; i++)
    {
          ActiveContour(&refArray[0], output, contour, width, height,0);
    }
    
    imshow("Output", ToMat(output, height, width));
    
    cout << "[OK]" << endl;
    		
    while (waitKey(10) == -1);*/
    
    // Follow the camera
    cout << "Following the camera ...";
    while(waitKey(10) == -1) {
        if (capture.read(frame) == NULL) {
            cout << "[ERROR] frame not read" << endl;
            return;
        }  
        
	cvtColor(frame, frame, COLOR_RGB2GRAY);
        
        vector<float> array = ToArray(frame);
        ActiveContour(&array[0], output, contour, width, height,1);  
        imshow("Output", ToMat(output, height, width));
    }
    return;
}

vector<float> Camera::ToArray(Mat src) {
    src.convertTo(src, CV_32FC1, 1/255.0);
    vector<float> array;
    array.assign((float*)src.datastart, (float*)src.dataend);
    return array;
}

Mat Camera::ToMat(float *src, int rows, int cols) {
    Mat dst = Mat(rows,cols,CV_32FC1); 
    memcpy(dst.data, src, rows * cols * sizeof(float));  
    return dst;
}