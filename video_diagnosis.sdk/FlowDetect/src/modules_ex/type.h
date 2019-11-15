#ifndef TYPE_H
#define TYPE_H
/*-----------------------------------*/
#include "linux_header.h"
#include "def.h"
#include "base.h"
#include <modules_ex/opencv_base.h>
/*-----------------------------------*/
#include <modules/uCOS/mem_pool_fixed.h>
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
#define FRAME_IDX_TYPE_FIRST_IMG 	(1)
#define FRAME_IDX_TYPE_START 		(0)
#define FRAME_IDX_TYPE_STOP 		(-1)
#define FRAME_IDX_TYPE_HEARBEAT 	(-2)
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
enum DEV {
		DEV_IPC = 0x00,
		DEV_PLC = 0x01,
		DEV_PLC_LR = 0x11,
		DEV_FPGA_ARM=0x02};
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
enum CMD_TYPE {

	CT_HEART='h',
	CT_QUERY='q',
	CT_CTRL='c',
	CT_RESP='r',
	CT_IMG='I',

};
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
enum CMD_TYPE_02 {

		CT_BEAT='b',

		CT_LR_RUN_2=0x20,
		CT_ROLLER_Q=0x10
	};
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
enum CMD_TYPE_02_RESP {

	CT_OK=0x00,
	CT_ERROR=0x01,
	CT_NONE=0x02,

	};
/*-----------------------------------*/
/**
*
*/
/*-----------------------------------*/
enum CMD_TYPE_02_C{

		CT_START=0x00,
		CT_STOP=0x01,

		CT_START_00=0x10,
		CT_STOP_00=0x11,
		CT_START_01=0x20,
		CT_STOP_01=0x21,

};
/*-----------------------------------*/
/**
*
*/
/*-----------------------------------*/
enum CMD_TYPE_02_I{

		CT_IMG_FRAME='F',
		CT_IMG_RECT='R',
		CT_IMG_MODE_CHANGE='M',
		CT_IMG_MASK_CHANGE='K',

};
/*-----------------------------------*/
/**
*
*/
/*-----------------------------------*/
enum CMD_TYPE_02_I_SIGMA{

		CT_IMG_SIGMA_UP_CHANGE=0xF1,
		CT_IMG_SIGMA_DOWN_CHANGE=0xF2,

};
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
enum WorkMode
{
	WM_SIZE_FULL=0x80,
	WM_SIZE_CUT=0x40,
	WM_ORG_IMG=0x20,
	WM_DIFF_IMG=0x10,
	WM_SIGMA_IMG=0x10,
	RESP=0x01

};
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
enum HearBeatResp
{
	HB_RESP='r',
	HB_NONE='n',
};
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
typedef struct _IplImageU
{
	unsigned char nSize[ALIGN_SIZE_T];//this struct size
	char prefix[ALIGN_SIZE_T];
	unsigned char IpAddrChannel[ALIGN_SIZE_T];
	unsigned char frame[ALIGN_SIZE_T];

	unsigned char width[ALIGN_SIZE_T];
	unsigned char height[ALIGN_SIZE_T];

	unsigned char width_roi[ALIGN_SIZE_T];
	unsigned char height_roi[ALIGN_SIZE_T];
	unsigned char x_roi[ALIGN_SIZE_T];
	unsigned char y_roi[ALIGN_SIZE_T];

	unsigned char sensor_stat[ALIGN_SIZE_T];
	unsigned char nChannels[ALIGN_SIZE_T];
	char colorModel[ALIGN_SIZE_T*8];/**<*/

	IplImage  	Iplimg;
} IplImageU;
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
typedef union _IplImageUI
{
	unsigned char buff[ALIGN_SIZE_T*64];
	IplImageU iplImgU;
}IplImageUI;
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
typedef struct {

	unsigned char f_header[4];//"Yjkj"
	unsigned char f_data_len_high[2];//length high
	unsigned char f_cmd_idx[4];//
	unsigned char f_dst_dev[2];
	unsigned char f_src_dev[2];
	unsigned char f_cmd[2];
	unsigned char f_data_len[2];//length low
}CMD_CTRL_HEADER;
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
typedef struct{
	CMD_CTRL_HEADER f_header;
	unsigned char* f_data;
	unsigned int f_data_size;
	unsigned char f_crc;
}CMD_CTRL;
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int IsCmdCtrlCmd(
		const CMD_CTRL* _cmd_ctrl,
		const unsigned char _cmd00,
		const unsigned char _cmd01);
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
extern int socket_read_1_cmd(int _sockfd,CMD_CTRL*  _cmd_ptr);
extern int socket_write_1_cmd(int _sockfd,CMD_CTRL*  _cmd_ptr);
extern int socket_write_1_cmd_release(int _sockfd,CMD_CTRL*  _cmd_ptr);
extern int socket_write_1_cmd_raw_release(int _sockfd,CMD_CTRL*  _cmd_ptr);
extern int socket_write_1_cmd_raw_data(int _sockfd,CMD_CTRL*  _cmd_ptr);
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
extern CMD_CTRL* CreateCmdCtrl(int body_size);
extern CMD_CTRL* CreateImageCtrl(int _ch,int _frame,int _width,int _height,int _nChs, int _seq);
extern int IsCmdCtrl(CMD_CTRL* cmd_t);

