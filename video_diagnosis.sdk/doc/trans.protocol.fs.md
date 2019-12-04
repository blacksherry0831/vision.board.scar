# 文件存取协议

## 一、命令字

### 命令字01

```C++
enum CMD_TYPE_00_F {
	CT_FILE='f',
};
```

### 命令字02

```c++
enum CMD_TYPE_02_F {
		CT_FILE_GET='g',
		CT_FILE_PUT='p',
    	CT_FILE_DELETE='d',
	};
```

```c++
enum CMD_TYPE_02_C{

		CT_START=0x00,
		CT_STOP=0x01,

		CT_START_00=0x10,
		CT_STOP_00=0x11,
		CT_START_01=0x20,
		CT_STOP_01=0x21,

};
```



## 二、文件操作命令

### 文件名

| fileFullPath     | example               | mean                     |
| ---------------- | --------------------- | ------------------------ |
| 全路径           | "/media/sdcard/up.sh" | 操作具体的文件           |
| 配置文件下的文件 | "filename.ext"        | 操作配置目录下的单个文件 |
| 配置文件目录     | "project.cfg."        | 操作配置目录下的所有文件 |

### 文件写入

| Command  | 命令字01 | 命令字02    | BODY（multi byte）                                     |
| -------- | -------- | ----------- | ------------------------------------------------------ |
| file put | CT_FILE  | CT_FILE_PUT | FileTransUI.fileFullPath=="/media/sdcard/filename.ext" |
| 应答     | CT_RESP  | CT_OK       |                                                        |

$$
BODY_{bytes}=sizeof(FileTransUI)+file_{size}
$$

### 读取文件

读取的文件会在数据通道传输

| Command  | 命令字01 | 命令字02    | BODY（multi byte）                                     |
| -------- | -------- | ----------- | ------------------------------------------------------ |
| file get | CT_FILE  | CT_FILE_GET | FileTransUI.fileFullPath=="/media/sdcard/filename.ext" |
| 应答     | CT_RESP  | CT_OK       |                                                        |

### 文件开始

| Command    | 命令字01 | 命令字02 | BODY（2 byte） |
| ---------- | -------- | -------- | -------------- |
| file start | CT_FILE  | CT_START | file count     |

### 文件结束

| Command   | 命令字01 | 命令字02 | BODY（2 byte） |
| --------- | -------- | -------- | -------------- |
| file stop | CT_FILE  | CT_STOP  | file count     |

### 删除文件

| Command     | 命令字01 | 命令字02       | BODY（multi byte）                                     |
| ----------- | -------- | -------------- | ------------------------------------------------------ |
| file delete | CT_FILE  | CT_FILE_DELETE | FileTransUI.fileFullPath=="/media/sdcard/filename.ext" |
| 应答        | CT_RESP  | CT_OK          |                                                        |

## 三、文件读取流程

### 1. 删除所有配置文件

| property           | value          |                                   |
| ------------------ | -------------- | --------------------------------- |
| Command            | file delete    |                                   |
| 命令字01           | CT_FILE        |                                   |
| 命令字02           | CT_FILE_DELETE |                                   |
| BODY（multi byte） | FileTransUI    | .fileFullPath==**"project.cfg."** |

### 2.读取所有配置文件

#### 发送

| property           | value       |                                   |
| ------------------ | ----------- | --------------------------------- |
| Command            | file get    |                                   |
| 命令字01           | CT_FILE     |                                   |
| 命令字02           | CT_FILE_GET |                                   |
| BODY（multi byte） | FileTransUI | .fileFullPath==**"project.cfg."** |

#### 接收

| property       | value      |            |
| -------------- | ---------- | ---------- |
| Command        | file start |            |
| 命令字01       | CT_FILE    |            |
| 命令字02       | CT_START   |            |
| BODY（2 byte） |            | file count |

| property           | value       |                                   |
| ------------------ | ----------- | --------------------------------- |
| Command            | file put    |                                   |
| 命令字01           | CT_FILE     |                                   |
| 命令字02           | CT_FILE_PUT |                                   |
| BODY（multi byte） |             | .fileFullPath==**"filename.ext"** |

| property       | value     |            |
| -------------- | --------- | ---------- |
| Command        | file stop |            |
| 命令字01       | CT_FILE   |            |
| 命令字02       | CT_STOP   |            |
| BODY（2 byte） |           | file count |

### 3.存储配置文件

| property           | value       |                                   |
| ------------------ | ----------- | --------------------------------- |
| Command            | file put    |                                   |
| 命令字01           | CT_FILE     |                                   |
| 命令字02           | CT_FILE_PUT |                                   |
| BODY（multi byte） |             | .fileFullPath==**"filename.ext"** |