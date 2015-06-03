#include "Camera.h"
#include<unistd.h>
Camera::Camera(int device, int width, int height) {
	this->device = device;
	this->width = width;
	this->height = height;
	cout << "Camera " << this->device << " [" << this->width << "x" << this->height << "]" << endl;
}

void Camera::OpenCamera(int device, int width, int height)
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


void Camera::crop(float *contour, float *output) {
        
    bool done = false;
    int x = 279, y = 190, dim = 50;
    Rect box(x, y, dim, dim);
    int dim_img=this->width*this->height;

          
    int tmp_out_view=0;

    while(!done) {
        // Read from camera
        if (capture.read(frame) == NULL) {
            cout << "[ERROR] frame not read" << endl;
            return;
        }
//        imshow("Webcam", frame);

        // Crop the image
         if (tmp_out_view == 0)
        {
           //do nothing
            tmp_out_view++;
        }
        Mat  croppedImage = frame;
        imshow("Cropped", croppedImage);
        

	// Convert to grayscale
	Mat croppedGray;
	cvtColor(croppedImage, croppedGray, COLOR_RGB2GRAY);
        
        // Convert to FP (between 0 and 1)
	Mat croppedFp;
        croppedGray.convertTo(croppedFp, CV_32FC1, 0.0/1.0);
        
        // FROM MAT TO ARRAY
        vector<float> array;
        array.assign((float*)croppedFp.datastart, (float*)croppedFp.dataend);
        
        // FROM ARRAY TO IMAGE STRUCT
        image frame = {&array[0], this->width, this->height, 1};
        
        // ACTIVE CONTOUR
        ActiveContour(contour,&frame,output,0);
        

        //FROM ARRAY TO MAT 
        Mat C=Mat(this->height,this->width,CV_32FC1); 
//        memcpy(C.data,contour,dim_img*sizeof(float)); 
//        imshow("Contour", C);
        Mat O=Mat(this->height,this->width,CV_32FC1); 
        memcpy(O.data,output,dim_img*sizeof(float)); 
        imshow("Output", O);
        
       
        
        
        
    }
}


//initialization of the algorithm
void Camera::init_active_con(float *contour,float *output)
{
    
    Mat test_image;
    int it;
    cout<<"initialization ..."<<endl;
    //read the test image
    test_image=imread("./train/test_image.jpg",1);
    //convert to grayscale
    cvtColor(test_image, test_image, COLOR_RGB2GRAY);
    //use value between 0 and 1
    test_image.convertTo(test_image, CV_32FC1, 0.0/1.0);
    //convert the image into an array
    vector<float> test_array;
    test_array.assign((float*)test_image.datastart, (float*)test_image.dataend);
    //make the struct image
    image test_img = {&test_array[0], this->width, this->height, 1};
    
    
    for (it = 0 ; it<40; it++)
    {
        
          ActiveContour(contour,&test_img,output,it+1);
          Mat Out=Mat(this->height,this->width,CV_32FC1); 
            
            memcpy(Out.data,output,this->width*this->height*sizeof(float));
            
            imshow("Output_1", Out);
            
         
    }
     
            
    cout<<"initialization completed ..."<<endl;
    
    
}