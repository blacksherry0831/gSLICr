# GPU SLIC

## 一、聚类参数配置

### 1.GPU并行参数

| 常量      | 值   |
| --------- | ---- |
| BLOCK_DIM | 16   |
|           |      |

| 并行块    | x         | y         | z    | Tip             |
| --------- | --------- | --------- | ---- | --------------- |
| BlockSize | BLOCK_DIM | BLOCK_DIM | 1    | 一个块256个线程 |
|           |           |           |      |                 |

### 2.图像矩阵

| 数据      | 数据结构 | 字节 | 像素内容            | 内容       |
| --------- | -------- | ---- | ------------------- | ---------- |
| SourceImg | 4char    | 4    | {b,g,r,a}           | 原始图像   |
| CvtImg    | float    | 4    | {x,y,z,?},{l,a,b,?} | 转换后图像 |
| IdxImg    | int      | 4    | labels              | 标签       |
|           |          |      |                     |            |

### 3.超像素参数

| 参数               |       | 内容                     | 计算方法                                                   |
| ------------------ | ----- | ------------------------ | ---------------------------------------------------------- |
| ImgSize            |       | 图像尺寸                 |                                                            |
| no.segs            |       | 分割超像素个数           |                                                            |
| cluster.size       | float | 单个超像素面积           | (ImgSize.Width *ImgSize.Height)/no.segs                    |
| spixel.size        | int   | 超像素长宽(像素)         | ceil(sqrt(cluster.size))                                   |
| spixel.per.col     | int   | X轴方向超像素个数        | ceil( ImgSize.Width/ spixel.size);                         |
| spixel.per.row     | int   | Y轴方向超像素个数        | ceil(ImgSize.Height / spixel.size);                        |
| spixel.map         |       | 超像素尺寸               | (spixel.per.col,spixel.per.row)                            |
| no.grid.per.center | int   | 9宫格对应的并行块个数    | ceil((spixel.size*spixel.size * 9)/ (BLOCK_DIM*BLOCK_DIM)) |
| no.blocks.per.line | int   | 9宫格对应的并行block长宽 | spixel.size * 3 / BLOCK_DIM                                |

$$
cluster.size = \frac {ImgSize.Width *ImgSize.Height}{no.segs}
$$

$$
spixel.size=ceil(\sqrt{cluster.size})
$$

$$
spixel.per.col=ceil(\frac{ ImgSize.Width}{spixel.size})
$$

$$
spixel.per.row=ceil(\frac{ ImgSize.Height}{spixel.size})
$$

$$
no.grid.per.center=ceil(\frac{spixel.size*spixel.size * 9}{BLOCK\_DIM*BLOCK\_DIM})
$$

$$
no.blocks.per.line=ceil(\frac{spixel.size * 3}{BLOCK_DIM})
$$



### 4.超像素聚类最大距离

| 超像素聚类最大距离 | 距离参数 | 公式                               |      |
| ------------------ | -------- | ---------------------------------- | ---- |
| max.xy.dist        | XY       | (1.0f / (1.4242f * spixel.size))^2 |      |
| max.color.dist.rgb | RGB      | (5.0f / (1.7321f * 255))^2         |      |
| max.color.dist.xyz | XYZ      | (5.0f / 1.7321f)^2                 |      |
| max.color.dist.lab | CIE.LAB  | (15.0f / (1.7321f * 128))^2        |      |

$$
max.xy.dist={(\frac{1}{\sqrt{2}*pixel.size})}^{2}
$$

$$
max.color.dist.rgb={(\frac{5}{\sqrt{3}*255})}^{2}
$$

$$
max.color.dist.xyz={(\frac{5}{\sqrt{3}})}^{2}
$$

$$
max.color.dist.lab={(\frac{15}{\sqrt{3}*128})}^{2}
$$



### 5.超像素中心

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

### 

## 二、颜色空间转换

### 1.并行计算

1. 按照Pixel并行；
2. 每一个线程计算一个Pixel的颜色空间转换

### 2.CODE

| 并行块    | x                                | y                                 | z    |
| --------- | -------------------------------- | --------------------------------- | ---- |
| BlockSize | BLOCK_DIM                        | BLOCK_DIM                         | 1    |
| GridSize  | ceil( ImgSize.Width/BlockSize.x) | ceil( ImgSize.Height/BlockSize.y) | 1    |
|           |                                  |                                   |      |

#### 2.1 RGB2XYZ

