# 超像素算法

## 算法

### 一. Convert RGB to LAB



### 二. GPU SuperPixel

1. 计算超像素初始种子点SuperPixelSeeds；
2. 执行超像素算法
3. 重新计算超像素种子SuperPixelSeeds,
4. 重复步骤2，步骤3；
5. 超像素迭代次数==2；

#### 超像素块的属性

- 超像素种子；其中LABXY属于**超像素块**的加权平均:
  $$
  Seed(i)=(L_{i},A_{i},B_{i},X_{i},Y_{i})
  $$

- 视平线超像素；

  

- 底线超像素；

#### 算法公式

1. Desired number of superpixels ==  K

2. compactness factor==M，M[1,40],  default M=10

   ​						

   ​	
   $$
   Size_{SuperPixel}=0.5+\frac{Width*Height}{K}
   $$
   ​	

$$
STEP=\sqrt{Size_{SuperPixel}}+0.5
$$

$$
INVWT =\frac{1.0}{(STEP/M)^{2}}
$$

$$
D_{color}=(L_{seed}-L_{0})^{2}+(A_{seed}-A_{0})^{2}+(B_{seed}-B_{0})^{2}
$$

$$
D_{coord}=(X_{seed}-X_{0})^{2}+(Y_{seed}-Y_{0})^{2}
$$

$$
D=D_{color}+D_{coord}*INVWT
$$

​				

### 三. Connectivity Repair

1. 连通域会改变原始超像素的数量、分布、以及labels矩阵；



