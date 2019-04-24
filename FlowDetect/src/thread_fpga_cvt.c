
#include "thread_fpga_cvt.h"

/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
pthread_t init_fpga_cvt_server(void *_data)
{
	pthread_t _thread_tid;
	if( pthread_create(&_thread_tid, NULL, fpga_cvt_server, _data) ){
			PRINTF_DBG(" Create print_thread1 thread error!\n");
			exit(0);
	}
 return _thread_tid;
}
