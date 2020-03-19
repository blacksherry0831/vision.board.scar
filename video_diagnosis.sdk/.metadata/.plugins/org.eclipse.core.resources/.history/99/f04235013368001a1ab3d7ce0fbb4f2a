#include "cetc_flash.h"

int debug = 1;
#define MTD_DEV "/dev/mtd1"

#define PAGE_OFFSET  (64*1024)

#define INT_OFFSET sizeof(int)
#define MAGIC 123456789
#define MAGIC_OFFSET 0
#define SERNO_OFFSET (MAGIC_OFFSET + PAGE_OFFSET)

#define ONLINE_OFFSET  (MAGIC_OFFSET+INT_OFFSET)
#define DEADLINE_OFFSET (ONLINE_OFFSET+INT_OFFSET)

#define BUF_SIZE	(64 * 1024 * sizeof(u_int8_t))

/* define a print format specifier for off_t */
#ifdef __USE_FILE_OFFSET64
#define PRIxoff_t PRIx64
#define PRIdoff_t PRId64
#else
#define PRIxoff_t "l"PRIx32
#define PRIdoff_t "l"PRId32
#endif



/*
 * MEMGETINFO
 */
static int getmeminfo(int fd, struct mtd_info_user *mtd)
{
	return ioctl(fd, MEMGETINFO, mtd);
}

/*
 * MEMERASE
 */
static int memerase(int fd, struct erase_info_user *erase)
{
	return ioctl(fd, MEMERASE, erase);
}

/*
 * MEMGETREGIONCOUNT
 * MEMGETREGIONINFO
 */
static int getregions(int fd, struct region_info_user *regions, int *n)
{
	int i, err;
	err = ioctl(fd, MEMGETREGIONCOUNT, n);
	if (err)
		return err;
	for (i = 0; i < *n; i++) {
		regions[i].regionindex = i;
		err = ioctl(fd, MEMGETREGIONINFO, &regions[i]);
		if (err)
			return err;
	}
	return 0;
}

int erase_flash(int fd, u_int32_t offset, u_int32_t bytes)
{
	int err;
	struct erase_info_user erase;
	erase.start = offset;
	erase.length = bytes;
	err = memerase(fd, &erase);
	if (err < 0) {
		perror("MEMERASE");
		return 1;
	}
    if(debug)
    	fprintf(stderr, "Erased %d bytes from address 0x%.8x in flash\n", bytes, offset);
	return 0;
}

int flash_to_file(int fd, off_t offset, size_t len, const char *filename)
{
	u_int8_t *buf = NULL;
	int outfd, err;
	int size = len * sizeof(u_int8_t);
	int n = len;

	if (offset != lseek(fd, offset, SEEK_SET)) {
		perror("lseek()");
		goto err0;
	}
	outfd = creat(filename, 0666);
	if (outfd < 0) {
		perror("creat()");
		goto err1;
	}

retry:
	if ((buf = (u_int8_t *) malloc(size)) == NULL) {
#define BUF_SIZE	(64 * 1024 * sizeof(u_int8_t))
		fprintf(stderr, "%s: malloc(%#x)\n", __func__, size);
		if (size != BUF_SIZE) {
			size = BUF_SIZE;
			fprintf(stderr, "%s: trying buffer size %#x\n", __func__, size);
			goto retry;
		}
		perror("malloc()");
		goto err0;
	}
	do {
		if (n <= size)
			size = n;
		err = read(fd, buf, size);
		if (err < 0) {
			fprintf(stderr, "%s: read, size %#x, n %#x\n", __func__, size, n);
			perror("read()");
			goto err2;
		}
		err = write(outfd, buf, size);
		if (err < 0) {
			fprintf(stderr, "%s: write, size %#x, n %#x\n", __func__, size, n);
			perror("write()");
			goto err2;
		}
		if (err != size) {
			fprintf(stderr, "Couldn't copy entire buffer to %s. (%d/%d bytes copied)\n", filename, err, size);
			goto err2;
		}
		n -= size;
	} while (n > 0);

	if (buf != NULL)
		free(buf);
	close(outfd);
	printf("Copied %zu bytes from address 0x%.8"PRIxoff_t" in flash to %s\n", len, offset, filename);
	return 0;

err2:
	close(outfd);
err1:
	if (buf != NULL)
		free(buf);
err0:
	return 1;
}

