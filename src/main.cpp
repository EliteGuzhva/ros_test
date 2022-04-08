#include <chrono>
#include <cmath>
#include <iostream>
#include <thread>

#include <geometry_msgs/Twist.h>
#include <ros/ros.h>
#include <turtlesim/Pose.h>

class Turtle {
  static constexpr double K_LINEAR = 0.5;
  static constexpr double K_ANGULAR = 4.0;

public:
  explicit Turtle(ros::NodeHandle &node) {
    velocityPublisher =
        node.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", queueSize);
  }

  void goTo(double xGoal, double yGoal) {
    auto msg = geometry_msgs::Twist();

    double distance = calcDist(xGoal, yGoal);
    double epsilon = 0.1;

    ros::Rate loopRate(publishRate);
    while (distance > epsilon) {
      double linearVel = distance * K_LINEAR;
      double angleGoal = std::atan2(yGoal - y, xGoal - x);
      double angularVel = (angleGoal - theta) * K_ANGULAR;

      msg.linear.x = linearVel;
      msg.angular.z = angularVel;

      velocityPublisher.publish(msg);

      ros::spinOnce();
      loopRate.sleep();

      distance = calcDist(xGoal, yGoal);
    }
  }

  void updatePose(const turtlesim::Pose::ConstPtr &poseMsg) {
    x = poseMsg->x;
    y = poseMsg->y;
    theta = poseMsg->theta;
  }

private:
  int x = 0;
  int y = 0;
  int theta = 0;
  double publishRate = 10.0;
  uint32_t queueSize = 10;
  ros::Publisher velocityPublisher;

  double calcDist(double xGoal, double yGoal) {
    return std::sqrt(std::pow((xGoal - x), 2) + std::pow((yGoal - y), 2));
  }
};

int main(int argc, char **argv) {
  ros::init(argc, argv, "turtlesim_commander");
  ros::NodeHandle node;

  Turtle turtle(node);

  auto poseSubscriber =
      node.subscribe("/turtle1/pose", 1, &Turtle::updatePose, &turtle);

  std::this_thread::sleep_for(std::chrono::seconds(2));

  turtle.goTo(5.0, 9.0);

  return 0;
}