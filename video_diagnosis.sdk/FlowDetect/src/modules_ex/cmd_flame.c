/*
 * cmd_flame.c
 *
 *  Created on: 2020Äê3ÔÂ24ÈÕ
 *      Author: yjkj909
 */
#include "cmd_flame.h"

int IsFlameMonitorCmd(const CMD_CTRL* _cmd_ctrl)
{
	return IsCmdCtrlCmd(_cmd_ctrl,CT_FLAME,CT_IS_FLAME_MONITOR);
}

int IsFlameAreaSetCmd(const CMD_CTRL* _cmd_ctrl)
{
	return IsCmdCtrlCmd(_cmd_ctrl,CT_FLAME,CT_FLAME_AREA_SET);
}

int IsFlameAreaQueryCmd(const CMD_CTRL* _cmd_ctrl)
{
	return IsCmdCtrlCmd(_cmd_ctrl,CT_FLAME,CT_FLAME_AREA_QUERY);
}

int IsFlameDifferenceSetCmd(const CMD_CTRL* _cmd_ctrl)
{
	return IsCmdCtrlCmd(_cmd_ctrl,CT_FLAME,CT_FLAME_DIFFERENCE_SET);
}

int IsFlameDifferenceQueryCmd(const CMD_CTRL* _cmd_ctrl)
{
	return IsCmdCtrlCmd(_cmd_ctrl,CT_FLAME,CT_FLAME_DIFFERENCE_QUERY);
}