```c++
_CPU_AND_GPU_CODE_ inline void rgb2xyz(
		const gSLICr::Vector4u& pix_in,
		gSLICr::Vector4f& pix_out)
{
	const float _b = (float)pix_in.b * 0.0039216f;
	const float _g = (float)pix_in.g * 0.0039216f;
	const float _r = (float)pix_in.r * 0.0039216f;

	pix_out.x = _r*0.412453f + _g*0.357580f + _b*0.180423f;
	pix_out.y = _r*0.212671f + _g*0.715160f + _b*0.072169f;
	pix_out.z = _r*0.019334f + _g*0.119193f + _b*0.950227f;
}
```

#### 2.2 RGB2CIELab

```C++
_CPU_AND_GPU_CODE_ inline void rgb2CIELab(
	const gSLICr::Vector4u& pix_in,
	gSLICr::Vector4f& pix_out)
{
	const float _b = (float)pix_in.b * 0.0039216f;
	const float _g = (float)pix_in.g * 0.0039216f;
	const float _r = (float)pix_in.r * 0.0039216f;

	const float x = _r*0.412453f + _g*0.357580f + _b*0.180423f;
	const float y = _r*0.212671f + _g*0.715160f + _b*0.072169f;
	const float z = _r*0.019334f + _g*0.119193f + _b*0.950227f;

	const float epsilon = 0.008856f;	//actual CIE standard
	const float kappa = 903.3f;		//actual CIE standard

	const float Xr = 0.950456f;	//reference white
	const float Yr = 1.0f;		//reference white
	const float Zr = 1.088754f;	//reference white

	const float xr = x / Xr;
	const float yr = y / Yr;
	const float zr = z / Zr;

	float fx, fy, fz;
	if (xr > epsilon)	fx = pow(xr, 1.0f / 3.0f);
	else				fx = (kappa*xr + 16.0f) / 116.0f;
	if (yr > epsilon)	fy = pow(yr, 1.0f / 3.0f);
	else				fy = (kappa*yr + 16.0f) / 116.0f;
	if (zr > epsilon)	fz = pow(zr, 1.0f / 3.0f);
	else				fz = (kappa*zr + 16.0f) / 116.0f;

	pix_out.L = 116.0f*fy - 16.0f;
	pix_out.A = 500.0f*(fx - fy);
	pix_out.B = 200.0f*(fy - fz);
}
```

## 三、初始化聚类中心

### 1.并行计算

1. 聚类中心即是Seeds;

2. 按照Seed并行;

3. 每一个线程计算一个Seed的坐标和色彩;

4. Seed坐标 (x,y);

5. Seed色彩(l,a,b);

6. 以超像素块中心的像素点的属性，作为超像素的seed属性


### 2.CODE

| 并行块    | x                                | y                                 | z    |
| --------- | -------------------------------- | --------------------------------- | ---- |
| BlockSize | BLOCK_DIM                        | BLOCK_DIM                         | 1    |
| GridSize  | ceil(spixel.per.col/BlockSize.x) | ceil( spixel.per.row/BlockSize.y) | 1    |
|           |                                  |                                   |      |

```C++
/*-------------------------------------------------------------------------*/
/**
*@param inimg			图像矩阵
*@param out_spixel		超像素属性
*@param map_size		超像素二维坐标
*@param img_size		图像尺寸
*@param spixel_size		超像素长宽(像素)
*@param x				超像素二维坐标，X轴坐标
*@param y				超像素二维坐标，Y轴坐标
*
*/
/*-------------------------------------------------------------------------*/
_CPU_AND_GPU_CODE_ inline void init_cluster_centers_shared(
	const gSLICr::Vector4f* inimg,
	gSLICr::objects::spixel_info* out_spixel,
	const gSLICr::Vector2i map_size,
	const gSLICr::Vector2i img_size,
	const int spixel_size,
	const int x,
	const int y)
{
	const int cluster_idx = y * map_size.x + x;

	int img_x = SuperPixelIdx_2_ImgCoord_Center(x, spixel_size);
	int img_y = SuperPixelIdx_2_ImgCoord_Center(y, spixel_size);

	img_x = img_x >= img_size.x ? (x * spixel_size + img_size.x) / 2 : img_x;
	img_y = img_y >= img_size.y ? (y * spixel_size + img_size.y) / 2 : img_y;

	// TODO: go one step towards gradients direction

	out_spixel[cluster_idx].id = cluster_idx;
	out_spixel[cluster_idx].center = gSLICr::Vector2f((float)img_x, (float)img_y);
	out_spixel[cluster_idx].color_info = inimg[img_y*img_size.x + img_x];
	
	out_spixel[cluster_idx].no_pixels = 0;
}
```



## 四、计算聚类标签

