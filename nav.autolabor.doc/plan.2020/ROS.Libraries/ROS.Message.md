# ROS MESSAGE

## [Odometry](http://docs.ros.org/api/nav_msgs/html/msg/Odometry.html)

------

### [nav_msgs](http://docs.ros.org/api/nav_msgs/html/index-msg.html)/[Odometry](http://docs.ros.org/api/nav_msgs/html/msg/Odometry.html)

Raw Message Definition

```shell
# This represents an estimate of a position and velocity in free space.  
# The pose in this message should be specified in the coordinate frame given by header.frame_id.
# The twist in this message should be specified in the coordinate frame given by the child_frame_id
```

Compact Message Definition

[std_msgs/Header](http://docs.ros.org/api/std_msgs/html/msg/Header.html) header
string child_frame_id
[geometry_msgs/PoseWithCovariance](http://docs.ros.org/api/geometry_msgs/html/msg/PoseWithCovariance.html) pose
[geometry_msgs/TwistWithCovariance](http://docs.ros.org/api/geometry_msgs/html/msg/TwistWithCovariance.html) twist

------

### [geometry_msgs](http://docs.ros.org/api/geometry_msgs/html/index-msg.html)/PoseWithCovariance

Raw Message Definition

```shell
# This represents a pose in free space with uncertainty.

Pose pose

# Row-major representation of the 6x6 covariance matrix
# The orientation parameters use a fixed-axis representation.
# In order, the parameters are:
# (x, y, z, rotation about X axis, rotation about Y axis, rotation about Z axis)
float64[36] covariance
```

Compact Message Definition

[geometry_msgs/Pose](http://docs.ros.org/api/geometry_msgs/html/msg/Pose.html) pose
float64[36] covariance //方差矩阵

------

### [geometry_msgs/Pose](http://docs.ros.org/api/geometry_msgs/html/msg/Pose.html) pose

```shell
# A representation of pose in free space, composed of position and orientation. 
Point position
Quaternion orientation
```

Compact Message Definition

[geometry_msgs/Point](http://docs.ros.org/api/geometry_msgs/html/msg/Point.html) position
[geometry_msgs/Quaternion](http://docs.ros.org/api/geometry_msgs/html/msg/Quaternion.html) orientation

------

### [geometry_msgs](http://docs.ros.org/api/geometry_msgs/html/index-msg.html)/Point

```shell
# This contains the position of a point in free space
float64 x
float64 y
float64 z
```

### [geometry_msgs](http://docs.ros.org/api/geometry_msgs/html/index-msg.html)/Quaternion

```shell
# This represents an orientation in free space in quaternion form.

float64 x
float64 y
float64 z
float64 w
```

------

### [geometry_msgs](http://docs.ros.org/api/geometry_msgs/html/index-msg.html)/TwistWithCovariance

Raw Message Definition

```shell
# This expresses velocity in free space with uncertainty.

Twist twist

# Row-major representation of the 6x6 covariance matrix
# The orientation parameters use a fixed-axis representation.
# In order, the parameters are:
# (x, y, z, rotation about X axis, rotation about Y axis, rotation about Z axis)
float64[36] covariance

```

Compact Message Definition

[geometry_msgs/Twist](http://docs.ros.org/api/geometry_msgs/html/msg/Twist.html) twist
float64[36] covariance

------

### [geometry_msgs](http://docs.ros.org/api/geometry_msgs/html/index-msg.html)/Twist

```shell
# This expresses velocity in free space broken into its linear and angular parts.
Vector3  linear
Vector3  angular
```

Compact Message Definition

[geometry_msgs/Vector3](http://docs.ros.org/api/geometry_msgs/html/msg/Vector3.html) linear
[geometry_msgs/Vector3](http://docs.ros.org/api/geometry_msgs/html/msg/Vector3.html) angular

### [geometry_msgs](http://docs.ros.org/api/geometry_msgs/html/index-msg.html)/Vector3

```
# This represents a vector in free space. 
# It is only meant to represent a direction. Therefore, it does not
# make sense to apply a translation to it (e.g., when applying a 
# generic rigid transformation to a Vector3, tf2 will only apply the
# rotation). If you want your data to be translatable too, use the
# geometry_msgs/Point message instead.

float64 x
float64 y
float64 z
```

## LaserScan

### sensor_msgs/LaserScan

```
#
# Laser scans angles are measured counter clockwise, with 0 facing forward
# (along the x-axis) of the device frame
#

Header header
float32 angle_min        # start angle of the scan [rad]
float32 angle_max        # end angle of the scan [rad]
float32 angle_increment  # angular distance between measurements [rad]
float32 time_increment   # time between measurements [seconds]
float32 scan_time        # time between scans [seconds]
float32 range_min        # minimum range value [m]
float32 range_max        # maximum range value [m]
float32[] ranges         # range data [m] (Note: values < range_min or > range_max should be discarded)
float32[] intensities    # intensity data [device-specific units]
```

激光扫描角度是逆时针测量的，0面朝前(沿x轴)的设备帧

## PointCloud

### sensor_msgs/PointCloud

```
ation about each point.
#Each Point32 should be interpreted as a 3d point in the frame given in the header

Header header
geometry_msgs/Point32[] points  #Array of 3d points
ChannelFloat32[] channels       #Each channel should have the same number of elements as points array, and the data in each channel should correspond 1:1 with each point
```

