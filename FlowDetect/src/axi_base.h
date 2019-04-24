#ifndef AXI_BASE_H
#define AXI_BASE_H
/*-----------------------------------*/
#include "linux_header.h"
#include "outside_process.h"
#include "def.h"
#include "type.h"
/*-----------------------------------*/
#include "msg_sysV_queue.h"
#include "axi_map.h"

#include "axi/axi_fpga_ctrl.h"

#include "hw_module/dma.h"
/*-----------------------------------*/
void outside_second_sync(int frame);
/*-----------------------------------*/
void send_image_2_queue(int _frameIdx,int MAP_WHAT);
int sensor_state();
/*-----------------------------------*/
void outside08_first_ex(int DATA_MODE);
void outside_inside_second_ex();
/*-----------------------------------*/
int init_fpga();
int GetSensorStat();
int SetSensorStat(int _sensor_stat);
/*-----------------------------------*/
pthread_mutex_t FPGA_mutex_cvt;
pthread_cond_t  FPGA_cond_cvt;
/*-----------------------------------*/
void SetoutsideSigma(int _sigma);
void SetinsideSigma(int _sigma);
void SetSigma(int _sigma);
int  GetSigma();
void SetSigma4SDCard();
void svm_enable(int _enable);
/*-----------------------------------*/
#endif
