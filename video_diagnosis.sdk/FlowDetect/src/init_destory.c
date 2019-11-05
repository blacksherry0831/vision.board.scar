#include "init_destory.h"
/*-----------------------------------*/
unsigned char G_MAC_ADDR[6]={0};
unsigned char G_IP_ADDR[4]={0};
const char G_ETH[]="eth0";
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int init_ip_addr(const char *ifname)
{
			int rc = 0;
	        struct sockaddr_in *addr = NULL;

	        struct ifreq ifr;
	        memset(&ifr, 0, sizeof(struct ifreq));

	        /* 0. create a socket */
	        int fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
	        if (fd == -1)
	                return -1;

	        /* 1. set type of address to retrieve : IPv4 */
	        ifr.ifr_addr.sa_family = AF_INET;

	        /* 2. copy interface name to ifreq structure */
	        strncpy(ifr.ifr_name, ifname, IFNAMSIZ - 1);

	        /* 3. get the IP address */
	        if ((rc = ioctl(fd, SIOCGIFADDR, &ifr)) != 0)
	                goto done;

	        char ipv4[16] = { 0 };
	        addr = (struct sockaddr_in *)&ifr.ifr_addr;
	        strncpy(ipv4, inet_ntoa(addr->sin_addr), sizeof(ipv4));

	       memcpy(G_IP_ADDR,&(addr->sin_addr),sizeof( uint32_t));

	        /* 4. get the mask */
	        if ((rc = ioctl(fd, SIOCGIFNETMASK, &ifr)) != 0)
	                goto done;

	        char mask[16] = { 0 };
	        addr = (struct sockaddr_in *)&ifr.ifr_addr;
	        strncpy(mask, inet_ntoa(addr->sin_addr), sizeof(mask));

	        /* 5. display */
	        printf("IFNAME:IPv4:MASK\n");
	        printf("%s:%s:%s\n", ifname, ipv4, mask);

	        /* 6. close the socket */
	done:
	        close(fd);

	        return rc;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int init_mac_addr(const char *ifname)
{
	 	struct ifreq ifreq;
	    int sock = 0;
	    char mac[32] = "";

	    sock = socket(AF_INET,SOCK_STREAM,0);
	    if(sock < 0)
	    {
	        perror("error sock");
	        return 2;
	    }

	    strcpy(ifreq.ifr_name,ifname);
	    if(ioctl(sock,SIOCGIFHWADDR,&ifreq) < 0)
	    {
	        perror("error ioctl");
	        return 3;
	    }

	    int i = 0;
	    for(i = 0; i < 6; i++){
	        sprintf(mac+3*i, "%02X:", (unsigned char)ifreq.ifr_hwaddr.sa_data[i]);
	        G_MAC_ADDR[i]=ifreq.ifr_hwaddr.sa_data[i];
	    }
	    mac[strlen(mac) - 1] = 0;
	    printf("MAC: %s\n", mac);

	    return 1;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void test_bitwidth()
{
	const int BITWIDTH=sizeof(void*);
		  PRINTF_DBG("bit Width is :%d !\n",BITWIDTH*8);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void test_mac_addr()
{
	init_mac_addr(G_ETH);
	init_ip_addr(G_ETH);

	if(G_MAC_ADDR[5]!=G_IP_ADDR[3]){
		  PRINTF_DBG("must G_MAC_ADDR[5]==G_IP_ADDR[3] !\n");
		  exit(EXIT_FAILURE);
	}
}

/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void test()
{
	test_bitwidth();
	test_mac_addr();
	test_life_cycle();
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void init_param()
{

	LoadImgCfgJson();

	if(GetProjectRun()==inside08){

		fpga_img_svm_enable(0);
	}

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void init()
{
	init_mem_pool();

	signal(SIGINT,StopRun);

	FPGA_CTRL_mmap();

	fpga_img_scar_reset();

	get_queue_img_buff();

	dmac_83c0_addr_mmap_hw();

	dmac_83c4_addr_mmap_hw();

	initSemSignal();

	init_param();
}

/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void destory()
{
	sleep(3);

	FPGA_CTRL_unmmap();

	remove_queue_img_buff();

	dmac_83c0_addr_unmap_hw();

	dmac_83c4_addr_mmap_hw();

	destorySemSignal();

	destory_mem_pool();
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int main_ring()
{

			init();
#if _DEBUG
			test();
#endif

			pthread_t thread_task_tcp_rcv=tcp_image_buff_trans_server(NULL);

			sleep(1);//let tcp data trans thread start first

				pthread_t thread_task_tcp_flow=task_flow_ctrl_server();


				pthread_t thread_task_fpga_cvt=init_fpga_cvt_server(NULL);
				pthread_t thread_task_dma=init_dma_server(NULL);
				pthread_t thread_task_memcpy=init_memcpy_server(NULL);


#if TRUE
				create_server_timers();
#endif
			run_main();


			destory();

			pthread_join(thread_task_tcp_flow,NULL);

			pthread_join(thread_task_tcp_rcv,NULL);

			pthread_join(thread_task_fpga_cvt,NULL);
			pthread_join(thread_task_dma,NULL);
			pthread_join(thread_task_memcpy,NULL);

			return EXIT_SUCCESS;

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void run_main()
{
	int time=0;
	do{

			sleep(1);

			if(time++%10==0){

			}


	}while(IsRun());
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int IsCmdProject(const struct cmd_param _cmd_param,enum ProjectRun _project )
{
	  if(strcmp(_cmd_param.project,ProjectName[_project])==0){
		  return 1;
	  }else{
		  return 0;
	  }
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void setProjectMode(const struct cmd_param _cmd_param)
{

	  if(IsCmdProject(_cmd_param,scar_detect_01)){
		  	  SetProjecRun(scar_detect_01);
	  }else	  if(IsCmdProject(_cmd_param,inside08)){
	 		  SetProjecRun(inside08);
	  }else	  if(IsCmdProject(_cmd_param,outside08)){
	 		  SetProjecRun(outside08);
	  }else{
		  printf("no in,no out ! \n");
	  }

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
