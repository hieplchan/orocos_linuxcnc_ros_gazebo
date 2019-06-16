# Orocos KDL integrate to ROS
- Add Orocos KDL, LinuxCNC component to ROS platform.

```
catkin_create_pkg joint_angle_msgs
```

- Create and config .msg files.
- Edit CMakeLists.txt and package.xml http://wiki.ros.org/ROS/Tutorials/CreatingMsgAndSrv
```
catkin_make install
```
- Create test_msgs.py

```
roscore

source devel/setup.sh
python src/joint_angle_msgs/test_msgs.py

source devel/setup.sh
rostopic echo /joint_angle

source /home/hiep/Desktop/ros_linuxcnc_gazebo/catkin_ws/devel/setup.sh
/home/hiep/Desktop/ros_linuxcnc_gazebo/catkin_ws/src/joint_angle_msgs

source /home/hiep/linuxcnc-dev/scripts/rip-environment
linuxcnc

python /home/hiep/Desktop/ros_linuxcnc_gazebo/test/linuxcnc_test.py
python /home/hiep/Desktop/ros_linuxcnc_gazebo/test/joint_angle_pub.py
python /home/hiep/Desktop/ros_linuxcnc_gazebo/test/test_msgs.py
```