int file_to_flash(int fd, off_t offset, u_int32_t len, const char *filename)
{
	u_int8_t *buf = NULL;
	FILE *fp;
	int err;
	int size = len * sizeof(u_int8_t);
	int n = len;

	if (offset != lseek(fd, offset, SEEK_SET)) {
		perror("lseek()");
		return 1;
	}
	if ((fp = fopen(filename, "r")) == NULL) {
		perror("fopen()");
		return 1;
	}
retry:
	if ((buf = (u_int8_t *) malloc(size)) == NULL) {
		fprintf(stderr, "%s: malloc(%#x) failed\n", __func__, size);
		if (size != BUF_SIZE) {
			size = BUF_SIZE;
			fprintf(stderr, "%s: trying buffer size %#x\n", __func__, size);
			goto retry;
		}
		perror("malloc()");
		fclose(fp);
		return 1;
	}
	do {
		if (n <= size)
			size = n;
		if (fread(buf, size, 1, fp) != 1 || ferror(fp)) {
			fprintf(stderr, "%s: fread, size %#x, n %#x\n", __func__, size, n);
			perror("fread()");
			free(buf);
			fclose(fp);
			return 1;
		}
int i;
        for(i=0; i<size; i++)   
            printf("write addr %ld buf 0x%x \n", offset+i, buf[i]);

		err = write(fd, buf, size);
		if (err < 0) {
			fprintf(stderr, "%s: write, size %#x, n %#x\n", __func__, size, n);
			perror("write()");
			free(buf);
			fclose(fp);
			return 1;
		}
		n -= size;
	} while (n > 0);

	if (buf != NULL)
		free(buf);
	fclose(fp);
	printf("Copied %d bytes from %s to address 0x%.8"PRIxoff_t" in flash\n", len, filename, offset);
	return 0;
}

int flash_read(int fd, off_t offset, size_t len, char * data)
{
	u_int8_t *buf = NULL;
	int outfd, err;
	int size = len * sizeof(u_int8_t);
	int n = len;
    int i;
	if (offset != lseek(fd, offset, SEEK_SET)) {
		perror("lseek()");
		goto err0;
	}

retry:
	if ((buf = (u_int8_t *) malloc(size)) == NULL) {
		fprintf(stderr, "%s: malloc(%#x)\n", __func__, size);
		if (size != BUF_SIZE) {
			size = BUF_SIZE;
			fprintf(stderr, "%s: trying buffer size %#x\n", __func__, size);
			goto retry;
		}
		perror("malloc()");
		goto err0;
	}
	do {
		if (n <= size)
			size = n;
		err = read(fd, buf, size);
		if (err < 0) {
			fprintf(stderr, "%s: read, size %#x, n %#x\n", __func__, size, n);
			perror("read()");
			goto err2;
		}

		if (err != size) {
			fprintf(stderr, "Couldn't copy entire buffer (%d/%d bytes copied)\n", err, size);
			goto err2;
		}
		n -= size;
	} while (n > 0);

    if(debug)
    {
        for(i=0; i<len; i++)   
            printf("read addr %ld buf 0x%x \n", offset+i, buf[i]);
    }
    memcpy(data, buf, len);

	if (buf != NULL)
		free(buf);
    if(debug)
    	printf("Copied %zu bytes from address 0x%.8"PRIxoff_t" in flash \n", len, offset);
	return 0;

err2:

err1:
	if (buf != NULL)
		free(buf);
err0:
	return 1;
}


