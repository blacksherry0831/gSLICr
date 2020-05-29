# 视觉AGV技术参数要求

​		我们的**视觉导航主控板**不直接读取传感器数据。需要OMARK的主控板读取相关传感器数据传输到**视觉导航主控板**。由**视觉导航主控板**发送运动控制命令，控制AGV车运动。



## 一、AGV本体参数

### 1.1AGV车尺寸

| 尺寸 | 单位（m） |
| ---- | --------- |
| 长   | ?         |
| 宽   | ?         |
| 高   | ?         |

### 1.2AGV坐标原点jig

​		AGV车本体坐标系为base_link。坐标原点位于小车运动中心。

## 二、避障定位传感器

### 2.1避障传感器

#### 2.1.1坐标

| 传感器        | 型号     | 相对于base_link的坐标(m) |
| ------------- | -------- | ------------------------ |
| 激光测距1     | UST-05LN | （x,y,z）                |
| 激光测距2     | UST-05LN | （x,y,z）                |
| 安全触边Front | ?        | （x,y,z）                |
| 安全触边Back  | ?        | （x,y,z）                |
| 二维码定位    | ？       | （x,y,z）                |
|               |          |                          |

#### 2.1.2数据格式

| 传感器        | 传感器数据格式                                               |
| ------------- | ------------------------------------------------------------ |
| 激光测距1     | [sensor_msgs](http://docs.ros.org/kinetic/api/sensor_msgs/html/index-msg.html)/[LaserScan](http://docs.ros.org/api/sensor_msgs/html/msg/LaserScan.html) |
| 激光测距2     | [sensor_msgs](http://docs.ros.org/kinetic/api/sensor_msgs/html/index-msg.html)/[LaserScan](http://docs.ros.org/api/sensor_msgs/html/msg/LaserScan.html) |
| 安全触边Front | [sensor_msgs](http://docs.ros.org/kinetic/api/sensor_msgs/html/index-msg.html)/[PointCloud2](http://docs.ros.org/kinetic/api/sensor_msgs/html/msg/PointCloud.html) |
| 安全触边Back  | [sensor_msgs](http://docs.ros.org/kinetic/api/sensor_msgs/html/index-msg.html)/[PointCloud2](http://docs.ros.org/kinetic/api/sensor_msgs/html/msg/PointCloud.html) |
| 二维码定位    | [geometry_msgs](http://docs.ros.org/jade/api/geometry_msgs/html/index-msg.html)/[Pose](http://docs.ros.org/jade/api/geometry_msgs/html/msg/Pose.html) |
|               |                                                              |

## 三、里程计与运动控制命令

### 3.1里程计

| 传感器 | 传感器数据格式                                               |
| ------ | ------------------------------------------------------------ |
| 里程计 | [nav_msgs](http://docs.ros.org/api/nav_msgs/html/index-msg.html)/[Odometry](http://docs.ros.org/api/nav_msgs/html/msg/Odometry.html) |
|        |                                                              |

### 3.2 运动控制命令

控制平面小车的速度矢量。

| 传感器   | 传感器数据格式                                               |
| -------- | ------------------------------------------------------------ |
| 运动控制 | [geometry_msgs](http://docs.ros.org/api/geometry_msgs/html/index-msg.html)/[Twist](http://docs.ros.org/api/geometry_msgs/html/msg/Twist.html) |
|          |                                                              |

## 四、通讯与人机交互

#### 3.1 WIFI



#### 3.2 触摸屏

触摸屏使用教程



##### 3.3  **视觉导航主控板**与OMARK的主控板的通讯

- OMARK的主控板通过网口使用*WebSocket*  发布传感器数据。
- OMARK的主控板通过网口作为ros node发布传感器数据。

## 五、