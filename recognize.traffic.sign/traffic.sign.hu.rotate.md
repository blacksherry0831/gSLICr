# 地面交通标志识别

本算法采用Hu矩和旋转模板匹配识别地面交通标志

-  Hu矩匹配箭头类型。
-  旋转模板匹配确定箭头方向。

## 一、交通标志模板

|      | 右转                                                         | 左转                                                         | 前进                                                         |
| ---- | ------------------------------------------------------------ | ------------------------------------------------------------ | ------------------------------------------------------------ |
| 黄橙 | <img src="\image\Template\Right\SKU-14-黄色-右转.png" style="zoom: 80%;" /> | <img src="\image\Template\Left\SKU-10-黄色-左转.png" alt="SKU-10-黄色-左转" style="zoom:80%;" /> | <img src="\image\Template\Forward\SKU-02-黄色-直行.png" alt="SKU-02-黄色-直行" style="zoom:80%;" /> |
| 青绿 | <img src="\image\Template\Right\SKU-16-绿色-右转.png" alt="SKU-16-绿色-右转" style="zoom:80%;" /> | <img src="\image\Template\Left\SKU-12-绿色-左转.png" alt="SKU-12-绿色-左转" style="zoom:80%;" /> | <img src="\image\Template\Forward\SKU-04-绿色-直行.png" alt="SKU-04-绿色-直行" style="zoom:80%;" /> |
| 红   | <img src="\image\Template\Right\SKU-13-红色-右转.png" alt="SKU-13-红色-右转" style="zoom:80%;" /> | <img src="\image\Template\Left\SKU-09-红色-左转.png" alt="SKU-09-红色-左转" style="zoom:80%;" /> | <img src="\image\Template\Forward\SKU-01-红色-直行.png" alt="SKU-01-红色-直行" style="zoom:80%;" /> |

## 二、检测区提取

### 1.1 原始图像转换到HSV通道

#### 1.1.1 HSV 颜色空间

​		HSV是一种将RGB色彩空间中的点在倒圆锥体中的表示方法。HSV即色相(Hue)、饱和度(Saturation)、明度(Value)，又称HSB(B即Brightness)。色相是色彩的基本属性，就是平常说的颜色的名称，如红色、黄色等。饱和度（S）是指色彩的纯度，越高色彩越纯，低则逐渐变灰，取0-100%的数值。明度（V），取0-max(计算机中HSV取值范围和存储的长度有关)。HSV颜色空间可以用一个圆锥空间模型来描述。圆锥的顶点处，V=0，H和S无定义，代表黑色。圆锥的顶面中心处V=max，S=0，H无定义，代表白色。

![HSV](\image\hsv.conical.png)

#### 1.1.2 颜色空间转换

###### cvCvtColor（颜色空间转换）

```
cvCvtColor(mImgOrg, mImgHsv, CV_BGR2HSV);//CV_BGR2HSV
```

### 1.2 分离红色、黄橙色、绿青色检测区

#### 1.2.1分离箭头区域

##### 各种颜色对应的HSV范围区域

![](\image\hsv.color.map.png)

##### 交通标志模板对应的颜色值

| 箭头颜色 | low range （H,S,V）           | high range（H,S,V）                |
| -------- | ----------------------------- | ---------------------------------- |
| 红       | （0, 43, 46）/（156, 43, 46） | （10, 255, 255）/（180, 255, 255） |
| 黄橙     | （11, 43, 46）                | （34, 255, 255）                   |
| 绿青     | （78, 43, 46）                | （99, 255, 255）                   |

##### 根据颜色在HSV颜色空间分离交通标志

###### cvInRangeS

```c++
	//分离黄色块
	cvInRangeS(mImgHsv, Orange_low, Y_up, mImgBinYellow);//yellow-orange
	//分离绿色
	cvInRangeS(mImgHsv, Cyan_low, Cyan_up, mImgBinGreen);//cyan
	//分离红色块	
	cvInRangeS(mImgHsv, R00_low, R00_up, mImgBinRed00);//red
	cvInRangeS(mImgHsv, R01_low, R01_up, mImgBinRed01);//red
	cvOr(mImgBinRed00, mImgBinRed01, mImgBinRed);//red
```

#### 1.2.2裁剪交通标志目标区域

- 使用轮廓法提取交通标志轮廓
- 提取轮廓的矩形区域、剪切图片
- 裁剪二值化

