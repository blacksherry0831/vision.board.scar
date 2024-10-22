/*-------------应用程序-----------------*/
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
/*
 *作用:打印./mian 的 argv参数
 *参数含义：参数值，参数全名，参数简称
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
/*
 *作用:打印./mian 的 argv参数
 *参数含义：参数序号，参数值，参数名
 */
/*-----------------------------------*/
void printf_cmd_param(int optind,char* _optarg,int cmd)
{
	char buffer[128];

	PRINTF_DBG_EX("optind: %d\n", optind);

	switch (cmd){
		case 'p':
			strcpy(buffer,"project");
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
		case 'D':
			strcpy(buffer,"debug mode !");
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
 * *作用:解析并打印./mian 的 argv参数，保存至cmd_param类型变量
 */
/*-----------------------------------*/
struct cmd_param process_argc_argv(int argc, char * argv[])
{
#if TRUE
	PRINTF_DBG_EX("\n\n");
	//optind argv[optind]是我们的操作数，也就是我们传递给主函数的参数
	//当发现无效项字符时，optopt会包含该字符，正如我们传递的‘t’缺少参数的选项。
	//opterr变量非零时，getopt()函数为“无效选项”和“缺少参数“选项，并输出其错误信息。
	PRINTF_DBG_EX("optind:%d，opterr：%d\n",optind,opterr);
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
	    	cmd=getopt_long(argc, argv, short_options,long_options,NULL);  //（逐个）解析参数
	    	printf_cmd_param(optind,optarg,cmd);  //打印参数

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
 *根据argv参数初始化项目相关参数（项目运行模式，摄像机通道序号，图像阈值等）
 */
/*-----------------------------------*/
void init_cmd_param(const struct cmd_param _cmd_param)
{
	 setProjectMode(_cmd_param);  //判断并设定项目运行模式：单目？外圆？内圆

	 SetGlobalSensor(_cmd_param.sensor);   //设置摄像机通道序号（数）

	 initViewInfo_basic(_cmd_param.width_param,
			 _cmd_param.height_param,
			 _cmd_param.space_frame);  //初始化摄像头参数和图像处理参数
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int main(int argc, char * argv[])
{
	const struct cmd_param cmdParam=process_argc_argv(argc,argv);  //参数解析

	init_cmd_param(cmdParam);  //根据argv参数初始化项目相关参数（项目运行模式，摄像机通道序号，图像阈值等）

	main_ring();  //主处理函数

	PRINTF_DBG_EX("Exit Main \n");

	return EXIT_SUCCESS;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
