#define _BSD_SOURCE
#define _GNU_SOURCE
#define _XOPEN_SOURCE 500
#include <assert.h>
#include <fcntl.h>
#include <getopt.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>

#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <sys/ioctl.h>
#include<sched.h>
#include<netinet/in.h>
#include <netinet/ip.h>
#include <sys/syscall.h>

#include <sys/socket.h>
#include <linux/netlink.h>
#include <sys/mman.h>
#include <pthread.h>

#include "../include/dma_test.h"

unsigned char *g_dma_virtual_baseaddr = NULL;
unsigned char *g_ps_ddr_virtual_baseaddr = NULL;
unsigned char *g_pl_ddr_virtual_baseaddr = NULL;
uint32_t g_transfer_id = 0;
unsigned int g_dma_flag = 0;
struct timeval btime,etime;
float costtime;
int dma_mallc_enable = 0;
struct user_msg_info dma_alloc_info;

#define MAX_PLOAD        125

struct user_msg {
    unsigned long type;
    unsigned long phy_addr;
    unsigned long virt_addr;
    unsigned long size;
} user_msg;


struct user_msg_info
{
    struct nlmsghdr hdr;
    struct user_msg msg;
};

struct user_msg msg_send;

struct sock_info
{
    int skfd;
    struct nlmsghdr *nlh;
    struct sockaddr_nl *daddr;
};



int read_netlink_init(struct sock_info *info , struct nlmsghdr **nlh, struct sockaddr_nl **daddr)
{
    int ret, skfd;
    struct sockaddr_nl saddr;

    /* creat NETLINK socket */
    skfd = socket(AF_NETLINK, SOCK_RAW, 30);
    if(skfd == -1) {
        printf("create socket error\n");
        return -1;
    }
    info->skfd = skfd;

    memset(&saddr, 0, sizeof(saddr));
    saddr.nl_family = AF_NETLINK; //AF_NETLINK
    saddr.nl_pid = 100;
    saddr.nl_groups = 0;
    if(bind(skfd, (struct sockaddr *)&saddr, sizeof(saddr)) != 0) {
        printf("bind() error\n");
        close(skfd);
        return -1;
    }

    *daddr = malloc(sizeof(struct sockaddr_nl));
    if(*daddr == NULL) {
        printf("malloc failed\n");
        return -1;
    }
    memset(*daddr, 0, sizeof(struct sockaddr_nl));
    (*daddr)->nl_family = AF_NETLINK;
    (*daddr)->nl_pid = 0; // to kernel
    (*daddr)->nl_groups = 0;

    *nlh = (struct nlmsghdr *)malloc(NLMSG_SPACE(MAX_PLOAD));
    if(*nlh == NULL) {
        printf("malloc failed\n");
        free(*daddr);
        return -1;
    }
    memset(*nlh, 0, sizeof(struct nlmsghdr));
    (*nlh)->nlmsg_len = NLMSG_SPACE(MAX_PLOAD);
    (*nlh)->nlmsg_flags = 0;
    (*nlh)->nlmsg_type = 0;
    (*nlh)->nlmsg_seq = 0;
    (*nlh)->nlmsg_pid = saddr.nl_pid; //self port

    return 0;
}

int get_dma_alloc_info(void)
{
    int ret;
    socklen_t len;
    struct sock_info sk_info;
    
    ret = read_netlink_init(&sk_info, &(sk_info.nlh), &(sk_info.daddr));
    if(ret != 0) 
    {
        printf("read_netlink_init failed!\n");
        return -1;
    }
    

    ret = recvfrom(sk_info.skfd , &dma_alloc_info, sizeof(struct user_msg_info), 0, (struct sockaddr *)(sk_info.daddr), &len);
    if(!ret) 
    {
        printf("recv form kernel error\n");
        close(sk_info.skfd);
        return -1;
    }
    
    printf("recvfrom user_msg.phy_addr = 0x%lx, user_msg.virt_addr = 0x%lx, user_msg.size = 0x%lx\n",\
    dma_alloc_info.msg.phy_addr, dma_alloc_info.msg.virt_addr, dma_alloc_info.msg.size);
    
    close(sk_info.skfd);
    free((void *)(sk_info.nlh));
    free((void *)(sk_info.daddr));
    return 0;
}



