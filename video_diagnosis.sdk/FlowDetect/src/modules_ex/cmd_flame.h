/*
 * cmd_flame.h
 *
 *  Created on: 2020Äê3ÔÂ24ÈÕ
 *      Author: yjkj909
 */

#ifndef CMD_FLAME_H_
#define CMD_FLAME_H_

/*-----------------------------------*/
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
/*-----------------------------------*/
#include "linux_header.h"
#include "def.h"
#include "base.h"
/*-----------------------------------*/
#include "modules_ex/type.h"
#include "modules_ex/fs_base.h"
/*-----------------------------------*/
#include "module_zynq7000_hi3516/def_hw_zynq7000_hi3516.h"

#include "status.h"
/*-----------------------------------*/

enum CMD_TYPE_00_FLAME {

	CT_FLAME='m',

};

/*-----------------------------------*/

enum CMD_TYPE_02_FLAME {

		CT_IS_FLAME_MONITOR=0x01,
		CT_FLAME_AREA_SET=0x11,
		CT_FLAME_AREA_QUERY=0x12,
		CT_FLAME_DIFFERENCE_SET=0x21,
		CT_FLAME_DIFFERENCE_QUERY=0x22,

};

/*-----------------------------------*/

int IsFlameMonitorCmd(const CMD_CTRL* _cmd_ctrl);
int IsFlameAreaSetCmd(const CMD_CTRL* _cmd_ctrl);
int IsFlameAreaQueryCmd(const CMD_CTRL* _cmd_ctrl);
int IsFlameDifferenceSetCmd(const CMD_CTRL* _cmd_ctrl);
int IsFlameDifferenceQueryCmd(const CMD_CTRL* _cmd_ctrl);

#endif /* CMD_FLAME_H_ */
