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

        Rect box(270, 190, 100, 100); 
	while(!done) {

		if (capture.read(frame) == NULL) {
			cout << "[ERROR] frame not read" << endl;
			return;
		}
                

        Mat croppedImage = frame(box);
        imshow("Cropped", croppedImage);
                
        rectangle( frame, Point(box.x, box.y), Point(box.x+box.width,box.y+box.height), Scalar(0,255,0) );
	imshow("Webcam", frame);
                
                
	// Grayscale
	Mat	gray;
	cvtColor(croppedImage, gray, COLOR_RGB2GRAY);

	// Blur
	Mat blur;
	GaussianBlur(gray, blur, cv::Size(5, 5), 0);

	// Canny
	Mat canny;
	Canny(blur, canny, 75, 200);
	dilate(canny, canny, cv::Mat(), cv::Point(-1, -1), 2, 1, 1);
	erode(canny, canny, cv::Mat(), cv::Point(-1, -1), 2, 1, 1);

	// Find contours
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	findContours(canny, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));

	// Approximate the contour with max area
	int maxArea = 0;
	vector<vector<Point> > hull(1);
	for (unsigned int i = 0; i<contours.size(); i++)
	{
		double area = contourArea(contours[i]);
		if (area > maxArea){
			maxArea = (int)area;
			convexHull(Mat(contours[i]), hull[0], false);
		}
	}

	// Draw contour on image
	Mat contour = Mat::zeros(croppedImage.size(), CV_8UC1);
	drawContours(contour, hull, 0, Scalar(255), 0, LINE_AA, vector<Vec4i>(), 0, Point());
                imshow("Contour", contour);
        }      
}
