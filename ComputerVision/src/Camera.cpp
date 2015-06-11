#include "Camera.h"
#include<unistd.h>

bool haveMask = false, clicked = false;
bool drawing_box = false;
Rect box;
Point initP(-1,-1);
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
    
    /*
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

    
    // Follow the 2nd reference frame
    cout << "Follow the 2nd reference frame ...";
    refFrame = imread("./train/test_image2.jpg",1);
    cvtColor(refFrame, refFrame, COLOR_RGB2GRAY);
    refArray = ToArray(refFrame);
    
    for (int i = 0 ; i<25; i++)
    {
          ActiveContour(&refArray[0], output, contour, width, height,0);
    }
    
    Mat Output = ToMat(output, height, width);
    imshow("Output", Output);
    
    // Find contours
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
                Output.convertTo(Output, CV_8UC1);

	findContours(Output, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));

	

	// Draw contour on image
	Mat Contour = Mat::zeros(Output.size(), CV_8UC1);
        for( int i = 0; i< contours.size(); i++ )         
            drawContours(Contour, contours, i, Scalar(255), 0, LINE_AA, vector<Vec4i>(), 0, Point());
            imshow("Contour", Contour);
    cout << "[OK]" << endl;
    		
    while (waitKey(10) == -1);
    */
    
    // Follow the camera
    cout << "Following the camera ...";
    cout << flush;
    Point p(-1,-1); Vec3b hsv; Mat mask, gray, HSV; Scalar lowerb, upperb;
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
            draw_box(&frame, box);
        
        if(clicked) {
            // Init mask
            if(!haveMask) {
                // Take hsv from mouse
                p = initP;
                hsv = HSV.at<Vec3b>(p.y,p.x);
                haveMask = true;
                cout << "HSV: " << hsv << endl;
                lowerb = Scalar(hsv.val[0] - 30, hsv.val[1] - 50, hsv.val[2] - 50);
                upperb = Scalar(hsv.val[0] + 30, hsv.val[1] + 50, hsv.val[2] + 50);
                cout << "lowerb: " << lowerb << endl;
                cout << "upperb: " << upperb << endl;  
                ROI = Mat::zeros( height, width, CV_8UC1 );
                rectangle( ROI, box.tl(), box.br(), Scalar(255), -1);
            }
            
            // Create the mask
            inRange(HSV, lowerb , upperb, mask);
            dilate(mask, mask, dilateElement);
            mask = mask.mul(ROI);
            imshow("ed", mask);
            
            frameArray = ToArray(gray);
            maskArray = ToArray(mask);
            ActiveContour(&frameArray[0], output, contour, &maskArray[0], width, height,0);  
            imshow("Output", ToMat(output, height, width));
            
            
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
            circle(frame, p, 5, Scalar(0,0,255), 5);

            for( int i = 0; i< contours.size(); i++ )
            {
                if(boundRect[i].contains(p)) {
                    drawContours( frame, contours, i, Scalar(255,255,255), 1, 8, vector<Vec4i>(), 0, Point() );
                    rectangle( frame, boundRect[i].tl(), boundRect[i].br(), Scalar(0,255,0), 2, 8, 0 );
                    p.x = boundRect[i].tl().x + boundRect[i].size().width/2;
                    p.y = boundRect[i].tl().y + boundRect[i].size().height/2;
                    
                    int v = (int)(sqrt((boundRect[i].size().width/boundRect[i].size().height)*area)/2);
                    int h = (int)(v * boundRect[i].size().height/boundRect[i].size().width)/2;
                    box = Rect(Point(p.x-h,p.y-v),Point(p.x+h,p.y+v));
                    ROI = Mat::zeros( height, width, CV_8UC1 );
                    rectangle( ROI, box.tl(), box.br(), Scalar(255), -1);
                    
                    break;
                }
            }
            imshow("ROI", ROI);

            //imshow( "Contours", drawing );*/

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
	rectangle(*img, Point(box.x, box.y), Point(box.x+box.width,box.y+box.height), Scalar(255,0,0), 2, 8, 0  );
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
				box.width = x-box.x;
				box.height = y-box.y;
			}
			break;

		case EVENT_LBUTTONDOWN:
			drawing_box = true;
			box = Rect( x, y, 0, 0 );
			break;

		case EVENT_LBUTTONUP:
			drawing_box = false;
                        clicked = true;
			if( box.width < 0 ){
				box.x += box.width;
				box.width *= -1;
			}
			if( box.height < 0 ){
				box.y += box.height;
				box.height *= -1;
			}
                        initP.x = box.tl().x + box.size().width/2;
                        initP.y = box.tl().y + box.size().height/2;
                        area = box.area()*1.2;
                        haveMask = false;
			break;
            
	}
}
