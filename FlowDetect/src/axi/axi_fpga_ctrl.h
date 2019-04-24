#ifndef AXI_FPGA_CTRL_H
#define AXI_FPGA_CTRL_H
/*-----------------------------------*/
#include "../linux_header.h"
#include "../outside_process.h"
#include "../def.h"
#include "../type.h"
/*-----------------------------------*/
#include "axi_api.h"
/*-----------------------------------*/

/*-----------------------------------*/
#define ADDR_OUTSIDE_RESET       (0x100*4)
#define ADDR_OUTSIDE_DATA_MODE   (0x101*4)
#define ADDR_OUTSIDE_START_EN    (0x102*4)

#define ADDR_OUTSIDE_WORK_MODE   (0x103*4)

#define FLOW_DETECT_THD			 (0x107*4)
#define ADDR_OUTSIDE_BUSY        (0x100*4)
#define ADDR_SENSOR_STATE        (0x110*4)
#define SVM_ENABLE_CTRL			 (0x10A*4)
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
int FPGA_CTRL_mmap();
void FPGA_CTRL_unmmap();
/*-----------------------------------*/
int FPGA_CTRL_send(int addr, int* pidata);
int FPGA_CTRL_read(int addr, int* pidata);
/*-----------------------------------*/
#endif
