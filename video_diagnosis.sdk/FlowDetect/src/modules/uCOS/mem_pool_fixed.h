#ifndef  MEM_POOL_FIXED
#define  MEM_POOL_FIXED

#include "os.h"

#include <stdio.h>
#include <assert.h>
#include <pthread.h>
#include <semaphore.h>

#include "cpu.h"
#include "cpu.h"


void init_mem_pool();

void* mem_malloc(int _size);
void  mem_free(void* _mem);
void  mem_free_clr(void** _mem_ptr);
void  mem_destory();

int MemPoolAddrZone(const void * _mem);
int destory_mem_pool();


#endif        

