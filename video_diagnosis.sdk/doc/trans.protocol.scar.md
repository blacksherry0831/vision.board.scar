# scar detect

## 一、命令字节

### 1.1	命令字01

```C++
enum CMD_TYPE {

	CT_HEART='h',
	CT_QUERY='q',
	CT_CTRL='c',
	CT_RESP='r',
	CT_IMG='I',

};
```

### 1.2	命令字02

```c++
enum CMD_TYPE_02_I_SCAR{

		CT_IMG_MODE_SCAR=0x80,
		CT_IMG_MASK_SET_SCAR=0x81,
		CT_IMG_MASK_SELECT_SCAR=0x82,

};
```

```
enum CMD_TYPE_02_I_SCAR_SIGMA{

		CT_IMG_SCAR_GLOBAL_SIGMA_UP=0xF3,
		CT_IMG_SCAR_GLOBAL_SIGMA_DOWN=0xF4,

		CT_IMG_SCAR_ROW_SIGMA_UP=0xF5,
		CT_IMG_SCAR_ROW_SIGMA_DOWN=0xF6,

		CT_IMG_SCAR_COL_SIGMA_UP=0xF7,
		CT_IMG_SCAR_COL_SIGMA_DOWN=0xF8,

};
```



## 二、图像处理SIGMA 上下限设置

$$
\sigma	\in	[0,255]
$$

### 2.1	设置Global门限

| Command | 类型   | 门限 | 命令字01 | 命令字02                      | BODY(2byte) |
| ------- | ------ | ---- | -------- | ----------------------------- | ----------- |
| 查询    | Global | 上   | CT_QUERY | CT_IMG_SCAR_GLOBAL_SIGMA_UP   |             |
| 设置    | Global | 上   | CT_IMG   | CT_IMG_SCAR_GLOBAL_SIGMA_UP   | SIGMA       |
| 查询    | Global | 下   | CT_QUERY | CT_IMG_SCAR_GLOBAL_SIGMA_DOWN |             |
| 设置    | Global | 下   | CT_IMG   | CT_IMG_SCAR_GLOBAL_SIGMA_DOWN | SIGMA       |
|         |        |      |          |                               |             |

### 2.2	设置Row门限

| Command | 类型 | 门限 | 命令字01 | 命令字02                   | BODY(2byte) |
| ------- | ---- | ---- | -------- | -------------------------- | ----------- |
| 查询    | Row  | 上   | CT_QUERY | CT_IMG_SCAR_ROW_SIGMA_UP   |             |
| 设置    | Row  | 上   | CT_IMG   | CT_IMG_SCAR_ROW_SIGMA_UP   | SIGMA       |
| 查询    | Row  | 下   | CT_QUERY | CT_IMG_SCAR_ROW_SIGMA_DOWN |             |
| 设置    | Row  | 下   | CT_IMG   | CT_IMG_SCAR_ROW_SIGMA_DOWN | SIGMA       |
|         |      |      |          |                            |             |

### 2.3	设置Col门限

| Command | 类型 | 门限 | 命令字01 | 命令字02                   | BODY(2byte) |
| ------- | ---- | ---- | -------- | -------------------------- | ----------- |
| 查询    | Col  | 上   | CT_QUERY | CT_IMG_SCAR_COL_SIGMA_UP   |             |
| 设置    | Col  | 上   | CT_IMG   | CT_IMG_SCAR_COL_SIGMA_UP   | SIGMA       |
| 查询    | Col  | 下   | CT_QUERY | CT_IMG_SCAR_COL_SIGMA_DOWN |             |
| 设置    | Col  | 下   | CT_IMG   | CT_IMG_SCAR_COL_SIGMA_DOWN | SIGMA       |
|         |      |      |          |                            |             |

## 三、Set work mode And mask image

### 3.1	设置工作模式

| Command      | 命令字01 | 命令字02         | BODY(2byte) |
| ------------ | -------- | ---------------- | ----------- |
| 设置工作模式 | CT_IMG   | CT_IMG_MODE_SCAR |             |
| 回复         | CT_RESP  | CT_OK            |             |

| bit3(undefine) | bit2(col) | bit1(row) | bit0(global) | mode     |
| -------------- | --------- | --------- | ------------ | -------- |
| 0              | 1         | 0         | 0            | 列检测   |
| 0              | 0         | 1         | 0            | 行检测   |
| 0              | 0         | 0         | 1            | 全局模式 |
| 0              | 0         | 0         | 0            | 原始图像 |

### 3.2	设置屏蔽图像

蒙版会存储到SD卡，下位机开机后会自动加载。

