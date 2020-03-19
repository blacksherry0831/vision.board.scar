#ifndef		_CRITICAL_SECTION_H_
#define		_CRITICAL_SECTION_H_
#ifdef __cplusplus
extern "C"{
#endif

#include <pthread.h>

extern void	CPU_IntDis(void);
extern void	CPU_IntEn(void);
extern void	CPU_IntDestory(void);


#ifdef __cplusplus
}
#endif
#endif




