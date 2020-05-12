# ROS [navigation](http://wiki.ros.org/action/fullsearch/navigation?context=180&value=linkto%3A"navigation")

​		使用ROS栈[navigation](http://wiki.ros.org/action/fullsearch/navigation?action=fullsearch&context=180&value=linkto%3A"navigation") stack中的节点the [move_base](http://wiki.ros.org/action/fullsearch/move_base?action=fullsearch&context=180&value=linkto%3A"move_base") ROS Node。完成路径规划。

​		[navigation](http://wiki.ros.org/action/fullsearch/navigation?action=fullsearch&context=180&value=linkto%3A"navigation") stack包括以下节点。

​		**navigation**: [amcl](http://wiki.ros.org/amcl?distro=kinetic) | [base_local_planner](http://wiki.ros.org/base_local_planner?distro=kinetic) | [carrot_planner](http://wiki.ros.org/carrot_planner?distro=kinetic) | [clear_costmap_recovery](http://wiki.ros.org/clear_costmap_recovery?distro=kinetic) | [costmap_2d](http://wiki.ros.org/costmap_2d?distro=kinetic) | [dwa_local_planner](http://wiki.ros.org/dwa_local_planner?distro=kinetic) | [fake_localization](http://wiki.ros.org/fake_localization?distro=kinetic) | [global_planner](http://wiki.ros.org/global_planner?distro=kinetic) | [map_server](http://wiki.ros.org/map_server?distro=kinetic) | [move_base](http://wiki.ros.org/move_base?distro=kinetic) | [move_base_msgs](http://wiki.ros.org/move_base_msgs?distro=kinetic) | [move_slow_and_clear](http://wiki.ros.org/move_slow_and_clear?distro=kinetic) | [nav_core](http://wiki.ros.org/nav_core?distro=kinetic) | [navfn](http://wiki.ros.org/navfn?distro=kinetic) | [robot_pose_ekf](http://wiki.ros.org/robot_pose_ekf?distro=kinetic) | [rotate_recovery](http://wiki.ros.org/rotate_recovery?distro=kinetic) | [voxel_grid](http://wiki.ros.org/voxel_grid?distro=kinetic)

![](..\ROS.Libraries\overview_tf.png)

## Package Summary

​		**A 2D navigation stack** that takes in information from odometry, sensor streams, and a goal pose and outputs safe velocity commands that are sent to a mobile base.

| key                                                          | 解释                             |
| ------------------------------------------------------------ | -------------------------------- |
| **2D navigation stack**                                      | 这是一个**2D**导航栈             |
| information from **odometry**, sensor streams, and a goal **pose** | 里程计、传感器流、目标位姿的信息 |
| outputs safe **velocity commands**                           | 输出速度命令                     |

一种二维导航堆栈，它接收来自里程计、传感器流和目标位姿的信息，并输出发送到移动基地的安全速度命令。

## Overview

The Navigation Stack is fairly simple on a conceptual level. It takes in information from odometry and sensor streams and outputs velocity commands to send to a mobile base. Use of the Navigation Stack on an arbitrary robot, however, is a bit more complicated. As a pre-requisite for navigation stack use, the robot must be running ROS, have a [tf](http://wiki.ros.org/tf) transform tree in place, and publish sensor data using the correct ROS [Message types](http://wiki.ros.org/msg). Also, the Navigation Stack needs to be configured for the shape and dynamics of a robot to perform at a high level. To help with this process, this manual is meant to serve as a guide to typical Navigation Stack set-up and configuration.

| key                                                         | 解释           |
| ----------------------------------------------------------- | -------------- |
| the robot must be running ROS,                              | 必须运行ROS    |
| have a [tf](http://wiki.ros.org/tf) transform tree in place | 准备好tf转换树 |
|                                                             |                |

## Hardware Requirements

While the Navigation Stack is designed to be as general purpose as possible, there are three main hardware requirements that restrict its use:

1. It is meant for both differential drive and holonomic wheeled robots only. It assumes that the mobile base is controlled by sending desired velocity commands to achieve in the form of: x velocity, y velocity, theta velocity.
2. It requires a planar laser mounted somewhere on the mobile base. This laser is used for **map building** and **localization**.
3. The Navigation Stack was developed on a square robot, so its performance will be best on robots that are nearly square or circular. It does work on robots of arbitrary shapes and sizes, but it may have difficulty with large rectangular robots in narrow spaces like doorways.

| hardware requirement                                 |                                            |
| ---------------------------------------------------- | ------------------------------------------ |
| differential drive and holonomic wheeled robots only | 只适用于差速器驱动和完整轮式机器人         |
| a planar lase                                        | 平面激光器。这种激光用于地图的建立和定位。 |
| a square robot                                       | 方形或圆形的机器人上性能最好               |

## Documentation

The following documentation assumes familiarity with the Robot Operating System. Documentation on ROS can be found here: [ROS Documentation](http://wiki.ros.org/ROS)

- [Navigation Stack Setup](http://wiki.ros.org/navigation/Tutorials/RobotSetup)
  - [Publishing Sensor Streams](http://wiki.ros.org/navigation/Tutorials/RobotSetup/Sensors)
  - [Publishing Odometry Information](http://wiki.ros.org/navigation/Tutorials/RobotSetup/Odom)
  - [Transform Configuration](http://wiki.ros.org/navigation/Tutorials/RobotSetup/TF)
- [Building a Map](http://wiki.ros.org/navigation/MapBuilding)

| key                                                          | 教程                               |      |
| ------------------------------------------------------------ | ---------------------------------- | ---- |
| [Publishing Sensor Streams](http://wiki.ros.org/navigation/Tutorials/RobotSetup/Sensors) | The LaserScan / PointCloud Message |      |
| [Publishing Odometry Information](http://wiki.ros.org/navigation/Tutorials/RobotSetup/Odom) | 发布里程计                         |      |
| [Transform Configuration](http://wiki.ros.org/navigation/Tutorials/RobotSetup/TF) | tf转换树                           |      |

## 构建静态地图

​		测绘，绘制出室内平面地图。并转换成pgm。

​		ROS gmapping地图格式为pgm，另外有一个配套的yaml文件。GM 是便携式灰度图像格式(portable graymap file format)。

```xml
 1<!--
 2  Copyright: 2016-2019 ROS小课堂 www.corvin.cn
 3  Author: corvin
 4  Description: 该启动文件用于加载自定义的home地图,这样就可以进行自动导航了.
 5  History:
 6    20190102: initial this file.
 7-->
 8<launch>
 9  <!-- load home map -->
10  <node pkg="map_server" type="map_server" name="stdr_load_home_map" args="$(find stdr_navigation)/maps/home.yaml">
11    <remap from="map" to="/amcl/map" />
12  </node>
13</launch>
```

```xml
 1<!--
 2  Copyright: 2016-2019 ROS小课堂 www.corvin.cn
 3  Author: corvin
 4  Description:
 5    STDR simulator robot auto navigation with amcl and move base packages.
 6    load home_map to test.
 7  History:
 8    20190102: 加载home_map地图进行自动导航测试.
 9-->
10<launch>
11  <!-- load stdr simulator with robot0 -->
12  <include file="$(find stdr_launchers)/launch/home_map_robot_gui.launch" />
13
14  <!-- startup move_base node -->
15  <include file="$(find stdr_move_base)/launch/stdr_move_base.launch" />
16
17  <!-- load home map -->
18  <include file="$(find stdr_navigation)/launch/load_home_map.launch" />
19
20  <!-- startup amcl node -->
21  <include file="$(find stdr_amcl)/launch/home_map_amcl.launch" />
22</launch>
```

## 组件

| 组件                                                      | 详解                                                         |
| --------------------------------------------------------- | ------------------------------------------------------------ |
| [amcl](https://wiki.ros.org/amcl?distro=kinetic)          | 一种机器人在2D中移动的概率定位系统。 它实现了自适应（或KLD采样）蒙特卡罗定位方法（如Dieter Fox所述），该方法使用粒子滤波器来针对已知地图跟踪机器人的位姿。 |
| **base_local_planner**                                    | 这个包提供了Trajectory Rollout以及Dynamic Window两种在2D平面局部导航的方法。通过提供一个跟随的规划路径和一个代价地图，控制器生成速度指令并发送至机器人。它支持全向和非全向机器人，以及任何可以用多边形或圆描述的机器人轮廓，并且可以在launch文件中设置这些参数。这个包已经被封装好，可以通过nav_core包的BaseLocolPlanner接口来调用。 |
| **carrot_planner**                                        | 这个规划器是一个简单的全局规划器，可以通过nav_core::BaseGlobalPlanner 来进行调用，并且被move_base节点用作一个全局规划的插件。这个规划器从用户处采集到一个目标点，之后检查用户指定的目标点是否是障碍物，如果是的话沿着robot与目标点构成的向量向后退，直到找到一点没有障碍物位置。之后它会将此目标点作为目标发送给局部规划器和控制器。这个规划器允许机器人尽可能到达离用户指定的目标点最近的位置。 |
| **clear_costmap_recovery**                                | 为导航包提供了一种自救行为，试图通过将代价地图还原成已知区域外的静态地图从而清除出空间。 |
| costmap                                                   | 用于描述环境中的障碍物信息，代价地图利用激光雷达、声呐、红外测距等探测传感器的数据来生成，大致的原理是通过建立不同的图层Layer然后叠在一起。 |
| **costmap_2d**                                            | 通过激光或点云的数据，投影到2D平面上，创建代价地图，并可以设置膨胀半径。 |
| **dwa_local_planner**                                     | 局部规划器，提供动态窗口方法（ Dynamic Window Approach）在平面上局部导航。与base_local_planner类似。 |
| **fake_localization**                                     | 提供了一个简单节点fake_localization node，可以代替一个定位系统，并提供了acml包的ROS API的子集。由于较低的计算量，这个节点非常频繁的用于在仿真环境中提供完美的定位。这个节点将里程计数据转换为位置、粒子云，并以acml发布的数据格式发布。 |
| map_server                                                | 地图服务器，主要功能是保存地图和导入地图                     |
| [move_base](http://wiki.ros.org/move_base?distro=kinetic) | 根据参照的消息进行路径规划，使移动机器人到达指定的位置       |
| **navfn**                                                 | 全局规划器，提供了一个快速插值的函数，可以在起始点到目标点之间快速插值，并找到代价最小的一条路径。 |
| [rotate_recovery](http://wiki.ros.org/rotate_recovery)    | 该包给导航功能包提供了修复机制，它尝试让机器人执行360度旋转来完成清理导航功能包里的地图空间。 |
| robot_pose_ekf                                            | 扩展卡尔曼滤波器，输入是里程计、IMU、VO中的任意两个或者三个，输出是一个融合之后的pose。 |

## 参考资料

[1]. ros wiki. Running STDR Simulator.

[http://wiki.ros.org/stdr_simulator/Tutorials/Running%20STDR%20Simulator](https://www.corvin.cn/go?url=http://wiki.ros.org/stdr_simulator/Tutorials/Running STDR Simulator)

[2]. ros wiki. How to load a map.

[http://wiki.ros.org/stdr_simulator/Tutorials/How%20to%20load%20a%20map](https://www.corvin.cn/go?url=http://wiki.ros.org/stdr_simulator/Tutorials/How to load a map)

[3]. ros wiki. map_server的介绍. [http://wiki.ros.org/map_server](https://www.corvin.cn/go?url=http://wiki.ros.org/map_server)

[4]. 天涯0508. ROS开发笔记（6）—利用 gmapping 构建环境地图（map）.

[https://blog.csdn.net/wsc820508/article/details/81556620](https://www.corvin.cn/go?url=https://blog.csdn.net/wsc820508/article/details/81556620)

[4]. [ROS自定义地图] https://www.pianshen.com/article/8670270577/