| Command      | 命令字01 | 命令字02             | BODY(multi-byte) |
| ------------ | -------- | -------------------- | ---------------- |
| 设置屏蔽图像 | CT_IMG   | CT_IMG_MASK_SET_SCAR | IplImageU        |
| 回复         | CT_RESP  | CT_OK                |                  |

| 蒙版存储     | min  | max  |
| ------------ | ---- | ---- |
| mask_channel | 0    | 7    |
| mask_frame   | 0    | 47   |
|              |      |      |

| IplImageU     | value(default)            | detail           |
| ------------- | ------------------------- | ---------------- |
| nSize         |                           | struct size      |
| prefix        | "Image"                   |                  |
| IpAddrChannel | mask_frame*8+mask_channel | 屏蔽图像存储位置 |
| width         | 1920                      | 屏蔽图像宽度     |
| height        | 1080                      | 屏蔽图像高度     |
| width_roi     | 0                         |                  |
| height_roi    | 0                         |                  |
| x_roi         | 0                         |                  |
| y_roi         | 0                         |                  |
| sensor_stat   | 0                         |                  |
| nChannels     | 1                         | 灰度图           |
| colorModel    | "gray"                    | 灰度图像         |
|               |                           |                  |

### 3.3	设置检测序列

1. 序列号为0xffffffff时，输出原始图像视频流；
2. 否则，正常输出检测结果；

| Command      | 命令字01 | 命令字02                | BODY(multi-byte) |
| ------------ | -------- | ----------------------- | ---------------- |
| 设置检测序列 | CT_IMG   | CT_IMG_MASK_SELECT_SCAR |                  |
| 回复         | CT_RESP  | CT_OK                   |                  |

#### 检测序列BODY区内容

| idx/4byte | sample     | property   |               |
| --------- | ---------- | ---------- | ------------- |
| 0         | 0x0000ff   | 检测序列号 | 工位          |
| 1         | N          | 蒙版个数   | 2             |
| 2         | 0x000000   | 0号蒙版    | 蒙版序号      |
| 3         | 0xffffffff | 0号蒙版    | Global 上门限 |
| 4         | 0xffffffff | 0号蒙版    | Global 下门限 |
| 5         | 0xffffffff | 0号蒙版    | Row  上门限   |
| 6         | 0xffffffff | 0号蒙版    | Row 下门限    |
| 7         | 0xffffffff | 0号蒙版    | Col  上门限   |
| 8         | 0xffffffff | 0号蒙版    | Col 下门限    |
| 9         | 0x000000   | 0号蒙版    | 工作模式      |
| 10        | 0x000001   | 1号蒙版    | 蒙版序号      |
| 11        | 0x0000ff   | 1号蒙版    | Global 上门限 |
| 12        | 0x0000ff   | 1号蒙版    | Global 下门限 |
| 13        | 0x0000ff   | 1号蒙版    | Row  上门限   |
| 14        | 0x0000ff   | 1号蒙版    | Row 下门限    |
| 15        | 0x0000ff   | 1号蒙版    | Col  上门限   |
| 16        | 0x0000ff   | 1号蒙版    | Col 下门限    |
| 17        | 0x000000   | 1号蒙版    | 工作模式      |
| ...       | ....       | ...        | ...           |

| 门限值     | 含义           |      |
| ---------- | -------------- | ---- |
| 0xffffffff | 使用全局参数   |      |
| otherwise  | 使用自定义参数 |      |
|            |                |      |

| 检测序列号 | 意义             |      |
| ---------- | ---------------- | ---- |
| 0xffffffff | 原始图像输出模式 |      |
| otherwise  | 正常检测         |      |
|            |                  |      |

## 四、工作触发

| 触发序列 | 输出          |      |
| -------- | ------------- | ---- |
| START    |               |      |
| START00  |               |      |
|          | nothing       |      |
| STOP00   |               |      |
| START01  |               |      |
|          | 图像[0,1,2..] |      |
| STOP01   |               |      |
| STOP     |               |      |

```c++
enum WorkMode
{
	WM_SIZE_FULL=0x80,
	WM_SIZE_CUT=0x40,
	WM_ORG_IMG=0x20,
	WM_DIFF_IMG=0x10,
	RESP=0x01

};
```

| 工作模式     | 详细         | support       |
| ------------ | ------------ | ------------- |
| WM_SIZE_FULL | 原图         | true          |
| WM_SIZE_CUT  | 切割图       | false         |
| WM_ORG_IMG   | 原始图像     | 图像位于通道0 |
| WM_DIFF_IMG  | 算法输出图像 | 图像位于通道1 |
|              |              |               |

