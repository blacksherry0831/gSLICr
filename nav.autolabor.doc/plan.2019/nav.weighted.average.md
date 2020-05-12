# 导航算法

## 图像加权平均计算路径规划

### 1.导航车静止时采集图像用作路径规划；

### 2.在静止状态下采集连续九张图像；

### 3.每一张图像,输出一个运动方向,总共八个方向

$$
DIR∈\{\\DOWN,\\DOWN.LEFT,\\DOWN.RIGHT,\\RIGHT,\\LEFT,\\UP.RIGHT,\\UP.LEFT,\\UP,\\\}
$$

#### N个图像判定的N个运行方向(按时间排序):

$$
D=
\begin{bmatrix}
D_{0}\\
D_{1}\\
D_{2}\\
...\\
D_{N}
\end{bmatrix}
\qquad
其中N=8
$$

#### 对每一个运行方向加权：

$$
W=
\begin{bmatrix}
0.1&
0.2&
0.3&
...&
0.9
\end{bmatrix}
$$

#### 加权后的结果：					

$$
DW=D*W=

\begin{bmatrix}

0.1D_{0}&
0.2D_{1}&
0.3D_{2}&
...&
0.9D_{N}

\end{bmatrix}
$$

### 4.统计九张图八个方向的权重

$$
Run(DIR) = \sum_{n=0}^N{
\begin{cases}
W(n) &if(D(n)=DIR)\cr 
0 &if(D(n)\not=DIR) \cr 
\end{cases}}
$$

### 5.以八个方向中最大的那个作为最终运动方向

$$
RunDir=MAX(\\
Run(DOWN),\\
Run(DOWN.LEFT),\\
Run(DOWN.RIGHT),\\
Run(RIGHT),\\
Run(LEFT),\\
Run(UP),\\
Run(UR.RIGHT),\\
Run(UP.LEFT)\\
)
$$

