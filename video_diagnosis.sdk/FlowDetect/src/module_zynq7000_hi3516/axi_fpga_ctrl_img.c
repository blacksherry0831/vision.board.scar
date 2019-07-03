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
	int  iTemp;
	int* piTemp=&iTemp;
	//**********************************************
	// ��ȡ sensor ״̬��0xFFΪ��������ʼ�����������˳�
	//**********************************************
	return FPGA_CTRL_read(ADDR_SENSOR_STATE, piTemp);
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
	// ��λ
	//**********************************************
	// 2.1 ��λ
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
	*piTemp=_DATA;	//ԭʼͼ��
	FPGA_CTRL_send(ADDR_OUTSIDE_DATA_MODE,piTemp);

	//	*piTemp=0;	// ������ֵ
	*piTemp=_WORK;	// ������ֵ
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

	// �ȴ����

	return TRUE;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
//**********************************************
// ��һȦ -  ���ֵͼ
//**********************************************
void fpga_set_outside_first(int DATA_MODE)
{
	int  iTemp;
	int* piTemp=&iTemp;

	// ����ģʽ
//	*piTemp=1;	//������
//	*piTemp=0;	//���
//	*piTemp=2;	//ȫ0
	*piTemp=DATA_MODE;
	FPGA_CTRL_send(ADDR_OUTSIDE_DATA_MODE,piTemp);
	// ����ģʽ
	*piTemp=0;	// ����ͼ��
	FPGA_CTRL_send(ADDR_OUTSIDE_WORK_MODE,piTemp);
	// 3.3 ��������
	*piTemp=1;
	FPGA_CTRL_send(ADDR_OUTSIDE_START_EN,piTemp);
	*piTemp=0;
	FPGA_CTRL_send(ADDR_OUTSIDE_START_EN,piTemp);
	// 3.4 �ȴ����

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void fpga_set_second_part()
{
	//**********************************************
	// 1 - ��ȡ sensor ״̬��0xFFΪ����
	//**********************************************
	if(fpga_img_read_sensor_status()==0x00){
			return ;
	}
	//**********************************************
	// 2 - �ȴ�����
	//**********************************************


	//**********************************************
	// 3 - ��λ
	//**********************************************
	fpga_reset();
//**********************************************
// 4 - ���ù���ģʽ
//**********************************************
	// ����ģʽ
//	*piTemp=1;	//������
////	*piTemp=0;	//ԭʼͼ��
//	FPGA_CTRL_send(ADDR_OUTSIDE_DATA_MODE,piTemp);

//	*piTemp=0;	// ������ֵ
////	*piTemp=1;	// ������ֵ
//	FPGA_CTRL_send(ADDR_OUTSIDE_WORK_MODE,piTemp);

	fpga_set_work_mode(1,0);

	return;
}
