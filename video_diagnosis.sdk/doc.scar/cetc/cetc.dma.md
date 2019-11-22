# FPGA程序设计说明

单目视频图像处理模块中FPGA芯片的外设接收主要有QSPI、UART、ENET、GPIO、DDR等，如下图所示。FPGA芯片主要完成BT1120数据的采集，处理和传输功能，并未调试提供RS232接口。

##  1	FPGA程序设计方案

FPGA程序可以工作在两种数据流模式：在线模式和离线模式。在线模式：实时采集BT1120数据，经过预处理后存储在PL DDR中，便于后期图像处理，处理后的图像数据可以通过PL DDR搬移到PS DDR中，然后通过网络传输。离线模式用于模拟在线模式，该模式下从外界通过网络传入的图像数据。

## 2    up_video_common控制模块

up_video_common模块主要是为bt1120模块提供一些控制信号。

up_video_common模块基地址0x83C10000

| 地址  | 名称             | 类型 | 默认值     | 描述                                                |
| ----- | ---------------- | ---- | ---------- | --------------------------------------------------- |
| 0x000 | 版本寄存器       | RO   | 0x58010061 | 程序版本                                            |
| 0x004 | ID寄存器         | RW   | 0x0        |                                                     |
| 0x008 | 测试寄存器       | RW   | 0x0        | 读写测试寄存器                                      |
| 0x040 | 使能寄存器       | RW   | 0x0        | 0：不工作  1：使能，开始采集数据                    |
| 0x060 | 时钟计数器       | RO   | 0x0        | 用于估算BT1120时钟频率  ((X*100MHz +  0x7FFF)>>16)M |
| 0x068 | sensor状态寄存器 | RO   | 0x0        | 指示sensor的工作状态，1时正常                       |
| 0x072 | 数据选择寄存器   | RW   | 0x0        | 0：sensor数据  1：PC端数据                          |
| 0x0B8 | 控制输入寄存器   | RW   | 0x0        | 用于输出控制信号                                    |
| 0x0BC | 控制状态寄存器   | RW   | 0x0        | 用于读取状态信号                                    |

## 3  DMAC模块

AXI DMAC是一个高速、高吞吐量的通用DMA控制器，用于系统内存空间和其它外置之间的数据传输。DMA（Direct Memory Access）是指外部设备不通过CPU而直接与系统内存交换数据的技术接口。

要把外设的数据读入内存或把内存的数据传送到外设，一般都要通过CPU控制完成，如CPU程序查询或中断方式。利用中断进行数据传送，可以大大提高CPU的利用率。但是采用中断传送有它的缺点，对于一个高速I/O设备，以及批量交换数据的情况，只能采用DMA方式，才能解决效率和速度问题。DMA在外设与内存间直接进行数据交换，而不通过CPU，这样数据传送的速度就取决于存储器和外设的工作速度。

在PS和PL需要进行批量交换数据的情况下，我们就可以使用DMA方式来处理，目前下位机我们使用的是PL端的DMA控制器，可以直接访问PS端的DDR，并且输入源接到lvds的输出，输入采用的是流模式。

### DMA控制模块基地址0x83C10000

| ~~DMA模块~~ | ~~基地址~~     | ~~中断号~~ | ~~数据源~~                        | ~~数据目的~~                      |
| :---------- | -------------- | ---------- | --------------------------------- | --------------------------------- |
| ~~DMAC0~~   | ~~0x83C00000~~ | ~~58~~     | ~~PL DDR  0x40000000-0x7FFFFFFF~~ | ~~PS DDR  0x00000000-0x3FFFFFFF~~ |
| ~~DMAC1~~   | ~~0x83C20000~~ | ~~57~~     | ~~数据流~~                        | ~~PL DDR  0x40000000-0x7FFFFFFF~~ |
| ~~DMAC2~~   | ~~0x83C30000~~ | ~~59~~     | ~~PS DDR  0x00000000-0x3FFFFFFF~~ | ~~数据流~~                        |
| ~~DMAC3~~   | ~~0x83C40000~~ | ~~56~~     | ~~PS DDR  0x00000000-0x3FFFFFFF~~ | ~~PL DDR  0x40000000-0x4FFFFFFF~~ |

| DMA模块 | 基地址     | 中断号 | 数据源                        | 数据目的                      |
| ------- | ---------- | ------ | ----------------------------- | ----------------------------- |
| DMAC0   | 0x83C00000 | 58     | PL DDR  0x40000000-0x7FFFFFFF | PS DDR  0x00000000-0x3FFFFFFF |
| DMAC1   | 0x83C10000 | 57     | PS DDR  0x00000000-0x3FFFFFFF | PL DDR  0x40000000-0x4FFFFFFF |

### DMA控制模块内部地址描述见下表

