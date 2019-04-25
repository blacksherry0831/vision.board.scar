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
  *
 */
/*-----------------------------------*/
static void
server_timer_proc_flash(TimerClientData client_data, struct timeval *nowP)
{

#if 1

    if(cetc_update_flash() < 0) {
        printf("updatedeadline fail\n");
        exit(1);
    }

#endif

}
/*-----------------------------------*/
 /* *
  *
 */
/*-----------------------------------*/
int
create_server_timers()
{
    struct timeval now;
    TimerClientData cd;
    static Timer   *timer;

    if (gettimeofday(&now, NULL) < 0) {
    	return -1;
    }
    cd.p = &now;

    timer = tmr_create(&now, server_timer_proc_flash, cd,  DEADLINE_SEC * SEC_TO_US, 1);
    if (timer == NULL) {
        return -1;
    }

    return 0;
}
/*-----------------------------------*/
 /* *
  *
 */
/*-----------------------------------*/
void test_life_cycle()
{
	 struct check data;

	 cetc_get_check(&data);

	 PRINTF_DBG("Magic: %x, DeadLine: %d, OnLine: %d\n",data.magic,data.deadline,data.online);

	 if(data.deadline!=0){

#if 1
		 if(cetc_update_flash() < 0) {
			 	       PRINTF_DBG("update deadline fail\n");
			 	       exit(1);
			 }
#endif

	 }else{

		 PRINTF_DBG("deadline==%d\n",data.deadline);

	 }

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/