### 1.并行计算

1. 按照Pixel并行；
2. 取出周围3x3邻域内9个Seeds;
3. 计算Seed与Pixel之间的距离；
4. 离Pixel距离最近的Seed设置为Pixel的label;

### 2.CODE

| 并行块    | x                                | y                                 | z    |
| --------- | -------------------------------- | --------------------------------- | ---- |
| BlockSize | BLOCK_DIM                        | BLOCK_DIM                         | 1    |
| GridSize  | ceil( ImgSize.Width/BlockSize.x) | ceil( ImgSize.Height/BlockSize.y) | 1    |
|           |                                  |                                   |      |

#### 2.1 计算距离

| 变量             | 值                 |
| ---------------- | ------------------ |
| normalizer_color | max.xy.dist        |
| normalizer_xy    | max.color.dist.lab |
| weight           | 0.6                |


$$
dcolor=(L_{0}-L{1})^{2}+(A_{0}-A{1})^{2}+(B_{0}-B{1})^{2}
$$

$$
dxy==(X_{0}-X{1})^{2}+(Y_{0}-Y{1})^{2}
$$

$$
retval =\sqrt{ dcolor * normalizer\_color + weight * dxy * normalizer\_xy}
$$



```C++
_CPU_AND_GPU_CODE_ inline float compute_slic_distance(
	const gSLICr::Vector4f& pix,
	const int x,
	const int y,
	const gSLICr::objects::spixel_info& center_info,
	const float weight,
	const float normalizer_xy,
	const float normalizer_color)
{
	const float dcolor =
				(pix.x - center_info.color_info.x)*(pix.x - center_info.color_info.x)
			+	(pix.y - center_info.color_info.y)*(pix.y - center_info.color_info.y)
			+	(pix.z - center_info.color_info.z)*(pix.z - center_info.color_info.z);

	const float dxy =
				(x - center_info.center.x) * (x - center_info.center.x)
			  + (y - center_info.center.y) * (y - center_info.center.y);


	const float retval = dcolor * normalizer_color + weight * dxy * normalizer_xy;
	return sqrtf(retval);
}
```

#### 2.2 计算标签

```C++
/*-------------------------------------------------------------------------*/
/**
*
*@param	[in]	inimg				图像数据
*@param	[in]	in_spixel_map		超像素属性
*@param	[out]	out_idx_img			标签矩阵
*@param	[in]	map_size			超像素尺寸
*@param	[in]	img_size			图像尺寸
*@param	[in]	spixel_size			超像素长宽(像素)	
*@param	[in]	weight				坐标距离权重
*@param	[in]	x					图像坐标X
*@param	[in]	y					图像坐标Y
*@param	[in]	max_xy_dist			坐标最大距离
*@param	[in]	max_color_dist		色彩最大距离
*/
/*-------------------------------------------------------------------------*/
_CPU_AND_GPU_CODE_ inline void find_center_association_shared(
	const gSLICr::Vector4f* inimg,
	const gSLICr::objects::spixel_info* in_spixel_map,
	int* out_idx_img,
	const gSLICr::Vector2i map_size,
	const gSLICr::Vector2i img_size,
	const int spixel_size,
	const float weight,
	const int x,
	const int y,
	const float max_xy_dist,
	const float max_color_dist)
{
	const int idx_img = y * img_size.x + x;

	const int ctr_x = x / spixel_size;
	const int ctr_y = y / spixel_size;

	int minidx = -1;
	const float DIST_MAX= 999999.9999f;
	float dist = DIST_MAX;

	// search 3x3 neighborhood
	for (int i = -1; i <= 1; i++)
		for (int j = -1; j <= 1; j++)
	{
		const int ctr_x_check = ctr_x + j;
		const int ctr_y_check = ctr_y + i;

		if (ctr_x_check >= 0 && 
			ctr_y_check >= 0 && 
			ctr_x_check < map_size.x && 
			ctr_y_check < map_size.y)
		{
			const int ctr_idx = ctr_y_check*map_size.x + ctr_x_check;

			const float cdist = compute_slic_distance(
														inimg[idx_img],
														x,
														y,
														in_spixel_map[ctr_idx],
														weight,
														max_xy_dist,
														max_color_dist);

			if (cdist < dist)
			{
				dist = cdist;
				minidx = in_spixel_map[ctr_idx].id;
			}

		}
	}

	if (minidx >= 0)
		out_idx_img[idx_img] = minidx;
}
```



## 五、计算聚类中心

### 1.并行计算

