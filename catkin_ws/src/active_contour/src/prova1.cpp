#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include "sensor_msgs/Image.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <image_transport/image_transport.h>

using namespace std;

//future snake
int a=0;
int chk;

//follow
void callBack(const sensor_msgs::Image::ConstPtr& ros_image){
  //cout << "in\n";
  cv::namedWindow("Image", CV_WINDOW_AUTOSIZE);
  cv::Mat matrix = cv::Mat(ros_image->height, ros_image->width, CV_8UC3, const_cast<uchar*>(&ros_image->data[0]), ros_image->step);
  cv::cvtColor(matrix, matrix, CV_BGR2RGB);
  /*
  try
  {
    matrix = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::RGB8);
  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("cv_bridge exception: %s", e.what());
    return;
  }
  */
  //cout << matrix;
  //cout << "\n";
  cv::imshow("Image", matrix);
  cv::waitKey(1);
  
}

int main(int argc, char** argv) {
  
  
    
    //ROS Init
    ros::init(argc, argv, "imm_show");

    ros::NodeHandle n;

    ros::Publisher pub;
    ros::Subscriber sub;
    
    pub = n.advertise<std_msgs::Int32>("chatterForward", 10);
    sub = n.subscribe("usb_cam/image_raw", 1, callBack);
    ros::Rate loop_rate(30);

    
  
  while(ros::ok()){  
    
    ros::spinOnce();
    
    /*
    if(chk)
    {
        std_msgs::Int32 msg;
        msg.data = a; 
    
        pub.publish(msg);
    }
    else
    {
        printf("no message to be processed\n");
    }
    chk=0;
    */ 
    //loop_rate.sleep();

  }  
    
    return 0;
}