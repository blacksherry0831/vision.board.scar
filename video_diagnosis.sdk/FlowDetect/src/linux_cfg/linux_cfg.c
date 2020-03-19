#define _BSD_SOURCE
#define _GNU_SOURCE

#include "linux_cfg.h"
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void set_cpu_mask(int _cpu)
{
	int ret = 0;
	pid_t tid= syscall(SYS_gettid);
	cpu_set_t mask;
	  CPU_ZERO(&mask);
	  CPU_SET(_cpu,&mask); /*bind to cpu0*/


	 printf("%s tid = %d\n",__FUNCTION__, tid);


#if 1
    ret = sched_setaffinity(tid, sizeof(cpu_set_t), &mask);
    if(ret != 0)
    {
        printf("sched_setaffinity[%d] error\n", pthread_self());
        return ;
    }
#endif

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/

