cmake_minimum_required(VERSION 3.0.2)
project(ros_test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(catkin REQUIRED COMPONENTS roscpp std_msgs message_generation)

add_service_files(
  FILES
  csv.srv
)

generate_messages(
  DEPENDENCIES
  std_msgs
)

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
add_dependencies(${PROJECT_NAME}_main ${ros_test_main_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(${PROJECT_NAME}_main
  ${catkin_LIBRARIES}
)

install(TARGETS ${PROJECT_NAME}_main
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)