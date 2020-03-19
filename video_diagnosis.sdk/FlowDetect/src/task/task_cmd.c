#include "task_cmd.h"
/*-----------------------------------*/
/**
 *设置FPGA和DMA的工作模式（原图？原尺寸）
 */
/*-----------------------------------*/
int SetFpgaCircleWorkMode(int _wm)
{

	setFpgaCircleWorkMode(_wm);  //设置FPGA的工作模式（原图？原尺寸）

	SetDmaFrameByWorkMode(_wm);  //设置DMA的工作模式（原图？原尺寸）

	return 1;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
