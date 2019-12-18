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
 *
 */
/*-----------------------------------*/
void SetSigmaUp(int _sigma)
{
	G_Sigma_Up=_sigma;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void SetSigmaUp2FPGA(int _sigma)
{
	SetSigmaUp(_sigma);
	fpga_set_sigma_up(G_Sigma_Up);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void SetSigmaDown(int _sigma)
{
	G_Sigma_Down=_sigma;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void SetSigmaDown2FPGA(int _sigma)
{
	SetSigmaDown(_sigma);
	fpga_set_sigma_down(G_Sigma_Down);
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
 *
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
 *
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
