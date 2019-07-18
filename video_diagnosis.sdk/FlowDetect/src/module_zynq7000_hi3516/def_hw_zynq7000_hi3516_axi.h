#ifndef DEF_HW_ZYNQ7000_HI3516_AXI_H
#define DEF_HW_ZYNQ7000_HI3516_AXI_H
/*-------------------------------------------------------------------*/
#include<limits.h>
/*-------------------------------------------------------------------*/
#define ALIGN_4_BYTE	(4)
/*-------------------------------------------------------------------*/
#define ADDR_OUTSIDE_RESET       (0x100 * ALIGN_4_BYTE)
#define ADDR_OUTSIDE_DATA_MODE   (0x101 * ALIGN_4_BYTE)
#define ADDR_OUTSIDE_START_EN    (0x102 * ALIGN_4_BYTE)
#define ADDR_OUTSIDE_WORK_MODE   (0x103 * ALIGN_4_BYTE)
/*-------------------------------------------------------------------*/
#define FLOW_DETECT_THD			 (0x107 * ALIGN_4_BYTE)
/*-------------------------------------------------------------------*/
#define SVM_ENABLE_CTRL			 (0x10A * ALIGN_4_BYTE)
/*-------------------------------------------------------------------*/
#define ADDR_OUTSIDE_BUSY        (0x100 * ALIGN_4_BYTE)
/*-------------------------------------------------------------------*/
#define ADDR_SENSOR_STATE        (0x110 * ALIGN_4_BYTE)				//read only
/*-------------------------------------------------------------------*/
#define ADDR_INTRINSIC_INV_R1C1  (0x110 * ALIGN_4_BYTE)				//write only
#define ADDR_INTRINSIC_INV_R1C3  (0x111 * ALIGN_4_BYTE)
#define ADDR_INTRINSIC_INV_R2C2  (0x112 * ALIGN_4_BYTE)
#define ADDR_INTRINSIC_INV_R2C3  (0x113 * ALIGN_4_BYTE)
/*-------------------------------------------------------------------*/
#define ADDR_INTRINSIC_FX        (0x114 * ALIGN_4_BYTE)
#define ADDR_INTRINSIC_FY        (0x115 * ALIGN_4_BYTE)
#define ADDR_INTRINSIC_CX        (0x116 * ALIGN_4_BYTE)
#define ADDR_INTRINSIC_CY        (0x117 * ALIGN_4_BYTE)
/*-------------------------------------------------------------------*/
#define ADDR_DISTORTION_K1       (0x118 * ALIGN_4_BYTE)
#define ADDR_DISTORTION_K2       (0x119 * ALIGN_4_BYTE)
#define ADDR_DISTORTION_P1       (0x11A * ALIGN_4_BYTE)
#define ADDR_DISTORTION_P2       (0x11B * ALIGN_4_BYTE)
#define ADDR_DISTORTION_K3       (0)
/*-------------------------------------------------------------------*/
#define SCALE_8_bit		(UCHAR_MAX)
#define SCALE_16_bit	(UCHAR_MAX*UCHAR_MAX)
#define SCALE_24_bit	(UCHAR_MAX*UCHAR_MAX*UCHAR_MAX)
/*-------------------------------------------------------------------*/
extern const float SCALE_DISTORTION;
extern const float SCALE_INTRINSIC;
/*-------------------------------------------------------------------*/
extern const unsigned int  ADDR_INTRINSIC[3][3];
extern const unsigned int  ADDR_INTRINSIC_INV[3][3];
extern const unsigned int  ADDR_DISTORTION[5][1];
extern const unsigned int  SCALE_INTRINSIC_INV[3][3];
/*-------------------------------------------------------------------*/
#endif
