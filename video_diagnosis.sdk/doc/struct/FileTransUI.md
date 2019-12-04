# FileTransUI

```c++
#define ALIGN_SIZE_T (8)
#define STRUCT_UNION_SIZE	(ALIGN_SIZE_T*64)
```



```c++
typedef struct _FileTrans
{
	unsigned char nSize[ALIGN_SIZE_T];//this struct size
	char prefix[ALIGN_SIZE_T];
	char fileFullPath[ALIGN_SIZE_T*16];
	char fileSize[ALIGN_SIZE_T];
} FileTrans;
```





```c++
typedef union _FileTransUI
{
	unsigned char buff[STRUCT_UNION_SIZE];
	FileTrans filetrans;
}FileTransUI;
```

