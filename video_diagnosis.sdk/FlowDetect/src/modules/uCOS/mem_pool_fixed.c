#include "mem_pool_fixed.h"

#define BLK_SIZE_2M (2097152)

#define BLK_NUM_2M  (64)

#define BLK_1K_SIZE (1024)

#define BLK_1K_NUM  (BLK_NUM_2M*2+256)

unsigned char    BUFF_2M[BLK_NUM_2M][BLK_SIZE_2M];

unsigned char    BUFF_1K[BLK_1K_NUM][BLK_1K_SIZE];

OS_MEM  m_os_2m_mem={0};
OS_MEM  m_os_1k_mem={0};
OS_ERR  m_os_err={0};

sem_t   m_sem_2m_buff;
/*-----------------------------------*/
#define PRINTF_MEM_USAGE	(0)
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int MemPoolAddrZone(void * _mem)
{

		const CPU_ADDR _mem_addr=(CPU_ADDR)_mem;

		const CPU_ADDR mem_1K_start=(CPU_ADDR) (BUFF_1K);
		const CPU_ADDR mem_1K_end= (CPU_ADDR)  ((void *) &BUFF_1K[BLK_1K_NUM-1][BLK_1K_SIZE-1]);

		const CPU_ADDR mem_2m_start=(CPU_ADDR) (BUFF_2M);
		const CPU_ADDR mem_2m_end=(CPU_ADDR)  ((void *) &BUFF_2M[BLK_NUM_2M-1][BLK_SIZE_2M-1]);

			if(			(_mem_addr >= mem_1K_start )&&
						(_mem_addr <= mem_1K_end )
																			){

					return BLK_1K_SIZE;

			}else if(	(_mem_addr >= mem_2m_start)&&
						(_mem_addr <= mem_2m_end)
			){

					return 	BLK_SIZE_2M;

			}else if(_mem_addr==0){
					return 0;
			}else{

				return -1;
			}

		return -1;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void init_mem_pool() 
{
#if 1
	const int cpu_addr=sizeof(CPU_ADDR);
	assert(cpu_addr==4);
#endif

	OSMemCreate(&m_os_2m_mem, "memory", BUFF_2M, BLK_NUM_2M,BLK_SIZE_2M, &m_os_err);

	if (m_os_err == OS_ERR_NONE) {

		int nRet = sem_init(&m_sem_2m_buff, 0,  BLK_NUM_2M-1);

		if (0 != nRet)
			exit(-1);

	}else{
		printf("mem init error");
		exit(-1);
	}


	OSMemCreate(&m_os_1k_mem, "memory", BUFF_1K, BLK_1K_NUM,BLK_1K_SIZE, &m_os_err);

	if (m_os_err == OS_ERR_NONE) {



	}else{
			printf("mem init error");
			exit(-1);
	}



	printf("init mem pool done \n");
		
	return;
}

/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void mem_assert()
{
	assert(m_os_1k_mem.AddrPtr!=NULL);
	assert(m_os_2m_mem.AddrPtr!=NULL);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void* mem_malloc(const int _size)
{

	void *data=NULL;
	mem_assert();

	if(_size<=BLK_1K_SIZE){

		 data = (unsigned char *)OSMemGet(&m_os_1k_mem, &m_os_err);

	}else if(_size>BLK_1K_SIZE && _size<=BLK_SIZE_2M){

		 sem_wait_infinite(&m_sem_2m_buff);

		 data = (unsigned char *)OSMemGet(&m_os_2m_mem, &m_os_err);

	}else{
			printf("mem malloc size error \n");
			return NULL;
	}

	if (m_os_err == OS_ERR_NONE) {

	}else if(m_os_err ==OS_ERR_MEM_NO_FREE_BLKS ){
		printf("OS_ERR_MEM_NO_FREE_BLKS: %d, \n",_size);
	}else {
		printf("mem malloc error");
		exit(-1);
	}

	return data;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void printf_mem_usage()
{
#if _DEBUG && PRINTF_MEM_USAGE
	float free2m=1.0*m_os_2m_mem.NbrFree/m_os_2m_mem.NbrMax;
	float free1k=1.0*m_os_1k_mem.NbrFree/m_os_1k_mem.NbrMax;

	PRINTF_DBG("2M free: %0.3f,1k free: %0.3 ",free2m,free1k);
	//PRINTF_DBG("\n");
	PRINTF_DBG("2M free(num): %d,1k free(num): %d ",m_os_2m_mem.NbrFree,m_os_1k_mem.NbrFree);
	PRINTF_DBG("\n");
#endif
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/

void mem_free(void* _mem)
{

	const int ADDR_ZONE=MemPoolAddrZone(_mem);

	mem_assert();

	printf_mem_usage();

	if(ADDR_ZONE==BLK_1K_SIZE){

				OSMemPut(&m_os_1k_mem, _mem, &m_os_err);

	}else if(ADDR_ZONE==BLK_SIZE_2M){

				OSMemPut(&m_os_2m_mem, _mem, &m_os_err);
				if (m_os_err == OS_ERR_NONE) {
					sem_post(&m_sem_2m_buff);
				}


	}else if(ADDR_ZONE==0){
			 return;
	}else{
			printf_mem_usage();
			printf("mem FREE error NOT A BUFF ADDR");
			exit(-1);
	}



	if (m_os_err == OS_ERR_NONE) {

	}else {
		printf("mem free error");
		printf_mem_usage();
		exit(-1);
	}

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void mem_free_clr(void** _mem_ptr)
{
	void* _mem=*_mem_ptr;

	mem_free(_mem);

	_mem_ptr=NULL;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/

void destory_mem_pool()
{

	CPU_IntDestory();

	int result_t=sem_destroy(&m_sem_2m_buff);



}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
