#ifndef _FS_BASE_H
#define _FS_BASE_H
/*-----------------------------------*/
#include <dirent.h>
/*-----------------------------------*/
#include "linux_header.h"
#include "def.h"
#include "type.h"
/*-----------------------------------*/
#include "modules/printf_log/printf_log.h"
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/

/*-----------------------------------*/
int 	fs_is_file_exist(const char * file_path);
int 	fs_is_file_reg_file(const char * file_path);
int 	fs_is_file_dir(const char * file_path);
/*-----------------------------------*/
int 	fs_count_files(const char *path);
/*-----------------------------------*/
void 	fs_readfile(const char *fname, char *buffer, size_t *size, mode_t *mode);
int  	fs_load_txt(const char *filepath,char* const buffer);
/*-----------------------------------*/
void 	fs_store_binary(const char *filepath, const char *_buffer,const int _sz);
void 	fs_store_txt(const char *filepath, const char *data);
/*-----------------------------------*/
int 	fs_file_size(const char *filepath);
void 	fs_get_file_path(const char *path, const char *filename,  char *filefullpath);
/*-----------------------------------*/
int 	fs_delete_file(const char* path);
/*-----------------------------------*/
#endif
