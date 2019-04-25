#include "dma.h"
/*-----------------------------------*/
volatile unsigned char  m_current_dmac_ch=0xFF;
volatile unsigned char  m_current_dmac_frame=0;
unsigned char *g_dma_virtual_baseaddr = NULL;
unsigned char *g_ps_ddr_virtual_baseaddr = NULL;
unsigned int g_pl_ddr_pyhaddr = NULL;
uint32_t g_transfer_id = 0;
/*-----------------------------------*/
MAP_OBJ  DMA_TRANS={0};
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/


pthread_mutex_t DMA_mutex_trans0 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t DMA_mutex_trans1 = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t  DMA_cond_trans0=PTHREAD_COND_INITIALIZER;

pthread_cond_t  DMA_cond_trans1=PTHREAD_COND_INITIALIZER;

unsigned int    DMA_TransDone=FALSE;
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void DmaTransDone01()
{
	pthread_mutex_lock(&DMA_mutex_trans0);//
		DMA_TransDone=TRUE;
	pthread_cond_signal(&DMA_cond_trans0);
	pthread_mutex_unlock(&DMA_mutex_trans0);//

	pthread_mutex_lock(&DMA_mutex_trans1);//
		DMA_TransDone=TRUE;
	pthread_cond_signal(&DMA_cond_trans1);
	pthread_mutex_unlock(&DMA_mutex_trans1);//

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int Wait4DmaTransDone0(long timeout_ms)
{
	int reslut_t=Wait4Signal(timeout_ms,&DMA_mutex_trans0,&DMA_cond_trans0);
	PRINTF_DBG("get DMA signal 00 \n");
	return reslut_t;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void SetCurrentDmaFrame(int _frame)
{
	m_current_dmac_frame=_frame;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int SetDmaFrameByWorkMode(int _wm)
{

			if(GetProjectRun()==outside08){

					SetCurrentDmaFrame(0);

			}else if(GetProjectRun()==inside08){

			if(WM_ORG_IMG==(GetFpgaCircleWorkMode()&WM_ORG_IMG)){
					SetCurrentDmaFrame(0);
			}else if(WM_DIFF_IMG==(GetFpgaCircleWorkMode()&WM_DIFF_IMG)){
					SetCurrentDmaFrame(1);
			}else{

			}

	}else{


	}
	return 0;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int Wait4DmaTransDone1(long timeout_ms)
{
	int reslut_t=Wait4Signal(timeout_ms,&DMA_mutex_trans1,&DMA_cond_trans1);
	PRINTF_DBG("get DMA signal 01 \n");
	return reslut_t;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void pl_dma_read(uint32_t regAddr, uint32_t *data)
{
	 assert(g_dma_virtual_baseaddr!=NULL);

    *data = *(volatile unsigned int*)(g_dma_virtual_baseaddr + regAddr);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void pl_dma_write(uint32_t regAddr, uint32_t data)
{
    *(volatile unsigned int*)(g_dma_virtual_baseaddr + regAddr) = data;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int dmac_addr_mmap(void)
{

	pthread_mutex_init(&(DMA_TRANS.lock),NULL);

    int fd = -1;

    fd = open(MEM_DEV, O_RDWR|O_SYNC);
    if(fd < 0)
    {
        PRINTF_DBG("open %s failed!\n",MEM_DEV);
        return -1;
    }

    g_dma_virtual_baseaddr = mmap(NULL, PL_RX_DMA_MMAP_LENGTH , \
		PROT_READ | PROT_WRITE, MAP_SHARED, fd, PL_RX_DMA_BASEADDR);
    if(g_dma_virtual_baseaddr == NULL)
    {
        PRINTF_DBG("mmap failed!\n");
        close(fd);
        return -1;
    }

    PRINTF_DBG("mmap dma_base_addr[0x%08x] to [0x%08x] successfully!\n",\
		PL_RX_DMA_BASEADDR, (unsigned int)g_dma_virtual_baseaddr);

    g_ps_ddr_virtual_baseaddr = mmap(NULL, PS_DDR_LENGTH_FOR_DMA ,	\
		PROT_READ | PROT_WRITE, MAP_SHARED, fd, PS_DDR_PHYADDR_FOR_DMA);
    if(g_ps_ddr_virtual_baseaddr == NULL)
    {
        PRINTF_DBG("mmap failed!\n");
        close(fd);
        munmap(g_dma_virtual_baseaddr, PL_RX_DMA_MMAP_LENGTH);
        g_dma_virtual_baseaddr = NULL;
        return -1;
    }

    PRINTF_DBG("mmap ps_ddr_addr[0x%08x] to [0x%08x] successfully!\n", \
		PS_DDR_PHYADDR_FOR_DMA, (unsigned int)g_ps_ddr_virtual_baseaddr);

    close(fd);
    return 0;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int dmac_addr_unmap(void)
{
	 pthread_mutex_lock(&DMA_TRANS.lock);

    if(g_dma_virtual_baseaddr != NULL)
    {
        munmap(g_dma_virtual_baseaddr, PL_RX_DMA_MMAP_LENGTH);
        g_dma_virtual_baseaddr = NULL;
    }

    if(g_ps_ddr_virtual_baseaddr != NULL)
    {
        munmap(g_ps_ddr_virtual_baseaddr, PS_DDR_LENGTH_FOR_DMA);
        g_ps_ddr_virtual_baseaddr = NULL;
    }
    pthread_mutex_unlock(&DMA_TRANS.lock);
    pthread_mutex_destroy(&(DMA_TRANS.lock));

    return 0;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int dmac_transfer_init_copy(unsigned char *dst_virtaddr, unsigned int src_phyaddr, unsigned int len)
{
    uint32_t reg_val;

    pl_dma_write(AXI_DMAC_REG_CTRL, 0x0);
    pl_dma_write(AXI_DMAC_REG_CTRL, AXI_DMAC_CTRL_ENABLE);

    pl_dma_write(AXI_DMAC_REG_IRQ_MASK, 0x0);

    pl_dma_read(AXI_DMAC_REG_TRANSFER_ID, &g_transfer_id);
//    PRINTF_DBG("[debug]transfer_id=0x%x \n", g_transfer_id);

    pl_dma_read(AXI_DMAC_REG_IRQ_PENDING, &reg_val);
//    PRINTF_DBG("[debug]reg_val=0x%x\n", reg_val);
    pl_dma_write(AXI_DMAC_REG_IRQ_PENDING, reg_val);

    pl_dma_write(AXI_DMAC_REG_DEST_ADDRESS, PS_DDR_PHYADDR_FOR_DMA);
    pl_dma_write(AXI_DMAC_REG_SRC_ADDRESS, src_phyaddr);
    pl_dma_write(AXI_DMAC_REG_DEST_STRIDE, 0x0);
    pl_dma_write(AXI_DMAC_REG_X_LENGTH, len - 1);
    pl_dma_write(AXI_DMAC_REG_Y_LENGTH, 0x0);

    pl_dma_write(AXI_DMAC_REG_START_TRANSFER, 0x1);
    /* Wait until the new transfer is queued. */
    do
    {
        pl_dma_read(AXI_DMAC_REG_START_TRANSFER, &reg_val);
    }while(reg_val == 1);
//   PRINTF_DBG("[debug]the new transfer is queued. \n");
	    /* Wait until the current transfer is completed. */
    do
    {
        pl_dma_read(AXI_DMAC_REG_IRQ_PENDING, &reg_val);
    }while(reg_val != (AXI_DMAC_IRQ_SOT | AXI_DMAC_IRQ_EOT));
    pl_dma_write(AXI_DMAC_REG_IRQ_PENDING, reg_val); /*clear interrupt*/
//    PRINTF_DBG("[debug]the current transfer is completed.\n");

    memcpy(dst_virtaddr, g_ps_ddr_virtual_baseaddr, len);
    return 0;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int dmac_config_and_transfer(unsigned int dst_phyaddr, unsigned int src_phyaddr, unsigned int len)
{
    uint32_t reg_val;
    pl_dma_write(AXI_DMAC_REG_CTRL, 0x0);
    pl_dma_write(AXI_DMAC_REG_CTRL, AXI_DMAC_CTRL_ENABLE);
    pl_dma_write(AXI_DMAC_REG_IRQ_MASK, 0x0);
    pl_dma_read(AXI_DMAC_REG_TRANSFER_ID, &g_transfer_id);
    pl_dma_read(AXI_DMAC_REG_IRQ_PENDING, &reg_val);
    pl_dma_write(AXI_DMAC_REG_IRQ_PENDING, reg_val);
    pl_dma_write(AXI_DMAC_REG_DEST_ADDRESS, dst_phyaddr);
    pl_dma_write(AXI_DMAC_REG_SRC_ADDRESS, src_phyaddr);
    pl_dma_write(AXI_DMAC_REG_DEST_STRIDE, 0x0);
    pl_dma_write(AXI_DMAC_REG_X_LENGTH, len - 1);
    pl_dma_write(AXI_DMAC_REG_Y_LENGTH, 0x0);
    pl_dma_write(AXI_DMAC_REG_START_TRANSFER, 0x1);
    do
    {
        pl_dma_read(AXI_DMAC_REG_START_TRANSFER, &reg_val);
    }while(reg_val == 1);
    do
    {
        pl_dma_read(AXI_DMAC_REG_IRQ_PENDING, &reg_val);
    }while(reg_val != (AXI_DMAC_IRQ_SOT | AXI_DMAC_IRQ_EOT));
    pl_dma_write(AXI_DMAC_REG_IRQ_PENDING, reg_val); /*clear interrupt*/
    return 0;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int dmac_transfer_init(void)
{
    uint32_t reg_val;

    pl_dma_read(0, &g_transfer_id);
    if(g_transfer_id != 0x40062)
    {
        PRINTF_DBG("[debug]dma id =0x%x\n", g_transfer_id);
    }

    pl_dma_write(AXI_DMAC_REG_CTRL, 0x0);
    pl_dma_write(AXI_DMAC_REG_CTRL, AXI_DMAC_CTRL_ENABLE);

    pl_dma_write(AXI_DMAC_REG_IRQ_MASK, 0x0);

    pl_dma_read(AXI_DMAC_REG_TRANSFER_ID, &g_transfer_id);
    //PRINTF_DBG("[debug]transfer_id=0x%x\n", g_transfer_id);

    pl_dma_read(AXI_DMAC_REG_IRQ_PENDING, &reg_val);
    //PRINTF_DBG("[debug]reg_val=0x%x\n", reg_val);
    pl_dma_write(AXI_DMAC_REG_IRQ_PENDING, reg_val);

    pl_dma_write(AXI_DMAC_REG_DEST_ADDRESS, PS_DDR_PHYADDR_FOR_DMA);
    pl_dma_write(AXI_DMAC_REG_SRC_ADDRESS, g_pl_ddr_pyhaddr);
    pl_dma_write(AXI_DMAC_REG_DEST_STRIDE, 0x0);
    pl_dma_write(AXI_DMAC_REG_X_LENGTH, EACH_FRAME_SIZE_FOR_CAMERA - 1);
    pl_dma_write(AXI_DMAC_REG_Y_LENGTH, 0x0);

    pl_dma_write(AXI_DMAC_REG_START_TRANSFER, 0x1);

    /* Wait until the new transfer is queued. */
    do
    {
        pl_dma_read(AXI_DMAC_REG_START_TRANSFER, &reg_val);
    }while(reg_val == 1);

   PRINTF_DBG("[debug]the new transfer is queued. \n");

	/* Wait until the current transfer is completed. */
    do
    {
        pl_dma_read(AXI_DMAC_REG_IRQ_PENDING, &reg_val);
    }while(reg_val != (AXI_DMAC_IRQ_SOT | AXI_DMAC_IRQ_EOT));
    PRINTF_DBG("[11111111111111debug]the current transfer is completed.\n");
    pl_dma_write(AXI_DMAC_REG_IRQ_PENDING, reg_val); /*clear interrupt*/


    return 0;
}


/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int write_tcp_direct_dmac(int socketfd,int _size)
{
    dmac_transfer_init();
    return writen(socketfd,g_ps_ddr_virtual_baseaddr,_size);

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
unsigned int GetFrameSizeOut08(int _frame)
{

	unsigned int  MAP_SIZE=0;
		if(_frame>=0&&_frame<=7){

				MAP_SIZE=image_size_frame();
		}else	if(_frame==-1){

				MAP_SIZE=IMAGE_SIZE_AVG;
		}else{
			assert(0);
		}
	return MAP_SIZE;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
unsigned int GetFrameSizeIn08(int _frame)
{

	unsigned int  MAP_SIZE=0;
		if(_frame>=0&&_frame<=7){

				MAP_SIZE=image_size_frame();
		}else	if(_frame==-1){

				MAP_SIZE=IMAGE_SIZE_AVG;
		}else{
			assert(0);
		}
	return MAP_SIZE;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
unsigned int GetFrameSize(int _frame)
{
	enum ProjectRun pr_t=GetProjectRun();

	if(pr_t==outside08){
		return GetFrameSizeOut08(_frame);
	}else if(pr_t==inside08){
		return GetFrameSizeIn08(_frame);
	}else{

	}

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
unsigned int getPhyChBaseAddr(int _ch)
{
	unsigned int Img_base_Addr=PL_DDR3_ADDR_BASE+_ch*CHANNEL_BLOCK_SIZE;
	return Img_base_Addr;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
unsigned int getPhyFrameBaseAddr(int _ch,int _frame)
{
	unsigned int  PhyChBaseAddr=getPhyChBaseAddr(_ch);
	unsigned int  PhyChFrameAddr=0;

	if(_frame>=0&&_frame<=7){


		if(GetProjectRun()==inside08){
			PhyChFrameAddr=PhyChBaseAddr+IMAGE_SIZE_AVG+_frame*image_size_frame();
		}else if(GetProjectRun()==outside08){
			PhyChFrameAddr=PhyChBaseAddr+IMAGE_SIZE_AVG+_frame*image_size_frame();
		}else{

		}


	}else if(_frame==-1){
				PhyChFrameAddr=PhyChBaseAddr;
	}else{
			assert(0);
	}

	return PhyChFrameAddr;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int video_map_dmac_ch(unsigned char _ch,int _frame,unsigned int *_phyaddr)
{
	unsigned int  PhyChFrameAddr=getPhyFrameBaseAddr(_ch,_frame);
	unsigned int  MAP_SIZE=GetFrameSize(_frame);

	*_phyaddr=PhyChFrameAddr;

	m_current_dmac_ch=_ch;

	return MAP_SIZE;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
unsigned int getDmaDstAddr(unsigned char _ch,int _frame)
{
	assert(_frame>=0);

	unsigned int  MAP_SIZE=GetFrameSize(_frame);
	unsigned int ps_phy_addr_dma = PS_DDR_PHYADDR_FOR_DMA + _ch*MAP_SIZE;//dma addr
	return ps_phy_addr_dma;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void dmac_trans(unsigned char _ch,int _frame)
{
	 if(pthread_mutex_lock(&DMA_TRANS.lock)==SUCCESS){

		 		unsigned int ps_phy_addr_dma=getDmaDstAddr(_ch,_frame);
				unsigned int phy_addr_img=0;
				int Size2tran=video_map_dmac_ch(_ch,_frame,&phy_addr_img);//image phy addr
				dmac_config_and_transfer(ps_phy_addr_dma,phy_addr_img, Size2tran);

				if(pthread_mutex_unlock(&DMA_TRANS.lock)==SUCCESS){
					return TRUE;
				}

	 }
			return FALSE;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void memcpyDMA2Mem(void *buff_dst,unsigned int _size)
{
	assert(_size<=PS_DDR_LENGTH_FOR_DMA);
	memcpy(buff_dst,g_ps_ddr_virtual_baseaddr,_size);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void memcpyDMA2MemCh(void *buff_dst,unsigned int _size,unsigned int _ch)
{

	assert(_size<=PS_DDR_LENGTH_FOR_DMA);

	//TIME_START();

	if(pthread_mutex_lock(&DMA_TRANS.lock)==SUCCESS){
			const unsigned char *src_addr=g_ps_ddr_virtual_baseaddr+_ch*image_size_frame();
			memcpy(buff_dst,src_addr,_size);
			if(pthread_mutex_unlock(&DMA_TRANS.lock)==SUCCESS){
				return TRUE;
			}
	}

	//TIME_END("memcpy a channel:");

	return FALSE;

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
unsigned char* GetVirtualAddrDMA(int _ch)
{
	unsigned char *src_addr=NULL;

	if(GetProjectRun()==inside08){
			src_addr=g_ps_ddr_virtual_baseaddr+_ch*image_size_frame();
	}else if(GetProjectRun()==outside08){
			src_addr=g_ps_ddr_virtual_baseaddr+_ch*image_size_frame();
	}else{

	}


	return src_addr;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int memcpyDMA2MemChEx(CMD_CTRL* img,unsigned int _ch)
{
	int result_t=FALSE;
#if 1
	TIME_START();
#endif

	assert(img->f_data_size<=PS_DDR_LENGTH_FOR_DMA);

	 if(pthread_mutex_lock(&DMA_TRANS.lock)==SUCCESS){

			unsigned char *src_addr=GetVirtualAddrDMA(_ch);

			CopyImage(src_addr,img,_ch);

			if(pthread_mutex_unlock(&DMA_TRANS.lock)==SUCCESS){

				result_t=TRUE;
			}

	 }

#if 1
	 PRINTF_DBG("Channel:[%d] ",_ch);

	TIME_END("memcpy a channel:");

#endif

	return result_t;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void dmac_trans_ex(unsigned char _ch,int _frame)
{

	if(GetGlobalChannelMask(_ch)){
			dmac_trans(_ch,_frame);
	}

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void *dma_work_server(void* _pdata)
{
	int chi=0;
	const unsigned time_ms=30*1000;
	static int DMA_COUNT=0;

	while(IsDMARun())
	{

								if(sem_wait_infinite(&m_sem_fpga_frame_done)!=SUCCESS) break;

								if(pthread_mutex_lock(&FPGA_mutex_cvt)==SUCCESS){

												if(pthread_mutex_lock(&DMA_mutex_trans0)==SUCCESS){

																	TIME_START();

																			for(chi=0;chi<8;chi++){
																				dmac_trans_ex(chi,m_current_dmac_frame);
																			}

																			PRINTF_DBG("DMA:%d___",DMA_COUNT++);

																	TIME_END("2> DMA cpy cost time");

																	if(pthread_mutex_unlock(&DMA_mutex_trans0)==SUCCESS){

																			if(pthread_mutex_unlock(&FPGA_mutex_cvt)==SUCCESS){

																						sem_post(&m_sem_dma_frame_done2Mem);
																						sem_post(&m_sem_dma_frame_done2fpga);
																						sched_yield();
																						sem_wait_infinite(&m_sem_memcpy_frame_done);


																		}
																	}

												}

								}



	}

	ExitDmaThread();
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
pthread_t init_dma_server(void *_data)
{
	pthread_t _thread_tid;
	if( pthread_create(&_thread_tid, NULL, dma_work_server, _data) ){
			PRINTF_DBG(" Create print_thread1 thread error!\n");
			exit(0);
	}
 return _thread_tid;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
