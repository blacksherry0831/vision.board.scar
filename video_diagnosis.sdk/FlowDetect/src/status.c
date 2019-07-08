#include "status.h"
/*-----------------------------------*/
static int SENSOR_STAT=0;
static volatile enum ProjectRun gProjectCurrentRunning=outside08;
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int GetSensorStat_T()
{
	return SENSOR_STAT;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int SetSensorStat_T(const int _s)
{
	return SENSOR_STAT=_s;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void SetProjecRun(enum ProjectRun _pr)
{
	gProjectCurrentRunning=_pr;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
enum ProjectRun GetProjectRun()
{

	return gProjectCurrentRunning;

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
char * GetProjectRunStr()
{

	if(GetProjectRun()==inside08){
		return	"inside";
	}else if(GetProjectRun()==outside08){
		return	"outside";
	}else{
		return 	"undefined";
	}


}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
