# 多点导航ROS机器人开发计划（室内导航）

机器人已具备激光SLAM功能。在此基础上修改出特定场景的多点导航功能。

# 激光SLAM导航有以下问题：

1.  需要构图才能导航
2. 坐标系建立的是相对坐标系
3. 线扫雷达盲区较大
4. 无法适应室外场景
5. 没有视觉图像

# 多点导航需要解决：

1. 预先加载已知地图

2. 建立绝对坐标系

3. 增加传感器

4. 适应室内外场景

5. 增加视觉系统

# 开发的软件硬件部分包括以下：

| 开发内容       | 硬件             | 软件包                                                       | 开发内容           | 开发者 | 进度               |
| -------------- | ---------------- | ------------------------------------------------------------ | ------------------ | ------ | ------------------ |
| 底盘           | 康尼底盘         |                                                              | 底盘运动控制模型   | 康尼   | ？                 |
| 加速计/陀螺仪  | IMU              |                                                              | 惯导模块           | ?      | 视康尼开发进度而定 |
| 室内定位       | UWB              |                                                              | 室内定位功能。     |        | ？                 |
| 避障雷达       | 超声波           |                                                              | 实现盲区避障       |        | ？                 |
| 线扫雷达       | RPLIDAR A Series | [Slamtec](https://github.com/Slamtec)/**[rplidar_sdk](https://github.com/Slamtec/rplidar_sdk)** | 360度避障          |        | OK                 |
| 室外定位       | 室外定位GNSS     | nmea_navsat_driver                                           | 室外全球定位功能   |        | OK                 |
| 图像节点       | 摄像头           | rocon_rtsp_camera_relay                                      | 图像显示           |        | OK                 |
| 遥控           | Logitech F710    | [ros-drivers](https://github.com/ros-drivers)/**[joystick_drivers](https://github.com/ros-drivers/joystick_drivers)** | 遥控小车           |        | OK                 |
| -              | -                | -                                                            | -                  | -      | -                  |
| 扩展卡尔曼滤波 |                  | [robot_pose_ekf](http://wiki.ros.org/action/fullsearch/robot_pose_ekf?action=fullsearch&context=180&value=linkto%3A"robot_pose_ekf") | 融合底盘与IMU      | ？     | 视康尼开发进度而定 |
| 地图           |                  | [map_server](http://wiki.ros.org/map_server/)                | 测绘并发布室内地图 |        | ？                 |
| 坐标系         |                  | TF                                                           | 传感器坐标系建立   |        | ？                 |
| 室内导航       |                  | [move_base](http://wiki.ros.org/action/fullsearch/move_base?action=fullsearch&context=180&value=linkto%3A"move_base") | 配置导航功能包     |        | ？                 |
| 室内多点导航   |                  | 参考autolabor最新设计                                        | 多点导航           |        | ?                  |
|                |                  |                                                              |                    |        |                    |
| -              | -                | -                                                            | -                  | -      | -                  |

[TOC]

## 一、全局静态地图

​    绘制全局地图并加载到ROS系统。

1. 使用画图、CAD工具绘制室内地图；
2. 将地图转换为PGM格式；
3. 编写地图尺寸分辨率信息（YAML文件）；
4. 在ROS中用map-server 加载地图；

### 1.1 地图格式**PGM**

​		PGM 是便携式灰度图像格式(portable graymap file format)。在黑白超声图像系统中经常使用PGM格式的图像。

### 1.2 地图描述文件

#### 1.2.1 YAML format

```yaml
image: xxx.pgm
resolution: 0.050000
origin: [-13.800000, -15.400000, 0.000000]
negate: 0
occupied_thresh: 0.65
free_thresh: 0.196
```

#### 1.2.2 Launch文件编写

```xml
<!-- Map server -->
<arg name="map_file" default="$(env TURTLEBOT_MAP_FILE)"/>
<node name="map_server" pkg="map_server" type="map_server" args="$(arg map_file)" />
```

```shell
rosrun map_server map_server mymap.yaml
```

## 二、传感器

### 2.1激光测距传感器

​		树莓派IIC 接口挂接8个激光测距设备。程序轮训IIC总线获得传感器8路数据。

#### 2.1.1激光测距传感器性能指标

​		传感器型号为TFmini Plus激光雷达模组。它是一款小型化单点测距产品，基于 ToF（飞行 时间）原理。产品同时兼容UART和IIC通信接口，可以通过指令进行切换。

​		激光雷达传感器性能指标：

| 参数名称   | 参数值   |
| ---------- | -------- |
| 测量范围   | 0.1m~12m |
| 距离分辨   | 1cm      |
| 信号接受角 | 3.6度    |
| 输出频率   | 1~1000Hz |
| ...        | ...      |

##### 资料链接：

http://www.benewake.com/support_article?catename=e1ba3171-58b3-419b-8895-855d6ce93b50&supportid=758813c9-5551-4751-8554-e8ff05b7ee3c&pageindex=1



#### 2.1.2 激光传感器数据格式/LaserScan

##### [sensor_msgs](http://docs.ros.org/api/sensor_msgs/html/index-msg.html)/LaserScan

###### Raw Message Definition

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

###### Compact Message Definition

```c++
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

### 2.2图像深度传感器

​		[在ROS上发布传感器数据流](http://wiki.ros.org/cn/navigation/Tutorials/RobotSetup/Sensors)请参考此链接http://wiki.ros.org/cn/navigation/Tutorials/RobotSetup/Sensors。

​		图像传感器用于测量图像中物体的深度信息。并转换成雷达图或3D点云投射到地图系统中。

​		第一代机器人并不直接处理图像数据。而是通过rosbridge_server接受并处理上位机处理好的数据。

​		导航功能包集只接受使用sensor_msgs/LaserScan或sensor_msgs/PointCloud消息类型发布的传感器数据。

​		我们还没有确实使用sensor_msgs/LaserScan或sensor_msgs/PointCloud之中的哪一个。

#### 2.2.1图像传感器数据格式/PointCloud

##### [sensor_msgs](http://docs.ros.org/api/sensor_msgs/html/index-msg.html)/PointCloud

###### Raw Message Definition

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

###### Compact Message Definition

```c++
std_msgs/Header header
geometry_msgs/Point32[] points
sensor_msgs/ChannelFloat32[] channels
```

### 2.3 定位惯导姿态传感器

#### 2.3.1定位与惯性导航模块性能指标

​		LinkTrack 是一款基于UWB 技术的多功能系统，支持LP（局部定位）、DR（分布式测距）、DT（数传）三种模式，支持配置为标签、基站等多种角色。LP 是支持定位、导航、授时与通信（PNTC）一体化功能的实时定位模式，分为标签、基站、控制台三种角色。标签实时测量并进行坐标解算，输出自身测距、坐标等信息，基站与控制台实时输出所有标签的定位信息。

​		支持1、2、3 维定位，典型1 维、2维定位精度10cm，典型第3 维定位精度30cm；定位频率高达200Hz，基站容量多达120 个，标签容量多达200 个（默认开放40 个标签容量，更多容量需申请开放）。

##### 定位性能指标：

| 参数名称                            | 参数值                   |
| ----------------------------------- | ------------------------ |
| 测距、定位刷新频率高达              | 200Hz                    |
| 1 维、2 维典型定位精度              | 10cm                     |
| 3维定位精度                         | 30cm                     |
| IMU（内嵌）三轴陀螺仪、三轴加速度计 | 原始数据、欧拉角、四元数 |
| ...                                 | ...                      |

##### 应用场景：

- 集群编队（无人机、机器人编队等）
- 机器人、无人机、无人车导航定位
- 轨迹监测与捕捉（追光灯等）
- 多机测距、交互、防碰撞（吊车、矿车等）
- 一维定位
- 高速低延迟无线数传

##### 资料链接：

https://www.nooploop.com/download/



## 三、传感器数据校正与位姿发布

​	车轮里程计、惯性测量单元、定位模块等互相校正共同确定小车的位姿。

​	此处应结合三个传感器的优缺点。

| 数据源       | 优                     | 缺               |
| ------------ | ---------------------- | ---------------- |
| 车轮里程计   | 短期定位姿态有效。     | 长期无效。       |
| 惯性测量单元 | 姿态测量较里程计可靠。 | 安装需精确。     |
| 定位模块     | 定位精确。             | 局部定位易漂移。 |
|              |                        |                  |

### 3.1 robot_pose_ekf

ROS下robot_pose_ekf扩展卡尔曼融合包的使用。

扩展卡尔曼滤波器，输入是里程计、IMU、VO中的任意两个或者三个，输出是一个融合之后的pose。

## 四、建立移动机器人坐标系

​		在机器人系统中，我们使用一棵树来来关联所有坐标系，因此每个坐标系都有一个父坐标系和任意子坐标系，如下：

```c++
map --> odom --> base_link
```

​		世界坐标系是odom坐标系的父，odom坐标系是base_link的父。每坐标系只能有一个父类。

参考资料：

http://wiki.ros.org/navigation/Tutorials/RobotSetup/TF

### 4.1 地图坐标（map）系

​		该map坐标系是一个世界固定坐标系，其Z轴指向上方。在创建地图之后，会根据地图设置了一个map坐标系。

 		在构建地图时，机器人构建地图的起点位置就是map坐标系的位置。

​		在导航节点，当加载地图时，map坐标系就确定了，其实是包含的地图属性中的，例如上面所说的origin属性。

### 4.2 里程计坐标（odom）系

​		在一个典型设置中，odom 坐标系是基于测距源来计算的，如车轮里程计，视觉里程计或惯性测量单元。
​		odom 坐标系作为一种精确，作为短期的本地参考是很有用的，但偏移使得它不能作为长期参考。

### 4.3 机器人基座坐标base_link

​		该base_link坐标刚性地连接到移动机器人基座。用于表示机器人本身位姿的坐标系，其始终与机器人本体保持一致。机器人的定位问题最本质的就是求出base_link在map坐标系下的坐标和姿态。

### 4.4 激光测距传感器坐标laser_link

​		需要发布laser->base_link之间的坐标关系。即，激光传感器相对于小车的位置关系。

### 4.5 图像坐标系camera_link

​		需要发布camera->base_link之间的坐标关系。即，激光传感器相对于小车的位置关系。

### 4.6 定位与惯性导航坐标系

​		需要发布linktrack->base_link之间的坐标关系。即，定位传感器相对于小车的位置关系。

## 五、导航

使用ROS栈[navigation](http://wiki.ros.org/action/fullsearch/navigation?action=fullsearch&context=180&value=linkto%3A"navigation") stack配置导航功能。

导航地图使用[costmap_2d](http://wiki.ros.org/action/fullsearch/costmap_2d?action=fullsearch&context=180&value=linkto%3A"costmap_2d")构建。

### 5.1导航代码配置参考

#### 5.1.1 launch 文件编写：

```xml
<launch>
  <master auto="start"/>
 
  <!-- Run the map server -->
  <node name="map_server" pkg="map_server" type="map_server" args="$(find my_map_package)/my_map.pgm my_map_resolution"/>
 
  <!--- Run AMCL -->
  <include file="$(find amcl)/examples/amcl_omni.launch" />
 
  <node pkg="move_base" type="move_base" respawn="false" name="move_base" output="screen">
    <rosparam file="../config/move_base_params.yaml" command="load" />
    <rosparam file="../config/global_costmap_params.yaml" command="load" ns="global_costmap"/>
    <rosparam file="../config/local_costmap_params.yaml" command="load" ns="local_costmap"/>
    <rosparam file="../config/global_planner_params.yaml" command="load" ns="GlobalPlanner"/>
    <rosparam file="../config/dwa_local_planner_params.yaml" command="load" ns="DWAPlannerROS"/>
    <remap from="/move_base/GlobalPlanner/plan" to="/move_base/NavfnROS/plan"/>
  </node>
    
</launch>
```

#### 5.1.2 yaml配置文件：

| 需要配置文件                  | 内容         |
| ----------------------------- | ------------ |
| move_base_params.yaml         |              |
| global_costmap_params.yaml    | 全局代价地图 |
| local_costmap_params.yaml     | 局部代价地图 |
| global_planner_params.yaml    | 全局路径规划 |
| dwa_local_planner_params.yaml | 本地路径规划 |

#### 5.1.3 代价地图

​		导航功能包集需要两个代价地图来保存世界中的障碍物信息。一张代价地图用于路径规划，在整个环境中创建长期的路径规划，另一个用于局部路径规划与避障。有一些参数两个地图都需要，而有一些则各不相同。

​		导航功能包集使用代价地图存储障碍物信息。为了使这个过程更合理，我们需要指出要监听的传感器的话题，以更新数据。

##### 全局配置(global_costmap)

```shell
# ns : global_costmap

# The global frame for the costmap to operate in. (string, default: "/map")
global_frame: map

# The name of the frame for the base link of the robot.(string, default: "base_link")
robot_base_frame: base_link

# distance a circular robot should be clear of the obstacle (kobuki: 0.18)
# robot_radius: 0.20  
footprint: [[0.175, 0.15], [0.175, -0.15], [-0.175, -0.15], [-0.175, 0.15]]  # if the robot is not circular

# used for obstacle_layer, 3D->voxel 2D->other
map_type: costmap

# Specifies the delay in transform (tf) data that is tolerable in seconds. This parameter serves as a safeguard to losing a link in the tf tree while still allowing an amount of latency the user is comfortable with to exist in the system. For example, a transform being 0.2 seconds out-of-date may be tolerable, but a transform being 8 seconds out of date is not. If the tf transform between the coordinate frames specified by the global_frame and robot_base_frame parameters is transform_tolerance seconds older than ros::Time::now(), then the navigation stack will stop the robot.(double, default: 0.2)
transform_tolerance: 0.5

# The frequency in Hz for the map to be updated.(double, default: 5.0)
update_frequency: 5.0

# The frequency in Hz for the map to be publish display information.(double, default: 0.0)
publish_frequency: 0.0

# Whether or not to use a rolling window version of the costmap. If the static_map parameter is set to true, this parameter must be set to false. (bool, default: false)
rolling_window: false
static_map: true

# If true the full costmap is published to "~<name>/grid" every update. If false only the part of the costmap that has changed is published on the "~<name>/grid_updates" topic. (bool, default: false)
always_send_full_costmap: false

# Sequence of plugin specifications, one per layer. Each specification is a dictionary with name and type fields. The name is used to define the parameter namespace for the plugin.
plugins:
  - {name: static_layer,            type: "costmap_2d::StaticLayer"}
  - {name: obstacle_layer,          type: "costmap_2d::ObstacleLayer"}
  - {name: inflation_layer,         type: "costmap_2d::InflationLayer"}

# The width of the map in meters.(int, default: 10)
width: 5

# The height of the map in meters.(int, default: 10)
height: 5

# The resolution of the map in meters/cell. (double, default: 0.05)
resolution: 0.05

# The x origin of the map in the global frame in meters. (double, default: 0.0)
origin_x: 0.0

# The y origin of the map in the global frame in meters. (double, default: 0.0)
origin_y: 0.0

#############################
#
#        static_layer
#
#############################
static_layer:
# The value for which a cost should be considered unknown when reading in a map from the map server. If the costmap is not tracking unknown space, costs of this value will be considered occupied. A value of zero also results in this parameter being unused. (int, default: -1)
  unknown_cost_value: -1

# The threshold value at which to consider a cost lethal when reading in a map from the map server.(int, default: 100)
  lethal_cost_threshold: 100

# The topic that the costmap subscribes to for the static map. This parameter is useful when you have multiple costmap instances within a single node that you want to use different static maps. (string, default: "map")
  map_topic: map

# Only subscribe to the first message on the map topic, ignoring all subsequent messages (bool, default: false)
  first_map_only: false

# In addition to map_topic, also subscribe to map_topic + "_updates" (bool, default: false)
  subscribe_to_updates: false

# If true, unknown values in the map messages are translated directly to the layer. Otherwise, unknown values in the map message are translated as FREE_SPACE in the layer.  (bool, default: true)
  track_unknown_space: true

# Only matters if the static layer is not the bottom layer. If true, only the maximum value will be written to the master costmap. (bool, default: false)
  use_maximum: false

# If true, translates all map message values to NO_INFORMATION/FREE_SPACE/LETHAL_OBSTACLE (three values). If false, a full spectrum of intermediate values is possible. (bool, default: true)
  trinary_costmap: true

#############################
#
#        inflation_layer
#
#############################
inflation_layer:
# The radius in meters to which the map inflates obstacle cost values. (double, default: 0.55)
  inflation_radius: 0.50

# A scaling factor to apply to cost values during inflation. The cost function is computed as follows for all cells in the costmap further than the inscribed radius distance and closer than the inflation radius distance away from an actual obstacle: exp(-1.0 * cost_scaling_factor * (distance_from_obstacle - inscribed_radius)) * (costmap_2d::INSCRIBED_INFLATED_OBSTACLE - 1), where costmap_2d::INSCRIBED_INFLATED_OBSTACLE is currently 254. NOTE: since the cost_scaling_factor is multiplied by a negative in the formula, increasing the factor will decrease the resulting cost values. (double, default: 10.0)
  cost_scaling_factor: 10.0

#############################
#
#      obstacle_layer
#
#############################
obstacle_layer:
# The maximum height of any obstacle to be inserted into the costmap in meters. This parameter should be set to be slightly higher than the height of your robot. (double, default: 2.0)
  max_obstacle_height: 2.0
# The default maximum distance from the robot at which an obstacle will be inserted into the cost map in meters. This can be over-ridden on a per-sensor basis. (double, default: 2.5)
  obstacle_range: 3.0
# The default range in meters at which to raytrace out obstacles from the map using sensor data. This can be over-ridden on a per-sensor basis. (double, default: 3.0)
  raytrace_range: 4.0
# If false, each pixel has one of 2 states: lethal obstacle or free. If true, each pixel has one of 3 states: lethal obstacle, free, or unknown.  (bool, default: false)
  track_unknown_space: false
# If true, the robot footprint will clear (mark as free) the space in which it travels. (bool, default: true)
  footprint_clearing_enabled: true
# A list of observation source names separated by spaces. This defines each of the <source_name> namespaces defined below. (string, default: "")
  observation_sources: scan
  
  scan:
# The topic on which sensor data comes in for this source. Defaults to the name of the source. (string, default: source_name)
    topic: scan
# The frame of the origin of the sensor. Leave empty to attempt to read the frame from sensor data. The frame can be read from both sensor_msgs/LaserScan, sensor_msgs/PointCloud, and sensor_msgs/PointCloud2 messages. (string, default: "")
    sensor_frame: ""
# How long to keep each sensor reading in seconds. A value of 0.0 will only keep the most recent reading. (double, default: 0.0)
    observation_persistence: 0.0
# How often to expect a reading from a sensor in seconds. A value of 0.0 will allow infinite time between readings. This parameter is used as a failsafe to keep the navigation stack from commanding the robot when a sensor has failed. It should be set to a value that is slightly more permissive than the actual rate of the sensor. For example, if we expect a scan from a laser every 0.05 seconds we might set this parameter to be 0.1 seconds to give a generous buffer and account for some amount of system latency. (double, default: 0.0)
    expected_update_rate: 0.0
# The data type associated with the topic, right now only "PointCloud", "PointCloud2", and "LaserScan" are supported. (string, default: "PointCloud")
    data_type: LaserScan
# Whether or not this observation should be used to clear out freespace.  (bool, default: false)
    clearing: true
# Whether or not this observation should be used to mark obstacles. (bool, default: true)
    marking: true
# The maximum height in meters of a sensor reading considered valid. This is usually set to be slightly higher than the height of the robot. Setting this parameter to a value greater than the global max_obstacle_height parameter has no effect. Setting this parameter to a value less than the global max_obstacle_height will filter out points from this sensor above that height.(double, default: 2.0)
    max_obstacle_height: 2.0
# The minimum height in meters of a sensor reading considered valid. This is usually set to be at ground height, but can be set higher or lower based on the noise model of your sensor. (double, default: 0.0)
    min_obstacle_height: 0.0
# The maximum range in meters at which to insert obstacles into the costmap using sensor data.  (double, default: 2.5)
    obstacle_range: 3.0
# The maximum range in meters at which to raytrace out obstacles from the map using sensor data.  (double, default: 3.0)
    raytrace_range: 4.0
# Allows for Inf values in "LaserScan" observation messages. The Inf values are converted to the laser maximum range.  (bool, default: false)
    inf_is_valid: true


```

##### 本地配置(local_costmap)

```shell
# ns : local_costmap

# The global frame for the costmap to operate in. (string, default: "/map")
global_frame: odom

# The name of the frame for the base link of the robot.(string, default: "base_link")
robot_base_frame: base_link

# distance a circular robot should be clear of the obstacle (kobuki: 0.18)
#robot_radius: 0.20  
footprint: [[0.18, 0.15], [0.18, -0.15], [-0.18, -0.15],[-0.18, 0.15]]  # if the robot is not circular

# used for obstacle_layer, 3D->voxel 2D->other
map_type: costmap

# Specifies the delay in transform (tf) data that is tolerable in seconds. This parameter serves as a safeguard to losing a link in the tf tree while still allowing an amount of latency the user is comfortable with to exist in the system. For example, a transform being 0.2 seconds out-of-date may be tolerable, but a transform being 8 seconds out of date is not. If the tf transform between the coordinate frames specified by the global_frame and robot_base_frame parameters is transform_tolerance seconds older than ros::Time::now(), then the navigation stack will stop the robot.(double, default: 0.2)
transform_tolerance: 0.5

# The frequency in Hz for the map to be updated.(double, default: 5.0)
update_frequency: 5.0

# The frequency in Hz for the map to be publish display information.(double, default: 0.0)
publish_frequency: 0.0

# Whether or not to use a rolling window version of the costmap. If the static_map parameter is set to true, this parameter must be set to false. (bool, default: false)
rolling_window: true
static_map: false

# If true the full costmap is published to "~<name>/grid" every update. If false only the part of the costmap that has changed is published on the "~<name>/grid_updates" topic. (bool, default: false)
always_send_full_costmap: false

# Sequence of plugin specifications, one per layer. Each specification is a dictionary with name and type fields. The name is used to define the parameter namespace for the plugin.
plugins:
  - {name: obstacle_layer,          type: "costmap_2d::ObstacleLayer"}
  - {name: inflation_layer,         type: "costmap_2d::InflationLayer"}

# The width of the map in meters.(int, default: 10)
width: 5.0

# The height of the map in meters.(int, default: 10)
height: 5.0

# The resolution of the map in meters/cell. (double, default: 0.05)
resolution: 0.05

# The x origin of the map in the global frame in meters. (double, default: 0.0)
origin_x: 0.0

# The y origin of the map in the global frame in meters. (double, default: 0.0)
origin_y: 0.0

#############################
#
#        inflation_layer
#
#############################
inflation_layer:
# The radius in meters to which the map inflates obstacle cost values. (double, default: 0.55)
  inflation_radius: 0.20

# A scaling factor to apply to cost values during inflation. The cost function is computed as follows for all cells in the costmap further than the inscribed radius distance and closer than the inflation radius distance away from an actual obstacle: exp(-1.0 * cost_scaling_factor * (distance_from_obstacle - inscribed_radius)) * (costmap_2d::INSCRIBED_INFLATED_OBSTACLE - 1), where costmap_2d::INSCRIBED_INFLATED_OBSTACLE is currently 254. NOTE: since the cost_scaling_factor is multiplied by a negative in the formula, increasing the factor will decrease the resulting cost values. (double, default: 10.0)
  cost_scaling_factor: 10.0

#############################
#
#      obstacle_layer
#
#############################
obstacle_layer:
# The maximum height of any obstacle to be inserted into the costmap in meters. This parameter should be set to be slightly higher than the height of your robot. (double, default: 2.0)
  max_obstacle_height: 2.0
# The default maximum distance from the robot at which an obstacle will be inserted into the cost map in meters. This can be over-ridden on a per-sensor basis. (double, default: 2.5)
  obstacle_range: 3.0
# The default range in meters at which to raytrace out obstacles from the map using sensor data. This can be over-ridden on a per-sensor basis. (double, default: 3.0)
  raytrace_range: 4.0
# If false, each pixel has one of 2 states: lethal obstacle or free. If true, each pixel has one of 3 states: lethal obstacle, free, or unknown.  (bool, default: false)
  track_unknown_space: false
# If true, the robot footprint will clear (mark as free) the space in which it travels. (bool, default: true)
  footprint_clearing_enabled: true
# A list of observation source names separated by spaces. This defines each of the <source_name> namespaces defined below. (string, default: "")
  observation_sources: scan
  
  scan:
# The topic on which sensor data comes in for this source. Defaults to the name of the source. (string, default: source_name)
    topic: scan
# The frame of the origin of the sensor. Leave empty to attempt to read the frame from sensor data. The frame can be read from both sensor_msgs/LaserScan, sensor_msgs/PointCloud, and sensor_msgs/PointCloud2 messages. (string, default: "")
    sensor_frame: ""
# How long to keep each sensor reading in seconds. A value of 0.0 will only keep the most recent reading. (double, default: 0.0)
    observation_persistence: 0.0
# How often to expect a reading from a sensor in seconds. A value of 0.0 will allow infinite time between readings. This parameter is used as a failsafe to keep the navigation stack from commanding the robot when a sensor has failed. It should be set to a value that is slightly more permissive than the actual rate of the sensor. For example, if we expect a scan from a laser every 0.05 seconds we might set this parameter to be 0.1 seconds to give a generous buffer and account for some amount of system latency. (double, default: 0.0)
    expected_update_rate: 0.0
# The data type associated with the topic, right now only "PointCloud", "PointCloud2", and "LaserScan" are supported. (string, default: "PointCloud")
    data_type: LaserScan
# Whether or not this observation should be used to clear out freespace.  (bool, default: false)
    clearing: true
# Whether or not this observation should be used to mark obstacles. (bool, default: true)
    marking: true
# The maximum height in meters of a sensor reading considered valid. This is usually set to be slightly higher than the height of the robot. Setting this parameter to a value greater than the global max_obstacle_height parameter has no effect. Setting this parameter to a value less than the global max_obstacle_height will filter out points from this sensor above that height.(double, default: 2.0)
    max_obstacle_height: 2.0
# The minimum height in meters of a sensor reading considered valid. This is usually set to be at ground height, but can be set higher or lower based on the noise model of your sensor. (double, default: 0.0)
    min_obstacle_height: 0.0
# The maximum range in meters at which to insert obstacles into the costmap using sensor data.  (double, default: 2.5)
    obstacle_range: 3.0
# The maximum range in meters at which to raytrace out obstacles from the map using sensor data.  (double, default: 3.0)
    raytrace_range: 4.0
# Allows for Inf values in "LaserScan" observation messages. The Inf values are converted to the laser maximum range.  (bool, default: false)
    inf_is_valid: true

```

#### 5.1.4 路径规划

路径规划使用the [move_base](http://wiki.ros.org/action/fullsearch/move_base?action=fullsearch&context=180&value=linkto%3A"move_base") ROS Node。

##### 导航算法、导航精度配置

```shell
base_global_planner: "global_planner/GlobalPlanner"
base_local_planner: "dwa_local_planner/DWAPlannerROS"
recovery_behaviors:
  - {name: conservative_reset, type: clear_costmap_recovery/ClearCostmapRecovery} 
  - {name: rotate_recovery, type: rotate_recovery/RotateRecovery} 
  - {name: aggressive_reset, type: clear_costmap_recovery/ClearCostmapRecovery}

# The rate in Hz at which to run the global planning loop. If the frequency is set to 0.0, the global planner will only run when a new goal is received or the local planner reports that its path is blocked.(double, default: 0.0)
planner_frequency: 2.0

# The rate in Hz at which to run the control loop and send velocity commands to the base.(double, default: 20.0)
controller_frequency: 5.0

# How long the planner will wait in seconds in an attempt to find a valid plan before space-clearing operations are performed.(double, default: 5.0)
planner_patience: 3.0

# How long the controller will wait in seconds without receiving a valid control before space-clearing operations are performed.(double, default: 15.0)
controller_patience: 2.0

# Whether or not to enable the move_base recovery behaviors to attempt to clear out space.(bool, default: true)
recovery_behavior_enabled: true

# Determines whether or not the robot will attempt an in-place rotation when attempting to clear out space. Note: This parameter is only used when the default recovery behaviors are in use, meaning the user has not set the recovery_behaviors parameter to anything custom.(bool, default: true)
clearing_rotation_allowed: true

# Determines whether or not to shutdown the costmaps of the node when move_base is in an inactive state (bool, default: false)
shutdown_costmaps: false

# How long in seconds to allow for oscillation before executing recovery behaviors. A value of 0.0 corresponds to an infinite timeout. (double, default: 0.0)
oscillation_timeout: 5.0

# How far in meters the robot must move to be considered not to be oscillating. Moving this far resets the timer counting up to the ~oscillation_timeout (double, default: 0.5)
oscillation_distance: 0.3

# How many times to allow for planning retries before executing recovery behaviors. A value of -1.0 corresponds to an infinite retries.(int32_t, default: -1)
#max_planning_retries: -1

#############################
# plug for recovery_behaviors
#############################
conservative_reset:
# The radius away from the robot in meters outside which obstacles will be removed from the costmaps when they are reverted to the static map.
    reset_distance: 1.0

aggressive_reset:
# The radius away from the robot in meters outside which obstacles will be removed from the costmaps when they are reverted to the static map.
    reset_distance: 0.0

```



##### 全局路径规划（global planner）

本次开发使用[navfn](http://wiki.ros.org/action/fullsearch/navfn?action=fullsearch&context=180&value=linkto%3A"navfn")作为全局导航。

参考文件：

```shell
# ns : GlobalPlanner

# Specifies whether or not to allow the planner to create plans that traverse unknown space. NOTE: if you are using a layered costmap_2d costmap with a voxel or obstacle layer, you must also set the track_unknown_space param for that layer to be true, or it will convert all your unknown space to free space (which planner will then happily go right through). (bool, default: true)
allow_unknown: true

# A tolerance on the goal point for the planner. The planner will attempt to create a plan that is as close to the specified goal as possible but no further than default_tolerance away. (double, default: 0.0)
default_tolerance: 0.0

# Specifies whether or not to visualize the potential area computed via a PointCloud2. (bool, default: false)
visualize_potential: false

# If true, use dijkstra's algorithm. Otherwise, A*. (bool, default: true)
use_dijkstra: true

# If true, use the quadratic approximation of the potential. Otherwise, use a simpler calculation. (bool, default: true)
use_quadratic: true

# If true, create a path that follows the grid boundaries. Otherwise, use a gradient descent method. (bool, default: false)
use_grid_path: false

# If for some reason, you want global_planner to exactly mirror the behavior of navfn, set this to true (and use the defaults for the other boolean parameters) (bool, default: false)
old_navfn_behavior: false

```

##### 本地实时规划（local planner）

本次开发使用[dwa_local_planner](http://wiki.ros.org/action/fullsearch/dwa_local_planner?action=fullsearch&context=180&value=linkto%3A"dwa_local_planner")用作局部导航。

参考文件：

```shell
DWAPlannerROS: 
 
# Robot Configuration Parameters - Kobuki 机器人配置参数，这里为Kobuki底座
  max_vel_x: 0.5  # 0.55 
  #x方向最大线速度绝对值，单位:米/秒
  min_vel_x: 0.0  
  #x方向最小线速度绝对值，单位:米/秒。如果为负值表示可以后退.
 
  max_vel_y: 0.0  # diff drive robot  
  #y方向最大线速度绝对值，单位:米/秒。turtlebot为差分驱动机器人，所以为0
  min_vel_y: 0.0  # diff drive robot  
  #y方向最小线速度绝对值，单位:米/秒。turtlebot为差分驱动机器人，所以为0
 
  max_trans_vel: 0.5 # choose slightly less than the base's capability 
  #机器人最大平移速度的绝对值，单位为 m/s
  min_trans_vel: 0.1  # this is the min trans velocity when there is negligible rotational velocity 
  #机器人最小平移速度的绝对值，单位为 m/s
  trans_stopped_vel: 0.1 
  #机器人被认属于“停止”状态时的平移速度。如果机器人的速度低于该值，则认为机器人已停止。单位为 m/s
 
  # Warning!
  #   do not set min_trans_vel to 0.0 otherwise dwa will always think translational velocities
  #   are non-negligible and small in place rotational velocities will be created.
  #注意不要将min_trans_vel设置为0，否则DWA认为平移速度不可忽略，将创建较小的旋转速度。
 
  max_rot_vel: 5.0  # choose slightly less than the base's capability #机器人的最大旋转角速度的绝对值，单位为 rad/s 
  min_rot_vel: 0.4  # this is the min angular velocity when there is negligible translational velocity #机器人的最小旋转角速度的绝对值，单位为 rad/s
  rot_stopped_vel: 0.4 #机器人被认属于“停止”状态时的旋转速度。单位为 rad/s
   
  acc_lim_x: 1.0 # maximum is theoretically 2.0, but we  机器人在x方向的极限加速度，单位为 meters/sec^2
  acc_lim_theta: 2.0 机器人的极限旋转加速度，单位为 rad/sec^2
  acc_lim_y: 0.0      # diff drive robot 机器人在y方向的极限加速度，对于差分机器人来说当然是0
 
# Goal Tolerance Parameters 目标距离公差参数
  yaw_goal_tolerance: 0.3  # 0.05 
  #到达目标点时，控制器在偏航/旋转时的弧度容差(tolerance)。即：到达目标点时偏行角允许的误差，单位弧度
  xy_goal_tolerance: 0.15  # 0.10 
  #到到目标点时，控制器在x和y方向上的容差（tolerence）（米）。即：到达目标点时,在xy平面内与目标点的距离误差
  # latch_xy_goal_tolerance: false 
  # 设置为true时表示：如果到达容错距离内,机器人就会原地旋转；即使转动是会跑出容错距离外。
#注：这三个参数的设置及影响讨论请参考《ROS导航功能调优指南》
 
# Forward Simulation Parameters 前向模拟参数
  sim_time: 1.0       # 1.7 
  #前向模拟轨迹的时间，单位为s(seconds) 
  vx_samples: 6       # 3  
  #x方向速度空间的采样点数.
  vy_samples: 1       # diff drive robot, there is only one sample
  #y方向速度空间采样点数.。Tutulebot为差分驱动机器人，所以y方向永远只有1个值（0.0）
  vtheta_samples: 20  # 20 
  #旋转方向的速度空间采样点数.
#注：参数的设置及影响讨论请参考《ROS导航功能调优指南》
 
# Trajectory Scoring Parameters 轨迹评分参数
  path_distance_bias: 64.0      # 32.0   - weighting for how much it should stick to the global path plan
  #控制器与给定路径接近程度的权重
  
  goal_distance_bias: 24.0      # 24.0   - weighting for how much it should attempt to reach its goal
  #控制器与局部目标点的接近程度的权重，也用于速度控制
  
  occdist_scale: 0.5            # 0.01   - weighting for how much the controller should avoid obstacles
  # 控制器躲避障碍物的程度
  
  forward_point_distance: 0.325 # 0.325  - how far along to place an additional scoring point
  #以机器人为中心，额外放置一个计分点的距离
  
  stop_time_buffer: 0.2         # 0.2    - amount of time a robot must stop in before colliding for a valid traj.
  #机器人在碰撞发生前必须拥有的最少时间量。该时间内所采用的轨迹仍视为有效。即：为防止碰撞,机器人必须提前停止的时间长度
 
  scaling_speed: 0.25           # 0.25   - absolute velocity at which to start scaling the robot's footprint
  #开始缩放机器人足迹时的速度的绝对值，单位为m/s。
  #在进行对轨迹各个点计算footprintCost之前，会先计算缩放因子。如果当前平移速度小于scaling_speed，则缩放因子为1.0，否则，缩放因子为(vmag - scaling_speed) / (max_trans_vel - scaling_speed) * max_scaling_factor + 1.0。然后，该缩放因子会被用于计算轨迹中各个点的footprintCost。
  # 参考：https://www.cnblogs.com/sakabatou/p/8297479.html
  #亦可简单理解为：启动机器人底盘的速度.(Ref.: https://www.corvin.cn/858.html)
  
  max_scaling_factor: 0.2       # 0.2    - how much to scale the robot's footprint when at speed.
  #最大缩放因子。max_scaling_factor为上式的值的大小。
 
# Oscillation Prevention Parameters 振荡预防参数
  oscillation_reset_dist: 0.05  # 0.05   - how far to travel before resetting oscillation flags
  #机器人必须运动多少米远后才能复位震荡标记(机器人运动多远距离才会重置振荡标记)
 
# Global Plan Parameters
  #prune_plan: false
  #机器人前进是否清除身后1m外的轨迹.
  
# Debugging 调试参数
  publish_traj_pc : true #将规划的轨迹在RVIZ上进行可视化
  publish_cost_grid_pc: true 
  #将代价值进行可视化显示
  #是否发布规划器在规划路径时的代价网格.如果设置为true,那么就会在~/cost_cloud话题上发布sensor_msgs/PointCloud2类型消息.
  global_frame_id: odom #全局参考坐标系为odom
 
 
# Differential-drive robot configuration - necessary? 差分机器人配置参数
#  holonomic_robot: false 
   #是否为全向机器人。 值为false时为差分机器人； 为true时表示全向机器人
```

### 5.2 多点导航功能

参考autolabor多点导航方案。

### 5.3 参考链接

http://roswiki.autolabor.com.cn/cn(2f)navigation(2f)Tutorials(2f)RobotSetup.html