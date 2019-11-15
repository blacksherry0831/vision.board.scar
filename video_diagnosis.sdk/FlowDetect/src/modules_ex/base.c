#include "base.h"
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
ssize_t readn(const int fd, void* const buf, const size_t n)
{
	size_t nleft = n;   // left的意思是“剩下”, 而非“左边”
	char *bufptr = buf;
	ssize_t nread;

	while(nleft > 0)
	{
		if((nread = read(fd, bufptr, nleft)) < 0)
		{
			if(errno == EINTR) 	// 遇到中断
			{
				nread = 0;
				continue;   // 或者用 nread = 0;
			}
			else
			{
				return -1;  // 真正错误
			}

		}else if(nread == 0) // 对端关闭
		{
			break;
		}

		nleft -= nread;
		bufptr += nread;
	}

	return (n - nleft);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int get_socket_buf_size(int sockfd)
{

	socklen_t optlen=sizeof(int);
	int send_buf_size=0;

	int gerr=getsockopt(sockfd,SOL_SOCKET,SO_SNDBUF,&send_buf_size,&optlen);

	if(gerr < 0){
			 printf_error();

	}

	return send_buf_size;

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int set_socket_buf_size(int sockfd,const int send_buf_size)
{

	socklen_t optlen=sizeof(int);

	int buf_size_get=get_socket_buf_size(sockfd);



	PRINTF_DBG_EX("SO_SNDBUF: %d(default)\n",buf_size_get);



	int err =  setsockopt(sockfd, SOL_SOCKET, SO_SNDBUF, (const void *)&send_buf_size, optlen);

	if(err < 0){
			 printf_error();

	}

	buf_size_get=get_socket_buf_size(sockfd);


	if(send_buf_size!=buf_size_get){

		PRINTF_DBG_EX("SO_SNDBUF: %d,but set value is %d\n",buf_size_get,send_buf_size);

	}

	return err;

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
ssize_t writen(const int fd, const void* const  buf, const size_t n)
{
	signal(SIGPIPE, SIG_IGN);//ignore sig pipe

	size_t nleft = n;
	const char *bufptr = buf;
	ssize_t nwrite;

	while(nleft > 0)
	{
		//assert(bufptr<(unsigned char *)buf+n);

		if((nwrite = write(fd, bufptr, nleft )) <= 0)
		{
			if(errno == EINTR){
				nwrite = 0;
			}else if(errno==SIGPIPE){
				printf_error();
				return -1;
			}else{
				printf_error();
				return -1;
			}

		}

		assert(nwrite>=0);

		nleft -= nwrite;
		bufptr += nwrite;
	}

	assert(nleft==0);

	return (n-nleft);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void SetInt2Char(const int _value,unsigned char* _data,int _size)
{
	_data[0]= _value%256;
	_data[1]= _value/256%256;
	_data[2]= _value/256/256%256;
	_data[3]= _value/256/256/256;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int SetChar2Int(const unsigned char* _data,int _size)
{
	int value_t=0;

	value_t=_data[0]+
			_data[1]*256+
			_data[2]*256*256+
			_data[3]*256*256*256;

	return value_t;

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int _4UChar2Int(const unsigned char* _data)
{
	int value_t=0;

		value_t=_data[0]+
				_data[1]*256+
				_data[2]*256*256+
				_data[3]*256*256*256;

		return value_t;

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int UChar2Int(const unsigned char* _data,const int _size)
{

	return SetChar2Int(_data,_size);

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int NativesAcceptClient(int s, int timeout)
{
   int iResult;
   /*------------*/
   struct timeval tv;
   tv.tv_sec = (long)timeout;
   tv.tv_usec = 0;
   /*------------*/
   fd_set rfds;
   FD_ZERO(&rfds);
   FD_SET(s, &rfds);
   /*------------*/
   iResult = select(s + 1, &rfds, (fd_set *) 0, (fd_set *) 0, &tv);

   if(iResult == 0) //超时
   {
	   //PRINTF_DBG("select time out!\n");
   }
   else if(iResult == -1)  //失败
   {
	  // PRINTF_DBG("fail to select!\n");
   }
   else  //成功
   {
	   //PRINTF_DBG("data is available!\n");
   }

   return iResult;

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int AcceptSocketRequestInSelect(int sock_descriptor)
{
 int nready = 0;

 unsigned int address_size = sizeof(struct sockaddr_in);
 struct sockaddr_in sPin ;

 int maxfdp = NULL;
 fd_set fdR;
 //struct timeval timeout={0,1};
 struct timeval timeout;
 timeout.tv_sec = 0;
 timeout.tv_usec = 0;

 FD_ZERO(&fdR);
 FD_SET(sock_descriptor, &fdR);


 if(nready = select(maxfdp + 1, &fdR, NULL, NULL, &timeout)) {
  int temp_sock_descriptor = accept(sock_descriptor, (struct sockaddr*) &sPin, &address_size);

  if(0 > temp_sock_descriptor) {
   //WritePrintLog("==================tcp socket accept error\n");
   return 1;
  }
 }
 else {
  //WritePrintLog("==================tcp socket selcet error\n");
  return 1;
 }

 //WritePrintLog("==================tcp socket accept ok\n");
 return 0;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int SelectAccept(int sockfd,int _sec)
{
	 struct timeval tv;
		   tv.tv_sec =_sec;
		   tv.tv_usec = 0;

	 fd_set rfds;
		   FD_ZERO(&rfds);
		   FD_SET(sockfd, &rfds);

	int err=select(sockfd + 1, &rfds, (fd_set *) 0, (fd_set *) 0, &tv);

	if(err == 0){
		 //PRINTF_DBG("socket tcp select> time out!\n");
	} else if(err == -1){
		 PRINTF_DBG_EX("socket tcp select> fail!\n");
	}else{

		if(FD_ISSET(sockfd,&rfds)){
			return 1;//can read
		}else{
			return -2;//error
		}

	}
	return err;

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
struct timespec getDelayTime(long timeout_ms)
{
		struct timespec abstime;
		struct timeval now;

		gettimeofday(&now, NULL);
					long nsec = now.tv_usec * 1000 + (timeout_ms % 1000) * 1000000;
					abstime.tv_sec=now.tv_sec + nsec / 1000000000 + timeout_ms / 1000;
					abstime.tv_nsec=nsec % 1000000000;
		return abstime;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int write_str(int socketfd,const char *buf)
{
	/* write the string in 'buf' to 'fd' */
	return write(socketfd, buf, strlen(buf));

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int GetFreeMemSizeMB()
{
		struct sysinfo si;
				sysinfo(&si);
      return si.freeram/1024/1024;
}

/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void wait4MemFree()
{
	while( IsRun()){

		if(GetFreeMemSizeMB()<16){
			PRINTF_DBG_EX("Memory Free Is: %d MB\n", GetFreeMemSizeMB());
			sleep(1);
		}else{
			break;
		}
	}
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void init_irh_irw(short* Irh,short* Irw,unsigned int *Irhw)
{
	 unsigned int sum=0;
	// >>>>>>>>>>>>>>>>>>>>>>>>>> 文件系统 >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
		FILE *fp;
		//★★★★★★★★★★★★★★读行纠偏数组★★★★★★★★★★★★★★★
		fp = fopen("/media/sdcard/Irh.txt","rb");
		sum=0;
		assert(fp!=0);
		fseek(fp,0L,SEEK_SET);
	    // 循环读取文件
	    while (1)
	    {
	//        // 清空缓冲区
	//        memset(Irh, 0, sizeof(Irh));
	        // 定义函数返回值
	        int rc = fread(Irh, sizeof(char), sizeof(Irh),fp);

	        // 读取到文件的结束，退出循环
	        if (rc <= 0)
	            break;
	        // 输出读取的结果到屏幕
	        sum+=rc;
	        PRINTF_DBG_EX("Irh is loaded %d !\n",sum);
	    }
	    // 关闭文件
	    fclose(fp);
	    //☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
		//★★★★★★★★★★★★★★读列纠偏数组★★★★★★★★★★★★★★★
		fp = fopen("/media/sdcard/Irw.txt","rb");
		sum=0;
		assert(fp!=0);
		fseek(fp,0L,SEEK_SET);
	    // 循环读取文件
	    while (1)
	    {
	//        // 清空缓冲区
	//        memset(Irw, 0, sizeof(Irw));
	        // 定义函数返回值
	        int rc = fread(Irw, sizeof(char), sizeof(Irw),fp);
	        // 读取到文件的结束，退出循环
	        if (rc <= 0)
	            break;
	        // 输出读取的结果到屏幕
	        sum+=rc;
	        PRINTF_DBG_EX("Irw is loaded %d !\n",sum);
	    }
	    // 关闭文件
	    fclose(fp);
	    //☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
#if 1
	    unsigned long const SIZE=1920*1080;
	    int i;
	    for (i=0;i<SIZE;i++){

	    	Irhw[i]=1080*(Irh[i]-1)+Irw[i]-1;
	    	assert(Irhw[i]>=0);
	    	assert(Irhw[i]<1920*1080);

	    }
#endif
}


/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int Wait4Signal(long timeout_ms,pthread_mutex_t *__mutex,pthread_cond_t *__restrict __cond)
{
	int reslut_t=0;

		pthread_mutex_lock(__mutex);//


						while(IsRun()){

							struct timespec abstime= getDelayTime(timeout_ms);
#if 0
							reslut_t=pthread_cond_timedwait(__cond,__mutex, &abstime);
#else
							reslut_t=pthread_cond_wait(__cond,__mutex);
#endif
							if(reslut_t==0){
								//rcv signal success
								break;
							}else if(reslut_t==ETIMEDOUT){
								//time out again
								continue;
							}else{
								PRINTF_DBG_EX("error");
								assert(0);
							}

						}


		pthread_mutex_unlock(__mutex);//

	return reslut_t;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void setCurrentThreadHighPriority(int value)
{
#if 0
  // Start out with a standard, low-priority setup for the sched params.
  struct sched_param sp;
  bzero((void*)&sp, sizeof(sp));
  const int policy = SCHED_RR;

  // If desired, set up high-priority sched params structure.
  {
    // FIFO scheduler, ranked above default SCHED_OTHER queue

    // The priority only compares us to other SCHED_FIFO threads, so we
    // just pick a random priority halfway between min & max.
    const int priority = (sched_get_priority_max(policy) + sched_get_priority_min(policy)) / 2+value;

    sp.sched_priority = priority;
  }

  // Actually set the sched params for the current thread.
  if (0 == pthread_setschedparam(pthread_self(), policy, &sp)) {
    printf("IO Thread #%d using high-priority scheduler!", pthread_self());
  }

#endif
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void sleepMS(int _ms)
{
	const int ms_1=1000;
	usleep(ms_1*_ms);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void sleep_1ms()
{
	sleepMS(1);
	sched_yield();
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int sem_wait_infinite(sem_t  *__sem)
{
	const long timeout_ms=3*1000;
	int reslut_t=-1;

						do{

							struct timespec abstime= getDelayTime(timeout_ms);

							reslut_t=sem_timedwait(__sem,&abstime);

							if(reslut_t==0){
								//rcv signal success
								break;

							}else if(reslut_t==-1){
								if(EINTR==errno ){

								}else if(EINVAL==errno){
									return -1;
								}else if(ETIMEDOUT== errno){

								}else{
									printf_error();
								}

							}else{
								DEBUG_PRINT("sem_timedwait error");
							}

						}while(IsRun());

	return reslut_t;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int fs_is_file_exist(const char * file_path)
{
	if(file_path==0)
			return ERROR;

		if(access(file_path,F_OK)==0)
			return SUCCESS;

		return ERROR;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void fs_store_txt(const char *filepath, const char *data)
{
	FILE *fp = fopen(filepath, "wt");
	    if (fp != NULL)
	    {
	        fputs(data, fp);
	        fclose(fp);
	    }
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int  fs_load_txt(const char *filepath,char* const buffer)
{
	  const  int string_size=fs_file_size(filepath);

	  int  read_size=0;

	  FILE *handler = fopen(filepath, "r");

	   if (handler)
	   {
	       // Read it all in one operation
	       read_size = fread(buffer, sizeof(char), string_size, handler);

	       // fread doesn't set it so put a \0 in the last position
	       // and buffer is now officially a string
	       buffer[string_size] = '\0';

	       if (string_size != read_size)
	       {
	    	   // Something went wrong, throw away the memory and set
	           return ERROR;
	       }

	       // Always remember to close the file.
	       fclose(handler);
	    }

	   return SUCCESS;

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int fs_file_size(const char *filepath)
{
	   int file_size=0;
	   FILE *handler = fopen(filepath, "r");

	   if (handler)
	   {
	       // Seek the last byte of the file
	       fseek(handler, 0, SEEK_END);
	       // Offset from the first to the last byte, or in other words, filesize
	       file_size = ftell(handler);

	       // Always remember to close the file.
	       fclose(handler);
	    }
	   return file_size;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
