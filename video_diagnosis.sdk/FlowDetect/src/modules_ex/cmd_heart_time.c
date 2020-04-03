/*
 * cmd_heart_time.c
 *
 *  Created on: 2020Äê4ÔÂ3ÈÕ
 *      Author: yjkj909
 */

#include "cmd_heart_time.h"

int IsHeartBeatTimeSetCmd(const CMD_CTRL* _cmd_ctrl)
{
	return IsCmdCtrlCmd(_cmd_ctrl,CT_HEART_TIME,CT_HEART_BEAT_TIME_SET);
}

int IsHeartBeatTimeQueryCmd(const CMD_CTRL* _cmd_ctrl)
{
	return IsCmdCtrlCmd(_cmd_ctrl,CT_HEART_TIME,CT_HEART_BEAT_TIME_QUERY);
}

int IsNetworkCheckTimeSetCmd(const CMD_CTRL* _cmd_ctrl)
{
	return IsCmdCtrlCmd(_cmd_ctrl,CT_HEART_TIME,CT_NETWORK_CHECK_SET);
}

int IsNetworkCheckTimeQueryCmd(const CMD_CTRL* _cmd_ctrl)
{
	return IsCmdCtrlCmd(_cmd_ctrl,CT_HEART_TIME,CT_NETWORK_CHECK_QUERY);
}
