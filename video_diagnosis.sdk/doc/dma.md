





# DMA功能模块

[TOC]

## PS->PL功能开发

1. 实现PS端到PL端的数据搬运，将数据从Linux能够访问的PS：00000000-40000000, 使用DMA方式搬运到 

PL：0x4000 0000~0x8000 0000；

2. 在单目摄像头内(外)孔、8目摄像头内(外)孔、导航摄像头上实现以此DMA模块；

 	3. 提供测试代码测试DMA功能，及数据正确性；
 	4. 提供必要的DMA模块使用文档；



| DMA模块 | 基地址     | 中断号 | 数据源                        | 数据目的                      |
| ------- | ---------- | ------ | ----------------------------- | ----------------------------- |
| DMAC0   | 0x83C00000 | 58     | PL DDR  0x40000000-0x7FFFFFFF | PS DDR  0x00000000-0x3FFFFFFF |
| DMAC1   | 0x83C10000 | 57     | PS DDR  0x00000000-0x3FFFFFFF | PL DDR  0x40000000-0x4FFFFFFF |



## 一、DMA，PL->PS

1. DMA将PL端数据传输到PS端；
2. DMA基地址0x83c00000，DMA配置空间0x1000；
3. DMA源地址0x4000 0000~0x8000 0000；
4. DMA目的地址0x1E00 0000~0x2000 0000；

### 1.1 DMA BASE ADDR

```c++
#define PL_RX_DMA_BASEADDR 0x83c00000
#define PL_RX_DMA_MMAP_LENGTH 0x1000
```

| physical address |                    |                |
| ---------------- | ------------------ | -------------- |
| 0x83c0 0000      | PL_RX_DMA_BASEADDR | DMA基地址      |
| ...              |                    | DMA 配置寄存器 |
| 0x83c0 1000      |                    | 4KB            |

### 1.2 DMA DEST MEM

```C++
#define PS_DDR_PHYADDR_FOR_DMA 	0x1E000000
#define PS_DDR_LENGTH_FOR_DMA 	 0x2000000
```

| physical address |                        |                       |
| ---------------- | ---------------------- | --------------------- |
| 0x1E00 0000      | PS_DDR_PHYADDR_FOR_DMA |                       |
| ...              |                        | DMA目的地址，暂存图像 |
| 0x2000 0000      |                        | 32MB=16*2MB           |

## 二、DMA，PS->PL

1. DMA将PS端数据传输到PL端；
2. DMA基地址0x83C10000，DMA配置空间0x1000；
3. DMA源地址0x????????~0x????????；
4. DMA目的地址0x4000 0000~0x8000 0000；

### 2.1 DMA BASE ADDR

```C++
#define PL_RX_DMA_BASEADDR 		0x????????
#define PL_RX_DMA_MMAP_LENGTH 	 0x1000
```

| physical address    |      |                |
| ------------------- | ---- | -------------- |
| 0x0x83C10000        |      | DMA基地址      |
| ...                 |      | DMA 配置寄存器 |
| 0x0x83C10000+0x1000 |      | 4KB            |

### 2.2 DMA DEST MEM

| physical address         |                           |
| ------------------------ | ------------------------- |
| 0x4000 0000              |                           |
| ...                      | 空白区域                  |
| 0x4000 0000+1920X1080X8  |                           |
| ...                      | 原始图像+算法输出图像+... |
| 0x4000 0000+1920X1080X16 |                           |
| ...                      | **存储模板**              |
| 0x4800 0000              |                           |

## 三、DMA寄存器配置

```c++
#define AXI_DMAC_REG_IRQ_MASK			0x80
#define AXI_DMAC_REG_IRQ_PENDING		0x84
#define AXI_DMAC_REG_IRQ_SOURCE			0x88
#define AXI_DMAC_REG_CTRL				0x400
#define AXI_DMAC_REG_TRANSFER_ID		0x404
#define AXI_DMAC_REG_START_TRANSFER		0x408
#define AXI_DMAC_REG_FLAGS				0x40c
#define AXI_DMAC_REG_DEST_ADDRESS		0x410
#define AXI_DMAC_REG_SRC_ADDRESS		0x414
#define AXI_DMAC_REG_X_LENGTH			0x418
#define AXI_DMAC_REG_Y_LENGTH			0x41c
#define AXI_DMAC_REG_DEST_STRIDE		0x420
#define AXI_DMAC_REG_SRC_STRIDE			0x424
#define AXI_DMAC_REG_TRANSFER_DONE		0x428
#define AXI_DMAC_REG_ACTIVE_TRANSFER_ID 0x42c
#define AXI_DMAC_REG_STATUS				0x430
#define AXI_DMAC_REG_CURRENT_DEST_ADDR	0x434
#define AXI_DMAC_REG_CURRENT_SRC_ADDR	0x438
#define AXI_DMAC_REG_DBG0				0x43c
#define AXI_DMAC_REG_DBG1				0x440
#define AXI_DMAC_CTRL_ENABLE			(1 << 0)
#define AXI_DMAC_CTRL_PAUSE				(1 << 1)
#define AXI_DMAC_IRQ_SOT				(1 << 0)
#define AXI_DMAC_IRQ_EOT				(1 << 1)
```

| DMA Address               | offset | tip         |
| ------------------------- | ------ | ----------- |
| AXI_DMAC_REG_DEST_ADDRESS | 0x410  | DMA目的地址 |
| AXI_DMAC_REG_SRC_ADDRESS  | 0x414  | DMA源地址   |

## 四、PL MEM

| physical address |                  |
| ---------------- | ---------------- |
| 0x4000 0000      | PL端内存起始地址 |
| ...              |                  |
| 0x4800 0000      | 每个块128MB      |
| ...              |                  |
| ...              |                  |
| 0x8000 0000      | 1GB              |

## 五、PS MEM

| physical address |                  |
| ---------------- | ---------------- |
| 0x0000 0000      | PS端内存起始地址 |
| ...              |                  |
| 0x4000 0000      | 1GB              |