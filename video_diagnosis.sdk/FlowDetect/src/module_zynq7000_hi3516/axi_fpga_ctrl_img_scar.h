#ifndef AXI_FPGA_CTRL_IMG_SCAR_H
#define AXI_FPGA_CTRL_IMG_SCAR_H
/*-----------------------------------*/
#include "linux_header.h"
/*-----------------------------------*/
#define 	SCAR_IMG_MASK_CHANNEL_MAX		(8)
#define 	SCAR_IMG_MASK_FRAME_MAX			(48)
#define 	SCAR_IMG_MASK_SQE_MAX			(SCAR_IMG_MASK_CHANNEL_MAX*SCAR_IMG_MASK_FRAME_MAX)
/*-----------------------------------*/
#define SCAR_DETECT_MODE_GLOBAL		(1)
#define SCAR_DETECT_MODE_ROW		(1<<1)
#define SCAR_DETECT_MODE_COL		(1<<2)
#define SCAR_DETECT_MODE_ORG		(0)
/*-----------------------------------*/
/**
 *
 *
 */
/*-----------------------------------*/
int fpga_img_scar_detect_reset();
int fpga_img_scar_detect_start_en();
int fpga_img_scar_detect_set_mask_addr(int _addr_zone,int _addr_idx);
/*-----------------------------------*/
int fpga_img_scar_detect_mode(int _mode);
/*-----------------------------------*/
int fpga_img_scar_detect_set_g_th_up(int _th);
int fpga_img_scar_detect_set_g_th_down(int _th);
/*-----------------------------------*/
int fpga_img_scar_detect_set_row_th_up(int _th);
int fpga_img_scar_detect_set_row_th_down(int _th);
/*-----------------------------------*/
int fpga_img_scar_detect_set_col_th_up(int _th);
int fpga_img_scar_detect_set_col_th_down(int _th);
/*-----------------------------------*/
void scar_cvt(int _org,const int _fi);
/*-----------------------------------*/
#endif
