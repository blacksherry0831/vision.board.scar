#include "cmd_file.h"
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int IsFileGet(const CMD_CTRL* _cmd_ctrl)
{
	return IsCmdCtrlCmd(_cmd_ctrl,CT_FILE,CT_FILE_GET);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int IsFilePut(const CMD_CTRL* _cmd_ctrl)
{
	return IsCmdCtrlCmd(_cmd_ctrl,CT_FILE,CT_FILE_PUT);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int SetFileCmd(CMD_CTRL* _cmd_ctrl,const unsigned char _flag)
{
	CMD_CTRL_HEADER* _cmd=&(_cmd_ctrl->f_header);

	 _cmd->f_cmd[0]=CT_FILE;

	 assert((_flag==CT_FILE_GET) || (_flag==CT_FILE_PUT));

	 _cmd->f_cmd[1]=_flag;

	return TRUE;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
FileTrans* GetFileTrans(const CMD_CTRL* cmd_t)
{
	 return (FileTrans *)(cmd_t->f_data);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
const FileTrans* GetFileTrans_const(const CMD_CTRL* cmd_t)
{
	 return (FileTrans *)(cmd_t->f_data);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
char* 	GetFileData(const CMD_CTRL* const  _cmd)
{
	char* data_t=(char *)( & (_cmd->f_data[sizeof(FileTransUI)]));

	return data_t;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
const char* 	GetFileData_const(const CMD_CTRL* const  _cmd)
{
	char* data_t=(char *)( & (_cmd->f_data[sizeof(FileTransUI)]));

	return data_t;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void InitFileCfg(
		CMD_CTRL* cmd_t,
		const char* 	_fileName,
		const char*  	_fileData,
		const int 		_fileSize)
{
	SetFileCmd(cmd_t,CT_FILE_PUT);

	FileTrans *file_t=GetFileTrans(cmd_t);

	if(file_t!=NULL){
		/*-----------------------------------*/
			SetInt2UChar(sizeof(FileTrans),file_t->nSize,ALIGN_SIZE_T);
		/*-----------------------------------*/
			file_t->prefix[0]='f';
			file_t->prefix[1]='i';
			file_t->prefix[2]='l';
			file_t->prefix[3]='e';
			file_t->prefix[4]='\0';
			/*-----------------------------------*/
			strcpy(file_t->fileFullPath,_fileName);
			/*-----------------------------------*/
			SetInt2Char(_fileSize,file_t->fileSize,ALIGN_SIZE_T);
			/*-----------------------------------*/

			 char* data_t=GetFileData(cmd_t);
			 memcpy(data_t,_fileData,_fileSize);

	}else{
			PRINTF_DBG_EX("no memory");
	}

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
CMD_CTRL* CreateFileCtrl(
		const char* 	_fileName,
		const char*  	_fileData,
		const int 		_fileSize,
		const int 		_seq)
{
	const unsigned int UnionSize=sizeof(FileTransUI);
	const unsigned int body_size=UnionSize+_fileSize;

	assert(UnionSize<=STRUCT_UNION_SIZE);

	CMD_CTRL*  cmd_t=CreateCmdCtrl(body_size);

	if(cmd_t!=NULL){
		InitFileCfg(cmd_t,_fileName,_fileData,_fileSize);
	}

	assert(IsCmdCtrl_Debug(cmd_t,"copy buff_src 2 image: image ctrl is not a valid buff"));
	return cmd_t;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
CMD_CTRL* CreateFileCtrlEx(
		const char* 	_fileName,
		const int 		_seq)
{
	CMD_CTRL*  cmd_t=NULL;

			char *buffer=NULL;
			 size_t size;
			 mode_t mode;

			 fs_readfile(_fileName,buffer,&size,&mode);
			 /* play with buffer here  */
			 {
				cmd_t=CreateFileCtrl(_fileName,buffer,size,_seq);
			 }
			 free(buffer);


	return cmd_t;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void sendFile2Queue_filetran(const CMD_CTRL* _cmd)
{

	const FileTrans* data_t=GetFileTrans_const(_cmd);
	const char*		filefullname_t=data_t->fileFullPath;
	const int		filesize_t= Char2Int(data_t->fileSize,sizeof(int));
	assert(filesize_t==0);

	if(fs_is_file_exist(filefullname_t)){

			CMD_CTRL* cmd_t=CreateFileCtrlEx(filefullname_t,0);

			snd_queue_img_buff(cmd_t);

	}

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void SaveFile2SdCard_filetran(const CMD_CTRL* _cmd)
{
	const FileTrans* data_t=GetFileTrans_const(_cmd);
	const char*		filefullname_t=data_t->fileFullPath;
	const int		filesize_t= UChar2Int(data_t->fileSize,sizeof(int)) ;
	const char*		buffer_t=GetFileData_const(_cmd);

	fs_store_binary(filefullname_t,buffer_t,filesize_t);

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
