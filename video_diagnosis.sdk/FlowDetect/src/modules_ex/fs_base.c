#include "fs_base.h"
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int fs_is_file_exist(const char * file_path)
{
	if(file_path==0)
			return ERROR;

		if(access(file_path,F_OK)==0)
			return SUCCESS;

		return ERROR;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void fs_store_binary(const char *filepath, const char *_buffer,const int _sz)
{
	FILE *fp = fopen(filepath, "wb");
	    if (fp != NULL)
	    {
	    	fwrite(_buffer,_sz,1,fp);
	        fclose(fp);
	    }
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void fs_store_txt(const char *filepath, const char *data)
{
	FILE *fp = fopen(filepath, "wt");
	    if (fp != NULL)
	    {
	        fputs(data, fp);
	        fclose(fp);
	    }
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int  fs_load_txt(const char *filepath,char* const buffer)
{
	  const  int string_size=fs_file_size(filepath);

	  int  read_size=0;

	  FILE *handler = fopen(filepath, "r");

	   if (handler)
	   {
	       // Read it all in one operation
	       read_size = fread(buffer, sizeof(char), string_size, handler);

	       // fread doesn't set it so put a \0 in the last position
	       // and buffer is now officially a string
	       buffer[string_size] = '\0';

	       if (string_size != read_size)
	       {
	    	   // Something went wrong, throw away the memory and set
	           return ERROR;
	       }

	       // Always remember to close the file.
	       fclose(handler);
	    }

	   return SUCCESS;

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int fs_file_size(const char *filepath)
{
	   int file_size=0;
	   FILE *handler = fopen(filepath, "r");

	   if (handler)
	   {
	       // Seek the last byte of the file
	       fseek(handler, 0, SEEK_END);
	       // Offset from the first to the last byte, or in other words, filesize
	       file_size = ftell(handler);

	       // Always remember to close the file.
	       fclose(handler);
	    }
	   return file_size;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
ssize_t readall(int fd, void *buf, size_t *bytes){
     ssize_t nread = 0, n=0;
     size_t nbyte = *bytes;

     do {
         if ((n = read(fd, &((char *)buf)[nread], nbyte - nread)) == -1) {
             if (errno == EINTR)
                 continue;
             else
                 return (-1);
         }
         if (n == 0)
             return nread;
         nread += n;
     } while (nread < nbyte);
     return nread;
}

/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void fs_readfile(const char *fname, char *buffer, size_t *size, mode_t *mode)
{
   int fd=0;
   struct stat st;

   ck(fd=open(fname,O_RDONLY) );
   ck(fstat(fd,&st) );
   *size=st.st_size;
   *mode=st.st_mode;
   buffer=calloc(1,*size+1);
   ck(readall(fd, buffer, size) );
   ck(close(fd) );
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
