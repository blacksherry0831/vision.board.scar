/*
 * cmd_heart_time.h
 *
 *  Created on: 2020年4月3日
 *      Author: yjkj909
 */

#ifndef CMD_HEART_TIME_H_
#define CMD_HEART_TIME_H_

#include "type.h"

/*-----------------------------------*/
enum CMD_TYPE_00_HEART_TIME {

	CT_HEART_TIME = 't',

};
/*-----------------------------------*/
enum CMD_TYPE_02_T {

	CT_HEART_BEAT_TIME_SET = 0x31,  //心跳包时间间隔-设置
	CT_HEART_BEAT_TIME_QUERY = 0x32,   //心跳包时间间隔-查询
	CT_NETWORK_CHECK_SET = 0x41,   //网络检测时间间隔-设置
	CT_NETWORK_CHECK_QUERY = 0x42,   //网络检测时间间隔-查询

};
/*-----------------------------------*/

int IsHeartBeatTimeSetCmd(const CMD_CTRL* _cmd_ctrl);
int IsHeartBeatTimeQueryCmd(const CMD_CTRL* _cmd_ctrl);
int IsNetworkCheckTimeSetCmd(const CMD_CTRL* _cmd_ctrl);
int IsNetworkCheckTimeQueryCmd(const CMD_CTRL* _cmd_ctrl);

#endif /* CMD_HEART_TIME_H_ */
