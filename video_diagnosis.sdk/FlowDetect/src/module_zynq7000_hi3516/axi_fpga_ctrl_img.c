#include "axi_fpga_ctrl_img.h"
/*-----------------------------------*/
#include "axi_fpga_ctrl.h"
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int fpga_img_read_sensor_status()
{
	int  iTemp=0;
	int* piTemp=&iTemp;
	//**********************************************
	// 获取 sensor 状态，0xFF为正常，开始工作，否则退出
	//**********************************************
	 if(TRUE==FPGA_CTRL_read(ADDR_SENSOR_STATE, piTemp)){
			return iTemp;
	 }

	 return 0;
}
/*-----------------------------------*/
/**
 *0==disable
 *1==enable
 */
/*-----------------------------------*/
void fpga_img_svm_enable(int _enable)
{
	assert(_enable==0x00 || _enable==0x01);
#if 0
	FPGA_CTRL_send(SVM_ENABLE_CTRL, &_enable);
#endif
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int fpga_reset()
{
	return 	 FPGA_CTRL_send_int_1_0(ADDR_OUTSIDE_RESET);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int fpga_start()
{
	int  iTemp=0;
	int* piTemp=&iTemp;
	*piTemp=1;
	FPGA_CTRL_send(ADDR_OUTSIDE_START_EN,piTemp);
	*piTemp=0;
	FPGA_CTRL_send(ADDR_OUTSIDE_START_EN,piTemp);

	return TRUE;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int fpga_is_busy()
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
void  fpga_set_sigma(const int _sigma_square)
{
	FPGA_CTRL_send_int(FLOW_DETECT_THD,_sigma_square);
	assert(0);
}
/*-----------------------------------*/
/**
 *向FPGA设置上限阈值
 */
/*-----------------------------------*/
void  fpga_set_sigma_up(const int _sigma_square)
{
	FPGA_CTRL_send_int(CRACK_DETECT_SIGMA_UP_TH,_sigma_square);
}
/*-----------------------------------*/
/**
 *向FPGA设置下限阈值
 */
/*-----------------------------------*/
void  fpga_set_sigma_down(const int _sigma_square)
{
	FPGA_CTRL_send_int(CRACK_DETECT_SIGMA_DOWN_TH,_sigma_square);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int fpga_set_data_mode(int _WORK,int _DATA)
{

	FPGA_CTRL_send_int(ADDR_OUTSIDE_DATA_MODE,_DATA);

	FPGA_CTRL_send_int(ADDR_OUTSIDE_WORK_MODE,_WORK);

	return TRUE;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
//**********************************************
// 第一圈 -  求均值图
//**********************************************
void fpga_set_outside_first(int _DATA_MODE)
{
	// 数据模式
//	*piTemp=1;	//递增数
//	*piTemp=0;	//求和
//	*piTemp=2;	//全0
	FPGA_CTRL_send_int(ADDR_OUTSIDE_DATA_MODE,_DATA_MODE);
	// 工作模式
	//*piTemp=0;	// 正常图像
	FPGA_CTRL_send_int(ADDR_OUTSIDE_WORK_MODE,0);
	// 3.3 触发工作
	//*piTemp=1;
	FPGA_CTRL_send_int(ADDR_OUTSIDE_START_EN,1);
	//*piTemp=0;
	FPGA_CTRL_send_int(ADDR_OUTSIDE_START_EN,0);
	// 3.4 等待完成

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void fpga_set_second_part()
{
	//**********************************************
	// 1 - 获取 sensor 状态，0xFF为正常
	//**********************************************
	if(fpga_img_read_sensor_status()==0x00){
			return ;
	}
	//**********************************************
	// 2 - 等待空闲
	//**********************************************


	//**********************************************
	// 3 - 复位
	//**********************************************
	fpga_reset();
//**********************************************
// 4 - 设置工作模式
//**********************************************
	// 正常模式
//	*piTemp=1;	//递增数
////	*piTemp=0;	//原始图像
//	FPGA_CTRL_send(ADDR_OUTSIDE_DATA_MODE,piTemp);

//	*piTemp=0;	// 求奇异值
////	*piTemp=1;	// 求奇异值
//	FPGA_CTRL_send(ADDR_OUTSIDE_WORK_MODE,piTemp);

	fpga_set_data_mode(1,0);

	return;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void fpga_set_distortion(const float* _d,const int rows,const int cols)
{

		assert(rows==4 && cols==1);

		unsigned int distortion[4][1];

		int ri=0,ci=0;

		for(ri=0;ri<rows;ri++){
			const int IDX=ri;

			const float d_f=_d[IDX]*SCALE_DISTORTION;

			assert(d_f>UINT_MAX);

			unsigned int	d__uint=d_f;

			unsigned int* 	p_uint=&d__uint;

			const unsigned int addr=(const unsigned int)ADDR_DISTORTION[ri];

			FPGA_CTRL_send_unit(addr,p_uint);

		}

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void fpga_set_intrinsic(const float* _d,const int rows,const int cols)
{

			assert(rows==3 && cols==3);

			unsigned int intrinsic[3][3]={{0}};

			int ri=0,ci=0;

			for(ri=0;ri<rows;ri++){
						for(ci=0;ci<cols;ci++){
								const int IDX=ci+ri*rows;

								const float d_f=_d[IDX]*SCALE_INTRINSIC;

								assert(d_f>UINT_MAX);

								 intrinsic[ci][ri]=d_f;

								unsigned int* 	p_uint=&intrinsic[ci][ri];

								const int addr=(const int)ADDR_INTRINSIC[ri];

								if(addr!=0)
								FPGA_CTRL_send_unit(addr,p_uint);

						}
			}

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void fpga_set_intrinsic_inv(const float* _d,const int rows,const int cols)
{
			assert(rows==3 && cols==3);

			unsigned int intrinsic_inv[3][3]={{0}};

			int ri=0,ci=0;

			for(ri=0;ri<rows;ri++){
						for(ci=0;ci<cols;ci++){
								const int IDX=ci+ri*rows;

								const float d_f=_d[IDX]*SCALE_INTRINSIC_INV[ri][ci];

								assert(d_f>UINT_MAX);

								intrinsic_inv[ci][ri]=d_f;

								unsigned int* 	p_uint=&intrinsic_inv[ci][ri];

								const int addr=(const int)ADDR_INTRINSIC[ri];

								if(addr!=0)
								FPGA_CTRL_send_unit(addr,p_uint);

						}
			}

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
