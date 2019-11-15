#include "axi_fpga_ctrl_img_scar.h"
/*-----------------------------------*/
#include "axi_fpga_ctrl.h"
/*-----------------------------------*/
#include "task/task_sync.h"
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
int fpga_img_scar_detect_set_mask_addr_1(const int _ch)
{
	const int _addr_zone=_ch%SCAR_IMG_MASK_CHANNEL_MAX;
	const int _addr_idx=_ch/SCAR_IMG_MASK_CHANNEL_MAX;

	return fpga_img_scar_detect_set_mask_addr(_addr_zone,_addr_idx);
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
int fpga_img_scar_reset()
{
	return 	 FPGA_CTRL_send_int_1_0(ADDR_OUTSIDE_RESET);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int fpga_scar_is_busy()
{
	int  iTemp=1;
	int* piTemp=&iTemp;


	if(FPGA_CTRL_read(ADDR_OUTSIDE_BUSY, piTemp)){

		if(iTemp==1){
			return TRUE;//busy
		}else{
			return FALSE;//free
		}


	}


	return -1;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int wait4FpgaScarConvertDone()
{
    int result_t=FALSE;

		while(IsRun()){

			if(fpga_scar_is_busy()==TRUE){

				sleep_1ms();
			}else{
				result_t=TRUE;//now free
				break;
			}

		}

	return result_t;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void set_mask_seq_param(const int _fi)
{

	const int sno=GetScarCurrentSerialNumber();

	if(sno==0xffffffff){

		fpga_img_scar_detect_set_mask_addr_1(0);
		fpga_img_scar_detect_mode(0);

	}else{

		const int mask_ch=GetMaskSeqChannel(_fi);

		const int work_mode=GetMaskSeq_work_mode(_fi);

		const int g_th_up=GetMaskSeq_g_th_up(_fi);
		const int g_th_down=GetMaskSeq_g_th_down(_fi);

		const int row_th_up=GetMaskSeq_row_th_up(_fi);
		const int row_th_down=GetMaskSeq_row_th_down(_fi);

		const int col_th_up=GetMaskSeq_col_th_up(_fi);
		const int col_th_down=GetMaskSeq_col_th_down(_fi);


		fpga_img_scar_detect_set_mask_addr_1(mask_ch);

		fpga_img_scar_detect_mode(work_mode);
		/*-----------------------------------*/
		fpga_img_scar_detect_set_g_th_up(g_th_up);
		fpga_img_scar_detect_set_g_th_down(g_th_down);
		/*-----------------------------------*/
		fpga_img_scar_detect_set_row_th_up(row_th_up);
		fpga_img_scar_detect_set_row_th_down(row_th_down);
		/*-----------------------------------*/
		fpga_img_scar_detect_set_col_th_up(col_th_up);
		fpga_img_scar_detect_set_col_th_down(col_th_down);

	}

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void scar_cvt(int _org,const int _fi)
{
	wait4FpgaScarConvertDone();
	{
		if(_org){

			fpga_img_scar_detect_reset();
			fpga_img_scar_detect_mode(0);
		}else{
			set_mask_seq_param(_fi);
		}

			fpga_img_scar_detect_start_en();
	}
	wait4FpgaScarConvertDone();
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
