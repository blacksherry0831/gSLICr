# 交通标志识别

## 一、检测

### 转换为HSV通道

```
hsv=cv2.cvtColor(img,cv2.COLOR_BGR2HSV)
cv2.imshow('hsv',hsv)
```

### 颜色过滤

```
#提取蓝色区域
blue_lower=np.array([100,50,50])
blue_upper=np.array([124,255,255])
mask=cv2.inRange(hsv,blue_lower,blue_upper)
print('mask',type(mask),mask.shape)
cv2.imshow('mask',mask)
```

### 裁剪目标区域

思路：此时的图像已经处理的很简单，所以进行查找轮廓，将轮廓转换为矩形，然后根据矩形的坐标，在原图进行裁剪，即可得到目标区域

```
image,contours, hierarchy=cv2.findContours(dilate.copy(), cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_SIMPLE)
```

## 二、识别

### 方法

#### Hu矩

Hu矩特性：具有较强的**平移**、**尺度**和**旋转**不变性，其中旋转不变性为360度

是一种基于区域的形状匹配方法。但由于匹配的数据量大，执行速度较慢。适合于进行一些更精确的匹配。由Hu矩组成的特征量对图片进行识别，优点就是速度很快，缺点是识别率比较低。
因此Hu不变矩一般用来识别图像中大的物体，对于物体的形状描述得比较好，图像的纹理特征不能太复杂。

#### 模板匹配

优点：简单、直接

缺点：不具有旋转不变性、不具有尺度不变性

#### 关键点

| 特征匹配       | 速度 | 尺度不变 | 旋转不变 |      |
| -------------- | ---- | -------- | -------- | ---- |
| SURF           | 10   | Y        |          |      |
| SIFT           | 1    | Y        | Y        |      |
| ORiented Brief | 100  | N        | N        |      |
| FAST           |      |          |          |      |
| Harris         |      | N        | Y        |      |



##### SIFT 

1、具有较好的**稳定性**和**不变性**，能够适应**旋转**、**尺度**缩放、亮度的变化，能在一定程度上不受视角变化、仿射变换、噪声的干扰。
2、**区分性**好，能够在海量特征数据库中进行快速准确的区分信息进行匹配
3、**多量性**，就算只有单个物体，也能产生大量特征向量
4、**高速性**，能够快速的进行特征向量匹配
5、**可扩展性**，能够与其它形式的特征向量进行联合

##### SIFT 匹配

- 比率测试 Ratio test
- 交叉过滤
- RASIC方法计算基础矩阵，并细化匹配结果
- 计算单应矩阵H，并细化匹配结果



## 参考资料

1. https://blog.csdn.net/haofan_/article/details/77090474
2. https://www.cnblogs.com/skyfsm/p/7401523.html
3. https://www.cnblogs.com/shine-lee/p/10950963.html
4. https://www.cnblogs.com/little-monkey/p/7634303.html
5. [矩阵求解](https://cloud.tencent.com/developer/article/1675672)
6. https://blog.csdn.net/m0_37598482/article/details/78654522

