#include <pthread.h>

pthread_mutex_t m_cpu_mutex= PTHREAD_MUTEX_INITIALIZER;

void        CPU_IntDis       (void)
{
	pthread_mutex_lock(&m_cpu_mutex);
	
}



void        CPU_IntEn        (void)
{
	pthread_mutex_unlock(&m_cpu_mutex);
	
}


void        CPU_IntDestory(void)
{
	pthread_mutex_destroy(&m_cpu_mutex);

}