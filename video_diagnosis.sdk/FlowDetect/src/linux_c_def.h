#ifndef LINUX_C_DEF_H
#define LINUX_C_DEF_H
/////////////////////////////////////////////////////

#ifndef FALSE
#define FALSE 		(0)
#endif

#ifndef TRUE
#define TRUE 		(1)
#endif

#ifndef SUCCESS
#define SUCCESS		(0)
#endif

/////////////////////////////////////////////////////
#define TIME_START()  do{struct timeval startTime,endTime;float Timeuse;gettimeofday(&startTime,NULL);

#define TIME_END(X)		gettimeofday(&endTime,NULL);Timeuse = 1000000*(endTime.tv_sec - startTime.tv_sec) + (endTime.tv_usec - startTime.tv_usec);	printf("%s = %f us,%f ms\n",X,Timeuse,Timeuse/1000);}while(0)
/////////////////////////////////////////////////////
#define _DEBUG TRUE
/////////////////////////////////////////////////////
#endif
