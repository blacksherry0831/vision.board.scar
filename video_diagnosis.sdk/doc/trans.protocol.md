# LINUX与上位机通讯协议

## 命令字01

```C++
enum CMD_TYPE {

	CT_HEART='h',
	CT_QUERY='q',
	CT_CTRL='c',
	CT_RESP='r',
	CT_IMG='I',

};
```

## 命令字02

```c++
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
enum CMD_TYPE_02 {

		CT_BEAT='b',

		CT_LR_RUN_2=0x20,
		CT_ROLLER_Q=0x10
	};
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
enum CMD_TYPE_02_RESP {

	CT_OK=0x00,
	CT_ERROR=0x01,
	CT_NONE=0x02,

	};
/*-----------------------------------*/
/**
*
*/
/*-----------------------------------*/
enum CMD_TYPE_02_C{

		CT_START=0x00,
		CT_STOP=0x01,

		CT_START_00=0x10,
		CT_STOP_00=0x11,
		CT_START_01=0x20,
		CT_STOP_01=0x21,

};
/*-----------------------------------*/
/**
*
*/
/*-----------------------------------*/
enum CMD_TYPE_02_I{

		CT_IMG_FRAME='F',
		CT_IMG_RECT='R',
		CT_IMG_MODE_CHANGE='M',

		CT_IMG_SIGMA_UP_CHANGE=0xF1,
		CT_IMG_SIGMA_DOWN_CHANGE=0xF2,

		CT_IMG_MASK_CHANGE='K',

};
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
enum WorkMode
{
	WM_SIZE_FULL=0x80,
	WM_SIZE_CUT=0x40,
	WM_ORG_IMG=0x20,
	WM_DIFF_IMG=0x10,
	RESP=0x01

};
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
enum HearBeatResp
{
	HB_RESP='r',
	HB_NONE='n',
};
```

## 图像处理SIGMA 上下限设置

| Command    | 命令字01 | 命令字02                 | BODY    |
| ---------- | -------- | ------------------------ | ------- |
| 查询上门限 | CT_QUERY | CT_IMG_SIGMA_UP_CHANGE   |         |
| 设置上门限 | CT_IMG   | CT_IMG_SIGMA_UP_CHANGE   | SIGMA^2 |
| 查询下门限 | CT_QUERY | CT_IMG_SIGMA_DOWN_CHANGE |         |
| 设置下门限 | CT_IMG   | CT_IMG_SIGMA_DOWN_CHANGE | SIGMA^2 |
| 应答上门限 | CT_RESP  | CT_OK                    | SIGMA^2 |
| 应答下门限 | CT_RESP  | CT_ERROR                 | SIGMA^2 |

$$
\sigma^{2}	\in	[0,255] \\
\sigma		\in	[0,\sqrt{255}]
$$

