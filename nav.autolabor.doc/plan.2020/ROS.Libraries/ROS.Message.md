# ROS MESSAGE

[TOC]



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

```shell
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

## Header 

### [std_msgs](http://docs.ros.org/api/std_msgs/html/index-msg.html)/Header Message

#### Raw Message Definition

```shell
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
string frame_id
```

#### Compact Message Definition

```shell
uint32 seq
time stamp
string frame_id
```

#### 参考资料

​		Header包括是哪个字段。字段seq对应一个标识符，随着消息被发布，它会自动增加。字段stamp存储与数据相关联的时间信息。以激光扫描为例，stamp可能对应每次扫描开始的时间。字段frame_id存储与数据相关联的tf帧信息。以激光扫描为例，它将是激光数据所在帧。

## LaserScan

### [sensor_msgs](http://docs.ros.org/api/sensor_msgs/html/index-msg.html)/LaserScan

#### Raw Message Definition

```shell
# Single scan from a planar laser range-finder
#
# If you have another ranging device with different behavior (e.g. a sonar
# array), please find or create a different message, since applications
# will make fairly laser-specific assumptions about this data

Header header            # timestamp in the header is the acquisition time of 
                         # the first ray in the scan.
                         #
                         # in frame frame_id, angles are measured around 
                         # the positive Z axis (counterclockwise, if Z is up)
                         # with zero angle being forward along the x axis
                         
float32 angle_min        # start angle of the scan [rad]
float32 angle_max        # end angle of the scan [rad]
float32 angle_increment  # angular distance between measurements [rad]

float32 time_increment   # time between measurements [seconds] - if your scanner
                         # is moving, this will be used in interpolating position
                         # of 3d points
float32 scan_time        # time between scans [seconds]

float32 range_min        # minimum range value [m]
float32 range_max        # maximum range value [m]

float32[] ranges         # range data [m] (Note: values < range_min or > range_max should be discarded)
float32[] intensities    # intensity data [device-specific units].  If your
                         # device does not provide intensities, please leave
                         # the array empty.
```

#### Compact Message Definition

```C++
std_msgs/Header header
float32 angle_min
float32 angle_max
float32 angle_increment
float32 time_increment
float32 scan_time
float32 range_min
float32 range_max
float32[] ranges
float32[] intensities
```

#### 参考资料

​		导航功能包集只接受使用sensor_msgs/LaserScan或sensor_msgs/PointCloud消息类型发布的传感器数据。

​		[在ROS上发布传感器数据流](http://wiki.ros.org/cn/navigation/Tutorials/RobotSetup/Sensors)请参考此链接http://wiki.ros.org/cn/navigation/Tutorials/RobotSetup/Sensors。

## PointCloud

### [sensor_msgs](http://docs.ros.org/api/sensor_msgs/html/index-msg.html)/PointCloud

#### Raw Message Definition

```shell
# This message holds a collection of 3d points, plus optional additional
# information about each point.

# Time of sensor data acquisition, coordinate frame ID.
Header header

# Array of 3d points. Each Point32 should be interpreted as a 3d point
# in the frame given in the header.
geometry_msgs/Point32[] points

# Each channel should have the same number of elements as points array,
# and the data in each channel should correspond 1:1 with each point.
# Channel names in common practice are listed in ChannelFloat32.msg.
ChannelFloat32[] channels
```

#### Compact Message Definition

```c++
std_msgs/Header header
geometry_msgs/Point32[] points
sensor_msgs/ChannelFloat32[] channels
```

#### 参考资料

​		导航功能包集只接受使用sensor_msgs/LaserScan或sensor_msgs/PointCloud消息类型发布的传感器数据。

​		[在ROS上发布传感器数据流](http://wiki.ros.org/cn/navigation/Tutorials/RobotSetup/Sensors)请参考此链接http://wiki.ros.org/cn/navigation/Tutorials/RobotSetup/Sensors。

## PointCloud2

### [sensor_msgs](http://docs.ros.org/api/sensor_msgs/html/index-msg.html)/PointCloud2

#### Raw Message Definition

```shell
# This message holds a collection of N-dimensional points, which may
# contain additional information such as normals, intensity, etc. The
# point data is stored as a binary blob, its layout described by the
# contents of the "fields" array.

# The point cloud data may be organized 2d (image-like) or 1d
# (unordered). Point clouds organized as 2d images may be produced by
# camera depth sensors such as stereo or time-of-flight.

# Time of sensor data acquisition, and the coordinate frame ID (for 3d
# points).
Header header

# 2D structure of the point cloud. If the cloud is unordered, height is
# 1 and width is the length of the point cloud.
uint32 height
uint32 width

# Describes the channels and their layout in the binary data blob.
PointField[] fields

bool    is_bigendian # Is this data bigendian?
uint32  point_step   # Length of a point in bytes
uint32  row_step     # Length of a row in bytes
uint8[] data         # Actual point data, size is (row_step*height)

bool is_dense        # True if there are no invalid points
```

#### Compact Message Definition

```shell
std_msgs/Header header
uint32 height
uint32 width
sensor_msgs/PointField[] fields
bool is_bigendian
uint32 point_step
uint32 row_step
uint8[] data
bool is_dense
```

#### 参考资料

​		导航功能包集只接受使用sensor_msgs/LaserScan或sensor_msgs/PointCloud消息类型发布的传感器数据。

​		[在ROS上发布传感器数据流](http://wiki.ros.org/cn/navigation/Tutorials/RobotSetup/Sensors)请参考此链接http://wiki.ros.org/cn/navigation/Tutorials/RobotSetup/Sensors。