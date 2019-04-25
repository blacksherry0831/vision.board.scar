#ifndef BASE_H
#define BASE_H
#include "linux_header.h"
#include "def.h"
#include "type.h"

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
void SetInt2Char(int _value,unsigned char* _data,int _size);
int GetChar2Int(unsigned char* _data,int _size);
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
void printf_error();
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
void sleep_1ms();
void sleepMS(int _ms);
/*-----------------------------------*/
int sem_wait_infinite(sem_t  *__sem);
/*-----------------------------------*/
void setCurrentThreadHighPriority(int value);
/*-----------------------------------*/
int is_file_exist(const char * file_path);
/*-----------------------------------*/
#endif