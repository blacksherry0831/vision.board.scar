#ifndef IMG_CFG_H
#define IMG_CFG_H
/*-----------------------------------*/
#include "../linux_header.h"
#include "modules_ex/type.h"
/*-----------------------------------*/

#include "modules_ex/type.h"
/*-----------------------------------*/
#include <modules/opencv2/core/types_c.h>
/*-----------------------------------*/
#include <modules/lodepng/lodepng.h>
/*-----------------------------------*/
extern const size_t IMAGE_SIZE_FRAME;
extern const size_t IMAGE_SIZE_AVG;
extern const size_t CHANNEL_BLOCK_SIZE;
extern const size_t CHANNELS;
/*-----------------------------------*/
CMD_CTRL* CreateImageCtrlLocal(int _ch,int _frame, int _seq);

void  MallocImageBuff(CMD_CTRL** _buff,const int _frame,const int _Chs);
/*-----------------------------------*/
void  SetRectCutCmd(CMD_CTRL*  cmd_t);
void  ClearRectCut();
/*-----------------------------------*/
void SaveImgMaskMatrix(const CMD_CTRL* const  _cmd);
/*-----------------------------------*/
void init_image_cfg(const int _width,const int _height);
/*-----------------------------------*/
void init_image_area(const int _width,const int _height);
int image_width();
int image_height();
int image_size_frame();
/*-----------------------------------*/
int init_image_mask();
/*-----------------------------------*/
#endif
