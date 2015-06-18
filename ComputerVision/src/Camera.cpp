#include "Camera.h"
#include<unistd.h>

#define EPS 1e-50

bool haveMask = false, haveRoi = false, drawing_box = false;
Rect roi; Point centerFrame, centerROI;
int area;

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

    centerFrame = Point(0,0);
    centerROI = Point(0,0);
    cout << "[START] Active Contour " << endl;
    
    // Follow the camera
    cout << "Following the camera ...";
    cout << flush;
    Vec3b hsv; Mat mask, gray, HSV, drawing; Scalar lowerb, upperb;
    int erosion_size = 2, dilation_size = 10;
    Mat erodeElement = getStructuringElement(MORPH_RECT, Size(2 * erosion_size + 1, 2 * erosion_size + 1), Point(erosion_size, erosion_size) );
    Mat dilateElement = getStructuringElement(MORPH_RECT, Size(2 * dilation_size + 1, 2 * dilation_size + 1), Point(dilation_size, dilation_size) );
    vector<float> frameArray, maskArray, outputArray, cntArray;
    Mat ROI = Mat::zeros( height, width, CV_8UC1 );
    Mat ACmask = Mat::zeros( height, width, CV_8UC1 );
    Mat croppedFrame;Mat OUT;
    namedWindow( "Frame", WINDOW_AUTOSIZE );
            setMouseCallback("Frame", onMouse);
            int count = 0; double sum = 0; 
                            Mat bigCNT = Mat::zeros(height, width, CV_8UC1 );

    while(waitKey(10) == -1) {
        
        if (capture.read(frame) == NULL) {
            cout << "[ERROR] frame not read" << endl;
            return;
        }
	
        clock_t startTime = clock(); // compute the time
        

        if( drawing_box ) 
            draw_box(&frame, roi);
        
        if(haveRoi) {
            croppedFrame = frame(roi);
            cvtColor(croppedFrame, gray, COLOR_RGB2GRAY); 
            cvtColor(croppedFrame, HSV, COLOR_RGB2HSV);
            if(!haveMask) {

                // Take the HSV value from the center of the ROI
                hsv = HSV.at<Vec3b>(centerROI);

                // Compute lower and upper bound of hsv
                lowerb = Scalar(hsv.val[0] - 30, hsv.val[1] - 50, hsv.val[2] - 50);
                upperb = Scalar(hsv.val[0] + 30, hsv.val[1] + 50, hsv.val[2] + 50);

                haveMask = true;
                
                sum = 0; count = 0; //benchmark
            }
                   
          
            // Create the HSV mask
            inRange(HSV, lowerb , upperb, mask);
            dilate(mask, mask, dilateElement);            
            //imshow("mask", mask);
            
            // Reset the output
            OUT = Mat::zeros(roi.height, roi.width, CV_8UC1 );
            //Mat bigOUT = Mat::zeros(height, width, CV_8UC1 );
            
            // Active Contour
            Mat smallCNT = bigCNT(roi);
            frameArray = ToArray(gray);
            maskArray = ToArray(mask);
            outputArray = ToArray(OUT);
            cntArray = ToArray(smallCNT);
            ActiveContour(&frameArray[0], &cntArray[0], &maskArray[0], roi.width, roi.height);
            smallCNT = ToMat(&cntArray[0], roi.height, roi.width);
            inRange(smallCNT, Scalar(0) , Scalar(1), OUT);
            smallCNT *= 0.001;
            smallCNT.copyTo(bigCNT(roi));

            
            // Find contours
            vector<vector<Point> > contours;
            vector<Vec4i> hierarchy;
            findContours(OUT, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));

            // Find bounding box for each contour
            vector<Rect> boundRect( contours.size() );
            for( int i = 0; i < contours.size(); i++ )
            { 
                boundRect[i] = boundingRect( Mat(contours[i]) );
            }

            for( int i = 0; i< contours.size(); i++ )
            {
                if(boundRect[i].contains(centerROI)) {
                    rectangle( croppedFrame, boundRect[i].tl(), boundRect[i].br(), Scalar(0,0,255), 2, 8, 0 );
                    drawContours( croppedFrame, contours, i, Scalar(255,255,255), 1, 8, vector<Vec4i>(), 0, Point() );
                    
                    // Compute the center of the  bounding box wrt ROI
                    Point centerBound(boundRect[i].tl().x + boundRect[i].size().width/2, boundRect[i].tl().y + boundRect[i].size().height/2);
                    centerROI = centerBound;
                    centerFrame = Point(centerBound.x + roi.tl().x, centerBound.y + roi.tl().y);

                    cout << endl << "centerBound " << centerBound << endl;
                    cout << "centerFrame " << centerFrame << endl;
                    cout << "centerROI " << centerROI << endl;

                    // Compute the shifting of the new center wrt the ROI
                    //Point shift(centerBound.x - centerROI.x, centerBound.y - centerROI.y);
                    //cout << "Shift " << shift << endl;

                    //int absX = abs(shift.x);
                    //int absY = abs(shift.y);
                    //if((absX > 4 && absX < 10)|| (absY > 4 && absY < 10)) {
                        // Update the center
                        
                        
                        //centerFrame = Point(centerFrame.x + shift.x, centerFrame.y + shift.y);

                        
                        //int width = roi.width;
                        //int height = roi.height;
                        int x = boundRect[i].width;
                        int y = boundRect[i].height;
                        int w = (int)(sqrt((x/(y+EPS))*area));
                        int h = (int)(area/w);
                        
                        int tlx = centerFrame.x-w/2;
                        int tly = centerFrame.y-h/2;
                        int brx = centerFrame.x+w/2;
                        int bry = centerFrame.y+h/2;
                        
                        tlx = (tlx < 0) ? 0 : tlx;
                        brx = (brx > width) ? width : brx;
                        tly = (tly < 0) ? 0 : tly;
                        bry = (bry > height) ? height : bry;  
                        
                        roi = Rect(Point(tlx,tly),Point(brx,bry));
                        //roi = Rect((int)(centerFrame.x-width/2),(int)(centerFrame.y-height/2),width,height);
                    //}
                    // Update the ROI

                    /*
                    // Center
                        int x = boundRect[i].width;
                        int y = boundRect[i].height;
                        int v = (int)(sqrt((x/(y+EPS))*area));
                        int h = (int)(area/v);
                        int deltax = (int)((h-y)/2);
                        int deltay = (int)((v-x)/2);
                        int tlx = boundRect[i].tl().x -deltax;
                        int tly = boundRect[i].tl().y -deltay;
                        int brx = boundRect[i].br().x +deltax;
                        int bry = boundRect[i].br().y +deltay;
                        tlx = (tlx < 0) ? 0 : tlx;
                        brx = (brx > width) ? width : brx;
                        tly = (tly < 0) ? 0 : tly;
                        bry = (bry > height) ? height : bry;                   
                        roi = Rect(Point(tlx,tly),Point(brx,bry));
                        ROI = Mat::zeros( height, width, CV_8UC1 );
                        rectangle( ROI, roi.tl(), roi.br(), Scalar(255), -1);
                        ACmask = Mat::zeros( height, width, CV_8UC1 );
                        rectangle( ACmask, roi.tl(), roi.br(), Scalar(1), -1);
                        rectangle( frame, roi.tl(), roi.br(), Scalar(0,0,255), 2, 8, 0 );*/
                        
                    break;
                }
            }
            //imshow("croppedFrame", croppedFrame);
        }

            circle(croppedFrame, centerROI, 5, Scalar(0,0,255), 5); // GREEN = FRAME
            circle(frame, centerFrame, 5, Scalar(0,255,0), 5);      // RED = ROI
            rectangle( frame, roi.tl(), roi.br(), Scalar(0,255,0), 2, 8, 0 );
        imshow("Frame", frame);
        //cout << double( clock() - startTime ) / (double)CLOCKS_PER_SEC << endl; 
        sum += double( clock() - startTime ) / (double)CLOCKS_PER_SEC;
        count++;
    }
    cout << sum / count << endl << flush;
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
void Camera::draw_box( Mat* img, Rect rect ){
	rectangle(*img, Point(roi.x, roi.y), Point(roi.x+roi.width,roi.y+roi.height), Scalar(255,0,0), 2, 8, 0  );
}
void Camera::onMouse( int event, int x, int y, int d, void *param )
{
    switch( event ){

		case EVENT_LBUTTONDOWN:
			drawing_box = true;             // LEFT BUTTON DOWN = START DRAWING
			roi = Rect( x, y, 0, 0 );
			break;
                        
		case EVENT_MOUSEMOVE:   
			if( drawing_box ){              // MOUSE MOVE + LEFT BUTTON DOWN = DRAWING
				roi.width = x-roi.x;
				roi.height = y-roi.y;
			}
			break;

		case EVENT_LBUTTONUP:               
			drawing_box = false;            // LEFT BUTTON UP = STOP DROWING
			if( roi.width < 0 ){
				roi.x += roi.width;
				roi.width *= -1;
			}
			if( roi.height < 0 ){
				roi.y += roi.height;
				roi.height *= -1;
			}
                        // Max area
                        area = roi.area()*0.8;
                        
                        // Center of ROI wrt FRAME
                        centerFrame.x = roi.tl().x + roi.size().width/2;
                        centerFrame.y = roi.tl().y + roi.size().height/2;
                        
                        // Center of ROI wrt ROI
                        centerROI.x = roi.size().width/2;
                        centerROI.y = roi.size().height/2;
                        
                        haveRoi = true;
                        haveMask = false;               // MUST REINITIALIZE MASK
			break;
            
	}
}