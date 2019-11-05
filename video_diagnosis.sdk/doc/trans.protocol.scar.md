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

| Command    | 类型   | 命令字01 | 命令字02                      | BODY(2byte) |
| ---------- | ------ | -------- | ----------------------------- | ----------- |
| 查询上门限 | Global | CT_QUERY | CT_IMG_SCAR_GLOBAL_SIGMA_UP   |             |
| 设置上门限 | Global | CT_IMG   | CT_IMG_SCAR_GLOBAL_SIGMA_UP   | SIGMA       |
| 查询下门限 | Global | CT_QUERY | CT_IMG_SCAR_GLOBAL_SIGMA_DOWN |             |
| 设置下门限 | Global | CT_IMG   | CT_IMG_SCAR_GLOBAL_SIGMA_DOWN | SIGMA       |
|            |        |          |                               |             |

### 2.2	设置Row门限

| Command    | 类型 | 命令字01 | 命令字02                   | BODY(2byte) |
| ---------- | ---- | -------- | -------------------------- | ----------- |
| 查询上门限 | Row  | CT_QUERY | CT_IMG_SCAR_ROW_SIGMA_UP   |             |
| 设置上门限 | Row  | CT_IMG   | CT_IMG_SCAR_ROW_SIGMA_UP   | SIGMA       |
| 查询下门限 | Row  | CT_QUERY | CT_IMG_SCAR_ROW_SIGMA_DOWN |             |
| 设置下门限 | Row  | CT_IMG   | CT_IMG_SCAR_ROW_SIGMA_DOWN | SIGMA       |
|            |      |          |                            |             |

### 2.3	设置Col门限

| Command    | 类型 | 命令字01 | 命令字02                   | BODY(2byte) |
| ---------- | ---- | -------- | -------------------------- | ----------- |
| 查询上门限 | Col  | CT_QUERY | CT_IMG_SCAR_COL_SIGMA_UP   |             |
| 设置上门限 | Col  | CT_IMG   | CT_IMG_SCAR_COL_SIGMA_UP   | SIGMA       |
| 查询下门限 | Col  | CT_QUERY | CT_IMG_SCAR_COL_SIGMA_DOWN |             |
| 设置下门限 | Col  | CT_IMG   | CT_IMG_SCAR_COL_SIGMA_DOWN | SIGMA       |
|            |      |          |                            |             |

## 三、Set work mode And mask image

### 3.1	设置工作模式

| Command      | 命令字01 | 命令字02         | BODY(2byte) |
| ------------ | -------- | ---------------- | ----------- |
| 设置工作模式 | CT_IMG   | CT_IMG_MODE_SCAR |             |
|              |          |                  |             |

| bit2(col) | bit1(row) | bit0(global) | mode     |
| --------- | --------- | ------------ | -------- |
| 1         | 0         | 0            | 列检测   |
| 0         | 1         | 0            | 行检测   |
| 0         | 0         | 1            | 全局模式 |
| 0         | 0         | 0            | 原始图像 |

### 3.2	设置屏蔽图像

| Command      | 命令字01 | 命令字02             | BODY(multi-byte) |
| ------------ | -------- | -------------------- | ---------------- |
| 设置屏蔽图像 | CT_IMG   | CT_IMG_MASK_SET_SCAR | IplImageU        |
|              |          |                      |                  |

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

| Command      | 命令字01 | 命令字02                | BODY(multi-byte) |
| ------------ | -------- | ----------------------- | ---------------- |
| 设置检测序列 | CT_IMG   | CT_IMG_MASK_SELECT_SCAR |                  |
|              |          |                         |                  |

#### 检测序列BODY区内容

| 4byte    | multi-byte   | property               |
| -------- | ------------ | ---------------------- |
| 序列长度 | 检测序列实体 | 依次设置蒙版的序列号， |
| LEN      | 4*LEN        |                        |
|          |              |                        |

