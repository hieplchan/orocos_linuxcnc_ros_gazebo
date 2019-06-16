#!/usr/bin/env python

import sys
sys.path.append('/home/hiep/linuxcnc-dev/lib/python')

import linuxcnc

import rospy
from joint_angle_msgs.msg import joint_angle_node

joint1 = 0.0
joint2 = 0.0
joint3 = 0.0
joint4 = 0.0
joint5 = 0.0
joint6 = 0.0

pub = rospy.Publisher('joint_angle', joint_angle_node, queue_size=10)
rospy.init_node('joint_angle_pub', anonymous=True)
rate = rospy.Rate(10) # 10hz

while(1):
    try:
        s = linuxcnc.stat() # create a connection to the status channel
        s.poll() # get current values
        x = 'joint_position'
        print x
        joint1 = (getattr(s,x) [1])/180*3.1416
        joint2 = (getattr(s,x) [2])/180*3.1416
        joint3 = (getattr(s,x) [3])/180*3.1416
        joint4 = (getattr(s,x) [4])/180*3.1416
        joint5 = (getattr(s,x) [5])/180*3.1416
        joint6 = (getattr(s,x) [6])/180*3.1416

        print joint1
        print joint2
        print joint3
        print joint4
        print joint5
        print joint6

        pub.publish(joint1, joint2, joint3, joint4, joint5, joint6)

        #print s.axis[0]
    except linuxcnc.error, detail:
        print "error", detail
        sys.exit(1)