1. 按照Seed和9Seeds对应GPU.Pixel.block并行；
2. 在旧label上搜索9Seed区域内与Seed值一样的点;
3. 累加所有符合labels条件的坐标(x,y)和颜色(l,a,b);
4. 求坐标和颜色的平均值;

### 2.CODE

| variate   | type        | x              | y              | z                  |
| --------- | ----------- | -------------- | -------------- | ------------------ |
| accum.map | spixel_info | spixel.per.col | spixel.per.row | no.grid.per.center |
|           |             |                |                |                    |

#### 2.1 统计坐标与颜色

| 并行块    | x              | y              | z                  |
| --------- | -------------- | -------------- | ------------------ |
| BlockSize | BLOCK_DIM      | BLOCK_DIM      | 1                  |
| GridSize  | spixel.per.col | spixel.per.row | no.grid.per.center |
|           |                |                |                    |

1. 统计超像素块中每一个并行块（16X16）中的坐标(x,y)和颜色(l,a,b);
2. GPU一个Block有（16X16）256个线程；
3. 一次统计一个block内的数据；
4. 一个warp包含32个并行thread;
5. 统计新seed时，是以旧的seed为中心的超像素的9宫格内统计；

```C++
__global__ void Update_Cluster_Center_device(
	const Vector4f* inimg,
	const int* in_idx_img,
	spixel_info* accum_map,
	const Vector2i map_size,
	const Vector2i img_size,
	const int spixel_size,
	const int no_blocks_per_line)
{
	const int local_id = threadIdx.y * blockDim.x + threadIdx.x;

	__shared__ Vector4f color_shared[BLOCK_DIM*BLOCK_DIM];
	__shared__ Vector2f xy_shared[BLOCK_DIM*BLOCK_DIM];
	__shared__ int count_shared[BLOCK_DIM*BLOCK_DIM];
	__shared__ bool should_add; 

	color_shared[local_id] = Vector4f(0, 0, 0, 0);
	xy_shared[local_id] = Vector2f(0, 0);
	count_shared[local_id] = 0;
	should_add = false;
	__syncthreads();

	const int no_blocks_per_spixel = gridDim.z;

	const int spixel_id = blockIdx.y * map_size.x + blockIdx.x;

	// compute the relative position in the search window
	const int block_x = blockIdx.z % no_blocks_per_line;
	const int block_y = blockIdx.z / no_blocks_per_line;

	const int x_offset = block_x * BLOCK_DIM + threadIdx.x;
	const int y_offset = block_y * BLOCK_DIM + threadIdx.y;

	if (x_offset < Grid_9_Length(spixel_size) && y_offset < Grid_9_Length(spixel_size))
	{
		// compute the start of the search window
		const int x_start = SuperPixelIdx_2_ImgCoord_9Grid_Start(blockIdx.x,spixel_size);
		const int y_start = SuperPixelIdx_2_ImgCoord_9Grid_Start(blockIdx.y,spixel_size);

		const int x_img = x_start + x_offset;
		const int y_img = y_start + y_offset;

		if (x_img >= 0 && x_img < img_size.x && y_img >= 0 && y_img < img_size.y)
		{
			int img_idx = y_img * img_size.x + x_img;
			if (in_idx_img[img_idx] == spixel_id)
			{
				color_shared[local_id] = inimg[img_idx];
				xy_shared[local_id] = Vector2f(x_img, y_img);
				count_shared[local_id] = 1;
				should_add = true;
			}
		}
	}
	__syncthreads();

	if (should_add)
	{
		if (local_id < 128)
		{
			color_shared[local_id] += color_shared[local_id + 128];
			xy_shared[local_id] += xy_shared[local_id + 128];
			count_shared[local_id] += count_shared[local_id + 128];
		}
		__syncthreads();

		if (local_id < 64)
		{
			color_shared[local_id] += color_shared[local_id + 64];
			xy_shared[local_id] += xy_shared[local_id + 64];
			count_shared[local_id] += count_shared[local_id + 64];
		}
		__syncthreads();

		if (local_id < 32)
		{
			color_shared[local_id] += color_shared[local_id + 32];
			color_shared[local_id] += color_shared[local_id + 16];
			color_shared[local_id] += color_shared[local_id + 8];
			color_shared[local_id] += color_shared[local_id + 4];
			color_shared[local_id] += color_shared[local_id + 2];
			color_shared[local_id] += color_shared[local_id + 1];

			xy_shared[local_id] += xy_shared[local_id + 32];
			xy_shared[local_id] += xy_shared[local_id + 16];
			xy_shared[local_id] += xy_shared[local_id + 8];
			xy_shared[local_id] += xy_shared[local_id + 4];
			xy_shared[local_id] += xy_shared[local_id + 2];
			xy_shared[local_id] += xy_shared[local_id + 1];

			count_shared[local_id] += count_shared[local_id + 32];
			count_shared[local_id] += count_shared[local_id + 16];
			count_shared[local_id] += count_shared[local_id + 8];
			count_shared[local_id] += count_shared[local_id + 4];
			count_shared[local_id] += count_shared[local_id + 2];
			count_shared[local_id] += count_shared[local_id + 1];
		}
	}
	__syncthreads();

	if (local_id == 0)
	{
		const int accum_map_idx = GetAccumMapIdx(spixel_id,no_blocks_per_spixel,blockIdx.z);
		accum_map[accum_map_idx].center = xy_shared[0];
		accum_map[accum_map_idx].color_info = color_shared[0];
		accum_map[accum_map_idx].no_pixels = count_shared[0];
	}


}
```

