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
	int  iTemp=0;
	//**********************************************
	// 复位
	//**********************************************
	// 2.1 复位
	 iTemp=1;
	 FPGA_CTRL_send(ADDR_OUTSIDE_RESET,&iTemp);
	 iTemp=0;
	 FPGA_CTRL_send(ADDR_OUTSIDE_RESET,&iTemp);

	return TRUE;
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
void  fpga_set_sigma(const int sigma)
{
	int  iTemp=sigma;
	int* piTemp=&iTemp;

	FPGA_CTRL_send(FLOW_DETECT_THD,piTemp);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int fpga_set_data_mode(int _WORK,int _DATA)
{
	int  iTemp;
	int* piTemp=&iTemp;
	*piTemp=_DATA;	//原始图像
	FPGA_CTRL_send(ADDR_OUTSIDE_DATA_MODE,piTemp);

	//	*piTemp=0;	// 求奇异值
	*piTemp=_WORK;	// 求奇异值
	FPGA_CTRL_send(ADDR_OUTSIDE_WORK_MODE,piTemp);

	return TRUE;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int fpga_set_work_mode(int _WORK,int _DATA)
{

	if(fpga_img_read_sensor_status()==0x00){
		return FALSE;
	}


	if(fpga_reset()==FALSE){
		return FALSE;
	}

	fpga_set_data_mode(_WORK,_DATA);

	fpga_start();

	// 等待完成

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
void fpga_set_outside_first(int DATA_MODE)
{
	int  iTemp;
	int* piTemp=&iTemp;

	// 数据模式
//	*piTemp=1;	//递增数
//	*piTemp=0;	//求和
//	*piTemp=2;	//全0
	*piTemp=DATA_MODE;
	FPGA_CTRL_send(ADDR_OUTSIDE_DATA_MODE,piTemp);
	// 工作模式
	*piTemp=0;	// 正常图像
	FPGA_CTRL_send(ADDR_OUTSIDE_WORK_MODE,piTemp);
	// 3.3 触发工作
	*piTemp=1;
	FPGA_CTRL_send(ADDR_OUTSIDE_START_EN,piTemp);
	*piTemp=0;
	FPGA_CTRL_send(ADDR_OUTSIDE_START_EN,piTemp);
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

	fpga_set_work_mode(1,0);

	return;
}
