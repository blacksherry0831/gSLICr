# ROS导航模块开发计划

## 开发计划

| 开发计划         | 详细                               | 时间 |
| ---------------- | ---------------------------------- | ---- |
| ROS 导航栈学习   | 学习navigation stack（2D）的使用。 |      |
| 地图测绘         | 绘制室内地图。                     | ？   |
| 多路单点激光测距 | 树莓派IIC 接口挂接8个激光设备。    | ？   |
| 定位与姿态集成   | 定位、地图、小车姿态整合           | ？   |
| 图像算法         | 识别天空立面地面。                 | ？   |

### ROS 导航栈学习

| 开发步骤     | 开发任务                                                     | 时间 |
| ------------ | ------------------------------------------------------------ | ---- |
| map          | 地图                                                         |      |
| costmap      | 静态地图层；障碍物地图层；膨胀地图层；                       |      |
| 全局静态地图 | map                                                          |      |
| 导航全局地图 | global_costmap                                               |      |
| 导航局部地图 | local_costmap                                                |      |
| 全局导航算法 | [navfn](http://wiki.ros.org/action/fullsearch/navfn?action=fullsearch&context=180&value=linkto%3A"navfn") |      |
| 局部导航算法 | [dwa_local_planner](http://wiki.ros.org/action/fullsearch/dwa_local_planner?action=fullsearch&context=180&value=linkto%3A"dwa_local_planner") |      |

### 地图测绘

| 开发步骤                 | 开发任务                | 时间 |
| ------------------------ | ----------------------- | ---- |
| 绘制室内地图             | 使用画图、CAD工具绘制。 |      |
| 转换地图格式             | 地图格式PGM             |      |
| 建立地图与物理世界的联系 | 编写YAML                |      |
| 在ROS中  加载地图        | map-server 加载地图     |      |

### 多路单点激光测距

| 开发步骤                                        | 开发任务                                             | 时间 |
| ----------------------------------------------- | ---------------------------------------------------- | ---- |
| 熟悉激光测距传感器TFminiPlus、树莓派、IIC接口。 | 学习IIC协议。树莓派IIC使用方法。TFminiPlus通讯协议。 |      |
| 熟悉ubuntu16.04，ROS ROS Kinetic。              | 用ROS 发布订阅消息。                                 |      |
| 硬件连接                                        | 树莓派IIC、电源、IIC总线、TFminiPlus连接。           |      |
| 读取激光传感器的数据                            | 树莓派读取TFminiPlus数据。                           |      |
| 激光数据和小车本体坐标的变换                    | laser_frame 与base_link之间的TF变换                  |      |
| 在ROS中发布激光数据                             | 消息格式sensor_msgs/LaserScan。                      |      |
| 激光数据接入导航地图                            | 标记激光测得的障碍物在地图中的位置                   |      |

### 定位与姿态集成

| 开发步骤                  | 开发任务                                  | 时间 |
| ------------------------- | ----------------------------------------- | ---- |
| 学习定位模块LinkTrack S/P | 定位模块的安装、调试。                    |      |
| 学习定位模块ROS 功能包    | 定位模块ROS包（官方提供）学习。           |      |
| 硬件连接                  | 定位惯性导航模块与树莓派连接（USB-typeC） |      |
| 定位姿态功能接入ROS       | 在ROS中读取位姿信息                       |      |
| 地图与里程计坐标变换      | map --> odom --> base_link --> laser      |      |
| 在ROS中发布位姿           |                                           |      |
|                           |                                           |      |

### 图像算法

| 开发步骤                                                     | 开发任务               | 时间 |
| ------------------------------------------------------------ | ---------------------- | ---- |
| 建立图像与物理的联系                                         |                        |      |
| 图像数据转换成三维的深度信息                                 | 利用图像判断障碍物远近 |      |
| 摄像头与小车本体坐标的变换                                   | 摄像头相对小车的位置   |      |
| 发布区图像原始数据                                           | ROS camera 原始数据    |      |
| 利用[rosbridge_suite](http://wiki.ros.org/action/fullsearch/rosbridge_suite?action=fullsearch&context=180&value=linkto%3A"rosbridge_suite")发布图像二维深度数据 | 只判断障碍物的直线距离 |      |
| 利用[rosbridge_suite](http://wiki.ros.org/action/fullsearch/rosbridge_suite?action=fullsearch&context=180&value=linkto%3A"rosbridge_suite")发布图像三维深度数据 | 判断障碍物高度信息     |      |
| 图像数据接入导航地图                                         |                        |      |

