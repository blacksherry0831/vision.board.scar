#ifndef CETC_FLASH_H
#define CETC_FLASH_H

#include "../linux_header.h"

struct check
{
    int magic;
    int online;
    int deadline;
    int seral[4];
    int crc;
};


int erase_flash(int fd, u_int32_t offset, u_int32_t bytes);

int flash_to_file(int fd, off_t offset, size_t len, const char *filename);

int file_to_flash(int fd, off_t offset, u_int32_t len, const char *filename);

int flash_read(int fd, off_t offset, size_t len, char * data);


int flash_write(int fd, off_t offset, u_int32_t len, const char *data);


u_int32_t flash_get_data(off_t offset);

u_int32_t flash_get_online();

u_int32_t flash_get_deadline();

u_int32_t flash_get_magic_inter();


void cetc_get_check(struct check *data);

int flash_set_data(off_t offset, char *data, u_int32_t len);


void cetc_set_check(struct check *data);

int cetc_update_flash();




#endif

