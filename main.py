import math
import time
import rospy
from geometry_msgs.msg import Twist
from turtlesim.msg import Pose
from std_srvs.srv import Empty

class Turtle:
    def __init__(self):
        self.x: int = 0
        self.y: int = 0
        self.theta: int = 0

        self.rate: int = 10

        self.vel_publisher = rospy.Publisher('/turtle1/cmd_vel', Twist, queue_size=10)

    def update_pose(self, pose_msg: Pose):
        self.x = pose_msg.x
        self.y = pose_msg.y
        self.theta = pose_msg.theta

    def move(self, speed: float, distance: float, is_forward: bool):
        vel_msg = Twist()

        x0 = self.x
        y0 = self.y

        if is_forward:
            vel_msg.linear.x = abs(speed)
        else:
            vel_msg.linear.x = -abs(speed)

        distance_moved = 0.0
        loop_rate = rospy.Rate(self.rate)

        while distance_moved < distance:
            self.vel_publisher.publish(vel_msg)

            loop_rate.sleep()

            distance_moved = math.sqrt((self.x - x0) ** 2 + (self.y - y0) ** 2)

        vel_msg.linear.x = 0
        self.vel_publisher.publish(vel_msg)


if __name__ == "__main__":
    turtle = Turtle()

    try:
        rospy.init_node('turtlesim_motion_pose', anonymous=True)
        pose_subscriber = rospy.Subscriber('/turtle1/pose', Pose, turtle.update_pose)

        time.sleep(2)

        turtle.move(1.0, 3.0, True)

    except rospy.ROSInterruptException:
        rospy.logerr("Node terminated")