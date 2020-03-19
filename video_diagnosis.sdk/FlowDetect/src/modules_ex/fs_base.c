#include "fs_base.h"
/*-----------------------------------*/
/**
 *判断文件是否存在
 */
/*-----------------------------------*/
int fs_is_file_exist(const char * file_path)
{
	if(file_path==0)
			return ERROR;

		if(access(file_path,F_OK)==0)
			return SUCCESS;

		return ERROR;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void fs_store_binary(const char *filepath, const char *_buffer,const int _sz)
{
	FILE *fp = fopen(filepath, "wb");
	    if (fp != NULL)
	    {
	    	fwrite(_buffer,_sz,1,fp);
	        fclose(fp);
	    }
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void fs_store_txt(const char *filepath, const char *data)
{
	FILE *fp = fopen(filepath, "wt");
	    if (fp != NULL)
	    {
	        fputs(data, fp);
	        fclose(fp);
	    }
}
/*-----------------------------------*/
/**
 *读取文件内容
 */
/*-----------------------------------*/
int  fs_load_txt(const char *filepath,char* const buffer)
{
	  const  int string_size=fs_file_size(filepath);  //获取文件数据长度

	  int  read_size=0;

	  FILE *handler = fopen(filepath, "r");

	   if (handler)
	   {
	       // Read it all in one operation
	       read_size = fread(buffer, sizeof(char), string_size, handler);

	       // fread doesn't set it so put a \0 in the last position
	       // and buffer is now officially a string
	       buffer[string_size] = '\0';

	       if (string_size != read_size)
	       {
	    	   // Something went wrong, throw away the memory and set
	           return ERROR;
	       }

	       // Always remember to close the file.
	       fclose(handler);
	    }

	   return SUCCESS;

}
/*-----------------------------------*/
/**
 *获取文件数据长度
 */
/*-----------------------------------*/
int fs_file_size(const char *filepath)
{
	   int file_size=0;
	   FILE *handler = fopen(filepath, "r");

	   if (handler)
	   {
	       // Seek the last byte of the file
	       fseek(handler, 0, SEEK_END);
	       // Offset from the first to the last byte, or in other words, filesize
	       file_size = ftell(handler);

	       // Always remember to close the file.
	       fclose(handler);
	    }
	   return file_size;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
ssize_t readall(int fd, void *buf, size_t *bytes){
     ssize_t nread = 0, n=0;
     size_t nbyte = *bytes;

     do {
         if ((n = read(fd, &((char *)buf)[nread], nbyte - nread)) == -1) {
             if (errno == EINTR)
                 continue;
             else
                 return (-1);
         }
         if (n == 0)
             return nread;
         nread += n;
     } while (nread < nbyte);
     return nread;
}

/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void fs_readfile(const char *fname, char *buffer, size_t *size, mode_t *mode)
{
   int fd=0;
   struct stat st;

   CK_F(fd=open(fname,O_RDONLY) );
   CK_F(fstat(fd,&st) );
   *size=st.st_size;
   *mode=st.st_mode;
   CK_F(readall(fd, buffer, size) );
   CK_F(close(fd) );
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
const char *fs_find_file_name(const char *name)
{
	const char *name_start = NULL;
	int sep = '/';
	if (NULL == name) {
			PRINTF_DBG_EX("the path name is NULL\n");
	    return NULL;
	}
	name_start = strrchr(name, sep);

	return (NULL == name_start)?name:(name_start + 1);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void fs_get_file_path(const char *path, const char *filename,  char *filefullpath)
{
    strcpy(filefullpath, path);
    if(filefullpath[strlen(path) - 1] != '/')
        strcat(filefullpath, "/");
    strcat(filefullpath, filename);

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int 	fs_is_file_reg_file(const char * _path)
{
		struct stat statbuf;
	    lstat(_path, &statbuf);
	    return (S_ISREG(statbuf.st_mode));//判断是否是常规文件
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int 	fs_is_file_dir(const char * _path)
{
		struct stat statbuf;
		lstat(_path, &statbuf);
		return (S_ISDIR(statbuf.st_mode));
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int fs_delete_file(const char* path)
{
    DIR *dir;
    struct dirent *dirinfo;
    struct stat statbuf;
    char filefullpath[MAX_PATH_LEN] = {0};
    lstat(path, &statbuf);

    if (S_ISREG(statbuf.st_mode))//判断是否是常规文件
    {
        remove(path);
    }
    else if (S_ISDIR(statbuf.st_mode))//判断是否是目录
    {
        if ((dir = opendir(path)) == NULL)
            return 1;
        while ((dirinfo = readdir(dir)) != NULL)
        {
        	fs_get_file_path(path, dirinfo->d_name, filefullpath);
            if (strcmp(dirinfo->d_name, ".") == 0 || strcmp(dirinfo->d_name, "..") == 0)//判断是否是特殊目录
            continue;
            fs_delete_file(filefullpath);
            PRINTF_DBG_EX("delete path is = %s\n",filefullpath);
            rmdir(filefullpath);
        }
        closedir(dir);
    }else{
    	assert(0);
    }
    return 0;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int fs_count_files(const char *path)
{
    DIR *dir_ptr = NULL;
    struct dirent *direntp;
    char *npath;
    if (!path) return 0;
    if( (dir_ptr = opendir(path)) == NULL ) return 0;

    int count=0;
    while( (direntp = readdir(dir_ptr)))
    {
        if (strcmp(direntp->d_name,".")==0 ||
            strcmp(direntp->d_name,"..")==0) continue;
        switch (direntp->d_type) {
            case DT_REG:
                ++count;
                break;
            case DT_DIR:
                npath=(char*)malloc(strlen(path)+strlen(direntp->d_name)+2);
                sprintf(npath,"%s/%s",path, direntp->d_name);
                count += fs_count_files(npath);
                free(npath);
                break;
        }
    }
    closedir(dir_ptr);
    return count;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
