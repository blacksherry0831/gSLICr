# FUZZY

## 一、天空立面地面模糊函数

$$
H_{s}==天空区域像素长度
$$

$$
H_{G}==地面区域像素长度
$$

$$
H=H_{G}+H_{S}
$$



### 视平线位置作为坐标轴零点。

#### 天空是负轴，地面是正轴

#### 注意，视平线是可以移动的,坐标轴零点也会移动


$$
\begin{equation}
    G(x)=
   \begin{cases}
   
   	\frac{2n+2}{2n+1}H_{G}^{	-\frac{2n+2}{2n+1}} |x|^{\frac{1}{2n+1}}	&	\mbox{if x>0}	\\
    
   	-\frac{2n+2}{2n+1}H_{G}^{	-\frac{2n+2}{2n+1}} |x|^{\frac{1}{2n+1}}	&		\mbox{if x<0}
   
   \end{cases}
  \end{equation}
$$

$$
\begin{equation}
    S(x)=
   \begin{cases}
   
   	\frac{2n+2}{2n+1}H_{S}^{	-\frac{2n+2}{2n+1}} |x|^{\frac{1}{2n+1}}	&	\mbox{if x>0}	\\
    
   	-\frac{2n+2}{2n+1}H_{S}^{	-\frac{2n+2}{2n+1}} |x|^{\frac{1}{2n+1}}	&		\mbox{if x<0}
   
   \end{cases}
  \end{equation}
$$

$$
V(x)=\frac{1}{\sqrt{2\pi}\delta}e^{-\frac{x^2}{\delta^{2}}}
$$

$$
\begin{equation}
   \delta =
   \begin{cases}
   
   	\frac{H_{G}}{6}
    &	\mbox{if x>0}	\\
    
   	\frac{H_{S}}{6}
   	&	\mbox{if x<0}
   
   \end{cases}
  \end{equation}
$$



## 二、统计图像中每一个超像素团块的属性


$$
\begin{equation*}

W(spi) = \frac{1}{N} \sum_{n=1}^N W(x,y) 

\\if ( IDX(x,y)==spi)

\end{equation*}
$$
