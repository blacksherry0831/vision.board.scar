/*
 * flame_monitor.h
 *
 *  Created on: 2020Äê3ÔÂ17ÈÕ
 *      Author: yjkj909
 */

#ifndef FLAME_MONITOR_H_
#define FLAME_MONITOR_H_

#include "linux_header.h"
#include "modules/printf_log/printf_log.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/tcp.h>
#include "sync/sync_global.h"

void init_fire();
void set_flame_monitor_flag(int _v);
int get_flame_monitor_flag();
void set_thresholde_area(double _v);
double get_thresholde_area();
void set_thresholde_difference(double _v);
double get_thresholde_difference();
void set_last_flame(double _v);
double get_last_flame();
void set_current_flame(double _v);
double get_current_flame();
void set_igniter_status(int _v);
int get_igniter_status();
void set_fire_on(int _v);
int get_fire_on();
void set_fire_off(int _v);
int get_fire_off();
int get_cnt_i();
void inc_cnt_i();
int is_up_to_thresholde_difference();

int init_socket_client(int* _scli);
void check_socket_client(int* _scli);
void *iginter_client(void* _pdata);
pthread_t connect_to_igniter();

#endif /* FLAME_MONITOR_H_ */
