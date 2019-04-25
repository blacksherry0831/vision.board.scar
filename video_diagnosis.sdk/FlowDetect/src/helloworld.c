// Ӧ�ó���
#include "linux_header.h"
#include "def.h"
#include "axi.h"
#include "tcp_server.h"
#include "task_flow.h"

#include "axi/axi_fpga_ctrl.h"
#include "init_destory.h"

/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
extern char* optarg;

extern int optind;

extern int opterr;

extern int optopt;

/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void test_memory()
{
		// >>>>>>>>>>>>>>>>>>>>>>>>>> �ڴ��д >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
		int i;
		unsigned char ucWrite[4096]={0},ucRead[4096]={0};

		for (i=0;i<4096;i++)
		{
			ucWrite[i]=i;
		}

		//DDR3 Saddr1 Init
		for (i=0;i<4096;i++)
		{
			AXILitemmap(DDR3_ADDR+i*4096);
			AXILitetoUser((int)g_virtual_addr, DDR3_ADDR+i*4096,ucWrite,4096);
			UsertoAXILite((int)g_virtual_addr, DDR3_ADDR+i*4096,ucRead,4096);
			if(0 != memcmp(ucRead,ucWrite,1024))
			{
				PRINTF_DBG("Error!\n");
			}
			AXILiteunmmap();
		}
		i=0;
		//<<<<<<<<<<<<<<<<<<<<<<<<<<<< �ڴ��д <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void printf_1_cmd_param(char* _optarg,int cmd,const char* _cmd_long)
{
	 	 if (_optarg){

			   printf ("option:[%s] %c argv: %s\n",_cmd_long, cmd, _optarg);
		}else{
				printf ("option:[%s] %c no argument\n",_cmd_long, cmd);
		}
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void printf_cmd_param(int optind,char* _optarg,int cmd)
{
	char buffer[128];

	printf("optind: %d\n", optind);

	   switch (cmd)
		        {
		               case 'i':
		            	   	   	   strcpy(buffer,"in");
		                       	   	   	   break;
		               case 'o':
		            	   	   	   strcpy(buffer,"out");
		                       	   	   	   break;
		               case 'f':
		            	   	   	   strcpy(buffer,"frame");
										   break;
		               case 'c':
		            	   	   	   strcpy(buffer,"channel");
		            	   	            	break;
		               case 'w':
		            	   	   	   strcpy(buffer,"width");
											break;
		               case 'h':
		            	   	   	   strcpy(buffer,"height");
		            	  					break;
		               case 'N':
		            	   	   	   strcpy(buffer,"frame max Number");
		            	   	   	   	   	   	break;
		               case '?':
		                       	   sprintf(buffer,"Unknown option: %c\n",(char)optopt);
		                       break;
		               }

	   printf_1_cmd_param(_optarg,cmd,buffer);
}
/*-----------------------------------*/
/**
 *w==width
 *h==height
 *c==channel 0xff 0x01 one bit means one channel;
 *i==in
 *o==out
 *f==frame image buffer frame buffer idx
 *n==number ,
 *
 */
/*-----------------------------------*/
struct cmd_param process_argc_argv(int argc, char * argv[])
{
#if TRUE
	    printf("\n\n");
	    printf("optind:%d��opterr��%d\n",optind,opterr);
	    printf("--------------------------\n");
#endif

	    struct cmd_param cmdParam;
	    cmdParam.in_out='n';

	    char* short_options="w:h:c:f:ioM:N:";

	    static struct option long_options[] = {
	           {"width", required_argument, NULL, 'w'},
	           {"height", required_argument, NULL, 'h'},
	           {"channel", required_argument, NULL, 'c'},
	           {"framebuffer", required_argument, NULL, 'f'},
	           {"in",  no_argument,       NULL, 'i'},
	           {"out",  no_argument,       NULL, 'o'},
	           {"frameNumMax", required_argument,       NULL, 'M'},
	           {"frameNumMin", required_argument,       NULL, 'N'},
	           {0, 0, 0, 0}
	       };

	    int cmd=-1;
	    do{
	    	cmd=getopt_long(argc, argv, short_options,long_options,NULL);
	    	printf_cmd_param(optind,optarg,cmd);

	    	   switch (cmd)
	    		        {
	    		               case 'i':
	    													   cmdParam.in_out=cmd;
	    													   break;
	    		               case 'o':
	    													   cmdParam.in_out=cmd;
	    													   break;
	    		               case 'f':
	    		            	   	   	   	   	   if (optarg){
	    		            	   	   	   	   		   	   	   cmdParam.frame=atoi(optarg);
	    										   }
	    										   break;
	    		               case 'c':
	    		            	   	   	   	   	    if (optarg){
	    		            	   	   	   	   	    			cmdParam.channel=atoi(optarg);
	    		            	   	   	   	   	    }
	    		            	   	            	break;

	    		               case 'w':
	    		            	   	   	   	   	   if (optarg){
	    		            	   	   	   	   		   	   	   cmdParam.width_param=atoi(optarg);
	    		            	   	   	   	   	   }
	    		            	   	   	   	   	   break;
	    		               case 'h':
	    		            	   	   	   	   	   if (optarg){
	    		            	   	   	   	   		   	   	   cmdParam.height_param=atoi(optarg);
	    		            	  					}
	    		            	  					break;
	    		               case 'N'://min
	    		            	   	   	   	   	   	if (optarg){
	    		            	  	            	   	   	   cmdParam.frame_idx_min=atoi(optarg);
	    		            	  	            	}
	    		            	  	            	break;
	    		               case 'M'://max
													if (optarg){
															   cmdParam.frame_idx_max=atoi(optarg);
													}
													break;
	    		               case '?':
	    		                       printf("Unknown option: %c\n",(char)optopt);
	    		                       break;
	    		               }


	    } while (cmd != -1);

	    return cmdParam;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void init_cmd_param(const struct cmd_param _cmd_param)
{
	 SetFrameIdxMin(_cmd_param.frame_idx_min);
	 SetFrameIdxMax(_cmd_param.frame_idx_max);
	 SetGlobalChannel(_cmd_param.channel);
	 SetCurrentDmaFrame(_cmd_param.frame);
	 init_image_area(_cmd_param.width_param,_cmd_param.height_param);
	 setProjectMode(_cmd_param);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int main(int argc, char * argv[])
{


	 const struct cmd_param cmdParam=process_argc_argv(argc,argv);

	 init_cmd_param(cmdParam);

	    main_ring();

	    printf("Exit Main \n");

	return EXIT_SUCCESS;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/