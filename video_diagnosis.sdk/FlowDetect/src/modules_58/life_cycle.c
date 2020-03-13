#include "life_cycle.h"
/*-----------------------------------*/
 /* *
  *
 */
/*-----------------------------------*/
#define DEADLINE_SEC (3600*2)  //second
#define SEC_TO_NS 1000000000LL	/* too big for enum/const on some platforms */
#define uS_TO_NS 1000
#define SEC_TO_US 1000000LL
/*-----------------------------------*/
 /* *
  *ˢ���ѷ���ʱ���ʣ�������
 */
/*-----------------------------------*/
static void
server_timer_proc_flash(TimerClientData client_data, struct timeval *nowP)
{

#if 1

    if(cetc_update_flash() < 0) {
        printf("update deadline fail\n");
        exit(1);
    }

#endif

}
/*-----------------------------------*/
 /* *
  *��ʱˢ�º�У���ѷ���ʱ���ʣ�������
 */
/*-----------------------------------*/
int create_server_timers()
{
    struct timeval now;
    TimerClientData cd;
    static Timer   *timer;

    if (gettimeofday(&now, NULL) < 0) {  //��ȡ��ǰϵͳʱ��
    	return -1;
    }
    cd.p = &now;

    timer = tmr_create(&now, server_timer_proc_flash, cd,  DEADLINE_SEC * SEC_TO_US, 1);  //��ʱ������ʱˢ���ѷ���ʱ���ʣ�������
    if (timer == NULL) {
        return -1;
    }

    return 0;
}
/*-----------------------------------*/
 /* *
  *���Բ�Ʒʣ���������
 */
/*-----------------------------------*/
void test_life_cycle()
{
	 struct check data;

	 cetc_get_check(&data);

	 PRINTF_DBG_EX("Magic: %x, DeadLine: %d, OnLine: %d\n",data.magic,data.deadline,data.online);

	 if(data.deadline!=0){

#if 0
		 if(cetc_update_flash() < 0) {
			 	       PRINTF_DBG_EX("update deadline fail\n");
			 	       exit(1);
			 }
#endif

	 }else{

		 PRINTF_DBG_EX("deadline==%d\n",data.deadline);

	 }

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/


