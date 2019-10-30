#ifndef _SCAR_CFG_H_
#define _SCAR_CFG_H_
/*-----------------------------------*/
#include "linux_header.h"
#include "def.h"
/*-----------------------------------*/
#include "modules_ex/base.h"
/*-----------------------------------*/
/*-----------------------------------*/
typedef struct scar_param{

	int		work_mode;
	int		global_th_up;
	int		global_th_down;
	int		row_th_up;
	int 	row_th_down;
	int		col_th_up;
	int		col_th_down;

}SCAR_PARAM;
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
void SetScarGlobalThresholdUp2FPGA(const int _th);
void SetScarGlobalThresholdDown2FPGA(const int _th);
void SetScarRowThresholdUp2FPGA(const int _th);
void SetScarRowThresholdDown2FPGA(const int _th);
void SetScarColThresholdUp2FPGA(const int _th);
void SetScarColThresholdDown2FPGA(const int _th);
/*-----------------------------------*/
#endif
