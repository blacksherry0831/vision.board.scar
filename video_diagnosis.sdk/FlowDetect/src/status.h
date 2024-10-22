#ifndef STATUS_H
#define STATUS_H
/*-----------------------------------*/
#include <sys/stat.h>
#include <assert.h>

#include "modules_ex/cmd_file.h"
/*-----------------------------------*/
enum ProjectRun{
	scar_detect_01=0,
	inside08,
	outside08,
    flame_monitor};
/*-----------------------------------*/
extern const char* ProjectName[];
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

enum ProjectRun GetProjectRun();
int IsProjectRun(const enum ProjectRun _p);
/*-----------------------------------*/
const char * GetProjectRunStr();

void SetProjecRun(enum ProjectRun _pr);
/*-----------------------------------*/
#define PRINTF_HB	(0)
/*-----------------------------------*/
#endif
