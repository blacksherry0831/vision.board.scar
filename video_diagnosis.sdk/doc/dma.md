# DMA

## 1.寄存器配置

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

| DMA Address               | offset | physical address |
| ------------------------- | ------ | ---------------- |
| AXI_DMAC_REG_DEST_ADDRESS | 0x410  |                  |
| AXI_DMAC_REG_SRC_ADDRESS  | 0x414  |                  |

## 2.DMA配置

### 2.1DMA ,PL->PS

#### 2.1.1 DMA CFG

```c++
#define PL_RX_DMA_BASEADDR 0x83c00000
#define PL_RX_DMA_MMAP_LENGTH 0x1000
```

| physical address |                    |                |
| ---------------- | ------------------ | -------------- |
| 0x83c0 0000      | PL_RX_DMA_BASEADDR | DMA基地址      |
| ...              |                    | DMA 配置寄存器 |
| 0x83c0 1000      |                    | 4KB            |

#### 2.1.2 DMA DEST MEM

```
#define PS_DDR_PHYADDR_FOR_DMA 	0x1E000000
#define PS_DDR_LENGTH_FOR_DMA 	 0x2000000
```

| physical address |                        |                       |
| ---------------- | ---------------------- | --------------------- |
| 0x1E00 0000      | PS_DDR_PHYADDR_FOR_DMA |                       |
| ...              |                        | DMA目的地址，暂存图像 |
| 0x2000 0000      |                        | 32MB=16*2MB           |

## 2.2 DMA,PS->PL

#### 2.2.1 DMA CFG

```c++
#define PL_RX_DMA_BASEADDR 
#define PL_RX_DMA_MMAP_LENGTH 
```

| physical address |      |                |
| ---------------- | ---- | -------------- |
|                  |      | DMA基地址      |
| ...              |      | DMA 配置寄存器 |
|                  |      |                |

#### 2.2.2 DMA DEST MEM

```c++
#define PS_DDR_PHYADDR_FOR_DMA 	 0x
#define PS_DDR_LENGTH_FOR_DMA 	 0x
```

| physical address |      |                       |
| ---------------- | ---- | --------------------- |
|                  |      |                       |
| ...              |      | DMA目的地址，暂存图像 |
|                  |      |                       |

## 4.PL MEM

| physical address |       |
| ---------------- | ----- |
| 0x4000 0000      |       |
| ...              |       |
| 0x4800 0000      | 128MB |
| ...              |       |
| ...              |       |
| 0x8000 0000      | 1GB   |

