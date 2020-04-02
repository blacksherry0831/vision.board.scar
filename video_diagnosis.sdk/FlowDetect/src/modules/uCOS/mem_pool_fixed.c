#include "mem_pool_fixed.h"
#include "cpu.h"
#include <stdlib.h>

/*-----------------------------------*/
#define BLK_SIZE_4M (4194304)
#define BLK_NUM_4M  (8)
/*-----------------------------------*/
#define BLK_SIZE_2M (2097152)
#define BLK_NUM_2M  (32)
/*-----------------------------------*/
#define BLK_1K_SIZE (1024)
#define BLK_1K_NUM  (256)
/*-----------------------------------*/
static unsigned char    BUFF_4M[BLK_NUM_4M][BLK_SIZE_4M];
static unsigned char    BUFF_2M[BLK_NUM_2M][BLK_SIZE_2M];
static unsigned char    BUFF_1K[BLK_1K_NUM][BLK_1K_SIZE];
/*-----------------------------------*/
static OS_MEM  m_os_4m_mem={0};
static OS_MEM  m_os_2m_mem={0};
static OS_MEM  m_os_1k_mem={0};
/*-----------------------------------*/
static OS_ERR  m_os_err={OS_ERR_NONE};
/*-----------------------------------*/
static sem_t   m_sem_4m_buff;
static sem_t   m_sem_2m_buff;
static sem_t   m_sem_1K_buff;
/*-----------------------------------*/
static  OS_MEM*			p_pool_os_mem[]={
										&m_os_4m_mem,
										&m_os_2m_mem,
										&m_os_1k_mem
										};

static    char  	p_pool_name[][64]={
										"mem4m",
										"mem2m",
										"mem1k"
										};

static    void*  	p_pool_addr[]={
										&BUFF_4M[0][0],
										&BUFF_2M[0][0],
										&BUFF_1K[0][0]
										};

static const unsigned int  		pool_blks[]={
										BLK_NUM_4M,
										BLK_NUM_2M,
										BLK_1K_NUM
										};

static const unsigned int  		pool_size[]={
										BLK_SIZE_4M,
										BLK_SIZE_2M,
										BLK_1K_SIZE
										};

static  sem_t*   			p_pool_sem[]={
										&m_sem_4m_buff,
										&m_sem_2m_buff,
										&m_sem_1K_buff
										};
/*-----------------------------------*/
#define PRINTF_MEM_USAGE	(0)
/*-----------------------------------*/
/**
 *检查内存地址？
 */
/*-----------------------------------*/
int MemPoolAddrZone(const void * _mem)
{

		const CPU_ADDR _mem_addr=(CPU_ADDR)_mem;

		const CPU_ADDR mem_1K_start=(CPU_ADDR) (BUFF_1K);
		const CPU_ADDR mem_1K_end= (CPU_ADDR)  ((void *) &BUFF_1K[BLK_1K_NUM-1][BLK_1K_SIZE-1]);

		const CPU_ADDR mem_2m_start=(CPU_ADDR) (BUFF_2M);
		const CPU_ADDR mem_2m_end=(CPU_ADDR)  ((void *) &BUFF_2M[BLK_NUM_2M-1][BLK_SIZE_2M-1]);

		const CPU_ADDR mem_4m_start=(CPU_ADDR) (BUFF_4M);
		const CPU_ADDR mem_4m_end=(CPU_ADDR)  ((void *) &BUFF_4M[BLK_NUM_4M-1][BLK_SIZE_4M-1]);

			if(		(_mem_addr >= mem_1K_start )&&
					(_mem_addr <= mem_1K_end )){

					return BLK_1K_SIZE;

			}else if(	(_mem_addr >= mem_2m_start)&&
						(_mem_addr <= mem_2m_end)){

					return 	BLK_SIZE_2M;

			}else if((_mem_addr >= mem_4m_start)&&
						(_mem_addr <= mem_4m_end)){

					return 	BLK_SIZE_4M;

			}else if(_mem_addr==0){
					return 0;// no mem
			}else{
					return  1; //free()
			}

		return -1;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void create_mem_pool(OS_MEM       *p_mem,
        CPU_CHAR     *p_name,
        void         *p_addr,
        OS_MEM_QTY    n_blks,
        OS_MEM_SIZE   blk_size,
        OS_ERR       *p_err,
        sem_t		 *p_sem)
{

	OSMemCreate(p_mem, p_name, p_addr,n_blks,blk_size, p_err);

		if (*p_err == OS_ERR_NONE) {

					int nRet = sem_init(p_sem, 0,  n_blks-1);

					if (0 != nRet)
						exit(-1);

		}else{
			printf("mem init error");
			exit(-1);
		}

}
/*-----------------------------------*/
/**
 *创建并初始化内存池
 */
/*-----------------------------------*/
void init_mem_pool() 
{
#if 1
	const int cpu_addr=sizeof(CPU_ADDR);
	assert(cpu_addr==4);
#endif

	const int POOL_NUMS=sizeof(pool_blks)/sizeof(unsigned int);

	int pi=0;

	for(pi=0;pi<POOL_NUMS;pi++){

		create_mem_pool(p_pool_os_mem[pi],
						&p_pool_name[pi][0],
						p_pool_addr[pi],
						pool_blks[pi],
						pool_size[pi],
						&m_os_err,
						p_pool_sem[pi]
						);

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

		 sem_wait(&m_sem_1K_buff);
		 data = (unsigned char *)OSMemGet(&m_os_1k_mem, &m_os_err);

	}else if(_size>BLK_1K_SIZE && _size<=BLK_SIZE_2M){

		 sem_wait(&m_sem_2m_buff);
		 data = (unsigned char *)OSMemGet(&m_os_2m_mem, &m_os_err);

	}else if(_size>BLK_SIZE_2M && _size<=BLK_SIZE_4M){

		sem_wait(&m_sem_4m_buff);
		 data = (unsigned char *)OSMemGet(&m_os_4m_mem, &m_os_err);

	}else{
			return malloc(_size);
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
				if (m_os_err == OS_ERR_NONE) {
					sem_post(&m_sem_1K_buff);
				}

	}else if(ADDR_ZONE==BLK_SIZE_2M){

				OSMemPut(&m_os_2m_mem, _mem, &m_os_err);
				if (m_os_err == OS_ERR_NONE) {
					sem_post(&m_sem_2m_buff);
				}

	}else if(ADDR_ZONE==BLK_SIZE_4M){

				OSMemPut(&m_os_4m_mem, _mem, &m_os_err);
				if (m_os_err == OS_ERR_NONE) {
					sem_post(&m_sem_4m_buff);
				}

	}else if(ADDR_ZONE==0){
			 return;//no mem
	}else if(ADDR_ZONE==1){
			free(_mem);
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
 *释放命令空间
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

int destory_mem_pool()
{

	CPU_IntDestory();

	const int result_t=sem_destroy(&m_sem_2m_buff);

	return result_t;

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
