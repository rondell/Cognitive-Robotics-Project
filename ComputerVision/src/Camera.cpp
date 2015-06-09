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
    Point p(-1,-1); Vec3b hsv; Mat mask, gray;

    while(waitKey(10) == -1) {
        if (capture.read(frame) == NULL) {
            cout << "[ERROR] frame not read" << endl;
            return;
        }  
        imshow("Frame", frame);

	cvtColor(frame, gray, COLOR_RGB2GRAY);
        cvtColor(frame, frame, COLOR_RGB2HSV);
        
        setMouseCallback("Frame", onMouse, &p );

        if(clicked) {
            // Init mask
            if(!haveMask) {
                // Take hsv from mouse
                hsv = frame.at<Vec3b>(p.y,p.x);
                haveMask = true;
                
                // Create the mask
                inRange(frame, Scalar(hsv.val[0] - 50, hsv.val[1] - 50, hsv.val[2] - 50), Scalar(hsv.val[0] + 50, hsv.val[1] + 50, hsv.val[2] + 50), mask);        
                
                // Erode to remove small object
                int erosion_size = 5;  
                Mat element = getStructuringElement(MORPH_ELLIPSE, Size(2 * erosion_size + 1, 2 * erosion_size + 1), Point(erosion_size, erosion_size) );
                erode(mask, mask, element);
                // Dilatate to include nearest points
                erosion_size = 20;  
                element = getStructuringElement(MORPH_ELLIPSE, Size(2 * erosion_size + 1, 2 * erosion_size + 1), Point(erosion_size, erosion_size) );
                dilate(mask, mask, element);

                // Init contour
                if(0) {
                    // With a circle on clicked point
                    Mat initContour = Mat(height, width, CV_32FC1, Scalar(-255));
                    circle(initContour, p, 20, Scalar(255),1);
                    vector<float> initContourArray = ToArray(initContour);
                    contour = &initContourArray[0];
                }else{
                    // Traditional chanvese
                    InitContour(contour, width, height);
                }
                
                for (int i = 0 ; i<25; i++) {
                    vector<float> array = ToArray(gray);
                    vector<float> mask_array = ToArray(mask);
                    ActiveContour(&array[0], output, contour, &mask_array[0], width, height,0);  
                }
            }
            
            // LOOP
            inRange(frame, Scalar(hsv.val[0] - 50, hsv.val[1] - 50, hsv.val[2] - 50), Scalar(hsv.val[0] + 50, hsv.val[1] + 50, hsv.val[2] + 50), mask);        
            imshow("inrange", mask);
            
            int erosion_size = 5;  
            Mat element = getStructuringElement(MORPH_ELLIPSE, Size(2 * erosion_size + 1, 2 * erosion_size + 1), Point(erosion_size, erosion_size) );
            erode(mask, mask, element);
            imshow("erode", mask);
            
            erosion_size = 20;  
            element = getStructuringElement(MORPH_ELLIPSE, Size(2 * erosion_size + 1, 2 * erosion_size + 1), Point(erosion_size, erosion_size) );
            dilate(mask, mask, element);
            imshow("dilate", mask);
            
            vector<float> array = ToArray(gray);
            vector<float> mask_array = ToArray(mask);
            ActiveContour(&array[0], output, contour, &mask_array[0], width, height,0);  
            imshow("Output", ToMat(output, height, width));
            
        }
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