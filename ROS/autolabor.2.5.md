# autolabor 2.5开发指南

## 网站

- http://www.autolabor.com.cn/
- http://www.autolabor.com.cn/usedoc/autolabor2_5/dev

## 功能包

http://wiki.ros.org/cn/ROS/Tutorials

### rosbridge

Rosbridge provides a JSON API to ROS functionality for non-ROS programs

- http://wiki.ros.org/rosbridge_suite

- https://github.com/RobotWebTools/rosbridge_suite
- https://github.com/RobotWebTools/rosbridge_suite/blob/develop/ROSBRIDGE_PROTOCOL.md

### ros_arduino_bridge

This stack includes a ROS driver and base controller for Arduino-compatible microcontrollers. The driver provides access to analog and digital sensors, PWM servos, and odometry data from encoders. It is meant to be a complete solution for running an Arduino-controlled robot under ROS.

- http://wiki.ros.org/ros_arduino_bridge

- https://github.com/hbrobotics/ros_arduino_bridge/tree/kinetic-devel

## [Nodes](http://wiki.ros.org/Nodes)/[Topics](http://wiki.ros.org/Topics)/[Messages](http://wiki.ros.org/Messages)

### Nodes

/arduino
/base_frame_laser
/move_base
/robot_pose_publisher
/rosapi
/rosbridge_udp
/rosbridge_websocket
/rosout
/rplidarNode
/slam_gmapping

--------------------------------------------------------------------------------
Node [/arduino]
Publications:

 * /tf [tf/tfMessage]
 * /odom [nav_msgs/Odometry]
 * /cmd_vel [geometry_msgs/Twist]
 * /rosout [rosgraph_msgs/Log]
 * /arduino/sensor_state [ros_arduino_msgs/SensorState]

Subscriptions:
 * /cmd_vel [geometry_msgs/Twist]

Services:
 * /arduino/get_loggers
 * /arduino/servo_write
 * /arduino/digital_read
 * /arduino/analog_read
 * /arduino/set_logger_level
 * /arduino/digital_write
 * /arduino/digital_set_direction
 * /arduino/servo_read
 * /arduino/analog_write


contacting node http://192.168.50.10:38769/ ...
Pid: 1538
Connections:
 * topic: /odom
    * to: /move_base
    * direction: outbound
    * transport: TCPROS
 * topic: /rosout
    * to: /rosout
    * direction: outbound
    * transport: TCPROS
 * topic: /cmd_vel
    * to: /arduino
    * direction: outbound
    * transport: TCPROS
 * topic: /tf
    * to: /slam_gmapping
    * direction: outbound
    * transport: TCPROS
 * topic: /tf
    * to: /robot_pose_publisher
    * direction: outbound
    * transport: TCPROS
 * topic: /tf
    * to: /move_base
    * direction: outbound
    * transport: TCPROS
 * topic: /tf
    * to: /rosbridge_udp
    * direction: outbound
    * transport: TCPROS
 * topic: /cmd_vel
    * to: /move_base (http://192.168.50.10:45278/)
    * direction: inbound
    * transport: TCPROS
 * topic: /cmd_vel
    * to: /arduino (http://192.168.50.10:38769/)
    * direction: inbound
    * transport: TCPROS
 * topic: /cmd_vel
    * to: /rosbridge_udp (http://192.168.50.10:44849/)
    * direction: inbound
    * transport: TCPROS



### Topics

/cmd_vel

/odom

#### /cmd_vel

rostopic info /cmd_vel
Type: geometry_msgs/Twist

Publishers:
 * /move_base (http://192.168.50.10:45278/)
 * /arduino (http://192.168.50.10:38769/)
 * /rosbridge_udp (http://192.168.50.10:44849/)

Subscribers:

 * /arduino (http://192.168.50.10:38769/)

linear:
  x: -0.180017545819
  y: 0.0
  z: 0.0
angular:
  x: 0.0
  y: 0.
  z: -0.0393577873707

#### /odom

 rostopic info /odom
Type: nav_msgs/Odometry

Publishers:
 * /arduino (http://192.168.50.10:38769/)

Subscribers:

 * /move_base (http://192.168.50.10:45278/)

---
header:
  seq: 18910
  stamp:
    secs: 1587352648
    nsecs: 371428966
  frame_id: odom
child_frame_id: base_link
pose:
  pose:
    position:
      x: 0.61399666022
      y: -0.143831788875
      z: 0.0
    orientation:
      x: 0.0
      y: 0.0
      z: -0.441766412345
      w: 0.89713011148
  covariance: [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0]
twist:
  twist:
    linear:
      x: 0.0
      y: 0.0
      z: 0.0
    angular:
      x: 0.0
      y: 0.0
      z: 0.0

  covariance: [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0]