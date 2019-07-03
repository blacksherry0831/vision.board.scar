#ifndef STATUS_H
#define STATUS_H
/*-----------------------------------*/
#include "linux_header.h"
/*-----------------------------------*/
enum ProjectRun{inside08,outside08};
/*-----------------------------------*/
int GetSensorStat_T();
/*-----------------------------------*/
int SetSensorStat_T(const int _s);
/*-----------------------------------*/
#endif
