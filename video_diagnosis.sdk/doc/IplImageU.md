# IplImageU

```
#define ALIGN_SIZE_T (8)
```



```c++
typedef struct _IplImageU
{
	unsigned char nSize[ALIGN_SIZE_T];//this struct size
	char prefix[ALIGN_SIZE_T];
	unsigned char IpAddrChannel[ALIGN_SIZE_T];
	unsigned char frame[ALIGN_SIZE_T];

	unsigned char width[ALIGN_SIZE_T];
	unsigned char height[ALIGN_SIZE_T];

	unsigned char width_roi[ALIGN_SIZE_T];
	unsigned char height_roi[ALIGN_SIZE_T];
	unsigned char x_roi[ALIGN_SIZE_T];
	unsigned char y_roi[ALIGN_SIZE_T];

	unsigned char sensor_stat[ALIGN_SIZE_T];
	unsigned char nChannels[ALIGN_SIZE_T];
	char colorModel[ALIGN_SIZE_T*8];/**<*/

	IplImage  	Iplimg;
} IplImageU;
```

```c++
typedef struct _IplImage
{
    int  nSize;             /* sizeof(IplImage) */
    int  ID;                /* version (=0)*/
    int  nChannels;         /* Most of OpenCV functions support 1,2,3 or 4 channels */
    int  alphaChannel;      /* Ignored by OpenCV */
    int  depth;             /* Pixel depth in bits: IPL_DEPTH_8U, IPL_DEPTH_8S, IPL_DEPTH_16S,
                               IPL_DEPTH_32S, IPL_DEPTH_32F and IPL_DEPTH_64F are supported.  */
    char colorModel[4];     /* Ignored by OpenCV */
    char channelSeq[4];     /* ditto */
    int  dataOrder;         /* 0 - interleaved color channels, 1 - separate color channels.
                               cvCreateImage can only create interleaved images */
    int  origin;            /* 0 - top-left origin,
                               1 - bottom-left origin (Windows bitmaps style).  */
    int  align;             /* Alignment of image rows (4 or 8).
                               OpenCV ignores it and uses widthStep instead.    */
    int  width;             /* Image width in pixels.                           */
    int  height;            /* Image height in pixels.                          */
    struct _IplROI *roi;    /* Image ROI. If NULL, the whole image is selected. */
    struct _IplImage *maskROI;      /* Must be NULL. */
    void  *imageId;                 /* "           " */
    struct _IplTileInfo *tileInfo;  /* "           " */
    int  imageSize;         /* Image data size in bytes
                               (==image->height*image->widthStep
                               in case of interleaved data)*/
    char *imageData;        /* Pointer to aligned image data.         */
    int  widthStep;         /* Size of aligned image row in bytes.    */
    int  BorderMode[4];     /* Ignored by OpenCV.                     */
    int  BorderConst[4];    /* Ditto.                                 */
    char *imageDataOrigin;  /* Pointer to very origin of image data
                               (not necessarily aligned) -
                               needed for correct deallocation */
}
IplImage;
```

