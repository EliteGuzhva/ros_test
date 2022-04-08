cmake_minimum_required(VERSION 3.0.2)
project(ros_test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(catkin REQUIRED COMPONENTS roscpp)

catkin_package()

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(${PROJECT_NAME}_main
  src/main.cpp
  src/point.cpp
  src/turtle.cpp
  src/coordwarehouse.cpp
)
set_target_properties(${PROJECT_NAME}_main PROPERTIES OUTPUT_NAME main PREFIX "")
target_link_libraries(${PROJECT_NAME}_main
  ${catkin_LIBRARIES}
)

install(TARGETS ${PROJECT_NAME}_main
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)