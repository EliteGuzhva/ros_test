# Ros test project

Trying to simulate a turtle

## Usage

1. Launch roscore
```shell
roscore
```

2. In a separate shell launch turtlesim
```shell
./turtlesim.sh
```

3. In a third shell run main program
```shell
cd ~/catkin_ws
catkin_make
source devel/setup.sh
rosrun ros_test main
```