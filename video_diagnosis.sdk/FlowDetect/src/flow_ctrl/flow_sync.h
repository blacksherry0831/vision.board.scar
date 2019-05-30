#ifndef FLOW_SYNC_H
#define FLOW_SYNC_H

#include "../linux_header.h"
#include  "../def.h"
#include "../type.h"
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
extern sem_t m_sem_fpga_frame_done;
extern sem_t m_sem_dma_frame_done2Mem;
extern sem_t m_sem_dma_frame_done2fpga;
extern sem_t m_sem_memcpy_frame_done;
/*-----------------------------------*/

int IsRun();
void StopRun(int _param);

/*-----------------------------------*/
enum ProjectRun{inside08,outside08};
void SetProjecRun(enum ProjectRun _pr);
enum ProjectRun GetProjectRun();
/*-----------------------------------*/
void StopFpgaCircleRunning();
/*-----------------------------------*/
int GetFpgaCircleWorkMode();

int SetFpgaCircleWorkMode(int _wm);
/*-----------------------------------*/
void EnterTcpTransImageThread(int _socket);
int IsTcpTransImageThreadRunning();
void ExitTcpTransImageThread();

int IsFpgaCircleRunning();
/*-----------------------------------*/
void ExitTaskFlowCtrl();
void EnterTaskFlowCtrl();
/*-----------------------------------*/
void SetGlobalChannel(unsigned int _channel);
unsigned int GetGlobalChannel();
unsigned int GetGlobalChannelMask(int _ch);
/*-----------------------------------*/
void SetFrameCircleSeq(unsigned int _seq);
unsigned int GetFrameCircleSeq();
/*-----------------------------------*/
int getFrameIdx();
int initFrameIdx();
void IncFrameIdx();
/*-----------------------------------*/
void SetFrameIdxMax(unsigned int _max);
unsigned int GetFrameIdxMax();

void SetFrameIdxMin(unsigned int _max);
unsigned int GetFrameIdxMin();
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
#endif
