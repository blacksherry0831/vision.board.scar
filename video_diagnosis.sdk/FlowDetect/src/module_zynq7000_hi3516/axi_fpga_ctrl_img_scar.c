#include "axi_fpga_ctrl_img_scar.h"
/*-----------------------------------*/
#include "axi_fpga_ctrl.h"
/*-----------------------------------*/
#include "def_hw_zynq7000_hi3516_axi_scar.h"
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int fpga_img_scar_detect_reset()
{
	 const int addr_rst= ADDR_SCAR_DETECT_RST;
	 return FPGA_CTRL_send_int_1_0(addr_rst);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int fpga_img_scar_detect_mode(int _mode)
{
	 return FPGA_CTRL_send_int(ADDR_SCAR_DETECT_MODE,_mode);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int fpga_img_scar_detect_start_en()
{
	 	 const int addr_rst= ADDR_SCAR_DETECT_START_EN;
	 	 return FPGA_CTRL_send_int_1_0(addr_rst);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int fpga_img_scar_detect_set_mask_addr(int _addr_zone,int _addr_idx)
{
	assert(_addr_zone>=0 &&_addr_zone<8);
	assert(_addr_idx>=0 &&_addr_idx<48);

			FPGA_CTRL_send_int(ADDR_SCAR_DETECT_MASK_ADDR_H,_addr_zone);
	return 	FPGA_CTRL_send_int(ADDR_SCAR_DETECT_MASK_ADDR_L,_addr_idx);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int fpga_img_scar_detect_set_g_th_up(int _th)
{
	 return FPGA_CTRL_send_int(ADDR_SCAR_DETECT_G_UP_TH,_th);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int fpga_img_scar_detect_set_g_th_down(int _th)
{
	 return FPGA_CTRL_send_int( ADDR_SCAR_DETECT_G_DOWN_TH,_th);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int fpga_img_scar_detect_set_row_th_up(int _th)
{
	 return FPGA_CTRL_send_int(ADDR_SCAR_DETECT_ROW_UP_TH,_th);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int fpga_img_scar_detect_set_row_th_down(int _th)
{
	 return FPGA_CTRL_send_int(ADDR_SCAR_DETECT_ROW_DOWN_TH,_th);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int fpga_img_scar_detect_set_col_th_up(int _th)
{
	 return FPGA_CTRL_send_int(ADDR_SCAR_DETECT_COL_UP_TH,_th);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int fpga_img_scar_detect_set_col_th_down(int _th)
{
	 return FPGA_CTRL_send_int(ADDR_SCAR_DETECT_COL_DOWN_TH,_th);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
