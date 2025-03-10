#ifndef CFG_H
#define CFG_H
/*-----------------------------------*/
#include "linux_header.h"
#include "def.h"
/*-----------------------------------*/
#include "modules_ex/base.h"

#include "module_zynq7000_hi3516/axi_fpga_ctrl_img.h"
/*-----------------------------------*/
struct cmd_param
{
  char project[32];  //项目名
  int  width_param;  //宽
  int height_param;  //长
  int space_frame;   //图像号
  int sensor;        //摄像机数
};
/*-----------------------------------*/
void SetFrameIdxMax(unsigned int _max);
unsigned int GetFrameIdxMax();
/*-----------------------------------*/
void SetFrameIdxMin(unsigned int _max);
unsigned int GetFrameIdxMin();
/*-----------------------------------*/
unsigned int GetGlobalSensorMask(const int _ch);
/*-----------------------------------*/
int  GetSigmaUp();
int  GetSigmaDown();
void SetSigmaUp2FPGA(int _sigma);
void SetSigmaDown2FPGA(int _sigma);
void SetSigmaUp(int _sigma);
void SetSigmaDown(int _sigma);

int IsFrameCollect(const unsigned int _current_idx);
unsigned int GetGlobalSensor();
void SetGlobalSensor(unsigned int _channel);

void SetHeartBeatTime(int _v);
void SetNetworkCheckTime(int _v);
int GetHeartBeatTime();
int GetNetworkCheckTime();
/*-----------------------------------*/
#endif
