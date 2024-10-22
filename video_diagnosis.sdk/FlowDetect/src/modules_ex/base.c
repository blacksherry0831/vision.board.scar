#include "base.h"
/*-----------------------------------*/
/**
 *从socket读取数据
 */
/*-----------------------------------*/
ssize_t readn(const int fd, void* const buf, const size_t n)
{
	size_t nleft = n;   // left的意思是“剩下”, 而非“左边”
	char *bufptr = (char*)buf;
	ssize_t nread=0;
	int r_timeout=0;
	while(nleft > 0)
	{
		nread = read(fd, bufptr, nleft);
		if(nread < 0)
		{
			if(errno == EINTR) 	// 遇到中断
			{
				nread = 0;
				continue;   // 或者用 nread = 0;
			}else if(EAGAIN==errno){
				r_timeout++;
			}else if(EWOULDBLOCK==errno){
				r_timeout++;
			}else{
				printf_error();
				return -1;  // 真正错误
			}

		}else if(nread == 0) {
			break;
		}else{
			nleft -= nread;
			bufptr += nread;
		}

		if(r_timeout>=2){
			return -1;
		}

	}

	return (n - nleft);
}
/*-----------------------------------*/
/**
 * 获取socket的发送缓冲区大小
 */
/*-----------------------------------*/
int get_socket_buf_size(int sockfd)
{

	socklen_t optlen=sizeof(int);
	int send_buf_size=0;

	//getsockopt-获取与某个套接字关联的选项  获取socket的发送缓冲区大小
	int gerr=getsockopt(sockfd,SOL_SOCKET,SO_SNDBUF,&send_buf_size,&optlen);

	if(gerr < 0){
			 printf_error();

	}

	return send_buf_size;

}
/*-----------------------------------*/
/**
 *设置socket的发送缓冲区大小
 */
/*-----------------------------------*/
int set_socket_buf_size(int sockfd,const int send_buf_size)
{

	socklen_t optlen=sizeof(int);

	int buf_size_get=get_socket_buf_size(sockfd);  // 获取socket的发送缓冲区大小

#if 0
	PRINTF_DBG_EX("SO_SNDBUF: %d(default)\n",buf_size_get);
#endif

	int err =  setsockopt(sockfd, SOL_SOCKET, SO_SNDBUF, (const void *)&send_buf_size, optlen);  //设置socket的发送缓冲区大小

	if(err < 0){
			 printf_error();

	}

	buf_size_get=get_socket_buf_size(sockfd);  // 获取socket的发送缓冲区大小

	if(send_buf_size!=buf_size_get){
#if 0
		PRINTF_DBG_EX("SO_SNDBUF: %d,but set value is %d\n",buf_size_get,send_buf_size);
#endif
	}

	return err;

}
/*-----------------------------------*/
/**
 *向socket连接写入数据
 */
/*-----------------------------------*/
ssize_t writen(const int fd, const void* const  buf, const size_t n)
{
	signal(SIGPIPE, SIG_IGN);//ignore sig pipe  为了避免因对端的关闭导致本进程退出,故可以捕获SIGPIPE信号, 并忽略它,

	size_t nleft = n;  //剩余的字节数
	const char *bufptr = (char *)buf;
	ssize_t nwrite=0;  //单次写入的字节数

	int w_timeout=0;

	while(nleft > 0)
	{

		nwrite = write(fd, bufptr, nleft );

		if(nwrite <= 0)
		{
			if(errno == EINTR){  //当阻塞于某个慢系统调用的一个进程捕获某个信号且相应信号处理函数,即遇到中断
				nwrite = 0;
			}else if(EAGAIN==errno){
				nwrite = 0;
				w_timeout++;
			}else if(EWOULDBLOCK==errno){
				nwrite = 0;
				w_timeout++;
			}else if(errno==SIGPIPE){  //对端即客户端关闭
				printf_error();
				return -1;
			}else{
				printf_error();
				return -1;
			}

		}else{
			assert(nwrite>=0);
			nleft -= nwrite;
			bufptr += nwrite;
		}

		if(w_timeout>=2){
			return -1;
		}

	}

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
void SetInt2UChar(const int _value,unsigned char* _data,int _size)
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
 *判断set集合中描述符socketfd是否准备好
 */
/*-----------------------------------*/
int SelectAccept(int sockfd,int _sec)
{
	 struct timeval tv;
	 tv.tv_sec =_sec;
	 tv.tv_usec = 0;

	 fd_set rfds;  //描述符集合
	 FD_ZERO(&rfds);    //将set初始化为空集NULL
	 FD_SET(sockfd, &rfds);  //向集合添加描述符sockfd

	 //参数为集合中所有文件描述符的范围，可读描述符，可写描述符，等待错误检查的描述符，时间
	 //select()调用返回处于就绪状态并且已经包含在fd_set结构中的描述字总数
	int err=select(sockfd + 1, &rfds, (fd_set *) 0, (fd_set *) 0, &tv);

	if(err == 0){  //超时
		 //PRINTF_DBG("socket tcp select> time out!\n");
	} else if(err == -1){  //报错
		 PRINTF_DBG_EX("socket tcp select> fail!\n");
	}else{

		if(FD_ISSET(sockfd,&rfds)){   //判断set集合中描述符fd是否准备好
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
void sleep_1_ms()
{
	sleepMS(1);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void sleep_1ms_yield()
{
	sleep_1_ms();
	sched_yield();
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
#if 0
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
#endif
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
