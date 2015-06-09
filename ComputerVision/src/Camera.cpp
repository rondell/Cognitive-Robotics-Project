#include "Camera.h"
#include<unistd.h>

bool haveMask = false, clicked = false;

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
    int erosion_size = 2, dilation_size = 20;
    Mat erodeElement = getStructuringElement(MORPH_ELLIPSE, Size(2 * erosion_size + 1, 2 * erosion_size + 1), Point(erosion_size, erosion_size) );
    Mat dilateElement = getStructuringElement(MORPH_ELLIPSE, Size(2 * dilation_size + 1, 2 * dilation_size + 1), Point(dilation_size, dilation_size) );
    vector<float> frameArray, maskArray;
    
    while(waitKey(10) == -1) {

        if (capture.read(frame) == NULL) {
            cout << "[ERROR] frame not read" << endl;
            return;
        }  
        clock_t startTime = clock(); // compute the time
	cvtColor(frame, gray, COLOR_RGB2GRAY);
        cvtColor(frame, HSV, COLOR_RGB2HSV);
        
        setMouseCallback("Frame", onMouse, &p );

        if(clicked) {
            // Init mask
            if(!haveMask) {
                // Take hsv from mouse
                hsv = HSV.at<Vec3b>(p.y,p.x);
                haveMask = true;
                cout << "HSV: " << hsv << endl;
                lowerb = Scalar(hsv.val[0] - 100, hsv.val[1] - 100, hsv.val[2] - 100);
                upperb = Scalar(hsv.val[0] + 100, hsv.val[1] + 100, hsv.val[2] + 100);
                cout << "lowerb: " << lowerb << endl;
                cout << "upperb: " << upperb << endl;
                // Create the mask
                inRange(HSV, lowerb , upperb, mask);        
                
                // Erode to remove small object
                erode(mask, mask, erodeElement);
                // Dilatate to include nearest points
                dilate(mask, mask, dilateElement);

                // Init contour
                    InitContour(contour, width, height);
                
                for (int i = 0 ; i<25; i++) {
                    frameArray = ToArray(gray);
                    maskArray = ToArray(mask);
                    ActiveContour(&frameArray[0], output, contour, &maskArray[0], width, height,0);  
                }
            }
            
            // LOOP
            inRange(HSV, lowerb, upperb, mask);        
            // Erode to remove small object
            erode(mask, mask, erodeElement);
            // Dilatate to include nearest points
            dilate(mask, mask, dilateElement);
            imshow("mask", mask);

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
            circle(frame, p, 20, Scalar(0,0,255));

            for( int i = 0; i< contours.size(); i++ )
            {
                if(boundRect[i].contains(p)) {
                    drawContours( frame, contours, i, Scalar(255,255,255), 1, 8, vector<Vec4i>(), 0, Point() );
                    rectangle( frame, boundRect[i].tl(), boundRect[i].br(), Scalar(0,255,0), 2, 8, 0 );
                    p.x = boundRect[i].tl().x + boundRect[i].size().width/2;
                    p.y = boundRect[i].tl().y + boundRect[i].size().height/2;
                    break;
                }
            }
            //imshow( "Contours", drawing );

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

void Camera::onMouse( int event, int x, int y, int d, void *ptr )
{
    if  ( event == EVENT_LBUTTONDOWN )
    {    
        Point*p = (Point*)ptr;
        p->x = x;
        p->y = y;
        clicked = true;
        haveMask = false;
    }
}