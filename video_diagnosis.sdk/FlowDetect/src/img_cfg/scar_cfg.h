#ifndef _SCAR_CFG_H_
#define _SCAR_CFG_H_
/*-----------------------------------*/
#include "linux_header.h"
#include "def.h"
#include "def_app.h"
/*-----------------------------------*/
#include "modules_ex/base.h"
#include "modules_ex/cmd_scar.h"
/*-----------------------------------*/
#include "module_zynq7000_hi3516/axi_fpga_ctrl_img_scar.h"
/*-----------------------------------*/
typedef struct scar_threshold{

	int		global_th_up;
	int		global_th_down;
	int		row_th_up;
	int 	row_th_down;
	int		col_th_up;
	int		col_th_down;

}SCAR_THRESHOLD;
/*-----------------------------------*/
typedef struct scar_param{

	SCAR_THRESHOLD  scar_th;

	int		work_mode;


}SCAR_PARAM;
/*-----------------------------------*/
typedef struct scar_mask_one{

	int     mask_id;

	SCAR_THRESHOLD  scar_th;

	int		work_mode;


}SCAR_MASK_ONE;
/*-----------------------------------*/
typedef struct scar_nask_seq{

	int				 mask_seq_num;
	int				 mask_seq_loop;
	int				 mask_seq_montage;
	SCAR_MASK_ONE    mask_seq[SCAR_IMG_MASK_SQE_MAX];

}SCAR_MASK_SEQ;
/*-----------------------------------*/
#define MAX_DETECT_SNO	(20)
/*-----------------------------------*/
typedef struct scar_nask_seq_multi{

	int				 mask_sno;
	SCAR_MASK_SEQ	 mask_seqs[MAX_DETECT_SNO];

}SCAR_MASK_SEQ_MULTI;
/*-----------------------------------*/
void SetScarCurrentMask(
		const int _sno,
		const unsigned int* 	_mask_seq,
		const int				_num,
		const int  				_loop,
		const int  				_seq_montage);
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
void SetScarMontage2FPGA(const int _en);

void SetScarMontage2FPGA_Frame(const int _fi,const int _en);
/*-----------------------------------*/
void SetScarGlobalThresholdUp2FPGA(const int _th);
void SetScarGlobalThresholdDown2FPGA(const int _th);
void SetScarRowThresholdUp2FPGA(const int _th);
void SetScarRowThresholdDown2FPGA(const int _th);
void SetScarColThresholdUp2FPGA(const int _th);
void SetScarColThresholdDown2FPGA(const int _th);
/*-----------------------------------*/
int GetScarMaskChannel_Total_Num();
int GetScarMaskSeqChannel_Is_Loop();
int GetScarMaskSeq_Is_Montage();
int GetScarMaskSeq_SNO();
/*-----------------------------------*/
void SetScarCurrentSerialNumber(
		const int	_sno);
/*-----------------------------------*/
void SetScarCurrentSerialNumber_default();
/*-----------------------------------*/

int GetMaskSeqChannel(const int _idx);
int GetMaskSeq_work_mode(const int _idx);
int GetMaskSeq_g_th_up(const int _idx);
int GetMaskSeq_g_th_down(const int _idx);
int GetMaskSeq_row_th_up(const int _idx);
int GetMaskSeq_row_th_down(const int _idx);
int GetMaskSeq_col_th_up(const int _idx);
int GetMaskSeq_col_th_down(const int _idx);
/*-----------------------------------*/

/*-----------------------------------*/
#endif
