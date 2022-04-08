#include <ros/init.h>

#include <ros_test/coordwarehouse.h>
#include <ros_test/turtle.h>

using namespace rt;

int main(int argc, char **argv) {
  ros::init(argc, argv, "turtlesim_commander");
  ros::NodeHandle node;

  if (argc != 2) {
    ROS_ERROR("Provide a path to .csv file with coordinates\n");
    return 1;
  }

  auto cwh = CoordWarehouse::fromCSV(argv[1]);

  Turtle turtle(node);
  for (const auto &coord : cwh.getCoords())
    turtle.goTo(coord);

  return 0;
}