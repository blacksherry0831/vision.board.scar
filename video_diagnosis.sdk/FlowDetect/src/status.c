#include "status.h"
/*-----------------------------------*/
#include "module_zynq7000_hi3516/def_hw_zynq7000_hi3516.h"
/*-----------------------------------*/
#define	OFFSET_VER_MAJOR		(1E3)
#define	OFFSET_VER_MINOR		(1E2)
#define	OFFSET_VER_SUBMINOR		(1)
/*-----------------------------------*/
static int SENSOR_STAT=0;
/*-----------------------------------*/
static const  short unsigned int VER_MAJOR=0;
static const  short unsigned int VER_MINOR=9;
static const  short unsigned int VER_SUBMINOR=2;
/*-----------------------------------*/
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
	sprintf(_path,"%s%s",GetProjectConfigPathPrefix(),GetProjectRunStr());
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
void debug_assert_ver()
{
	assert(VER_MAJOR>=0 	&& VER_MAJOR<=65);
	assert(VER_MINOR>=0 	&& VER_MINOR<=9);
	assert(VER_SUBMINOR>=0	&& VER_SUBMINOR<=99);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void PrintBuildTime()
{
#ifdef _DEBUG
	debug_assert_ver();
#endif
	printf("version	>> d%.d%.d%	\n",VER_MAJOR,VER_MINOR,VER_SUBMINOR);
	printf("build time >> data: %s		time: %s \n",__DATE__,__TIME__);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
short unsigned int GetVersion()
{
#ifdef _DEBUG
	debug_assert_ver();
#endif
	const unsigned int	app_ver_t=
			VER_MAJOR*OFFSET_VER_MAJOR+
			VER_MINOR*OFFSET_VER_MINOR+
			VER_SUBMINOR*OFFSET_VER_SUBMINOR;
	return app_ver_t;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
