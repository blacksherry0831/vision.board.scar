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
  int frame;
  int channel;
  int frame_idx_max;
  int frame_idx_min;
};
/*-----------------------------------*/
void SetSigma(int _sigma);
int  GetSigma();
void SetSigma4SDCard();
/*-----------------------------------*/
void SaveParam2SDCard(const char* const path,const int* _param,const int _size);
void ReadParam4SDCard(const char* const path, int* _param,const int _size);
/*-----------------------------------*/
#endif
