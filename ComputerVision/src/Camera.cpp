#include "Camera.h"

Camera::Camera(int device, int width, int height) {
	this->device = device;
	this->width = width;
	this->height = height;
	cout << "Camera " << this->device << " [" << this->width << "x" << this->height << "]" << endl;

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

void Camera::crop(void) {
        
    bool done = false;
    int x = 279, y = 190, dim = 100;
    Rect box(x, y, dim, dim);


    //while(!done) {
        // Read from camera
        if (capture.read(frame) == NULL) {
            cout << "[ERROR] frame not read" << endl;
            return;
        }
        imshow("Webcam", frame);

        // Crop the image
        Mat  croppedImage = frame(box);
        imshow("Cropped", croppedImage);
        

	// Convert to grayscale
	Mat croppedGray;
	cvtColor(croppedImage, croppedGray, COLOR_RGB2GRAY);
        
        // Convert to FP (between 0 and 1)
	Mat croppedFp;
        croppedGray.convertTo(croppedFp, CV_32FC1, 1.0/255.5);
        /*
        // AT (ROW, COL)
        cout << "1st row of matrix" << endl;
        for(int i=0; i<10; i++)
            cout << croppedFp.at<float>(0,i) << " " ;
        cout << endl;*/
        
        // Reshape in 1D
        Mat croppedArray = croppedFp.reshape(1,0); 
         /*
        cout << "1st element of array" << endl;
        for(int i=0; i<10; i++)
            cout << croppedArray.at<float>(i,0) << " " ;
        cout << endl;*/
        
        image frame = {NULL, dim, dim, 1};
        
        ActiveContour(NULL,frame,NULL);
        //   }
}
