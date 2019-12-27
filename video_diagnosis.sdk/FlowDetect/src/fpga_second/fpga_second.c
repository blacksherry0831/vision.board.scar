#include "fpga_second.h"

/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void outside_second()
{


	wait4FpgaConvertDone();

	fpga_set_second_part();

	fpga_set_sigma_up(GetSigmaUp());
	fpga_set_sigma_down(GetSigmaDown());

//**********************************************
// 5 - ´¥·¢¹¤×÷ £¨Âö³å£©
//**********************************************
	fpga_start();


	wait4FpgaConvertDone();


	return;
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
		fpga_img_scar_detect_reset();

			if(_org){
				fpga_img_scar_detect_mode(0);
				fpga_img_scar_detect_set_mask_addr_1(0);
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
