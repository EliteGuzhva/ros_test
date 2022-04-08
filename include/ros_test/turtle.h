#pragma once

#include "ros/node_handle.h"
#include "ros/publisher.h"
#include "ros/subscriber.h"
#include "turtlesim/Pose.h"

#include "pose.h"

namespace rt {

class Turtle {
public:
    explicit Turtle(ros::NodeHandle &node);
    explicit Turtle(ros::NodeHandle &node, double linearCoef, double angularCoef);

    void goTo(const Point& goal);

private:
    Pose pose;

    double kLinear = 0.5;
    double kAngular = 4.0;
    double epsilon = 0.1;

    double publishRate = 10.0;
    uint32_t queueSize = 10;
    int64_t timeToInit = 1;
    ros::Publisher velocityPublisher;
    ros::Subscriber poseSubscriber;

    void updatePose(const turtlesim::Pose::ConstPtr &poseMsg);
};

} // namespace rt