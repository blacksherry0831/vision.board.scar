#include "dma_hw_base.h"
/*-----------------------------------*/

/*-----------------------------------*/
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int dmac_addr_mmap_hw_base(DMA_PS_PL_OBJ* _dma_obj)
{

    int fd = -1;

    fd = open(_dma_obj->DEV, O_RDWR|O_SYNC);
    if(fd < 0)
    {
        PRINTF_DBG_EX("open %s failed!\n",_dma_obj->DEV);
        return -1;
    }

    _dma_obj->DMA_Base_Addr_Virtual =(unsigned char*) mmap(
    		NULL,
    		_dma_obj->DMA_Space_size ,
    		PROT_READ | PROT_WRITE,
    		MAP_SHARED,
    		fd,
    		_dma_obj->DMA_Base_Addr_Phy);

    if(_dma_obj->DMA_Base_Addr_Virtual == NULL)
    {
        PRINTF_DBG_EX("mmap failed!\n");
        close(fd);
        return -1;
    }else{
     PRINTF_DBG_EX("mmap dma_base_addr[0x%08x] to [0x%08x] successfully!\n",
    		_dma_obj->DMA_Base_Addr_Phy,
    		(unsigned int)_dma_obj->DMA_Base_Addr_Virtual);
    }




    _dma_obj->MEM_PS_Base_Addr_Virtual = (unsigned char*) mmap(NULL,
    		_dma_obj->MEM_PS_Space_size,
    		PROT_READ | PROT_WRITE,
    		MAP_SHARED,
    		fd,
    		_dma_obj->MEM_PS_Base_Addr_Phy);


    if(_dma_obj->MEM_PS_Base_Addr_Virtual == NULL)
    {
        PRINTF_DBG_EX("mmap failed!\n");
        close(fd);
        munmap(_dma_obj->DMA_Base_Addr_Virtual,
        		_dma_obj->DMA_Space_size);
        _dma_obj->DMA_Base_Addr_Virtual = NULL;
        return -1;
    }else{
     PRINTF_DBG_EX("mmap ps_ddr_addr[0x%08x] to [0x%08x] successfully!\n",
    		_dma_obj->MEM_PS_Base_Addr_Phy,
		(unsigned int)_dma_obj->MEM_PS_Base_Addr_Virtual);
    }



    close(fd);
    return 0;
}

/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int dmac_addr_unmap_hw_base(DMA_PS_PL_OBJ* _dma_obj)
{

    if( _dma_obj->DMA_Base_Addr_Virtual != NULL)
    {
        munmap( _dma_obj->DMA_Base_Addr_Virtual, _dma_obj->DMA_Space_size);
        _dma_obj->DMA_Base_Addr_Virtual = NULL;
    }




    if(_dma_obj->MEM_PS_Base_Addr_Virtual != NULL)
    {
        munmap(_dma_obj->MEM_PS_Base_Addr_Virtual, _dma_obj->MEM_PS_Space_size);
        _dma_obj->MEM_PS_Base_Addr_Virtual = NULL;
    }

    return 0;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void pl_dma_read_base(
		const DMA_PS_PL_OBJ* _dma_obj,
		const uint32_t _regAddr,
		uint32_t *_data)
{
	 assert(_dma_obj->DMA_Base_Addr_Virtual !=NULL);

    *_data = *(volatile unsigned int*)(_dma_obj->DMA_Base_Addr_Virtual + _regAddr);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void pl_dma_write_base(
		DMA_PS_PL_OBJ* 	_dma_obj,
		const uint32_t 	_regAddr,
		uint32_t *		_data)
{
    *(volatile unsigned int*)( _dma_obj->DMA_Base_Addr_Virtual + _regAddr ) = (unsigned int) _data;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/

/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int dmac_config_and_transfer_base(
		DMA_PS_PL_OBJ* 	_dma_obj,
		unsigned int dst_phyaddr,
		unsigned int src_phyaddr,
		unsigned int len)
{
    uint32_t reg_val;
    pl_dma_write_base(_dma_obj,AXI_DMAC_REG_CTRL, 0x0);
    pl_dma_write_base(_dma_obj,AXI_DMAC_REG_CTRL, (uint32_t*)AXI_DMAC_CTRL_ENABLE);
    pl_dma_write_base(_dma_obj,AXI_DMAC_REG_IRQ_MASK, 0x0);
    pl_dma_read_base(_dma_obj,AXI_DMAC_REG_TRANSFER_ID, &_dma_obj->transfer_id);

    pl_dma_read_base(_dma_obj,AXI_DMAC_REG_IRQ_PENDING, &reg_val);
    pl_dma_write_base(_dma_obj,AXI_DMAC_REG_IRQ_PENDING, &reg_val);

    pl_dma_write_base(_dma_obj,AXI_DMAC_REG_DEST_ADDRESS, (uint32_t*)dst_phyaddr);
    pl_dma_write_base(_dma_obj,AXI_DMAC_REG_SRC_ADDRESS, (uint32_t*)src_phyaddr);

    pl_dma_write_base(_dma_obj,AXI_DMAC_REG_DEST_STRIDE, 0x0);
    pl_dma_write_base(_dma_obj,AXI_DMAC_REG_X_LENGTH, (uint32_t*)(len - 1));
    pl_dma_write_base(_dma_obj,AXI_DMAC_REG_Y_LENGTH, 0x0);

    pl_dma_write_base(_dma_obj,AXI_DMAC_REG_START_TRANSFER, (uint32_t*)0x1);

    /* Wait until the new transfer is queued. */
    do
    {
        pl_dma_read_base(_dma_obj,AXI_DMAC_REG_START_TRANSFER, &reg_val);
    }while(reg_val == 1);

    /* Wait until the current transfer is completed. */
    do
    {
        pl_dma_read_base(_dma_obj,AXI_DMAC_REG_IRQ_PENDING, &reg_val);
    }while(reg_val != (AXI_DMAC_IRQ_SOT | AXI_DMAC_IRQ_EOT));

    pl_dma_write_base(_dma_obj,AXI_DMAC_REG_IRQ_PENDING, (uint32_t*)reg_val); /*clear interrupt*/

    return 0;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
