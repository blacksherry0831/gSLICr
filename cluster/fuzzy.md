# FUZZY

## 一、天空立面地面模糊函数

$$
H_{s}==天空到视平线的像素距离
$$

$$
H_{G}==地面到视平线的像素距离
$$


$$
\begin{equation}
    G(x)=
   \begin{cases}
   
   	\frac{2n+2}{2n+1}H_{G}^{	\frac{2n+2}{2n+1}} |x|^{\frac{1}{2n+1}}	&	\mbox{if x>0}	\\
    
   	-\frac{2n+2}{2n+1}H_{G}^{	\frac{2n+2}{2n+1}} |x|^{\frac{1}{2n+1}}	&		\mbox{if x<0}
   
   \end{cases}
  \end{equation}
$$

$$
\begin{equation}
    S(x)=
   \begin{cases}
   
   	\frac{2n+2}{2n+1}H_{G}^{	\frac{2n+2}{2n+1}} |x|^{\frac{1}{2n+1}}	&	\mbox{if x>0}	\\
    
   	-\frac{2n+2}{2n+1}H_{G}^{	\frac{2n+2}{2n+1}} |x|^{\frac{1}{2n+1}}	&		\mbox{if x<0}
   
   \end{cases}
  \end{equation}
$$

$$
V(x)=\frac{1}{\sqrt{2\pi}\delta}e^{-\frac{x^2}{\delta^{2}}}
$$

## 二、统计图像中每一个超像素团块的属性


$$
\begin{equation*}

W(spi) = \frac{1}{N} \sum_{n=1}^N W(x,y) 

\\if  IDX(x,y)==spi

\end{equation*}
$$