CMD_CTRL* CreateImageStart(int _ch,unsigned int _seq);
CMD_CTRL* CreateImageStop(int _ch,unsigned int _seq);

extern void ReleaseCmdCtrl(CMD_CTRL** _cmd_ctrl);
extern void FreeCmdBody(CMD_CTRL*  _cmd_ptr);
extern void CreateCmdBody(CMD_CTRL* cmd_t,unsigned int body_size);
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
extern int isStartCmd(const CMD_CTRL* const _cmd_ctrl);
extern int isDoneCmd(const CMD_CTRL* const _cmd_ctrl);
/*-----------------------------------*/
int isHeartbeatCmd(const CMD_CTRL*  _cmd_ctrl);
int IsImageFrame(const CMD_CTRL* _cmd_ctrl);
int IsImageRect(const CMD_CTRL* _cmd_ctrl);
int IsImageMaskChange(const CMD_CTRL* _cmd_ctrl);
int IsImageChangeWorkMode(const CMD_CTRL* _cmd_ctrl);
/*-----------------------------------*/
int GetCmdCmd02(const CMD_CTRL* const _cmd_ctrl);
int GetCmdParam(const CMD_CTRL* const _cmd_ctrl);
/*-----------------------------------*/
extern unsigned int GetCMDBodySize(CMD_CTRL_HEADER _cmd);
extern void initRespCmd(CMD_CTRL* cmd_t,int _ok);
extern int SendRespCmd(int _socketfd,int _ok,int _body);
extern int SendHeartbeatCmd(int _socketfd,int _need_resp,int _seq);
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int GetStartCmdParam(const CMD_CTRL* const _cmd_ctrl);
unsigned int GetCmdFrameSeq(const CMD_CTRL* const _cmd_ctrl);
/*-----------------------------------*/

/*-----------------------------------*/
void SetSensorStatus(CMD_CTRL* _cmd,int _status,int _channel);
/*-----------------------------------*/
void init_cmd_buff_size(int nSemaphoreCount);
/*-----------------------------------*/
int initSemSignal();
/*-----------------------------------*/
int IsImageChangeSigmaUp(const CMD_CTRL* _cmd_ctrl);
int IsImageQuerySigmaUp(const CMD_CTRL* _cmd_ctrl);
/*-----------------------------------*/
int IsImageChangeSigmaDown(const CMD_CTRL* _cmd_ctrl);
int IsImageQuerySigmaDown(const CMD_CTRL* _cmd_ctrl);
/*-----------------------------------*/
IplImage * GetIplImage(const CMD_CTRL* cmd);
IplImageU* GetIplImageUx(const CMD_CTRL* cmd_t);
/*-----------------------------------*/
int GetCmdImgViewChannel(const CMD_CTRL* const _cmd_ctrl);
/*-----------------------------------*/
#endif
