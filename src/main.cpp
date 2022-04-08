#include <ros/init.h>
#include "ros/node_handle.h"
#include "ros/service_server.h"

#include <ros_test/coordwarehouse.h>
#include <ros_test/turtle.h>

#include "ros_test/csv.h"

using namespace rt;

struct ServiceCallback {
    ros::NodeHandle& node;

    bool callback(ros_test::csv::Request& request, ros_test::csv::Response& response) {
        auto cwh = CoordWarehouse::fromCSV(request.filename);
        const auto& coords = cwh.getCoords();
        response.num = coords.size();

        Turtle turtle(node);
        for (const auto &coord : coords)
            turtle.goTo(coord);

        return true;
    }
};

int main(int argc, char **argv) {
  ros::init(argc, argv, "turtlesim_csv");
  ros::NodeHandle node;

  ServiceCallback sc {node};
  ros::ServiceServer service = node.advertiseService("turtlesim_csv", &ServiceCallback::callback, &sc);

  ros::spin();

  return 0;
}