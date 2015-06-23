#include "ros/ros.h"
#include "std_msgs/Int32.h"

//future snake
int a=0;
int chk;

//follow
void callBack(const std_msgs::Int32::ConstPtr& msg){

   a=msg->data;
   a++;
   chk=1;

}

int main(int argc, char** argv) {
  
  
    
    //ROS Init
    ros::init(argc, argv, "forward");

    ros::NodeHandle n;

    ros::Publisher pub;
    ros::Subscriber sub;
    
    pub = n.advertise<std_msgs::Int32>("chatterForward", 10);
    sub = n.subscribe("chatter", 1, callBack);
    ros::Rate loop_rate(1);
  
  while(ros::ok()){  
    
    ros::spinOnce();
    
    if(chk){
      std_msgs::Int32 msg;
      msg.data = a; 
    
      pub.publish(msg);
   }
   else{
      printf("no message to be processed\n");
   }
    chk=0; 
    loop_rate.sleep();

  }  
    
    return 0;
}