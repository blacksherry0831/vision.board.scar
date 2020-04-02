#ifndef _MSG_SYSV_Q_H_
#define _MSG_SYSV_Q_H_
/*-----------------------------------*/
#include "linux_header.h"
/*-----------------------------------*/
#ifdef __cplusplus             //告诉编译器，这部分代码按C语言的格式进行编译，而不是C++的
extern "C"{
#endif
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
typedef struct {

	long int message_type;

	void* _data;

}MESSAGE;
/*-----------------------------------*/
int get_queue(key_t _key);
int snd_queue(int _msgid,int _type,void* _data);
MESSAGE rcv_queue(int _msgid,int _type);
int remove_queue(const int _id);
/*-----------------------------------*/
#ifdef __cplusplus
}
#endif
/*-----------------------------------*/
#endif
