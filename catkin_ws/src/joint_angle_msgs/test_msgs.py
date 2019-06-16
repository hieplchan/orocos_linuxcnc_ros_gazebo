#!/usr/bin/env python
import rospy
from joint_angle_msgs.msg import joint_angle_node

def talker():
    pub = rospy.Publisher('joint_angle', joint_angle_node, queue_size=10)
    rospy.init_node('test_node', anonymous=True)
    rate = rospy.Rate(10) # 10hz
    while not rospy.is_shutdown():
        pub.publish(0.0, 0.0, 0.0, 0.0, 0.0, 0.0)
        rate.sleep()

if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        pass
