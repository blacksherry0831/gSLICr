# 机器人开发平台硬件清单

[TOC]

## 一、安卓APP开发平台硬件清单

### 1.1、安卓开发环境

| 物品     | 品牌        | 型号      | 单价      | 数量 |
| -------- | ----------- | --------- | --------- | ---- |
| 平板电脑 | Xiaomi/小米 | 小米平板4 | ￥1399.00 | 0    |
| 充电器   |             |           |           | 0    |
| 数据线   |             |           |           | 0    |
|          |             |           |           |      |

### 1.2、安卓ROS主机开发环境

配置环境完整清单如下：

| 物品          | 品牌      | 型号       | 单价     | 数量 |
| ------------- | --------- | ---------- | -------- | ---- |
| 插排          | 公牛      |            |          | 1    |
| 显示器        |           |            |          | 1    |
| 鼠键          |           |            |          | 1    |
| 网线          |           |            |          | 1    |
| 工控机        |           |            |          | 1    |
| 12.6V电源     |           |            |          | 1    |
| 激光雷达      | SLAMTEC   | RPLIDAR A1 | ¥582.00  | 1    |
| GNSS接收器    | beitian   | BD-8953D   | ¥298.00  | 1    |
| 摄像头        |           |            |          | 1    |
| ROS机器人小车 | Autolabor | 2.5        | ¥3950.00 | 1    |
| /             | /         | /          | /        | /    |

### 1.3 ROS 节点说明

| 机器人参数 | 值                                  |      |
| ---------- | ----------------------------------- | ---- |
| ros master | http://192.168.50.12:11311          |      |
| cmd_vel    | /cmd_vel                            |      |
| 激光       | /scan                               |      |
| 地图       | /map                                |      |
| 摄像头     | /rtsp_camera_relay/image/compressed |      |
| GPS        | /fix                                |      |
| 里程计     | /odom                               |      |
| 姿态       | /robot_pose                         |      |
| 导航       | /move_base/goal                     |      |
| /          | /                                   |      |

```shell
iagumilukarin@user-laptop:~$ rosnode list
/arduino
/base_frame_laser
/move_base
/nmea_serial_driver_node
/robot_pose_publisher
/rosapi
/rosbridge_udp
/rosbridge_websocket
/rosout
/rplidarNode
/rtsp_camera_relay
/slam_gmapping
iagumilukarin@user-laptop:~$ rostopic list 
/arduino/parameter_descriptions
/arduino/parameter_updates
/arduino/sensor_state
/cmd_vel
/diagnostics
/fix
/map
/map_metadata
/move_base/DWAPlannerROS/cost_cloud
/move_base/DWAPlannerROS/global_plan
/move_base/DWAPlannerROS/local_plan
/move_base/DWAPlannerROS/parameter_descriptions
/move_base/DWAPlannerROS/parameter_updates
/move_base/DWAPlannerROS/trajectory_cloud
/move_base/GlobalPlanner/parameter_descriptions
/move_base/GlobalPlanner/parameter_updates
/move_base/GlobalPlanner/potential
/move_base/NavfnROS/plan
/move_base/cancel
/move_base/current_goal
/move_base/feedback
/move_base/global_costmap/costmap
/move_base/global_costmap/costmap_updates
/move_base/global_costmap/footprint
/move_base/global_costmap/inflation_layer/parameter_descriptions
/move_base/global_costmap/inflation_layer/parameter_updates
/move_base/global_costmap/obstacle_layer/parameter_descriptions
/move_base/global_costmap/obstacle_layer/parameter_updates
/move_base/global_costmap/parameter_descriptions
/move_base/global_costmap/parameter_updates
/move_base/global_costmap/static_layer/parameter_descriptions
/move_base/global_costmap/static_layer/parameter_updates
/move_base/goal
/move_base/local_costmap/costmap
/move_base/local_costmap/costmap_updates
/move_base/local_costmap/footprint
/move_base/local_costmap/inflation_layer/parameter_descriptions
/move_base/local_costmap/inflation_layer/parameter_updates
/move_base/local_costmap/obstacle_layer/parameter_descriptions
/move_base/local_costmap/obstacle_layer/parameter_updates
/move_base/local_costmap/parameter_descriptions
/move_base/local_costmap/parameter_updates
/move_base/parameter_descriptions
/move_base/parameter_updates
/move_base/result
/move_base/status
/move_base_simple/goal
/odom
/robot_pose
/rosout
/rosout_agg
/rtsp_camera_relay/camera_info
/rtsp_camera_relay/image
/rtsp_camera_relay/image/compressed
/rtsp_camera_relay/image/compressed/parameter_descriptions
/rtsp_camera_relay/image/compressed/parameter_updates
/rtsp_camera_relay/image/compressedDepth
/rtsp_camera_relay/image/compressedDepth/parameter_descriptions
/rtsp_camera_relay/image/compressedDepth/parameter_updates
/rtsp_camera_relay/image/theora
/rtsp_camera_relay/image/theora/parameter_descriptions
/rtsp_camera_relay/image/theora/parameter_updates
/rtsp_camera_relay/status
/scan
/slam_gmapping/entropy
/tf
/tf_static
/time_reference
/vel
```



### 1.4 操作说明

1. 开机
2. 登录账户IaGumiLukaRin。  用户名：IaGumiLukaRin ，密码 Cui@14310531
3. 在命令行su切换到root账户 。用户名：root,密码root。
4. 执行脚本。 bash  /usr/local/autolabor.x86/config/up.sh 

### 1.5物品签收

| 项目                     | 确认签字 |
| ------------------------ | -------- |
| 以上物品类型和数量以配齐 |          |
| 签收人                   |          |
| 签收日期                 |          |
| 参与交接人员             |          |