int flash_write(int fd, off_t offset, u_int32_t len, const char *data)
{
	u_int8_t *buf = NULL;
	int err;
	int size = len * sizeof(u_int8_t);
	int n = len;

	if (offset != lseek(fd, offset, SEEK_SET)) {
		perror("lseek()");
		return 1;
	}

retry:
	if ((buf = (u_int8_t *) malloc(size)) == NULL) {
		fprintf(stderr, "%s: malloc(%#x) failed\n", __func__, size);
		if (size != BUF_SIZE) {
			size = BUF_SIZE;
			fprintf(stderr, "%s: trying buffer size %#x\n", __func__, size);
			goto retry;
		}
		perror("malloc()");
		return 1;
	}
	do {
		if (n <= size)
			size = n;
        
		memcpy(buf, data, size); 

		err = write(fd, buf, size);
		if (err < 0) {
			fprintf(stderr, "%s: write, size %#x, n %#x\n", __func__, size, n);
			perror("write()");
			free(buf);
			return 1;
		}
		n -= size;
	} while (n > 0);

	if (buf != NULL)
		free(buf);
    if(debug)
    	printf("Copied %d bytes  to address 0x%.8"PRIxoff_t" in flash\n", len, offset);
	return 0;
}

u_int32_t flash_get_data(off_t offset)
{
	int err = 0, fd = 0;
    char read_data[4] = {0};
    u_int32_t data;     
	/* open device */
    if ((fd = open(MTD_DEV, O_SYNC | O_RDWR)) < 0)
    {
        printf("open %s fail\n",MTD_DEV);
        return -1;
    }
    
	err = flash_read(fd, offset, sizeof(data), &data);
    if(err == 1)
    {
        printf("flash_read fail\n");
        close(fd);
        return -1;
    }

    if(debug)
        printf("read  data  %ld (0x%lx),\n",data, data);
    
    close(fd);

    return data;
}

u_int32_t flash_get_online()
{
    return flash_get_data(ONLINE_OFFSET);
}

u_int32_t flash_get_deadline()
{
    return flash_get_data(DEADLINE_OFFSET);
}

u_int32_t flash_get_magic_inter()
{
    return flash_get_data(MAGIC_OFFSET);
}

//获取服务期校验日期
void cetc_get_check(struct check *data)
{
    data->magic = flash_get_magic_inter();
    data->online = flash_get_online();
    data->deadline = flash_get_deadline();
}

//刷新已服务时间和剩余服务期
int flash_set_data(off_t offset, char *data, u_int32_t len)
{
	int err = 0, fd = 0;
    if(len > BUF_SIZE)
    {
        printf("len is out\n");
        return -1;
    }    
	/* open device */
    if ((fd = open(MTD_DEV, O_SYNC | O_RDWR)) < 0)
    {
        printf("open %s fail\n",MTD_DEV);
        return -1;
    }
    
    err = erase_flash(fd, offset, BUF_SIZE);
    if(err == 1)
    {
        printf("erase_flash fail\n");
        close(fd);
        return -1;
    }

	err = flash_write(fd, offset, len, data);
    if(err == 1)
    {
        printf("flash_write fail\n");
        close(fd);
        return -1;
    }

    close(fd);
    return 0;
}

void cetc_set_check(struct check *data)
{
    flash_set_data(MAGIC_OFFSET, (char *)data, sizeof(struct check));

}

//刷新已服务时间和剩余服务期
int cetc_update_flash()
{
    struct check data;
    static char first = 1;

    cetc_get_check(&data);
    
    if(first) {
        first = 0;
        if(data.magic != MAGIC) {
            printf("magic wrong\n");
            exit(1);
        }
    }

    if(0 == data.deadline || 0xffffffff == data.deadline) {
        printf("time out !!!!!!!!\n");
        exit(1);
    }

    data.deadline--;
    data.online++;

    return flash_set_data(MAGIC_OFFSET, &data, sizeof(struct check));  //刷新已服务时间和剩余服务期
}
