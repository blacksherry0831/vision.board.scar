#include "cfg.h"
/*-----------------------------------*/
static int G_Sigma_Up=6;
static int G_Sigma_Down=6;
/*-----------------------------------*/
static volatile unsigned int G_FRAME_IDX_MAX=UINT_MAX;
static volatile unsigned int G_FRAME_IDX_MIN=0;
/*-----------------------------------*/
static volatile unsigned int G_SENSOR=0xff;
/*-----------------------------------*/
static int G_Heart_Beat_Time=5000;
static int G_NetWork_Check_Time=5000;
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int GetSigmaUp()
{
	return G_Sigma_Up;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int GetSigmaDown()
{
	return G_Sigma_Down;
}
/*-----------------------------------*/
/**
 *��¼������ֵ
 */
/*-----------------------------------*/
void SetSigmaUp(int _sigma)
{
	G_Sigma_Up=_sigma;
}
/*-----------------------------------*/
/**
 *��FPGA����������ֵ
 */
/*-----------------------------------*/
void SetSigmaUp2FPGA(int _sigma)
{
	SetSigmaUp(_sigma);  //��¼������ֵ
	fpga_set_sigma_up(G_Sigma_Up); //��FPGA����������ֵ
}
/*-----------------------------------*/
/**
 *��¼������ֵ
 */
/*-----------------------------------*/
void SetSigmaDown(int _sigma)
{
	G_Sigma_Down=_sigma;
}
/*-----------------------------------*/
/**
 *��FPGA����������ֵ
 */
/*-----------------------------------*/
void SetSigmaDown2FPGA(int _sigma)
{
	SetSigmaDown(_sigma);  //��¼������ֵ
	fpga_set_sigma_down(G_Sigma_Down);  //��FPGA����������ֵ
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void SetoutsideSigma()
{
		fpga_set_sigma_up(GetSigmaUp());
		fpga_set_sigma_down(GetSigmaDown());
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void SetinsideSigma()
{
		fpga_set_sigma_up(GetSigmaUp());
		fpga_set_sigma_down(GetSigmaDown());
}
/*-----------------------------------*/
/**
 *���������ͨ�����
 */
/*-----------------------------------*/
void SetGlobalSensor(unsigned int _channel)
{
	G_SENSOR=_channel;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
unsigned int GetGlobalSensor()
{
	return G_SENSOR;
}
/*-----------------------------------*/
/**
 *�ж�argv�������Ƿ�������Ӧ������ͷ
 */
/*-----------------------------------*/
unsigned int GetGlobalSensorMask(const int _ch)
{
	if(G_SENSOR & (0x01<<_ch)){
		return TRUE;
	}else{
		return FALSE;
	}
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void SetFrameIdxMin(const unsigned int _max)
{
	G_FRAME_IDX_MIN=_max;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
unsigned int GetFrameIdxMin()
{
	return G_FRAME_IDX_MIN;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void SetFrameIdxMax(const unsigned int _max)
{
	G_FRAME_IDX_MAX=_max;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
unsigned int GetFrameIdxMax()
{
	return G_FRAME_IDX_MAX;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int IsFrameCollect(const unsigned int _current_idx)
{

	if(_current_idx<GetFrameIdxMax()){
		return TRUE;
	}else{
		return FALSE;
	}

}
/*-----------------------------------*/
/**
 *��¼������ʱ����
 */
/*-----------------------------------*/
void SetHeartBeatTime(int _v)
{
	G_Heart_Beat_Time = _v;
}
/*-----------------------------------*/
/**
 *��¼������ʱ����
 */
/*-----------------------------------*/
void SetNetworkCheckTime(int _v)
{
	G_NetWork_Check_Time = _v;
}
/*-----------------------------------*/
/**
 *��ȡ������ʱ����
 */
/*-----------------------------------*/
int GetHeartBeatTime()
{
	return G_Heart_Beat_Time;
}
/*-----------------------------------*/
/**
 *��¼������ʱ����
 */
/*-----------------------------------*/
int GetNetworkCheckTime()
{
	return G_NetWork_Check_Time;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/

