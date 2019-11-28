#ifndef _CMD_FILE_H_
#define _CMD_FILE_H_
/*-----------------------------------*/
#include "linux_header.h"
#include "def.h"
#include "base.h"
/*-----------------------------------*/
#include "modules_ex/type.h"
#include "modules_ex/fs_base.h"
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
enum CMD_TYPE_00_F {

	CT_FILE='f',

};
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
enum CMD_TYPE_02_F {
		CT_FILE_GET='g',
		CT_FILE_PUT='p',
	};
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
typedef struct _FileTrans
{
	unsigned char nSize[ALIGN_SIZE_T];//this struct size
	char prefix[ALIGN_SIZE_T];
	char fileFullPath[ALIGN_SIZE_T*8];
	char fileSize[ALIGN_SIZE_T];
} FileTrans;
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
typedef union _FileTransUI
{

	unsigned char buff[STRUCT_UNION_SIZE];
	FileTrans filetrans;

}FileTransUI;
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int IsFileGet(const CMD_CTRL* _cmd_ctrl);
int IsFilePut(const CMD_CTRL* _cmd_ctrl);
/*-----------------------------------*/
void sendFile2Queue_filetran(const CMD_CTRL* _cmd);
void SaveFile2SdCard_filetran(const CMD_CTRL* _cmd);
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
#endif
