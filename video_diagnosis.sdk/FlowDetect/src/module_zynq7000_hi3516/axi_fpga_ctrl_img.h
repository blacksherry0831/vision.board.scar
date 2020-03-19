#ifndef AXI_FPGA_CTRL_IMG_H
#define AXI_FPGA_CTRL_IMG_H
/*-----------------------------------*/
#include "linux_header.h"
/*-----------------------------------*/
#define  FPGA_WORK_MODE_AVG 		(0)
#define  FPGA_WORK_MODE_DIFF		(1)
/*-----------------------------------*/
#define  FPGA_WORK_MODE_DATA_ZERO	(2)
#define  FPGA_WORK_MODE_DATA_AVG	(0)
#define  FPGA_WORK_MODE_DATA_DIFF	(0)
/*-----------------------------------*/
/**
 *
 * D=0 W=0  D=0 W=1//diff image
 * D=2 W=0  D=0 W=1//org image
 *
 */
/*-----------------------------------*/
/*-----------------------------------*/
/**
 *
 * D=0 W=0  D=0 W=1//diff image
 * D=2 W=0  D=0 W=1//org image
 *
 */
/*-----------------------------------*/
int fpga_img_read_sensor_status();
int fpga_set_data_mode(int _WORK,int _DATA);
void  fpga_set_sigma(const int sigma);
int fpga_is_busy();
int fpga_reset();
int fpga_start();
/*-----------------------------------*/
void  fpga_set_sigma_up(const int _sigma_square);
void  fpga_set_sigma_down(const int _sigma_square);
void fpga_img_svm_enable(int _enable);
/*-----------------------------------*/
#endif
