#include "ros/ros.h"
#include <geometry_msgs/Polygon.h>

void chatterCallback(const geometry_msgs::Polygon::ConstPtr& msg)
{
  int i=0;
  for(i=0; i<msg->points.size(); i++)
{
     printf("%d:\t%f\t%f\n", i, msg->points[i].x, msg->points[i].y);
}
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "get_polygon");

  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("snake", 1000, chatterCallback);
  ros::spin();

  return 0;
}