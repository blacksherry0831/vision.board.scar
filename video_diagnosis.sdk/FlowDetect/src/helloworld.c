/*-------------”¶”√≥Ã–Ú-----------------*/
#include "linux_header.h"
/*-----------------------------------*/
#include "init_destory.h"
/*-----------------------------------*/
#include "modules/printf_log/printf_log.h"
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
void printf_1_cmd_param(char* _optarg,int cmd,const char* _cmd_long)
{
	 	 if(_optarg){
	 		PRINTF_DBG_EX("option:[%s] %c argv: %s\n",_cmd_long, cmd, _optarg);
		}else{
			PRINTF_DBG_EX("option:[%s] %c no argument\n",_cmd_long, cmd);
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

	PRINTF_DBG_EX("optind: %d\n", optind);

	   switch (cmd){
		               case 'i':
		            	   	   	   strcpy(buffer,"in");
		                       	   	   	   break;
		               case 'o':
		            	   	   	   strcpy(buffer,"out");
		                       	   	   	   break;
		               case 'f':
		            	   	   	   strcpy(buffer,"frame");
										   break;
		               case 's':
		            	   	   	   strcpy(buffer,"sensor");
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
	PRINTF_DBG_EX("\n\n");
	PRINTF_DBG_EX("optind:%d£¨opterr£∫%d\n",optind,opterr);
	PRINTF_DBG_EX("--------------------------\n");
#endif

	    struct cmd_param cmdParam;


	    char* short_options="w:h:s:f:p:D";

	    static struct option long_options[] = {
	           {"width", required_argument, NULL, 'w'},
	           {"height", required_argument, NULL, 'h'},
	           {"sensor", required_argument, NULL, 's'},
	           {"framebuffer", required_argument, NULL, 'f'},

	           {"project", required_argument,       NULL, 'p'},

	           {"debugOutput",  no_argument,       NULL, 'D'},

	           {0, 0, 0, 0}

	       };

	    int cmd=-1;
	    do{
	    	cmd=getopt_long(argc, argv, short_options,long_options,NULL);
	    	printf_cmd_param(optind,optarg,cmd);

	    	   switch (cmd)
	    		        {
	    		              case 'p':
	    		            	   	   	   	   	   	if (optarg){
	    		            	 	    		       	   	  strcpy(cmdParam.project,optarg);
	    		            	 	    			}
	    		            	 	    			break;

	    		               case 'f':
	    		            	   	   	   	   	   if (optarg){
	    		            	   	   	   	   		   	   	   cmdParam.space_frame=atoi(optarg);
	    										   }
	    										   break;
	    		               case 's':
	    		            	   	   	   	   	    if (optarg){
	    		            	   	   	   	   	    			cmdParam.sensor=atoi(optarg);
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
	    		               case 'D':
	    		            	   	   	   	   	   setPrintConsole(1);
	    		            	   	   	   	   	   break;

	    		               case '?':
	    		            	   	   	   	   	   PRINTF_DBG_EX("Unknown option: %c\n",(char)optopt);
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
	 setProjectMode(_cmd_param);

	 SetGlobalSensor(_cmd_param.sensor);

	 initViewInfo_basic(_cmd_param.width_param,
			 _cmd_param.height_param,
			 _cmd_param.space_frame);
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

	    PRINTF_DBG_EX("Exit Main \n");

	return EXIT_SUCCESS;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
