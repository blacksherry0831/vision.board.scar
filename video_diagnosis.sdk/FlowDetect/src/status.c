#include "status.h"
/*-----------------------------------*/
static int SENSOR_STAT=0;
static volatile enum ProjectRun gProjectCurrentRunning=outside08;
/*-----------------------------------*/
const char* ProjectName[]={
		"scar_detect_01",
		"inside08",
		"outside08"};
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
	const int project_t=GetProjectRun();

	if(		project_t==inside08  	||
			project_t==outside08	||
			project_t==scar_detect_01){

		return	ProjectName[project_t];

	}else{
		assert(0);
		return 	"undefined";
	}


}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
