# RaspberryPi2b  Upgrade to 4b

[TOC]

## 项目需求

​		将Autolabor2.5开源机器人。硬件升级到[Raspberry Pi 4 Model B](https://www.raspberrypi.org/products/raspberry-pi-4-model-b/)。操作系统升级到Ubuntu 20.04 LTS。ROS升级到[ROS Noetic Ninjemys](http://wiki.ros.org/noetic/Installation)。

并实现激光SLAM功能和内置WEB服务器。

## 一、机器人

​		我是使用的是Autolabor2.5。详细说明参考http://www.autolabor.com.cn/pro/detail/1。

​		Autolabor2.5 是一款基于ROS的开源机器人。内置功能为激光SLAM构图导航。主控系统采用[RaspberryPi](https://www.raspberrypi.org/)。操作系统采用ubuntu。	

### 1.1雷达

​		激光雷达采用思岚科技的[RPLIDAR A1](http://www.slamtec.com/cn/Lidar/A1)。资料下载地址http://www.slamtec.com/cn/Support#rplidar-a-series。官方已经集成ROS程序包。

## 二、原版镜像

### 2.1镜像文件

​		参考此链接下载Autolabor2.5操作系统镜像 http://www.autolabor.com.cn/download。

​		我们使用的是雷达版。镜像文件为Autolabor OS SD卡镜像(雷达版)【[磁力链接](magnet:?xt=urn:btih:A7E6C8B0AE6255ECB76BB63A8B0C204E9E327513&dn=autolaborOS20180117.zip&tr=udp%3a%2f%2f172.104.100.32%3a9090&tr=udp%3a%2f%2f192.144.142.81%3a9090&tr=udp%3a%2f%2ftracker.coppersurfer.tk%3a6969%2fannounce&tr=udp%3a%2f%2ftracker.open-internet.nl%3a6969%2fannounce&tr=udp%3a%2f%2ftracker.skyts.net%3a6969%2fannounce&tr=udp%3a%2f%2ftracker.piratepublic.com%3a1337%2fannounce&tr=udp%3a%2f%2ftracker.opentrackr.org%3a1337%2fannounce&tr=udp%3a%2f%2f9.rarbg.to%3a2710%2fannounce&tr=udp%3a%2f%2fpublic.popcorn-tracker.org%3a6969%2fannounce&tr=udp%3a%2f%2fwambo.club%3a1337%2fannounce&tr=udp%3a%2f%2ftracker4.itzmx.com%3a2710%2fannounce&tr=udp%3a%2f%2ftracker1.wasabii.com.tw%3a6969%2fannounce&tr=udp%3a%2f%2ftracker.zer0day.to%3a1337%2fannounce&tr=udp%3a%2f%2ftracker.xku.tv%3a6969%2fannounce&tr=udp%3a%2f%2ftracker.vanitycore.co%3a6969%2fannounce&tr=udp%3a%2f%2fipv4.tracker.harry.lu%3a80%2fannounce&tr=udp%3a%2f%2finferno.demonoid.pw%3a3418%2fannounce&tr=udp%3a%2f%2fopen.facedatabg.net%3a6969%2fannounce&tr=udp%3a%2f%2fmgtracker.org%3a6969%2fannounce&tr=udp%3a%2f%2ftracker.mg64.net%3a6969%2fannounce&tr=udp%3a%2f%2fthetracker.org%3a80%2fannounce&tr=udp%3a%2f%2ftracker.tiny-vps.com%3a6969%2fannounce&tr=udp%3a%2f%2fp4p.arenabg.com%3a1337%2fannounce&tr=udp%3a%2f%2fopen.stealth.si%3a80%2fannounce&tr=udp%3a%2f%2fexplodie.org%3a6969%2fannounce&tr=udp%3a%2f%2fbt.xxx-tracker.com%3a2710%2fannounce&tr=udp%3a%2f%2ftracker.internetwarriors.net%3a1337%2fannounce&tr=udp%3a%2f%2ftracker.grepler.com%3a6969%2fannounce&tr=udp%3a%2f%2ftracker.files.fm%3a6969%2fannounce&tr=udp%3a%2f%2ftracker.dler.org%3a6969%2fannounce&tr=udp%3a%2f%2ftracker.desu.sh%3a6969%2fannounce&tr=udp%3a%2f%2ftracker.cypherpunks.ru%3a6969%2fannounce&tr=http%3a%2f%2ftracker.city9x.com%3a2710%2fannounce&tr=http%3a%2f%2fretracker.mgts.by%3a80%2fannounce&tr=udp%3a%2f%2ft.agx.co%3a61655%2fannounce&tr=udp%3a%2f%2fsd-95.allfon.net%3a2710%2fannounce&tr=udp%3a%2f%2fsantost12.xyz%3a6969%2fannounce&tr=udp%3a%2f%2fsandrotracker.biz%3a1337%2fannounce&tr=udp%3a%2f%2fretracker.nts.)】 【[下载](http://192.144.142.81/autolaborOS20180117.zip)】适用产品：Autolabor2.X（雷达+树莓派）。

​		原版操作系统镜像基于Ubuntu16.04。ROS版本为 Kinetic。此镜像已实现激光SLAM（同步定位构图导航）。

### 2.2源代码

​		激光SLAM构图导航及内置WEB服务器源代码均已包含在镜像中 。源代码位于home目录之下适用于Autolabor2.5的catkin工程。启动脚本在~/firmware/autolabor2.5/目录下。

## 三、参考链接

| item                                             | link                                               |                                                              |
| ------------------------------------------------ | -------------------------------------------------- | ------------------------------------------------------------ |
| ubuntu                                           | https://ubuntu.com/download/raspberry-pi           |                                                              |
| ROS                                              | https://www.ros.org/                               | The Robot Operating System (ROS) is a flexible framework for writing robot software |
| [Wiring Pi](http://wiringpi.com/)                | http://wiringpi.com/                               | GPIO Interface library for the Raspberry Pi                  |
| autolabor 机器人                                 | http://www.autolabor.com.cn/                       |                                                              |
| [RPLIDAR A1](http://www.slamtec.com/cn/Lidar/A1) | http://www.slamtec.com/cn/Support#rplidar-a-series |                                                              |
|                                                  |                                                    |                                                              |

## 四、软硬件升级清单

​		需要对原版Ubuntu操作系统、ROS系统以及WEB服务器等进行升级。升级后的软硬件系统必须实现原版的全部功能。

### 4.1 硬件及系统

| item     | old                                                          | new                                                          | confirm |
| -------- | ------------------------------------------------------------ | ------------------------------------------------------------ | ------- |
| hardware | [Raspberry Pi 2 Model B](https://www.raspberrypi.org/products/raspberry-pi-2-model-b/) | [Raspberry Pi 4 Model B](https://www.raspberrypi.org/products/raspberry-pi-4-model-b/) | Y       |
| os       | Ubuntu 16.04 LTS                                             | Ubuntu 20.04 LTS                                             | Y       |

### 4.2 软件库

| item                              | old                                                          | new                                                          | confirm |
| --------------------------------- | ------------------------------------------------------------ | ------------------------------------------------------------ | ------- |
| ros                               | [ROS Kinetic Kame](http://wiki.ros.org/kinetic/Installation) | [ROS Noetic Ninjemys](http://wiki.ros.org/noetic/Installation) | Y       |
| java                              | 不限版本，能用就行                                           | 不限版本，能用就行                                           | Y       |
| python                            | 不限版本，能用就行                                           | 不限版本，能用就行                                           | Y       |
| CMAKE                             | ROS能够使用catkin_make                                       | ROS能够使用catkin_make                                       | Y       |
| opencv                            | ROS能够使用[cv_bridge](http://wiki.ros.org/action/fullsearch/cv_bridge?action=fullsearch&context=180&value=linkto%3A"cv_bridge")工具集 | ROS能够使用[cv_bridge](http://wiki.ros.org/action/fullsearch/cv_bridge?action=fullsearch&context=180&value=linkto%3A"cv_bridge")工具集 | Y       |
| qt                                | ROS能够使用rqt-*工具                                         | ROS能够使用rqt-*工具                                         |         |
| [Wiring Pi](http://wiringpi.com/) | 能够使用Raspberry Pi的GPIO，IIC，UART...                     | 能够使用Raspberry Pi的GPIO，IIC，UART...                     | Y       |

### 4.3 功能

| item | old                     | new                     | confirm |
| ---- | ----------------------- | ----------------------- | ------- |
| SLAM | 激光SLAM构图导航        | 激光SLAM构图导航        | Y       |
| WEB  | WEB服务器               | WEB服务器               | Y       |
| UART | 40P-插针的UART(TTL)功能 | 40P-插针的UART(TTL)功能 | Y       |
| IIC  | 40P-插针的IIC功能       | 40P-插针的IIC功能       | Y       |
|      |                         |                         |         |

# 五、物品清单

| 物品                               | 数量 | confirm |
| ---------------------------------- | ---- | ------- |
| Raspberry Pi 4B 主板               | 1    | Y       |
| Micro HDMI 线                      | 1    | Y       |
| 电源适配器 5V 3A Type-C带开关      | 1    | Y       |
| 闪迪（SanDisk）16GB TF（MicroSD）  | 1    | Y       |
| Raspberry Pi 4B 主板+风扇+塑料外壳 | 1    | Y       |

