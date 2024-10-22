#ifndef _SYNC_TASK_H_
#define _SYNC_TASK_H_
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
#include "linux_c_def.h"
/*-----------------------------------*/
#include "modules/printf_log/printf_log.h"
/*-----------------------------------*/
#include "modules_ex/def_frame.h"
#include "modules_ex/def_work_mode.h"
/*-----------------------------------*/
extern volatile int FRAME_IDX_FIRST;
/*-----------------------------------*/
extern volatile int FRAME_IDX_SECOND;
/*-----------------------------------*/
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/

void SetFrameCircleSeq(unsigned int _seq);
int printf_dbg_fpga_param();
int getFpgaCircleWorkMode();
int IsWorkMode_DiffImg();
int IsWorkMode_OrgImg();
void IncFrameIdx();
int getFrameIdx();
unsigned int GetFrameCircleSeq();
int initFrameIdx();

#endif