#### 2.2 求平均

| 并行块    | x              | y              | z    |
| --------- | -------------- | -------------- | ---- |
| BlockSize | BLOCK_DIM      | BLOCK_DIM      | 1    |
| GridSize  | spixel.per.col | spixel.per.row | 1    |
|           |                |                |      |

1. 一个超像素对应no.grid.per.center个block;
2. 累加no.grid.per.center个统计数据;
3. 求平均；

```C++
_CPU_AND_GPU_CODE_ inline void finalize_reduction_result_shared(
	const gSLICr::objects::spixel_info* accum_map,
	gSLICr::objects::spixel_info* spixel_list,
	const gSLICr::Vector2i map_size,
	const int no_blocks_per_spixel,
	const int x,
	const int y)
{
	const int spixel_idx = y * map_size.x + x;

	spixel_list[spixel_idx].center = gSLICr::Vector2f(0, 0);
	spixel_list[spixel_idx].color_info = gSLICr::Vector4f(0, 0, 0, 0);
	spixel_list[spixel_idx].no_pixels = 0;

	for (int i = 0; i < no_blocks_per_spixel; i++)
	{
		const int accum_list_idx = GetAccumMapIdx(spixel_idx, no_blocks_per_spixel,i);

		spixel_list[spixel_idx].center += accum_map[accum_list_idx].center;
		spixel_list[spixel_idx].color_info += accum_map[accum_list_idx].color_info;
		spixel_list[spixel_idx].no_pixels += accum_map[accum_list_idx].no_pixels;
	}

	if (spixel_list[spixel_idx].no_pixels != 0)
	{
		spixel_list[spixel_idx].center /= (float)spixel_list[spixel_idx].no_pixels;
		spixel_list[spixel_idx].color_info /= (float)spixel_list[spixel_idx].no_pixels;
	}
}
```

## 六、计算聚类标签（同步骤四）

## 七、重复步骤五和步骤六

## 八、执行连通域

### 1.并行计算

1. 按照Pixel并行；
2. 搜索Pixel周围25个像素点的labels;
3. 若label差异小于16，像素label保持不变；
4. 若label差异大于等于16，像素label随机选择周围的值；
5. 重复（一次）步骤一到步骤四；
6. 结束；

### 2.CODE

| 并行块    | x                                | y                                 | z    |
| --------- | -------------------------------- | --------------------------------- | ---- |
| BlockSize | BLOCK_DIM                        | BLOCK_DIM                         | 1    |
| GridSize  | ceil( ImgSize.Width/BlockSize.x) | ceil( ImgSize.Height/BlockSize.y) | 1    |
|           |                                  |                                   |      |

```C++
_CPU_AND_GPU_CODE_ inline void supress_local_lable(
	const int* in_idx_img,
	int* out_idx_img,
	const gSLICr::Vector2i img_size,
	const int x,
	const int y)
{
	const int IDX = y*img_size.x + x;
	const int clable = in_idx_img[IDX];

	// don't suppress boundary
	if (x <= 1 || y <= 1 || x >= img_size.x - 2 || y >= img_size.y - 2)
	{ 
		out_idx_img[IDX] = clable;
		return; 
	}

	int diff_count = 0;
	int diff_lable = -1;

	for (int j = -2; j <= 2; j++) for (int i = -2; i <= 2; i++)
	{
		int nlable = in_idx_img[(y + j)*img_size.x + (x + i)];
		if (nlable!=clable)
		{
			diff_lable = nlable;
			diff_count++;
		}
	}

	if (diff_count>=16)
		out_idx_img[IDX] = diff_lable;
	else
		out_idx_img[IDX] = clable;
}
```



