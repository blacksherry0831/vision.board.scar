#ifndef _AXI_FPGA_CTRL_IMG_SCAR_H
#define _AXI_FPGA_CTRL_IMG_SCAR_H
/*-----------------------------------*/
#include "linux_header.h"
/*-----------------------------------*/
#include "def_img_space_scar.h"
/*-----------------------------------*/
#include "img_cfg/scar_cfg.h"
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
int fpga_img_scar_detect_mode(int _mode);
int fpga_img_scar_detect_start_en();
/*-----------------------------------*/
int fpga_img_scar_detect_set_mask_addr(int _addr_zone,int _addr_idx);
/*-----------------------------------*/
int fpga_img_scar_detect_montage(const int _en);
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
int fpga_img_scar_detect_set_mask_addr_1(const int _ch);
/*-----------------------------------*/
void scar_cvt(int _org,const int _fi);
void set_mask_seq_param(const int _fi);
int fpga_scar_is_busy();
int fpga_img_scar_reset();
/*-----------------------------------*/
#endif
