///laser_flipper takes a laser scan topic (default: base_scan) and publishes a reversed copy of it (default: base_scan_flipped)

#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"

ros::Publisher scan_pub;

std::string laser_scan = "base_scan";
std::string new_topic_name = "base_scan_flipped";

void laserCallback(const sensor_msgs::LaserScan& scan){
  //if (scan.ranges[0]==NULL) return;

  sensor_msgs::LaserScan rscan; //(reverse scan)

  //copy all values
  rscan.header=scan.header;
  rscan.angle_min=scan.angle_min;
  rscan.angle_max=scan.angle_max;
  rscan.angle_increment=scan.angle_increment;
  rscan.time_increment=scan.time_increment;
  rscan.scan_time=scan.scan_time;
  rscan.range_min=scan.range_min;
  rscan.range_max=scan.range_max;

  //get the size of the arrays
  int n =  (int)((scan.angle_max-scan.angle_min)/scan.angle_increment);
  rscan.ranges.resize(n);
  //rscan.intensities.resize(n);

  //populate arrays in reverse
  int i;
  for (i=0; i<n; i++) {
    rscan.ranges[i]=scan.ranges[n-1-i];
    //rscan.intensities[n-1-i]=scan.intensities[i];
  }

  //publish the reversed scan
  scan_pub.publish(rscan);

}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "laser_flipper");

  ros::NodeHandle n;
  //n.param<std::string>("laser_scan",laser_scan,std::string("base_scan"));
  //n.param<std::string>("new_topic_name",new_topic_name,std::string("base_scan_flipped"));
  ros::Subscriber scan_sub;
  scan_sub=n.subscribe("base_scan", 1, &laserCallback);
  scan_pub=n.advertise<sensor_msgs::LaserScan>(new_topic_name.c_str(),1);


  ros::Rate rate(100); //Input and output at the same time... (in Hz)

  while (n.ok()){
    ros::spinOnce();
    rate.sleep();
  }

  return 0;
}
