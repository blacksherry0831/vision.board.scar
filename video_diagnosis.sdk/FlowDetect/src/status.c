#include "status.h"
/*-----------------------------------*/
#include "module_zynq7000_hi3516/def_hw_zynq7000_hi3516.h"
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
const char * GetProjectRunStr()
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
void initProjectCfgDir(char *_path)
{
	sprintf(_path,"%s%s","project.cfg.",GetProjectRunStr());
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void initProjectCfgDirPath(char *_path)
{
	char pathname[1024]={0};
	initProjectCfgDir(pathname);
	sprintf(_path,"%s%s",PATH_SDCARD,pathname);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void initProjectCfgDirPath_Separator(char *_path)
{
	char filename[1024]={0};
	initProjectCfgDir(filename);
	sprintf(_path,"%s%s%s",PATH_SDCARD,filename,"/");
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int MakeProjectDirectory()
{
	char filefullpath[1024]={0};
	initProjectCfgDirPath(filefullpath);
	return mkdir(filefullpath,0777);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
