#ifndef AXI_BASE_H
#define AXI_BASE_H
/*-----------------------------------*/
#include "linux_header.h"
/*-----------------------------------*/
#include "def.h"
#include "modules_ex/type.h"
/*-----------------------------------*/

#include "module_zynq7000_hi3516/axi_fpga_ctrl_img.h"

#include "module_zynq7000_hi3516/dma.h"

#include "task/task_sync.h"
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
/*-----------------------------------*/
void SetSigma4SDCard();
void svm_enable(int _enable);
/*-----------------------------------*/
void sendImageMask();
/*-----------------------------------*/
#endif
