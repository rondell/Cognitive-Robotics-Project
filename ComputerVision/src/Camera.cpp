#include "Camera.h"
#include<unistd.h>

#define EPS 1e-50

bool haveMask = false, clicked = false;
bool drawing_box = false;
Rect roi;
Point initCenter(-1,-1);
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

    cout << "[START] Active Contour " << endl;
    
    // Follow the camera
    cout << "Following the camera ...";
    cout << flush;
    Point center(-1,-1); Vec3b hsv; Mat mask, gray, HSV; Scalar lowerb, upperb;
    int erosion_size = 2, dilation_size = 10;
    Mat erodeElement = getStructuringElement(MORPH_RECT, Size(2 * erosion_size + 1, 2 * erosion_size + 1), Point(erosion_size, erosion_size) );
    Mat dilateElement = getStructuringElement(MORPH_RECT, Size(2 * dilation_size + 1, 2 * dilation_size + 1), Point(dilation_size, dilation_size) );
    vector<float> frameArray, maskArray;
    Mat ROI = Mat::zeros( height, width, CV_8UC1 );
    while(waitKey(10) == -1) {
        if (capture.read(frame) == NULL) {
            cout << "[ERROR] frame not read" << endl;
            return;
        }
	
        clock_t startTime = clock(); // compute the time
	cvtColor(frame, gray, COLOR_RGB2GRAY);        
        cvtColor(frame, HSV, COLOR_RGB2HSV);
        
        setMouseCallback("Frame", onMouse);

        if( drawing_box ) 
            draw_box(&frame, roi);
        
        if(clicked) {
            // Init mask
            if(!haveMask) {
                // Take hsv from mouse
                center = initCenter;
                hsv = HSV.at<Vec3b>(center.y,center.x);
                haveMask = true;
                //cout << "HSV: " << hsv << endl;
                lowerb = Scalar(hsv.val[0] - 30, hsv.val[1] - 50, hsv.val[2] - 50);
                upperb = Scalar(hsv.val[0] + 30, hsv.val[1] + 50, hsv.val[2] + 50);
                //cout << "lowerb: " << lowerb << endl;
                //cout << "upperb: " << upperb << endl;  
                ROI = Mat::zeros( height, width, CV_8UC1 );
                rectangle( ROI, roi.tl(), roi.br(), Scalar(255), -1);
            }
            
            // Create the mask
            inRange(HSV, lowerb , upperb, mask);
            dilate(mask, mask, dilateElement);
            mask = mask.mul(ROI);
            //imshow("mask", mask);
            
            frameArray = ToArray(gray);
            maskArray = ToArray(mask);
            ActiveContour(&frameArray[0], output, contour, &maskArray[0], width, height,0);  
            //imshow("Output", ToMat(output, height, width));
            
            
            Mat OUT = ToMat(output, height, width);
            OUT.convertTo(OUT, CV_8UC1);
            vector<vector<Point> > contours;
            vector<Vec4i> hierarchy;
            findContours(OUT, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));
        
            vector<Rect> boundRect( contours.size() );

            for( int i = 0; i < contours.size(); i++ )
            { 
                boundRect[i] = boundingRect( Mat(contours[i]) );
            }
  
            /// Draw polygonal contour + bonding rects + circles
            Mat drawing = Mat::zeros( height, width, CV_8UC3 );
            circle(frame, center, 5, Scalar(0,0,255), 5);

            for( int i = 0; i< contours.size(); i++ )
            {
                if(boundRect[i].contains(center)) {

                    drawContours( frame, contours, i, Scalar(255,255,255), 1, 8, vector<Vec4i>(), 0, Point() );
                    rectangle( frame, boundRect[i].tl(), boundRect[i].br(), Scalar(0,255,0), 2, 8, 0 );

                    // Center
                    center.x = boundRect[i].tl().x + boundRect[i].size().width/2;
                    center.y = boundRect[i].tl().y + boundRect[i].size().height/2;
                    
                    int x = boundRect[i].size().width;
                    int y = boundRect[i].size().height;
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
                        rectangle( frame, roi.tl(), roi.br(), Scalar(0,0,255), 2, 8, 0 );
                    break;
                }
            }
        }
        imshow("Frame", frame);
        //cout << double( clock() - startTime ) / (double)CLOCKS_PER_SEC<< " seconds." << endl; 
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
void Camera::draw_box( Mat* img, Rect rect ){
	rectangle(*img, Point(roi.x, roi.y), Point(roi.x+roi.width,roi.y+roi.height), Scalar(255,0,0), 2, 8, 0  );
}
void Camera::onMouse( int event, int x, int y, int d, void *param )
{   /*
    if  ( event == EVENT_LBUTTONDOWN )
    {
        Point*p = (Point*)ptr;
        p->x = x;
        p->y = y;
        clicked = true;
        haveMask = false;
    }*/
    switch( event ){
		case EVENT_MOUSEMOVE: 
			if( drawing_box ){
				roi.width = x-roi.x;
				roi.height = y-roi.y;
			}
			break;

		case EVENT_LBUTTONDOWN:
			drawing_box = true;
			roi = Rect( x, y, 0, 0 );
			break;

		case EVENT_LBUTTONUP:
			drawing_box = false;
                        clicked = true;
			if( roi.width < 0 ){
				roi.x += roi.width;
				roi.width *= -1;
			}
			if( roi.height < 0 ){
				roi.y += roi.height;
				roi.height *= -1;
			}
                        initCenter.x = roi.tl().x + roi.size().width/2;
                        initCenter.y = roi.tl().y + roi.size().height/2;
                        area = roi.area()*0.8;
                        haveMask = false;
			break;
            
	}
}
