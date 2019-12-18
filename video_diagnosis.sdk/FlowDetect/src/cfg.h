#ifndef CFG_H
#define CFG_H
/*-----------------------------------*/
#include "linux_header.h"
#include "def.h"
/*-----------------------------------*/
#include "modules_ex/base.h"
/*-----------------------------------*/
struct cmd_param
{
  char project[32];
  int  width_param;
  int height_param;
  int space_frame;
  int sensor;
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
/*-----------------------------------*/
#endif
