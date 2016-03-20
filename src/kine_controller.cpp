#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <geometry_msgs/Twist.h>
int main (int argc, char **argv)
{
    double v=1, w =0;
    double b=0.35,R=0.1;
    //Start ROS within this node
    ros::init(argc, argv, "controller");
    //declaring node
    ros::NodeHandle node;
    //Declare topic to be published
    ros::Publisher pub_right = node.advertise<std_msgs::Float64>("/vrep/vehicle/motorRightSpeed", 1);
    ros::Publisher pub_left = node.advertise<std_msgs::Float64>("/vrep/vehicle/motorLeftSpeed", 1);
    
    //Define ROS loop_rate
    ros::Rate loop_rate(60);
    //Define message
    std_msgs::Float64 wl,wr;
    while(ros::ok()){
        //Compute wr and wl
        wr.data = (v + (b/2)*w)/R;
        wl.data = (v - (b/2)*w)/R;
        //Publish
        ROS_INFO("Publishing angular motors speeds...");
        pub_right.publish(wr) ;
        pub_left.publish(wl) ;
        //ROS routine
        ros::spinOnce;
        loop_rate.sleep();
        
    }
}