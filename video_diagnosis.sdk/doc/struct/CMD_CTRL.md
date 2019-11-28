# CMD_CTRL

```C++
typedef struct {
	unsigned char f_header[4];//"Yjkj"
	unsigned char f_data_len_high[2];//length high
	unsigned char f_cmd_idx[4];//
	unsigned char f_dst_dev[2];
	unsigned char f_src_dev[2];
	unsigned char f_cmd[2];
	unsigned char f_data_len[2];//length low
}CMD_CTRL_HEADER;
```

| data            | detail      | content        |
| --------------- | ----------- | -------------- |
| f_header        | 报头标记    | "Yjkj"         |
| f_data_len_high | length high |                |
| f_cmd_idx       | 任务序列号  | 1970年时间序列 |
| f_dst_dev       | 目标设备    |                |
| f_src_dev       | 源设备      |                |
| f_cmd           | command     |                |
| f_data_len      | length low  |                |
|                 |             |                |



```c++
typedef struct{
	CMD_CTRL_HEADER f_header;
	unsigned char* f_data;
	unsigned int f_data_size;
	unsigned char f_crc;
}CMD_CTRL;
```

