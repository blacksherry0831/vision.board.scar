#ifndef DEF_HW_ZYNQ7000_HI3516_AXI_SCAR_H
#define DEF_HW_ZYNQ7000_HI3516_AXI_SCAR_H
/*-------------------------------------------------------------------*/
#include<limits.h>
/*-------------------------------------------------------------------*/
#define ALIGN4BYTE	(4)
/*-------------------------------------------------------------------*/
#define ADDR_SCAR_DETECT_RST    					(0x100 * ALIGN4BYTE)
#define ADDR_SCAR_DETECT_MODE    					(0x101 * ALIGN4BYTE)
#define ADDR_SCAR_DETECT_START_EN    				(0x102 * ALIGN4BYTE)
/*-------------------------------------------------------------------*/
#define ADDR_SCAR_DETECT_MASK_ADDR_H    			(0x104 * ALIGN4BYTE)
#define ADDR_SCAR_DETECT_MASK_ADDR_L    			(0x105 * ALIGN4BYTE)
/*-------------------------------------------------------------------*/
#define ADDR_SCAR_DETECT_DDR3_BASE    				(0x109 * ALIGN4BYTE)
#define ADDR_SCAR_DETECT_G_UP_TH    				(0x110 * ALIGN4BYTE)
#define ADDR_SCAR_DETECT_G_DOWN_TH    				(0x111 * ALIGN4BYTE)
#define ADDR_SCAR_DETECT_ROW_UP_TH    				(0x112 * ALIGN4BYTE)
#define ADDR_SCAR_DETECT_ROW_DOWN_TH    			(0x113 * ALIGN4BYTE)
#define ADDR_SCAR_DETECT_COL_UP_TH    				(0x114 * ALIGN4BYTE)
#define ADDR_SCAR_DETECT_COL_DOWN_TH    			(0x115 * ALIGN4BYTE)
/*-------------------------------------------------------------------*/



/*-------------------------------------------------------------------*/
#endif