![](\image\process\forward.binary.png)

###### cvFindContours

###### cvBoundingRect

```c++
cvFindContours(pBinary, mMemStorage, &pContour, sizeof(CvContour), CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);// 查找所有轮廓 

const CvRect rect = cvBoundingRect(pContour, B);

cvDrawContours(_imgOut, pContour, ColorWhite, ColorWhite, 0, CV_FILLED,CV_AA);
```



## 三、识别标志

### 3.1 识别方法

#### 3.1.1 Hu矩

​		Hu矩特性：具有较强的**平移**、**尺度**和**旋转**不变性，其中旋转不变性为360度。是一种基于区域的形状匹配方法。但由于匹配的数据量大，执行速度较慢。适合于进行一些更精确的匹配。由Hu矩组成的特征量对图片进行识别，优点就是速度很快，缺点是识别率比较低。因此Hu不变矩一般用来识别图像中大的物体，对于物体的形状描述得比较好，图像的纹理特征不能太复杂。

##### 计算轮廓的Hu距

![](\image\process\forward.binary.contours.png)

###### cvMatchShapes（Hu距匹配）

```C++
double TrafficSignPropertyHu::matchShapesSeq(const CvSeq * _seq)
{
	this->mHuSimilar=cvMatchShapes(this->mContours, _seq, CV_CONTOURS_MATCH_I1);
	return this->mHuSimilar;
}
```

#### 3.1.2 模板匹配

- 优点：简单、直接

- 缺点：不具有旋转不变性、不具有尺度不变性


##### 模板匹配方法

- 计算检测区域的最小外接矩形；

  ![最小外接矩形](\image\process\rect.png)

- 旋转外接矩形图片到水平位置；

- 继续旋转90度、180度、270度；

  ![](\image\process\forward.rotate.png)

- 模板匹配找到最优匹配结果

  

###### minAreaRect（最小外接矩形）

###### matchTemplate（模板匹配）

```C++
double TrafficSignPropertyHu::calcRotateAngle1(
	 cv::Mat & roi,
	 cv::Mat & tmpl,
	 std::vector<std::vector<cv::Point>>& roiContours)
 {
	 cv::RotatedRect minRect = minAreaRect(roiContours[0]);
	 double baseAngle = minRect.angle;

	 cv::Mat  image[4];
	 cv::Mat  imgret[4];

	 std::vector<double>  angles;
	 std::vector<double>  similars;
	 	 
	 double		similar=0;
	 double		similar_max = 0;
	 int		similar_idx = 0;

	 const int match_method = cv::TM_CCOEFF_NORMED;

	 for (int i = 0; i < 4; ++i) {		
		 const double angle = baseAngle + 90 * i;
		 angles.push_back(angle);
		 Rotate(roi, image[i], angle);

		 matchTemplate(tmpl,image[i] , imgret[i], match_method);

		 double minVal = -1;
		 double maxVal;
		 cv::Point minLoc;
		 cv::Point maxLoc;
		 cv::Point matchLoc;
		 minMaxLoc(imgret[i], &minVal, &maxVal, &minLoc, &maxLoc, cv::Mat());

		 matchLoc = minLoc;
		 		
		 if (match_method == cv::TM_SQDIFF || match_method == cv::TM_SQDIFF_NORMED){
			 matchLoc = minLoc;
			 similar = 1 - minVal;
		 } else {
			 matchLoc = maxLoc;
			 similar = maxVal;
		 }
		 		 
		 similars.push_back(similar);
		 
		 if (similar>similar_max){
			 similar_idx = i;
			 similar_max = similar;

		 }
		 
	 }
	 
	 return angles.at(similar_idx);
 }
```



#### 3.1.3 组合Hu距和模板匹配识别

- 利用Hu的不变性匹配箭头类型
- 旋转模板匹配箭头的方向



## 参考资料

1. https://blog.csdn.net/haofan_/article/details/77090474
2. https://www.cnblogs.com/skyfsm/p/7401523.html
3. https://www.cnblogs.com/shine-lee/p/10950963.html
4. https://www.cnblogs.com/little-monkey/p/7634303.html
5. [矩阵求解](https://cloud.tencent.com/developer/article/1675672)
6. https://blog.csdn.net/m0_37598482/article/details/78654522

