#include <ros_test/turtle.h>

#include <cmath>
#include <thread>

#include "geometry_msgs/Twist.h"

namespace rt {

Turtle::Turtle(ros::NodeHandle &node) {
  velocityPublisher =
      node.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", queueSize);

  poseSubscriber =
      node.subscribe("/turtle1/pose", 1, &Turtle::updatePose, this);

  std::this_thread::sleep_for(std::chrono::seconds(timeToInit));
}

Turtle::Turtle(ros::NodeHandle &node, double linearCoef, double angularCoef)
    : Turtle(node) {
  kLinear = linearCoef;
  kAngular = angularCoef;
}

void Turtle::goTo(const Point &goal) {
  auto msg = geometry_msgs::Twist();

  Point diff = goal - pose.pos;
  double dist = distance(diff);

  ros::Rate loopRate(publishRate);
  while (dist > epsilon) {
    double linearVel = dist * kLinear;
    double angleGoal = std::atan2(diff.y, diff.x);
    double angularVel = (angleGoal - pose.theta) * kAngular;

    msg.linear.x = linearVel;
    msg.angular.z = angularVel;

    velocityPublisher.publish(msg);

    ros::spinOnce();
    loopRate.sleep();

    diff = goal - pose.pos;
    dist = distance(diff);
  }
}

void Turtle::updatePose(const turtlesim::Pose::ConstPtr &poseMsg) {
  pose = {.pos = Point(poseMsg->x, poseMsg->y), .theta = poseMsg->theta};
}

} // namespace rt