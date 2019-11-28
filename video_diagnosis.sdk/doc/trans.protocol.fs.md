# 文件存取协议

## 命令字01

```C++
enum CMD_TYPE_00_F {
	CT_FILE='f',
};
```

## 命令字02

```c++
enum CMD_TYPE_02_F {
		CT_FILE_GET='g',
		CT_FILE_PUT='p',
	};
```

## 文件写入

| Command  | 命令字01 | 命令字02    | BODY（multi byte）            |
| -------- | -------- | ----------- | ----------------------------- |
| 文件写入 | CT_FILE  | CT_FILE_PUT | sizeof(FileTransUI)+FILE_SIZE |
| 应答     | CT_RESP  | CT_OK       |                               |

$$
BODY_{LEN}=sizeof(FileTransUI)+file_{size}
$$



## 读取文件

读取的文件会在数据通道传输

| Command  | 命令字01 | 命令字02    | BODY（multi byte） |
| -------- | -------- | ----------- | ------------------ |
| 文件读取 | CT_FILE  | CT_FILE_GET | FileTransUI        |
| 应答     | CT_RESP  | CT_OK       |                    |

