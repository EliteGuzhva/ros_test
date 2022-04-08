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

3. In a third shell build this project and run service server
```shell
cd ~/catkin_ws
catkin_make
source devel/setup.sh
rosrun ros_test main
```

4. In yet another shell call turtlesim_csv service
```shell
cd ~/catkin_ws
source devel/setup.sh
rosservice call /turtlesim_csv "filename: src/ros_test/input/example.csv"
```