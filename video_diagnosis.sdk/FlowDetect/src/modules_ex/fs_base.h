#ifndef _FS_BASE_H
#define _FS_BASE_H
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
#define ck(x) \
if( (x) == (-1) ){ perror("");exit(EXIT_FAILURE);}
/*-----------------------------------*/
int 	fs_is_file_exist(const char * file_path);
/*-----------------------------------*/
void 	fs_readfile(const char *fname, char *buffer, size_t *size, mode_t *mode);
int  	fs_load_txt(const char *filepath,char* const buffer);
/*-----------------------------------*/
void 	fs_store_binary(const char *filepath, const char *_buffer,const int _sz);
void 	fs_store_txt(const char *filepath, const char *data);
/*-----------------------------------*/
int 	fs_file_size(const char *filepath);
/*-----------------------------------*/
#endif
