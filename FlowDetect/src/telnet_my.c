#include "telnet_my.h"
int save_fd;
#define BUFSIZE 1024
/*telnet_cmd:ff fb 01 ff fb 03 ff fc 1f*/
const unsigned char cmd_telnet[9] = {0xff, 0xfb, 0x01, 0xff, 0xfb, 0x03, 0xff, 0xfc, 0x1f};
const unsigned char cmd_telnet_iwe[9] = {0xff, 0xfb, 0x01};//IAC WILL ECHO
const unsigned char cmd_telnet_wt[9] = {0xff, 0xfb, 0x03};//WON'T
const unsigned char cmd_telnet_wtX[9] = {0xff, 0xfb, 0x03};//WON'T
char cmdLine[BUFSIZE] = {0};

void task_process(int sockfd);
int telnetd(void);
void *telnetd_pthread(void * arg);
void *task_process_pthread(void *arg) ;

/*����telnet����*/
int telnetd_start()
{
#if 1
    pthread_t id;
    int i,ret;

    ret=pthread_create(&id,NULL,(void *) telnetd_pthread,NULL);
    if(ret!=0){
        PRINTF_DBG ("Telnet: telnet_starting.......err!\n");
        return -1;
    }

#else
    int pid;
    int status;

    if(pid=fork()) {
        //exit(0);        //�Ǹ����̣�����������
        waitpid(-1, &status, WNOHANG | WUNTRACED | WCONTINUED);
        return 0;
    } else if(pid < 0) {
        return -1;//exit(1);        //forkʧ�ܣ��˳�
    }
    PRINTF_DBG("Telnet: telnet_starting.......\n");
    telnetd();
#endif
}


