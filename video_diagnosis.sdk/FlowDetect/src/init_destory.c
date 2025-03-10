#include "init_destory.h"
#include "flame_monitor.h"
#include "img_cfg/img_cfg_scar.h"
/*-----------------------------------*/
static unsigned char G_MAC_ADDR[6]={0};
static unsigned char G_IP_ADDR[4]={0};
static const char G_ETH[]="eth0";
/*-----------------------------------*/
/**
 *打印IP
 */
/*-----------------------------------*/
int init_ip_addr(const char *ifname)
{
			int rc = 0;
	        struct sockaddr_in *addr = NULL;

	        struct ifreq ifr;
	        memset(&ifr, 0, sizeof(struct ifreq));

	        char mask[16] = { 0 };
	        char ipv4[16] = { 0 };

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

	        addr = (struct sockaddr_in *)&ifr.ifr_addr;
	        strncpy(ipv4, inet_ntoa(addr->sin_addr), sizeof(ipv4));

	       memcpy(G_IP_ADDR,&(addr->sin_addr),sizeof( uint32_t));

	        /* 4. get the mask */
	        if ((rc = ioctl(fd, SIOCGIFNETMASK, &ifr)) != 0)
	                goto done;


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
 *打印mac地址
 */
/*-----------------------------------*/
int init_mac_addr(const char *ifname)
{
	 	struct ifreq ifreq;  //ifreq用来配置ip地址，激活接口，配置MTU等接口信息的
	    int sock = 0;
	    char mac[32] = "";

	    sock = socket(AF_INET,SOCK_STREAM,0);
	    if(sock < 0)
	    {
	        perror("error sock");
	        return 2;
	    }

	    strcpy(ifreq.ifr_name,ifname);
	    if(ioctl(sock,SIOCGIFHWADDR,&ifreq) < 0)  //运行终端口命令 eth0
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
 *测试打印1个bit的长度
 */
/*-----------------------------------*/
void test_bitwidth()
{
	const int BITWIDTH=sizeof(void*);
	PRINTF_DBG_EX("bit Width is :%d !\n",BITWIDTH*8);
}
/*-----------------------------------*/
/**
 *测试mac地址和ip
 */
/*-----------------------------------*/
void test_mac_addr()
{
	init_mac_addr(G_ETH);  //打印mac地址
	init_ip_addr(G_ETH);   //打印IP

	if(G_MAC_ADDR[5]!=G_IP_ADDR[3]){
		  PRINTF_DBG_EX("must G_MAC_ADDR[5]==G_IP_ADDR[3] !\n");
		  exit(EXIT_FAILURE);
	}
}

/*-----------------------------------*/
/**
 *测试
 */
/*-----------------------------------*/
void test()
{
	test_bitwidth();  //测试打印1个bit的长度
	test_mac_addr();  //测试mac地址和ip
	test_life_cycle();  //测试产品剩余服务期限
}
/*-----------------------------------*/
/**
 *读取项目配置文件img.cfg.json.txt的参数，并记录至项目变量中且发送至FPGA
 */
/*-----------------------------------*/
void init_param()
{

	LoadImgCfgJson();  //读取项目配置文件img.cfg.json.txt的JSON数据，并将相关参数记录至项目变量中且发送至FPGA

	if(GetProjectRun()==inside08){

		fpga_img_svm_enable(0);  //向FPGA使能SVM
	}

}
/*-----------------------------------*/
/**
 *初始化并创建项目配置文件目录：/media/sdcard/project.cfg./项目运行模式
 */
/*-----------------------------------*/
void init_once()
{
	MakeProjectDirectory(); //初始化并创建项目配置文件目录：/media/sdcard/project.cfg./项目运行模式
}
/*-----------------------------------*/
/**
 *初始化设备（重置启动FPGA+读取已存蒙板数据+读取配置文件中参数并设置）
 */
/*-----------------------------------*/
void init_device()
{
	fpga_img_scar_reset();  //重置启动FPGA 向FPGA发送命令0和1
	InitMaskImage_scar();   //初始化0号和已保存在sd卡中的蒙板数据，并进行dma数据交互
	init_param();  //读取项目配置文件img.cfg.json.txt的参数，并记录至项目变量中且发送至FPGA
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void install()
{
		init_mem_pool();

		FPGA_CTRL_mmap();
		get_queue_img_buff();
		dmac_83c0_addr_mmap_hw();
		dmac_83c1_addr_mmap_hw();
		initSemSignal();
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void uninstall()
{
		FPGA_CTRL_unmmap();
		remove_queue_img_buff();
		dmac_83c0_addr_unmap_hw();
		dmac_83c1_addr_mmap_hw();
		destorySemSignal();

		destory_mem_pool();
}
/*-----------------------------------*/
/**
 *程序初始化（初始化内存池+重置启动FPGA+读取已存蒙板数据+读取配置文件中参数并设置）
 */
/*-----------------------------------*/
void init()
{
	PrintBuildTime();  //打印版本号和编译时间
	init_once();  //初始化并创建项目配置文件目录：/media/sdcard/project.cfg./项目运行模式
	install();  //创建并初始化内存池
	init_device();  //初始化设备（重置启动FPGA+读取已存蒙板数据+读取配置文件中参数并设置）
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void destory()
{
	sleep(3);
	uninstall();
}
/*-----------------------------------*/
/**
 *主处理函数
 */
/*-----------------------------------*/
int main_ring()
{
	init();  //程序初始化（初始化内存池+重置启动FPGA+读取已存蒙板数据+读取配置文件中参数并设置）
#ifdef _DEBUG
	test();  //测试
#endif

#if TRUE
	create_server_timers();  //定时刷新和校验已服务时间和剩余服务期
#endif

	pthread_t thread_task_tcp_igniter;

	pthread_t thread_task_inner_rcv=inner_image_buff_trans_server(NULL); //（若无客户端相连）图片数据交互线程  从图片消息队列中读取图片，并释放空间
	pthread_t thread_task_tcp_rcv=tcp_image_buff_trans_server(NULL);   //创建与IPC-图片交互的服务端线程

	sleep(1);//let tcp data trans thread start first 让TCP数据交互线程先启动

	pthread_t thread_task_tcp_flow=task_flow_ctrl_server();   //创建与IPC-cmd交互的服务端线程
	pthread_t thread_task_fpga_cvt=init_fpga_cvt_server(NULL);  //fpga
	pthread_t thread_task_dma=init_dma_server(NULL);  //dma
	pthread_t thread_task_memcpy=init_memcpy_server(NULL);  //内存块

	if(IsProjectRun(flame_monitor)){
		thread_task_tcp_igniter=connect_to_igniter();   //点火器
	}else if(IsProjectRun(scar_detect_01)){

	}else{
			assert(0);
	}

	run_main();
	destory();
#if 1
	pthread_join(thread_task_inner_rcv,NULL);
	pthread_join(thread_task_tcp_flow,NULL);
	pthread_join(thread_task_tcp_rcv,NULL);
	pthread_join(thread_task_fpga_cvt,NULL);
	pthread_join(thread_task_dma,NULL);
	pthread_join(thread_task_memcpy,NULL);

	if(IsProjectRun(flame_monitor)){
		pthread_join(thread_task_tcp_igniter,NULL);
	}else if(IsProjectRun(scar_detect_01)){

	}else{
		assert(0);
	}

#endif
	return EXIT_SUCCESS;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void run_main()
{
	int time_t=0;
	do{

			sleep(1);

			if(time_t++%10==0){

			}


	}while(IsRun());
}
/*-----------------------------------*/
/**
 *判断项目运行模式：外圆？内圆？单目
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
 *根据argv参数判断并设定项目运行模式：外圆？内圆？单目
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
	  }else	  if(IsCmdProject(_cmd_param,flame_monitor)){
 		  	  SetProjecRun(flame_monitor);
	  }
	  else{
		  assert(0);
		  PRINTF_DBG_EX("no in,no out ! \n");
	  }

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
