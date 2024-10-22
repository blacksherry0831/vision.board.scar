#ifndef BASE_H
#define BASE_H
#include "linux_header.h"
#include "def.h"
#include "type.h"
/*-----------------------------------*/
#include "modules/printf_log/printf_log.h"

#include "sync/sync_global.h"
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
extern ssize_t readn(const int fd, void* const buf, const size_t n);
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
extern ssize_t writen(const int fd, const void* const buf, const size_t n);
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void SetInt2Char(const int _value,unsigned char* _data,int _size);
void SetInt2UChar(const int _value,unsigned char* _data,int _size);
int  SetChar2Int(const unsigned char* _data,int _size);
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int UChar2Int(const unsigned char* _data,const int _size);
int Char2Int(const unsigned char* _data,const int _size);
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int NativesAcceptClient(int s, int timeout);

/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int SelectAccept(int sockfd,int _sec);

int write_str(int socketfd,const char *buf);
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
struct timespec getDelayTime(long timeout_ms);
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void wait4MemFree();
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int Wait4Signal(long timeout_ms,pthread_mutex_t *__mutex,pthread_cond_t *__restrict __cond);
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int set_socket_buf_size(int sockfd,int send_buf_size);
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void sleep_1_ms();
void sleep_1ms_yield();
void sleepMS(int _ms);
void sleep_1_ms();
/*-----------------------------------*/
int sem_wait_infinite(sem_t  *__sem);
/*-----------------------------------*/
void setCurrentThreadHighPriority(int value);
/*-----------------------------------*/
int 	fs_is_file_exist(const char * file_path);
int  	fs_load_txt(const char *filepath,char* const buffer);
void 	fs_store_txt(const char *filepath, const char *data);
int 	fs_file_size(const char *filepath);
int 	fs_file_size(const char *filepath);
/*-----------------------------------*/

int _4UChar2Int(const unsigned char* _data);

#endif
