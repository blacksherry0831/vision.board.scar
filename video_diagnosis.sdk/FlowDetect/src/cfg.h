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
  char in_out;
  int  width_param;
  int height_param;
  int space_frame;
  int sensor;
  int frame_idx_max;
  int frame_idx_min;
};
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
void SaveParam2SDCard(const char* const path,const int* _param,const int _size);
void ReadParam4SDCard(const char* const path, int* _param,const int _size);
/*-----------------------------------*/
#endif
