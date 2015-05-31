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
         
    float* contour = new float[dim*dim]();
    float* output = new float[dim*dim]();

    // INIT EXTERNAL CONTOUR 
    for(int i=0; i<dim*dim; i++)
        contour[i] = 1;


    while(!done) {
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
        
        // FROM MAT TO ARRAY
        vector<float> array;
        array.assign((float*)croppedFp.datastart, (float*)croppedFp.dataend);
        
        // FROM ARRAY TO IMAGE STRUCT
        image frame = {&array[0], dim, dim, 1};
        
        // ACTIVE CONTOUR
        ActiveContour(contour,&frame,output);

        //FROM ARRAY TO MAT 
        Mat C=Mat(dim,dim,CV_32FC1); 
        memcpy(C.data,contour,dim*dim*sizeof(float)); 
        imshow("Contour", C);
        Mat O=Mat(dim,dim,CV_32FC1); 
        memcpy(O.data,contour,dim*dim*sizeof(float)); 
        imshow("Output", O);
    }
}
