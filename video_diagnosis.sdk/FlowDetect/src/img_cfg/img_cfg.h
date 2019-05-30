#ifndef IMG_CFG_H
#define IMG_CFG_H
/*-----------------------------------*/
#include "../linux_header.h"
#include "../type.h"
/*-----------------------------------*/
#include "../flow_ctrl/flow_sync.h"
#include "../type.h"
/*-----------------------------------*/
extern const size_t IMAGE_SIZE_FRAME;
extern const size_t IMAGE_SIZE_AVG;
extern const size_t CHANNEL_BLOCK_SIZE;
extern const size_t CHANNELS;
/*-----------------------------------*/
void  MallocImageBuff(CMD_CTRL** _buff,const int _frame,const int _Chs);
/*-----------------------------------*/
void  SetRectCutCmd(CMD_CTRL*  cmd_t);
void  ClearRectCut();
/*-----------------------------------*/
void init_image_cfg(const int _width,const int _height);
/*-----------------------------------*/
void init_image_area(const int _width,const int _height);
int image_width();
int image_height();
int image_size_frame();
void EraseMaskImage(CMD_CTRL* _img,int _channel);
/*-----------------------------------*/
int init_image_mask();
int IsEffectiveRect(const CvRect*  _rect);
/*-----------------------------------*/
#endif
