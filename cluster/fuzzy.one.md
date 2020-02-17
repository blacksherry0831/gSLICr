# fuzzy one  example

## 天空立面地面模糊函数

### 视平线位于图像中线位置

#### 注意，视平线是可以移动的

$$
H=image \quad height
$$


$$
H_{G}=H_{S}=H_{0}=\frac{H}{2} \qquad \mbox{视平线位置}
$$

$
G(x)、S(x)为幂函数；V(x)正态分布；
$



$$
\begin{equation}    G(x)=   \begin{cases}       {\frac{4}{3}}{H_{0}^{	-\frac{4}{3}}}	 |x|^{\frac{1}{3}}	&    \mbox{if x>0}	\\-{\frac{4}{3}}{ H_{0}^{	-\frac{4}{3}}}	 |x|^{\frac{1}{3}}	&    \mbox{if x<0}      \end{cases}  \end{equation}
$$

$$
\begin{equation}    S(x)=   \begin{cases}       -{\frac{4}{3}}{ H_{0}^{	-\frac{4}{3}}}	 |x|^{\frac{1}{3}}	&    \mbox{if x>0}	\\        {\frac{4}{3}}{ H_{0}^{-\frac {4}{3}}}	 |x|^{\frac{1}{3}}	&    \mbox{if x<0}	\\      \end{cases}  \end{equation}
$$

$$
V(x)=W\frac{1}{\sqrt{2\pi}\delta}e^{-\frac{x^2}{\delta^{2}}}	\\
\delta= \frac{ H_{0}}{D}	\\
W=2	\quad \mbox{权重参数}	\\
D=6	\quad \mbox{权重参数}	\\
$$

