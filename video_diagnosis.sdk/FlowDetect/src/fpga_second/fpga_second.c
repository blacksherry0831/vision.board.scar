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
	sensor_state();
	wait4FpgaConvertDone();
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
	wait4FpgaConvertDone();
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void scar_cvt_cost_time(int _org,const int _fi)
{
					static int FPGA_COUNT=0;
#if defined(_DEBUG) && defined(_DEBUG_WF)
					TIME_START();
#endif

					scar_cvt(_org,_fi);

#if defined(_DEBUG) && defined(_DEBUG_WF)
					PRINTF_DBG_EX("FPGA:%d___",FPGA_COUNT++);
#endif

#if defined(_DEBUG) && defined(_DEBUG_WF)
					TIME_END("1> FPGA Convert cost time : ");
#endif
}
