# CLUSTER

## 一、重算聚类中心Seed

### 1.超像素中心属性

| 超像素中心 |         | 超像素中心     |
| ---------- | ------- | -------------- |
| center     | (x,y)   | 在图像中的坐标 |
| color_info | (l,a,b) | 颜色           |
| id         | labels  | 超像素唯一标识 |
| no_pixels  |         | 超像素个数     |

```C++
struct spixel_info
		{
			Vector2f center;
			Vector4f color_info;
			int id;
			int no_pixels;
		};
```

## 二、连接矩阵E

### 1.并行计算

1. 按照Pixel并行；
2. 搜索Pixel周围9个像素点的labels;
3. 若找到与 中心点idx不同的labels，则认为两个超像素是相邻的；

## 三、相似度矩阵W

### 1.算法计算

1. 按照相邻关系计算两个超像素的相似度
2. 相似度必须大于一定阈值

### 2.计算公式

#### 2.1 CIE L*a*b↔ LθM

$$
θ= \frac{ atan2(B,A)}{(2 * PI)}+0.5
$$

$$
m=  \frac{ \sqrt{ A^2+B^2 }  }{ 128* \sqrt{2} }
$$

$$
l=\frac{L}{100}
$$

```C++
inline void ImageColorSpaceThetaML::ColorSpaceLab2ThetaML(
	const double L,
	const double A,
	const double B,
	double & _theta,
	double & _m,
	double & _l)
{
	const float LAB_M_MAX = 128 * 1.4142135623731;
	const float X2_PI = 2 * CV_PI;
	///////////////////////////////////////
	if (A == B && B == 0) {
		_theta = 0;
	}
	else
	{
		_theta = atan2(B, A);//(-pi,pi]
		_theta = _theta / X2_PI + 0.5F;
	}
	///////////////////////////////////////
	_m = sqrt(A*A + B*B);
	_m = _m / (LAB_M_MAX);
	///////////////////////////////////////
	_l = L / 100;
	///////////////////////////////////////
}
```

#### 2.2 相似度

##### 2.2.1 BHATTACHARYYA

$$
BC(p,q)=\sum_{i=1}^n {\sqrt{p_{i}q_{i}}}
$$

$$
W(p,q)=\sqrt{1-\frac{1}{\sqrt{\overline{p}\overline{q}N^2}}\sum_{i=1}^n {\sqrt{p_{i}q_{i}}}}
$$





## 四.聚类

1. 利用相似度矩阵W生成聚类关系图；
2. 完成聚类；