#include "critical_section.h"

static pthread_mutex_t m_cpu_mutex= PTHREAD_MUTEX_INITIALIZER;

extern void	CPU_IntDis(void)
{
	pthread_mutex_lock(&m_cpu_mutex);
	
}



extern void	CPU_IntEn(void)
{
	pthread_mutex_unlock(&m_cpu_mutex);
	
}


extern void	CPU_IntDestory(void)
{
	pthread_mutex_destroy(&m_cpu_mutex);

}
