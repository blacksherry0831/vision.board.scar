#include "cmd_file.h"
/*-----------------------------------*/
#include "msg_queue/msg_sysV_queue.h"
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
const char* SYS_CFG_FILES[]={
		"up.sh",
#if 0
		"top.bit",
#endif
		"project.run/FlowDetect",
		"project.run/deadline_server"};
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int IsFileDelete(const CMD_CTRL* _cmd_ctrl)
{
	return IsCmdCtrlCmd(_cmd_ctrl,CT_FILE,CT_FILE_DELETE);
}
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

	 assert((_flag==CT_FILE_GET) ||
			(_flag==CT_FILE_PUT) ||
			(_flag==CT_START)	 ||
			(_flag==CT_STOP));

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
const char*	GetCmdCtrl_File_FullName(const CMD_CTRL* _cmd)
{
	 return ((FileTrans *)(_cmd->f_data))->fileFullPath;
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
			assert(strlen(_fileName)<(ALIGN_SIZE_T*16));
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
int GetFileBodySize(const int _sz)
{
		const unsigned int UnionSize=sizeof(FileTransUI);
		const unsigned int body_size=UnionSize+_sz;
		assert(UnionSize<=STRUCT_UNION_SIZE);
		return body_size;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
CMD_CTRL* CreateFileStart(
		const int 		_seq,
		const unsigned int		_cmd_param)
{
	const unsigned int body_size=GetFileBodySize(1);

	CMD_CTRL*  cmd_t=CreateCmdCtrl(body_size);

	if(cmd_t!=NULL){
		SetFileCmd(cmd_t,CT_START);
		SetCmdParam(cmd_t,_cmd_param);
	}

	assert(IsCmdCtrl_Debug(cmd_t,"copy buff_src 2 image: image ctrl is not a valid buff"));
	return cmd_t;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
CMD_CTRL* CreateFileStop(
		const int 				_seq,
		const unsigned int		_cmd_param)
{

	const unsigned int body_size=GetFileBodySize(1);

	CMD_CTRL*  cmd_t=CreateCmdCtrl(body_size);

	if(cmd_t!=NULL){
		SetFileCmd(cmd_t,CT_STOP);
		SetCmdParam(cmd_t,_cmd_param);
	}
	assert(IsCmdCtrl_Debug(cmd_t,"copy buff_src 2 image: image ctrl is not a valid buff"));
	return cmd_t;
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
	const unsigned int body_size=GetFileBodySize(_fileSize);

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

			const int file_size=fs_file_size(_fileName);

			char *buffer=(char *)mem_malloc(file_size+1);
			 size_t size;
			 mode_t mode;

			 fs_readfile(_fileName,buffer,&size,&mode);
			 assert(size==file_size);
			 /* play with buffer here  */
			 {
				cmd_t=CreateFileCtrl(_fileName,buffer,size,_seq);
			 }
			 mem_free(buffer);


	return cmd_t;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void send_1_file_2_queue(const char* _f)
{
		assert(SUCCESS==fs_is_file_exist(_f));
		PRINTF_DBG_EX("file put path is = %s\n",_f);
	    CMD_CTRL* cmd_t=CreateFileCtrlEx(_f,0);
	    snd_queue_img_buff(cmd_t);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int get_sys_cfg_files_num()
{
	return sizeof(SYS_CFG_FILES)/sizeof(char*);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void send_sys_file()
{
	int fi=0;
	const int F_MAX=get_sys_cfg_files_num();

	for(fi=0;fi<F_MAX;fi++){
		char ffp[MAX_PATH_LEN] = {0};
		sprintf(ffp,"%s%s",PATH_SDCARD,SYS_CFG_FILES[fi]);
		send_1_file_2_queue(ffp);
	}

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void send_dir(char* _path)
{
    DIR *d = NULL;
    struct dirent *dp = NULL; /* readdir函数的返回值就存放在这个结构体中 */
    struct stat st;
    char p[MAX_PATH_LEN] = {0};

    if(stat(_path, &st) < 0 || !S_ISDIR(st.st_mode)) {
    	PRINTF_DBG_EX("invalid path: %s\n", _path);
        return;
    }

    if(!(d = opendir(_path))) {
    	PRINTF_DBG_EX("opendir[%s] error: %m\n", _path);
        return;
    }

    while((dp = readdir(d)) != NULL) {
        /* 把当前目录.，上一级目录..及隐藏文件都去掉，避免死循环遍历目录 */
        if((!strncmp(dp->d_name, ".", 1)) || (!strncmp(dp->d_name, "..", 2)))
            continue;

        snprintf(p, sizeof(p) - 1, "%s/%s", _path, dp->d_name);
        stat(p, &st);
        if(!S_ISDIR(st.st_mode)) {
        	{
        		char filefullpath[MAX_PATH_LEN] = {0};
        		fs_get_file_path(_path, dp->d_name, filefullpath);
        		send_1_file_2_queue(filefullpath);
        	}
        } else {
        	PRINTF_DBG_EX("%s/\n", dp->d_name);
            send_dir(p);
        }
    }
    closedir(d);

    return;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int IsFileNameOnly(const char* _file)
{
	const char* idx=strchr(_file,'/');
	if(idx==NULL){
		return TRUE;
	}else{
		return FALSE;
	}
	return FALSE;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void getFileFullPath(char* _ffp,const char* _file_name)
{

		char path_cfg[MAX_PATH_LEN]={0};
		initProjectCfgDirPath_Separator(path_cfg);
		sprintf(_ffp,"%s%s",path_cfg,_file_name);

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
const char* GetProjectConfigPathPrefix()
{
	return "project.cfg.";
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void mergeCmdFileFullPath(char* _ffp,const char* _file_name)
{

	assert(_file_name!=NULL);
	assert(strlen(_file_name)<MAX_PATH_LEN);

	if(IsFileNameOnly(_file_name)){

		if(strcmp(_file_name,GetProjectConfigPathPrefix())==0){
			getFileFullPath(_ffp,"");
		}else{
			getFileFullPath(_ffp,_file_name);
		}

	}else{
			strcpy(_ffp,_file_name);
	}

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void deleteFile_SdCard(const CMD_CTRL* _cmd)
{

	const FileTrans* data_t=GetFileTrans_const(_cmd);
	const char*		filefullname_t=data_t->fileFullPath;
	const int		filesize_t= UChar2Int(data_t->fileSize,sizeof(int));
	assert(filesize_t==0);

	char filefullpath[MAX_PATH_LEN]={0};

	mergeCmdFileFullPath(filefullpath,filefullname_t);

	fs_delete_file(filefullpath);


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
	const int		filesize_t= UChar2Int(data_t->fileSize,sizeof(int));
	assert(filesize_t==0);

	char filefullpath[MAX_PATH_LEN]={0};
	mergeCmdFileFullPath(filefullpath,filefullname_t);

	if(fs_is_file_dir(filefullpath)){

		const int file_count=fs_count_files(filefullpath)+get_sys_cfg_files_num();
		snd_queue_img_buff(CreateFileStart(0,file_count));
		send_dir(filefullpath);
		send_sys_file();
		snd_queue_img_buff(CreateFileStop(0,file_count));

	}else	if(fs_is_file_reg_file(filefullpath)){

		assert(TRUE==fs_is_file_exist(filefullpath));
		CMD_CTRL* cmd_t=CreateFileCtrlEx(filefullpath,0);
		snd_queue_img_buff(cmd_t);

	}else{
		assert(0);
	}

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void SaveFile2SdCard_filetran_TimeCost(const CMD_CTRL* _cmd)
{
	const char * TopBit="/media/sdcard/top.bit";
	const FileTrans* data_t=GetFileTrans_const(_cmd);
	const char*		filefullname_t=data_t->fileFullPath;
	PRINTF_DBG_EX("file save==%s\n",filefullname_t);


	TIME_START();
	SaveFile2SdCard_filetran(_cmd);
	TIME_END("save file cost time:");

	if(0==strcmp(TopBit,filefullname_t)){
		assert(1);
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

	char filefullpath[MAX_PATH_LEN]={0};

	mergeCmdFileFullPath(filefullpath,filefullname_t);

	fs_store_binary(filefullpath,buffer_t,filesize_t);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
