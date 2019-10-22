#  Similar Matrix

## 一、相似度矩阵W转换为三角矩阵

### 1.1相似度矩阵W

$$
\begin{matrix}
   			&j_{0} & j_{1} & j_{2} & j_{3} &j_{4} & j_{...} & j_{n-1} &j_{n}	\\
  i_{0} 	& 1 & 0 & 1 & 0 & 0 & ... & 0 & 0\\
  i_{1} 	& 0 & 1 & 0 & 1 & 0 & ... & 0 & 0\\
  i_{2} 	& 1 & 0 & 1 & 0 & 0 & ... & 0 & 0\\
  i_{3} 	& 0 & 1 & 0 & 1 & 1 & ... & 0 & 0\\
  i_{4} 	& 0 & 0 & 0 & 1 & 1 & ... & 0 & 0\\
  i_{...} 	&...&...&...&...&...& ... &...&...\\
  i_{n-1}  	& 0 & 0 & 0 & 0 & 0 & ... & 1 & 1\\
  i_{n}  	& 0 & 0 & 0 & 0 & 0 & ... & 1 & 1\\
  \end{matrix} \tag{1}
$$

### 1.2三角矩阵$W_{3}$

#### 将右下角全部置零

$$
\begin{matrix}
   			&j_{0} & j_{1} & j_{2} & j_{3} &j_{4} & j_{...} & j_{n-1} &j_{n}	\\
  i_{0} 	& 1 & 0 & 1 & 0 & 0 & ... & 0 & 0\\
  i_{1} 	& 0 & 1 & 0 & 1 & 0 & ... & 0 & 0\\
  i_{2} 	& 0 & 0 & 1 & 0 & 0 & ... & 0 & 0\\
  i_{3} 	& 0 & 0 & 0 & 1 & 1 & ... & 0 & 0\\
  i_{4} 	& 0 & 0 & 0 & 0 & 1 & ... & 0 & 0\\
  i_{...} 	&...&...&...&...&...& ... &...&...\\
  i_{n-1}  	& 0 & 0 & 0 & 0 & 0 & ... & 1 & 1\\
  i_{n}  	& 0 & 0 & 0 & 0 & 0 & ... & 0 & 1\\
  \end{matrix} \tag{1}
$$

#### CODE

```c++
void gSLICr::engines::getMatTriangular_Float(float* _mat, const int _wh)
{

	for (size_t ri = 0; ri <_wh; ri++) {
		for (size_t ci = 0; ci < ri; ci++) {
			const int IDX = ri*_wh + ci;
			_mat[IDX] = 0;
		}
	}

}
```

## 二、三角矩阵生成聚类关系图

### 2.1.算法步骤

#### 1.从第n列开始，找出列上值为1的所有行：

$$
i_{min},i_{min+1},...,i_{max-1},i_{max}
$$

$$
W_{3}(i_{min},j_{n})==
W_{3}(i_{min+1},j_{n})==
...==
W_{3}(i_{max-1},j_{n})==
W_{3}(i_{max},j_{n})==1
$$

#### 2.合并所有行，结果保存到最小行，擦除其他行：

$$
row(i_{min})=row(i_{min}) || row(i_{min+1})... || row({i_{max-1}} )|| row(i_{max})
$$

$$
row(i_{min+1})=0
$$

$$
...
$$

$$
row(i_{max-1})=0
$$

$$
row(i_{max})=0
$$

#### 3.从第n-1列开始重复以上步骤；

#### 4.结束运算

则矩阵中所有不全为零的行即为。
$$
\begin{matrix}   			
		&j_{0} & j_{1} & j_{2} & j_{3} &j_{4} & j_{...} & j_{n-1} &j_{n}	\\
i_{0} 		& 1 & 0 & 1 & 0 & 0 & ... & 0 & 0\\
i_{1} 		& 0 & 1 & 0 & 1 & 1 & ... & 0 & 0\\
i_{2} 		& 0 & 0 & 0 & 0 & 0 & ... & 0 & 0\\
i_{3} 		& 0 & 0 & 0 & 0 & 0 & ... & 0 & 0\\
i_{4} 		& 0 & 0 & 0 & 0 & 0 & ... & 0 & 0\\
i_{...} 	&...&...&...&...&...& ... &...&...\\
i_{n-1}  	& 0 & 0 & 0 & 0 & 0 & ... & 1 & 1\\
i_{n}  		& 0 & 0 & 0 & 0 & 0 & ... & 0 & 0\\  
\end{matrix}
$$

### 2.2 CODE


```c++
void gSLICr::engines::getMatCluster_Float(float * _mat, const int _wh)
{
	for (int ci = _wh - 1; ci >= 0; ci--) {

		std::vector<int> sameClass;

		for (int ri = 0; ri <_wh; ri++) {
			const int IDX = ci + ri*_wh;
			const int W = _mat[IDX];
			if (W) {
				sameClass.push_back(ri);
			}
		}

		if (sameClass.size() > 0) {
			const int ri_min = sameClass.at(0);
			for (int ri = 1; ri < sameClass.size(); ri++) {
				const int ri_current = sameClass.at(ri);
				MergeNeighbor_Float(_mat, _wh, ri_current, ri_min);
				RemoveLine_Float(_mat, _wh, ri_current);
			}
		}
	}
}
```

