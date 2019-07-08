#include "dma_hw.h"
/*-----------------------------------*/

volatile unsigned char  m_current_dmac_frame=0;
/*-----------------------------------*/
unsigned char *g_dma_virtual_baseaddr = NULL;
unsigned char *g_ps_ddr_virtual_baseaddr = NULL;
unsigned int   g_pl_ddr_pyhaddr = NULL;
/*-----------------------------------*/
uint32_t g_transfer_id = 0;
/*-----------------------------------*/

/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
unsigned char *get_ps_ddr_virtual_baseaddr()
{
	return g_ps_ddr_virtual_baseaddr;
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
int dmac_addr_mmap_hw(void)
{

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
int dmac_addr_unmap_hw(void)
{

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
