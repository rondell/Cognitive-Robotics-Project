#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "active_contour/Camera.h"
#include "ros/ros.h"
#include "sensor_msgs/Image.h"
#include <sensor_msgs/image_encodings.h>
#include <image_transport/image_transport.h>
#include <geometry_msgs/Polygon.h>
#include <unistd.h>
#include <iostream>
#include <vector>
#include "chanvese/contour.h"

#define EPS 1e-50

using namespace cv;
using namespace std;

bool haveMask, clicked;
bool drawing_box;
Rect roi;
Point initCenter(-1,-1);
int area;
float* contour;
float* output;
vector<float> temp;
Vec3b hsv;
Mat mask, gray, HSV; 
Scalar lowerb, upperb;
int erosion_size, dilation_size;
Mat erodeElement, dilateElement;
vector<float> frameArray, maskArray;
Mat ROI;
int device;
int width;
int height;
bool chk;
vector<Point> snake;
int conteggio = 0;
double somma = 0;
Point center(-1, -1);

vector<float> ToArray(Mat src) {
    src.convertTo(src, CV_32FC1, 1/255.0);
    vector<float> array;
    array.assign((float*)src.datastart, (float*)src.dataend);
    return array;
}

Mat ToMat(float *src, int rows, int cols) {
    Mat dst = Mat(rows,cols,CV_32FC1); 
    memcpy(dst.data, src, rows * cols * sizeof(float));  
    return dst;
}

void onMouse( int event, int x, int y, int d, void *param )
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
            area = roi.area()*1.2;
            haveMask = false;
            break;
            
    }
}

void draw_box( Mat* img, Rect rect ){
    rectangle(*img, Point(roi.x, roi.y), Point(roi.x+roi.width,roi.y+roi.height), Scalar(255,0,0), 2, 8, 0  );
}

void Follow(Mat frame){
	
	clock_t startTime = clock(); // compute the time
        cvtColor(frame, gray, CV_RGB2GRAY);     
        cvtColor(frame, HSV, CV_RGB2HSV);
        cout << "done 1\n"; 
        namedWindow("Frame", CV_WINDOW_AUTOSIZE);
        imshow("Frame", frame);
        waitKey(1);
        setMouseCallback("Frame", onMouse);
        cout << "done 2\n"; 
        if( drawing_box ){
            draw_box(&frame, roi);
	    //drawing_box = true;
    	}
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
                
                somma = 0; 
                conteggio = 0; //benchmark
                
            }
	    // Create the mask
            inRange(HSV, lowerb , upperb, mask);
            dilate(mask, mask, dilateElement);
            mask = mask.mul(ROI);
            
            //imshow("mask", mask);
            
            frameArray = ToArray(gray);
            maskArray = ToArray(mask);
            ActiveContour(&frameArray[0], output, contour, &maskArray[0], width, height, roi.br().y);  
            
            Mat OUT = ToMat(output, height, width);
            OUT.convertTo(OUT, CV_8UC1);
            //imshow("Output", OUT);
            
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
                    //imshow("ROI", ROI);
                    break;
                }
            }
	snake = contours.front();
	cout << "contours size" << contours.size() << "\n";
        }
        imshow("Frame", frame);
	waitKey(1);
        somma += double( clock() - startTime ) / (double)CLOCKS_PER_SEC;
        conteggio++;
       	cout << somma / conteggio << endl << flush;
    	return;
}

void callBack(const sensor_msgs::Image::ConstPtr& ros_image){

    Mat frame = Mat(ros_image->height, ros_image->width, CV_8UC3, const_cast<uchar*>(&ros_image->data[0]), ros_image->step);
    cvtColor(frame, frame, CV_BGR2RGB);
    Follow(frame);
    cout << snake.size() << "\n";
    chk=true;
    cout << "true\n";
    return;

}

int main(int argc, char **argv) {
    //init
    cout << "OpenCV version: " << CV_VERSION << endl;
    height=480;
    width=640;
    geometry_msgs::Polygon msg;
    contour=new float[height*width]();
    output=new float[height*width]();
    temp = ToArray(Mat::zeros(height, width, CV_8UC1 ));
    output = &temp[0];
    erosion_size = 2, dilation_size = 10;
    erodeElement = getStructuringElement(MORPH_RECT, Size(2 * erosion_size + 1, 2 * erosion_size + 1), Point(erosion_size, erosion_size) );
    dilateElement = getStructuringElement(MORPH_RECT, Size(2 * dilation_size + 1, 2 * dilation_size + 1), Point(dilation_size, dilation_size) );
    ROI = Mat::zeros( height, width, CV_8UC1 );
    haveMask = false;
    clicked = false;
    drawing_box = false;

    //ros init
    ros::init(argc, argv, "active_contour");
    ros::NodeHandle n;
    ros::Publisher pub;
    ros::Subscriber sub;

    //publisher
    pub = n.advertise<geometry_msgs::Polygon>("snake", 1);
    //subscriber
    sub = n.subscribe("usb_cam/image_raw", 1, callBack);
    //loop rate (30 Fps)
    ros::Rate loop_rate(30);
    
    //loop active contour
    while(ros::ok()){
        //check for messages and get the current frame
        ros::spinOnce();
	cout << snake.size() <<"\n"; 
	msg.points.resize(snake.size());      
        if(chk){
	    //built msg
	    for(int i=0; i<snake.size(); i++){
		cout << i << "\n";
		msg.points.at(i).x=snake.at(i).x;
		msg.points.at(i).y=snake.at(i).y;
	    }
            pub.publish(msg);
        }
        chk = false;
        //loop_rate.sleep();
    }

    return 0;
}

