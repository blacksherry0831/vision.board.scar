/*
 * cmd_heart_time.h
 *
 *  Created on: 2020��4��3��
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

	CT_HEART_BEAT_TIME_SET = 0x31,  //������ʱ����-����
	CT_HEART_BEAT_TIME_QUERY = 0x32,   //������ʱ����-��ѯ
	CT_NETWORK_CHECK_SET = 0x41,   //������ʱ����-����
	CT_NETWORK_CHECK_QUERY = 0x42,   //������ʱ����-��ѯ

};
/*-----------------------------------*/

int IsHeartBeatTimeSetCmd(const CMD_CTRL* _cmd_ctrl);
int IsHeartBeatTimeQueryCmd(const CMD_CTRL* _cmd_ctrl);
int IsNetworkCheckTimeSetCmd(const CMD_CTRL* _cmd_ctrl);
int IsNetworkCheckTimeQueryCmd(const CMD_CTRL* _cmd_ctrl);

#endif /* CMD_HEART_TIME_H_ */