/*telnet ����������*/
//int main(int argc, char *argv[])
int telnetd(void)
{
    pid_t fpid;
    int status;
    int server_sockfd;//���������׽���
    int client_sockfd;//�ͻ����׽���
    int len;
    struct sockaddr_in server_addr;   //�����������ַ�ṹ��
    struct sockaddr_in remote_addr; //�ͻ��������ַ�ṹ��
    int sin_size;
    memset(&server_addr,0,sizeof(server_addr)); //���ݳ�ʼ��--����
    server_addr.sin_family=AF_INET; //����ΪIPͨ��
    server_addr.sin_addr.s_addr=htonl(INADDR_ANY);//������IP��ַ--�������ӵ����б��ص�ַ��
    server_addr.sin_port=htons(23); //������telnet�˿ں�

    //init_telnetd();

    /*�������������׽���--IPv4Э�飬��������ͨ�ţ�TCPЭ��*/
    if((server_sockfd=socket(AF_INET,SOCK_STREAM,0))<0)
    {
        perror("socket");
        return -1;
    }

        /*���׽��ְ󶨵��������������ַ��*/
    if (bind(server_sockfd,(struct sockaddr *)&server_addr,sizeof(struct sockaddr))<0)
    {
        perror("bind");
        return -1;
    }

    /*������������*/
    listen(server_sockfd,1);

    PRINTF_DBG("Telnet: listening for telnet requests....\n");

    sin_size=sizeof(struct sockaddr_in);
    while(1) {
        /*�ȴ��ͻ����������󵽴�*/
        if((client_sockfd=accept(server_sockfd,(struct sockaddr *)&remote_addr,&sin_size))<0)
        {
            perror("accept");
            return 1;
        }
        //PRINTF_DBG("accept client %s\n",inet_ntoa(remote_addr.sin_addr));
#if 0
        fpid = fork();
        if (fpid < 0) {
               perror("call fork() err!\n");
               exit(1);
        } else if (fpid == 0) {
               task_process(client_sockfd);
               close(client_sockfd);
               exit(0);
        } else {
            waitpid(-1, &status, WNOHANG | WUNTRACED | WCONTINUED);
        }
#else
        pthread_t id;
        int i,ret;

        ret=pthread_create(&id,NULL,(void *) task_process_pthread,(void *)client_sockfd);
        if(ret!=0){
            PRINTF_DBG ("Telnet: telnet_starting.......err!\n");
            return -1;
        }
        pthread_join(id,NULL);
#endif

    }
    close(client_sockfd);
    close(server_sockfd);
    return 0;
}
void * telnetd_pthread(void *arg)
{
    telnetd();
}
/*����telnetЭ������*/
int send_telnet_cmd(int fd)
{
    return write(fd, cmd_telnet, sizeof(cmd_telnet));
}
/*��ȡ�����ַ���*/
int read_cmdline(int sockfd, char *cmdLine, int size)
{
    int ret, rev_count = 0;
    char *buf = NULL;
    buf = cmdLine;
    while(1 == (ret = read(sockfd, buf, 1))) {
        rev_count++;
       // write(sockfd,buf,1);
        if(rev_count > BUFSIZE - 2) {
            return rev_count;
        }
        if(*buf == '\n') {
            return rev_count;
        }
        buf++;
    }
    return ret;
}
/*����ض���*/
int ioStdSet(int src_fd, int dest_fd, int *save_fd)
{
    *save_fd = dup(dest_fd);
    dup2(src_fd, dest_fd);
    //close(src_fd);
    return *save_fd;
}
/*�ָ�����ض���*/
void recoverIoStdSet(int src_fd, int dest_fd)
{
    dup2(src_fd, dest_fd);
    close(src_fd);
}
/*�����ַ���*/
int cmd_analyze(char *cmd)
{
    unsigned char *ptr = NULL;
    unsigned char *ptr_tmp;


    /*ȥ������Ļ��з������������ַ�*/
    while((ptr = strstr(cmd, "\r")) != 0 ) {
        while(*ptr != 0) {
            *ptr = *(ptr+1);
            ptr++;
        }
    }

    while((ptr = strstr(cmd, "\n")) != 0 ) {
        while(*ptr != 0) {
            *ptr = *(ptr+1);
            ptr++;
        }
    }

#if 0
    ptr = cmd;
    while((!((*ptr > 'a' && *ptr < 'z') || (*ptr > 'A' && *ptr < 'Z') || (*ptr > '0' && *ptr < '9'))) && (*ptr != 0)) {
        ptr_tmp = ptr;
        while(*ptr_tmp != 0) {
            *ptr_tmp = *(ptr_tmp+1);
            ptr_tmp++;
        }
    }

#endif

    return 0;
}
/*ִ��������Ե�telnet�ն�*/
int cmd_process(int fd, char *cmdLine)
{
	  ioStdSet(fd, 1, &save_fd);

			if(strcmp(cmdLine,"stop")==0){
					StopRun(0);
			}else if(strcmp(cmdLine,"exit")==0){
					close(fd);
			}else if(strcmp(cmdLine,"sensor")==0){
					int stat=sensor_state();
			}else {
				write_str(fd,"stop : stop process\r\n");
				write_str(fd,"exit : exit telnet\r\n");
				write_str(fd,"sensor :sensor stat\r\n");
			}

    recoverIoStdSet(save_fd, 1);

    return 0;
}
/*telnet����������*/
void task_process(int sockfd)
{
    char cmdLine[BUFSIZE]={0};
    int count = 0;
    int i=0,tmp = 0;
    int ret;

    //send_telnet_cmd(sockfd);

    while(IsRun()) {

      //
    	write_str(sockfd,"welcome to linux !\r\n");
        memset(cmdLine, 0, sizeof(cmdLine));

        count = read_cmdline(sockfd, cmdLine, BUFSIZE);
        if(count <= 0) {
            //perror("read err");
            //exit(1);�Է��Ͽ����ӣ�����
            return ;
        }
        ret = cmd_analyze(cmdLine);

        if(ret == 0) {
            cmd_process(sockfd, cmdLine);
        }

    }

    close(sockfd);
}
void *task_process_pthread(void *arg)
{
    int sockfd;
    sockfd = (int) arg;
    task_process(sockfd);

    pthread_exit(NULL);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void* tcp_telnet_process(void *_data)
{
	int *_clientfd_p=(int*)_data;

	int clientfd=*_clientfd_p;

	task_process(clientfd);

	free(_data);
	return NULL;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
pthread_t tcp_telnet(void *_data)
{
	pthread_t _thread_tid;

	TCP_SERVER* tcp_server_data=malloc(sizeof(TCP_SERVER));
		 	 	 	 tcp_server_data->port=TCP_PORT_TELNET;
		 	 	 	 tcp_server_data->pfunClient=tcp_telnet_process;

		if( pthread_create(&_thread_tid, NULL, tcp_server, tcp_server_data) ){
				PRINTF_DBG(" Create print_thread1 thread error!\n");
				exit(0);
		}


	return _thread_tid;
}