| **地址** | **名称**           | **类型**        | **默认值** | **描述**                     |                              |
| -------- | ------------------ | --------------- | ---------- | ---------------------------- | ---------------------------- |
| 0x000    | 版本号             | RO              | 0x00040062 |                              |                              |
|          | [31:16]            | VERSION_MAJOR   | RO         | 0x0004                       |                              |
| [15:8]   | VERSION_MINOR      | RO              | 0x00       |                              |                              |
| [7:0]    | VERSION_PATCH      | RO              | 0x62       |                              |                              |
| 0x004    | PERIPHERAL_ID      | RO              |            | ID                           |                              |
| 0x008    | SCRATCH            | RW              | 0x00000000 | 读写测试寄存器               |                              |
| 0x00c    | IDENTIFICATION     | RO              | 0x444d4143 | 外设ID('D',  'M', 'A', 'C'). |                              |
| 0x080    | IRQ_MASK           | RW              | 0x00000003 | 中断屏蔽                     |                              |
|          | [31:2]             | Reserved        | RO         | 0x00                         |                              |
| [1]      | TRANSFER_COMPLETED | RW              | 0x0        |                              |                              |
| [0]      | TRANSFER_QUEUED    | RW              | 0x0        |                              |                              |
| 0x084    | IRQ_PENDING        | RW1C-V          | 0x00000000 | 挂起和使能中断               |                              |
|          | [31:2]             | Reserved        | RO         | 0x00                         |                              |
| [1]      | TRANSFER_COMPLETED | RW1C-V          | 0x0        |                              |                              |
| [0]      | TRANSFER_QUEUED    | RW1C-V          | 0x0        |                              |                              |
| 0x088    | IRQ_SOURCE         | RW1C-V          | 0x00000000 | 挂起中断                     |                              |
|          | [31:2]             | Reserved        | RO         | 0x00                         |                              |
| [1]      | TRANSFER_COMPLETED | RW1C-V          | 0x0        |                              |                              |
| [0]      | TRANSFER_QUEUED    | RW1C-V          | 0x0        |                              |                              |
| 0x400    | CONTROL            | RW              | 0x00000000 | 传输控制                     |                              |
|          | [31:2]             | Reserved        | RO         | 0x00                         |                              |
| [1]      | PAUSE              | RW              | 0x0        | 暂停当前传输                 |                              |
| [0]      | ENABLE             | RW              | 0x0        | 使能DMA通道.                 |                              |
| 0x404    | TRANSFER_ID        | RO              | 0x00000000 | ID of the next transfer.     |                              |
|          | [31:5]             | Reserved        | RO         | 0x00                         |                              |
| [4:0]    | TRANSFER_ID        | RO              | 0x0        | ID of the next transfer.     |                              |
| 0x408    | TRANSFER_SUBMIT    | RW1S            | 0x00000000 | 提交一个传输                 |                              |
|          | [31:1]             | Reserved        | RO         | 0x00                         |                              |
| [0]      | TRANSFER_SUBMIT    | RW1S            | 0x0        | 排队一个新的传输             |                              |
| 0x40C    | FLAGS              | RW              | 0x00000000 | 传输标志.                    |                              |
|          | [31:2]             | Reserved        | RO         | 0x00                         |                              |
| [1]      | LAST               | RW              | 0x0        | 传输产生的 TLAST 信号.       |                              |
| [0]      | CYCLIC             | RW              | 0x0        | 传输类型是cyclic.            |                              |
| 0x410    | DEST_ADDRESS       | RW              | 0x00000000 | 传输目的地址                 |                              |
|          | [31:0]             | DEST_ADDRESS    | RW         | 0x00000000                   | 传输目的地址                 |
| 0x414    | SRC_ADDRESS        | RW              | 0x00000000 | 传输的源地址.                |                              |
|          | [31:0]             | SRC_ADDRESS     | RW         | 0x00000000                   | 传输的源地址.                |
| 0x418    | X_LENGTH           | RW              | 0x00000000 | 传输的 X-length.             |                              |
|          | [31:24]            | Reserved        | RO         | 0x00                         |                              |
| [23:0]   | X_LENGTH           | RW              | 0x000000   | 传输的X-length.              |                              |
| 0x41C    | Y_LENGTH           | RW              | 0x00000000 | 传输的Y-length.              |                              |
|          | [31:24]            | Reserved        | RO         | 0x00                         |                              |
| [23:0]   | Y_LENGTH           | RW              | 0x000000   | 传输的Y-length.              |                              |
| 0x420    | STRIDE             | RW              | 0x00000000 | Transfer stride.             |                              |
|          | [31:24]            | Reserved        | RO         | 0x00                         |                              |
| [23:0]   | STRIDE             | RW              | 0x000000   | Transfer stride.             |                              |
| 0x424    | TRANSFER_DONE      | RO              | 0x00000000 | Transfer done bitmap.        |                              |
|          | [31]               | TRANSFER_DONE31 | RO         | 0x0                          | 指示传输ID为31的传输是否完成 |
| …        |                    |                 |            |                              |                              |
| [1]      | TRANSFER_DONE1     | RO              | 0x0        | 指示传输ID为1的传输是否完成  |                              |
| [0]      | TRANSFER_DONE0     | RO              | 0x0        | 指示传输ID为0的传输是否完成  |                              |
| 0x428    | ACTIVE_TRANSFER_ID | RO              | 0x00000000 | 当前传输ID                   |                              |
| [4:0]    | ACTIVE_TRANSFER_ID | RO              | 0x0        | 当前传输ID                   |                              |