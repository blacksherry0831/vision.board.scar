#ifndef _SCAR_CFG_H_
#define _SCAR_CFG_H_
/*-----------------------------------*/
#include "linux_header.h"
#include "def.h"
/*-----------------------------------*/
#include "modules_ex/base.h"
/*-----------------------------------*/
#include "module_zynq7000_hi3516/axi_fpga_ctrl_img_scar.h"
/*-----------------------------------*/
typedef struct scar_param{

	int		work_mode;
	int		global_th_up;
	int		global_th_down;
	int		row_th_up;
	int 	row_th_down;
	int		col_th_up;
	int		col_th_down;
	int     current_mask_seq[SCAR_IMG_MASK_SQE_MAX];

}SCAR_PARAM;
/*-----------------------------------*/
void SetScarCurrentMask(
		const int* 	_mask_seq,
		const int	_num);
/*-----------------------------------*/
void SetScarCurrentMask_Cmd(const CMD_CTRL* const  _cmd);
/*-----------------------------------*/
int GetScarWorkMode();
int GetScarGlobalThresholdUp();
int GetScarGlobalThresholdDown();
int GetScarRowThresholdUp();
int GetScarRowThresholdDown();
int GetScarColThresholdUp();
int GetScarColThresholdDown();
/*-----------------------------------*/
void SetScarWorkMode2FPGA(const int _th);
/*-----------------------------------*/
void SetScarGlobalThresholdUp2FPGA(const int _th);
void SetScarGlobalThresholdDown2FPGA(const int _th);
void SetScarRowThresholdUp2FPGA(const int _th);
void SetScarRowThresholdDown2FPGA(const int _th);
void SetScarColThresholdUp2FPGA(const int _th);
void SetScarColThresholdDown2FPGA(const int _th);
/*-----------------------------------*/
#endif
