#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <geometry_msgs/Twist.h>

double v,w;
ros::Publisher pub_right;
ros::Publisher pub_left ;
double b=0.35,R=0.1;
std_msgs::Float64 wl,wr;

void speedCallBack(const geometry_msgs::TwistConstPtr &msg){
    
    ROS_INFO("Received message, %f %f", msg->linear.x, msg->angular.z);
    

        //Compute wr and wl
        wr.data = (msg->linear.x + (b/2)*msg->angular.z)/R;
        wl.data = (msg->linear.x - (b/2)*msg->angular.z)/R;
        //Publish
        ROS_INFO("Publishing angular motors speeds...");
        pub_right.publish(wr) ;
        pub_left.publish(wl) ;
        //ROS routine
     
        
}

int main (int argc, char **argv)
{

    
    //Start ROS within this node
    ros::init(argc, argv, "controller");
    //declaring node
    ros::NodeHandle node;
    //receive velocity
    //ros::Subscriber twist_sub = node.subscribe<geometry_msgs::Twist>("obstacle/Twist",1, speedCallBack);
    ros::Subscriber twist_sub = node.subscribe<geometry_msgs::Twist>("go2point/robotSpeeds",1, speedCallBack);
    //Declare topic to be published
    pub_right = node.advertise<std_msgs::Float64>("vrep/vehicle/motorRightSpeed", 1);
    pub_left = node.advertise<std_msgs::Float64>("vrep/vehicle/motorLeftSpeed", 1);
    
    //Define ROS loop_rate
    ros::spin();
    //Define message

}