void pl_dma_read(uint32_t regAddr, uint32_t *data)
{
    *data = *(volatile unsigned int*)(g_dma_virtual_baseaddr + regAddr);
}

void pl_dma_write(uint32_t regAddr, uint32_t data)
{
    *(volatile unsigned int*)(g_dma_virtual_baseaddr + regAddr) = data;
}

int dmac_addr_mmap(void)
{
    int fd = -1;
 
    fd = open(MEM_DEV, O_RDWR|O_SYNC);
    if(fd < 0)
    {
        printf("open %s failed!\n",MEM_DEV);
        return -1;
    }
  
	// DMA3
    g_dma_virtual_baseaddr = mmap(NULL, PL_RX_DMA_MMAP_LENGTH , \
		PROT_READ | PROT_WRITE, MAP_SHARED, fd, PL_RX_DMA_BASEADDR);
    if(g_dma_virtual_baseaddr == NULL)
    {
        printf("mmap failed!\n");
        close(fd);
        return -1;
    }
	
    printf("mmap dma_base_addr[0x%08x] to [0x%08x] successfully!\n",\
		PL_RX_DMA_BASEADDR, g_dma_virtual_baseaddr);

	// ps
    if(0 == dma_mallc_enable)
    {
        g_ps_ddr_virtual_baseaddr = mmap(NULL, PS_DDR_LENGTH_FOR_DMA ,	\
		    PROT_READ | PROT_WRITE, MAP_SHARED, fd, PS_DDR_PHYADDR_FOR_DMA);
        if(g_ps_ddr_virtual_baseaddr == NULL)
        {
            printf("mmap failed!\n");
            close(fd);
            munmap(g_dma_virtual_baseaddr, PL_RX_DMA_MMAP_LENGTH);
            g_dma_virtual_baseaddr = NULL;
            return -1;
        }	
        
        printf("mmap ps_ddr_addr[0x%08x] to [0x%08x] successfully!\n", \
            PS_DDR_PHYADDR_FOR_DMA, g_ps_ddr_virtual_baseaddr);
    }else
    {
        g_ps_ddr_virtual_baseaddr = dma_alloc_info.msg.virt_addr;
        
        printf("dma alloc phy [0x%08x] to virt [0x%08x] successfully!\n", \
            dma_alloc_info.msg.phy_addr, g_ps_ddr_virtual_baseaddr);
    }
    

	// pl
    g_pl_ddr_virtual_baseaddr = mmap(NULL, PS_DDR_LENGTH_FOR_DMA , 	\
		PROT_READ | PROT_WRITE, MAP_SHARED, fd, PL_DDR_SRC_ADDR);
    if(g_pl_ddr_virtual_baseaddr == NULL)
    {
        printf("mmap failed!\n");
        close(fd);
        munmap(g_dma_virtual_baseaddr, PL_RX_DMA_MMAP_LENGTH);
        g_dma_virtual_baseaddr = NULL;
        munmap(g_ps_ddr_virtual_baseaddr, PS_DDR_LENGTH_FOR_DMA);
        g_ps_ddr_virtual_baseaddr = NULL;
        return -1;
    }	


    printf("mmap pl_ddr_addr[0x%08x] to [0x%08x] successfully!\n", \
		PL_DDR_SRC_ADDR, g_pl_ddr_virtual_baseaddr);
	
    close(fd); 
    return 0;
}
static int memcmp1(const void * cs,const void * ct,int count)
{
	const unsigned char *su1, *su2;
	int res = 0;
	for( su1 = cs, su2 = ct; 0 < count; ++su1, ++su2, count--)
		if ((res = *su1 - *su2) != 0)
			break;
	return res;
}

