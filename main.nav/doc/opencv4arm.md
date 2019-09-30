# Opencv 移植需求

[TOC]

## 一、移植平台

### 软件

| 移植条件      | 详细                                     |
| ------------- | ---------------------------------------- |
| Opencv 版本   | OpenCV – 2.4.13.6                        |
| Linux操作系统 | Built with PetaLinux v2014.4 (Yocto 1.7) |
|               |                                          |

### 硬件

| 移植硬件 |           |
| -------- | --------- |
| CPU      | ZYNQ 7100 |

## 二、移植模块

| Opencv模块     | 模块说明                                          | 移植 |
| -------------- | ------------------------------------------------- | ---- |
| **core**       | THE CORE FUNCTIONALITY                            | Y    |
| **imgproc**    | IMAGE PROCESSING                                  | Y    |
| **highgui**    | HIGH-LEVEL GUI AND MEDIA I/O                      | Y    |
| **video**      | VIDEO ANALYSIS                                    | Y    |
| **calib3d**    | CAMERA CALIBRATION AND 3D RECONSTRUCTION          | Y    |
| **features2d** | 2D FEATURES FRAMEWORK                             | Y    |
| **objdetect**  | OBJECT DETECTION                                  | Y    |
| **ml**         | MACHINE LEARNING                                  | Y    |
| **flann**      | CLUSTERING AND SEARCH IN MULTI-DIMENSIONAL SPACES | Y    |
| **gpu**        | GPU-ACCELERATED COMPUTER VISION                   | Y    |
| **photo**      | COMPUTATIONAL PHOTOGRAPHY                         | Y    |
| **stitching**  | IMAGES STITCHING                                  | Y    |
| **nonfree**    | NON-FREE FUNCTIONALITY                            | Y    |
| **contrib**    | CONTRIBUTED/EXPERIMENTAL STUFF                    | Y    |
| **legacy**     | DEPRECATED STUFF                                  | Y    |
| **ocl**        | OPENCL-ACCELERATED COMPUTER VISION                | Y    |
| **superres**   | SUPER RESOLUTION                                  | Y    |
| **viz**        | 3D VISUALIZER                                     | Y    |

## 三、交付代码

- 提供移植源代码；
- 提供使用教程文档；
- 移植完成后，附上必要的演示代码；