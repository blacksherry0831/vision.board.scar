#ifndef STATUS_H
#define STATUS_H
/*-----------------------------------*/
#include "linux_header.h"
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
char * GetProjectRunStr();
/*-----------------------------------*/
#endif
