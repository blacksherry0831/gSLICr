# 室内小车巡航算法B

## 一、导航目标

小车避开障碍物在室内路面上向指定目标点巡航。

## 二、导航组件

### 1. 硬件模块

#### 1.1机器人结构

| 功能模块 | 硬件支持                                                     |
| -------- | ------------------------------------------------------------ |
| 控制主板 | Raspberry Pi 2 Model B                                       |
| 底盘结构 | Differential Drive (两轮差速)                                |
| 传感器   | [UWB](https://baike.baidu.com/item/UWB/184309?fr=aladdin)，IMU，Camera，radar，Encoder |
| 电源     | 锂电池                                                       |

##### 树莓派

​		树莓派外设接口包括GPIO、PWM、UART、I²C、SPI等。使用这些外设接口。可以方便的与其他传感器通讯。

#### 1.2 硬件及电气特性

| module                 | power interface | data interface       | voltage（V） | **current**（mA） | power(W) | SIZE（mm）  |
| ---------------------- | --------------- | -------------------- | ------------ | ----------------- | -------- | ----------- |
| power                  | DC 2.1mm        | /                    | 12.0         |                   |          |             |
| Raspberry Pi 2 Model B | MicroUSB        | /                    | 5.1          | 350               | 1.75     | 85x56x17    |
| Raspberry Pi 4 Model B | USB Type-C      | /                    | 5.1          | 600               | 3        | 85x56x17    |
| Arduino Mega 2560      | DC 2.1mm        | USB Type B           | 5.0          |                   |          | 53.3x101.52 |
| Motor                  | /               | IO-1                 | 12.0         | ?                 | ?        | ?           |
| TFminiPlus             | GH1.25 4P       | GH1.25 4P            | 5.0          | 110mA             | 0.55     | 35x19x21    |
| LinkTrack P            | USB Type-C      | USB Type C/GH1.25 4P | 5.0          | 270               | 1.35     | 60x29x10    |
|                        |                 |                      |              |                   |          |             |

##### 1.2.1 Raspberry Pi 驱动能力

​	Raspberry Pi 电源建议使用5V 3A 以上电源供电

| **Product**            | 供电                                                         | 裸板耗电(mA) | USB 总功率 |
| ---------------------- | ------------------------------------------------------------ | ------------ | ---------- |
| Raspberry Pi 2 Model B | [2.5A micro USB](https://www.raspberrypi.org/products/raspberry-pi-universal-power-supply/) | 350          | 600mA      |
| Raspberry Pi 4 Model B | [3A USB-C Supply](https://www.raspberrypi.org/products/type-c-power-supply/) | 600          | 1.2A       |
|                        |                                                              |              |            |

​		USB外设建议使用自供电带隔离的USB HUB来连接外设。

##### 1.2.2 单点激光雷达模组

​		八路单点激光，在正常模式下，同时工作瞬时电流可达到1.12A。建议工作在低功耗模式下。

| module        | 平均电流(mA) | 瞬时电流(mA) | 低功耗模式(mA) |
| ------------- | ------------ | ------------ | -------------- |
| TFminiPlus    | 110          | 140          | 20             |
| TFminiPlus x8 | 880          | 1120         | 160            |
|               |              |              |                |

##### 1.2.3 LinkTrack定位惯性导航模块

​		LinkTrack P 供电接口USB Type-C。耗电270mA。Raspberry Pi 4 Model B的USB总功耗1.2A。LinkTrack P可直接由Raspberry Pi 4 供电。

​		LinkTrack P 另一个接口为GH1.25 4P。UART：接口线序简写为“V G R T”，对应VCC、GND、RX、TX（TTL 3.3V 电平），图示中线序从上到下
（从左到右）与接口一一对应；LTS、LTP 存在一个UART 接口，LTSS、LTPS 存在两个电气连接完全一致的UART 接口。

#### 1.3传感器模块

| 功能模块         | 硬件支持                 | 型号          | 详细                     |
| ---------------- | ------------------------ | ------------- | ------------------------ |
| 空间定位         | UWB，IMU（惯性测量单元） | LinkTrack UWB | 集成UWB定位与IMU测量单元 |
| 姿态反馈         | Motor&Encoder，UWB，IMU  |               | 综合计算得出             |
| 行驶方向路况采集 | Camera                   | Howell-Hi3516 | 摄像机                   |
| 四周行车路况采集 | 激光雷达传感器           | TFminiPlus    | 测距雷达                 |
| 车轮驱动系统     | Motor&Encoder            | Mega2560      | 驱动马达和电机编码器     |

#### 1.3.1 空间定位

##### 功能简介

​		空间定位模块用于确定小车在空间中的位置。

​		本项目为室内平面小车。小车行驶在二维[笛卡尔坐标系](https://baike.baidu.com/item/笛卡尔坐标系)中。

##### 定位技术原理

| 测量方法 | 英文全称                  | 中文             |
| -------- | ------------------------- | ---------------- |
| AOA      | Angle of Arriva           | 到达角度定位     |
| TOA      | Time of Arriva            | 到达时间定位     |
| TDOA     | Time Difference of Arriva | 到达时间差分法   |
| TOF      | Time of flight            | 飞行时间测距法   |
| RSS      | Received Signal Strength  | 接收信号强度定位 |
|          |                           |                  |

##### 几种定位比较

| 技术                                                         | 精度          | 优点     | 缺点   | 场景 |
| ------------------------------------------------------------ | ------------- | -------- | ------ | ---- |
| GPS([全球卫星定位系统](https://www.baidu.com/s?wd=全球卫星定位系统&tn=SE_PcZhidaonwhc_ngpagmjz&rsv_dl=gh_pc_zhidao)) | 10米          |          |        |      |
| GNSS(全球导航卫星系度统)                                     | 厘米          |          |        |      |
| 基站定位                                                     | 500米到2000米 |          |        |      |
| 蓝牙                                                         | 3米-5米       |          |        |      |
| WIFI                                                         | 2米           |          |        |      |
| 地磁定位                                                     | 0.1 米到 2 米 |          | 米级   |      |
| RFID                                                         |               |          |        |      |
| UWB                                                          | 1厘米-10厘米  | 实时性好 | 怕干扰 | 工厂 |

##### 传感器

​	LinkTrack P。采用TOF技术 三边定位。

##### ROS



#### 1.3.2姿态反馈

##### 功能简介

​		用于确定导航车的姿态信息。导航车姿态包含俯仰（pitch）、滚转（roll）、偏航（yaw）。欧拉角（姿态角）用以确保导航车处于 正确的行驶方向。

##### 传感器

​		本项目为室内平面小车。没有俯仰（pitch）、滚转（roll）。

​		使用惯性测量单元（IMU）计算出偏航角（yaw）即可。

##### ROS

##### 	

#### 1.3.3行驶方向路况采集

##### 功能简介

​		导航车必须能够识别道路及道路上的路况，在无障碍物的路面上向前行驶，因此在行驶方向上必须能检测到足够远的障碍物。

##### 传感器

​		本项目使用摄像机分析路况。采用空间识别相机识别路面及路面障碍物。摄像机为极坐标原点，小车前进方向为极轴，障碍物坐标为极坐标（ρ，θ）；也可以绘制出障碍物的3D点云。

#### 1.3.4四周行车路况采集

##### 功能简介

​		导航车行驶过程中需要与左右车辆或障碍物保持一定的安全距离。

##### 传感器

​		TFminiPlus激光雷达传感器。量程 0.1-12m，只有10cm的盲区。支持UART 、IC接口。可以通过IIC与树莓派连接。

#### 1.3.5车轮驱动系统

功能简介

​		驱动导航车运动，同时反馈导航车的运动状态（即，速度矢量、行驶里程）。

传感器

​		[Mega2560](https://baike.baidu.com/item/Mega2560/973064?fr=aladdin)驱动板，测速编码器。

模块

​		本项目使用[Mega2560](https://baike.baidu.com/item/Mega2560/973064?fr=aladdin)驱动两轮差速车运动。并结合小车轴距、轮胎大小动态计算小车位姿。



### 2. 软件模块

| 功能模块     | 库          | 软件包                                                       |
| ------------ | ----------- | ------------------------------------------------------------ |
| 位置姿态控制 |             | /                                                            |
| 视觉图像分析 |             | /                                                            |
| 运动控制     | ROS Package | [ros_arduino_bridge](https://wiki.ros.org/ros_arduino_bridge) |
| 雷达测距     |             | /                                                            |
| 构建地图     | ROS Package | [map_server](http://wiki.ros.org/action/fullsearch/map_server?action=fullsearch&context=180&value=linkto%3A"map_server") |
| 路径规划     | ROS Package | [move_base](http://wiki.ros.org/action/fullsearch/move_base?action=fullsearch&context=180&value=linkto%3A"move_base") |

#### 2.1位置姿态控制

​		导航车感知自身位姿，确保行车安全。能够根据目标线路迅速调整偏航角。协助完成路径规划。

##### ROS

对应的数据类型为 [geometry_msgs/Pose](http://docs.ros.org/api/geometry_msgs/html/msg/Pose.html) pose。三维坐标位置 Pose(x,y,z)、方向四元数Quaternion（x,y,z,w）。



#### 2.2视觉图像分析

​		图像分析识别路面及路面障碍物。确定障碍物的相对位置（比如，极坐标系下的角度θ和距离ρ），同时在地图上动态构建障碍物。协助完成本地实时路径规划。

#### 2.3运动控制

​		控制小车按照给定的速度矢量运动，同时反馈当前的速度矢量。协助完成运动规划。

##### ROS

​		[ros_arduino_bridge](https://wiki.ros.org/ros_arduino_bridge)这个堆栈包括一个ROS驱动程序和arduino兼容的微控制器的基本控制器。可以获得里程计数据

```
This stack includes a ROS driver and base controller for Arduino-compatible microcontrollers. The driver provides access to analog and digital sensors, PWM servos, and odometry data from encoders. It is meant to be a complete solution for running an Arduino-controlled robot under ROS.
```

#### 2.4雷达测距

​		确定近距离内的障碍物。同时在地图上动态构建障碍物。协助完成本地实时路径规划。

#### 2.5构建地图

​		本项目是平面小车。地图为二维笛卡尔坐标系下的室内平面地图。

##### 坐标系

​		参考静态地图构建的坐标系。

##### 定位

​		开机后，小车利用三点定位、罗盘确定自己在空间中的位置姿态。

##### 2.5.1静态地图

​		室内静态地图是指墙体、桌椅、静止驶入区域等。

​		静态地图获取方式主要是测绘。

| 地图类型           | 地图坐标系                                                   | 来源     |
| ------------------ | ------------------------------------------------------------ | -------- |
| 室内或厂区平面地图 | 二维[笛卡尔坐标系](https://zh.wikipedia.org/wiki/笛卡尔坐标系) | 自行测绘 |

##### 2.5.2动态地图

​		行驶过程中利用传感器动态发现近距离障碍物。并将障碍物添加到地图中，用于本地实时路径规划。

​		传感器主要有视觉传感器。雷达测距传感器等。

​		障碍物可以是的路中央的花坛，两边的围栏、隧道墙体等，也可以是临时放置的水马围挡等路障，或者是正在行驶的车辆、路边行走和过马路的行人。

#### 2.6路径规划

##### ROS

​		使用ROS栈[navigation](http://wiki.ros.org/action/fullsearch/navigation?action=fullsearch&context=180&value=linkto%3A"navigation") stack中的节点the [move_base](http://wiki.ros.org/action/fullsearch/move_base?action=fullsearch&context=180&value=linkto%3A"move_base") ROS Node。完成路径规划。

##### 2.6.1全局路径规划（global planner）

​		根据给定的目标位置进行总体路径的规划。

​		 在ROS的导航中，首先会通过全局路径规划，计算出机器人到目标位置的全局路线。这一功能是navfn这个包实现的。

​		[navfn](https://wiki.ros.org/action/fullsearch/navfn?action=fullsearch&context=180&value=linkto%3A"navfn")通过Dijkstra最优路径的算法，计算costmap上的最小花费路径，作为机器人的全局路线。

##### 2.6.2本地实时规划（local planner）

​		根据附近的障碍物进行躲避路线规划。

​		本地的实时规划是利用base_local_planner包实现的。该包使用Trajectory Rollout 和Dynamic Window approaches算法计算机器人每个周期内应该行驶的速度和角度（dx，dy，dtheta velocities）。

​		base_local_planner这个包通过地图数据，通过算法搜索到达目标的多条路经，利用一些评价标准（是否会撞击障碍物，所需要的时间等等）选取最优的路径，并且计算所需要的实时速度和角度。
其中，Trajectory Rollout 和Dynamic Window approaches算法的主要思路如下：

1. 采样机器人当前的状态（dx,dy,dtheta）；
2.  针对每个采样的速度，计算机器人以该速度行驶一段时间后的状态，得出一条行驶的路线。
3. 利用一些评价标准为多条路线打分。
4.  根据打分，选择最优路径。
5.  重复上面过程。
