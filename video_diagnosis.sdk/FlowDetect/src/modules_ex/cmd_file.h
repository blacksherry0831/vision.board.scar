#ifndef _CMD_FILE_H_
#define _CMD_FILE_H_
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
		CT_FILE_DELETE='d',
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
	char fileFullPath[ALIGN_SIZE_T*16];
	unsigned char fileSize[ALIGN_SIZE_T];
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
int IsFileDelete(const CMD_CTRL* _cmd_ctrl);
int IsFileGet(const CMD_CTRL* _cmd_ctrl);
int IsFilePut(const CMD_CTRL* _cmd_ctrl);
/*-----------------------------------*/
void sendFile2Queue_filetran(const CMD_CTRL* _cmd);
void SaveFile2SdCard_filetran_TimeCost(const CMD_CTRL* _cmd);
void SaveFile2SdCard_filetran(const CMD_CTRL* _cmd);
void deleteFile_SdCard(const CMD_CTRL* _cmd);
/*-----------------------------------*/
const char* GetCmdCtrl_File_FullName(const CMD_CTRL* _cmd);
/*-----------------------------------*/
const char* GetProjectConfigPathPrefix();
/*-----------------------------------*/
#endif
