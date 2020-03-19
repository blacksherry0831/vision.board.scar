#ifndef STATUS_H
#define STATUS_H
/*-----------------------------------*/
#include <sys/stat.h>
#include <assert.h>
/*-----------------------------------*/
enum ProjectRun{
	scar_detect_01=0,
	inside08,
	outside08};
/*-----------------------------------*/
extern const char* ProjectName[];
/*-----------------------------------*/
int GetSensorStat_T();
/*-----------------------------------*/
int SetSensorStat_T(const int _s);
/*-----------------------------------*/
const char * GetProjectRunStr();
/*-----------------------------------*/
int MakeProjectDirectory();
/*-----------------------------------*/
void initProjectCfgDirPath_Separator(char *_path);
void initProjectCfgDirPath(char *_path);
/*-----------------------------------*/
void PrintBuildTime();
short unsigned int GetVersion();
/*-----------------------------------*/
#define PRINTF_HB	(0)
/*-----------------------------------*/
#endif