int dmac_transfer_init(void)
{
    uint32_t reg_val;
    struct timeval btime,etime;
    float costtime;
    int ret;
    memset(g_pl_ddr_virtual_baseaddr, 0xa5, PS_DDR_LENGTH_FOR_DMA);
	memset(g_ps_ddr_virtual_baseaddr, 0x3, PS_DDR_LENGTH_FOR_DMA);
	
    pl_dma_write(AXI_DMAC_REG_CTRL, 0x0);
    pl_dma_write(AXI_DMAC_REG_CTRL, AXI_DMAC_CTRL_ENABLE);
	
    pl_dma_write(AXI_DMAC_REG_IRQ_MASK, 0x0);
    pl_dma_read(AXI_DMAC_REG_TRANSFER_ID, &g_transfer_id);
    printf("[debug]transfer_id=0x%x\n", g_transfer_id);
    
    pl_dma_read(AXI_DMAC_REG_IRQ_PENDING, &reg_val);
    printf("[debug]reg_val=0x%x\n", reg_val);
    pl_dma_write(AXI_DMAC_REG_IRQ_PENDING, reg_val);
    
    if(0 == dma_mallc_enable)
    {    
        pl_dma_write(AXI_DMAC_REG_DEST_ADDRESS, PL_DDR_SRC_ADDR);
    }else
    {
        pl_dma_write(AXI_DMAC_REG_DEST_ADDRESS, dma_alloc_info.msg.phy_addr);
    }
	pl_dma_write(AXI_DMAC_REG_SRC_ADDRESS, PS_DDR_PHYADDR_FOR_DMA);
    pl_dma_write(AXI_DMAC_REG_DEST_STRIDE, 0x0);
    pl_dma_write(AXI_DMAC_REG_X_LENGTH, PS_DDR_LENGTH_FOR_DMA - 1);
    pl_dma_write(AXI_DMAC_REG_Y_LENGTH, 0x0);

    gettimeofday(&btime,NULL); //start time
    
    pl_dma_write(AXI_DMAC_REG_START_TRANSFER, 0x1);

    /* Wait until the new transfer is queued. */
    do 
    {
        pl_dma_read(AXI_DMAC_REG_START_TRANSFER, &reg_val);
    }while(reg_val == 1);
   
//    printf("[debug]the new transfer is queued. \n");

	    /* Wait until the current transfer is completed. */
    do 
    {
        pl_dma_read(AXI_DMAC_REG_IRQ_PENDING, &reg_val);
    }while(reg_val != (AXI_DMAC_IRQ_SOT | AXI_DMAC_IRQ_EOT));

    pl_dma_write(AXI_DMAC_REG_IRQ_PENDING, reg_val); /*clear interrupt*/

    gettimeofday(&etime,NULL); //start time
    costtime = 1000000*(etime.tv_sec - btime.tv_sec) + (etime.tv_usec - btime.tv_usec);
    costtime /= 1000;	
    printf("total cost time: %.4f ms\n", costtime);
    printf("[debug]the current transfer is completed.\n");
    if(0 == (ret= memcmp1(g_pl_ddr_virtual_baseaddr, g_ps_ddr_virtual_baseaddr, PS_DDR_LENGTH_FOR_DMA)))
        printf("dma copy from ps to pl successfully!len=0x%x\n", PS_DDR_LENGTH_FOR_DMA);
    else
        printf("dma copy from ps to pl fail!len=0x%x,ret=%d\n", PS_DDR_LENGTH_FOR_DMA,ret);
    
    return 0;
}


int main(int argc, char* argv[])
{
    int ret, i;
    
    if(argc == 2 && atoi(argv[1]) == 1)
    {
        dma_mallc_enable = 1;
    }
    else
        dma_mallc_enable = 0;
    
    if(dma_mallc_enable == 1)
    {   
        ret = get_dma_alloc_info();
        if(ret != 0) 
        {
            printf("get dma alloc info failed!\n");
            goto error2;
        }
    }
    
    ret = dmac_addr_mmap();
    if(ret != 0) 
    {
        printf("dmac_addr_mmap failed!\n");
        goto error2;
    }

    /*initialize dma to transfer data from ps to pl*/	
	printf("DMA start transfer--!\n");
    dmac_transfer_init();

    munmap(g_dma_virtual_baseaddr, PL_RX_DMA_MMAP_LENGTH);
    g_dma_virtual_baseaddr = NULL;
    munmap(g_ps_ddr_virtual_baseaddr, PS_DDR_LENGTH_FOR_DMA);
    g_ps_ddr_virtual_baseaddr = NULL;
    munmap(g_pl_ddr_virtual_baseaddr, PS_DDR_LENGTH_FOR_DMA);
    g_pl_ddr_virtual_baseaddr = NULL;	
error2:
    return 0;
}



