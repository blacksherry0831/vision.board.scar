# vision.board.scar

## 开发工具

| 开发平台 | 版本              |
| -------- | ----------------- |
| 操作系统 | windows 7/10      |
| 开发工具 | Xilinx SDK 2015.4 |
|          |                   |

## 程序配置

开机后自动执行up.sh脚本，

| 启动参数 | detail       | default        | mean          |
| -------- | ------------ | -------------- | ------------- |
| p        | project      | scar_detect_01 | 球笼检测      |
| s        | sensor       | 1              | 单目摄像机    |
| w        | width        | 1920           | 图像宽        |
| h        | height       | 1080           | 图像高        |
| f        | frame        | 0              | 输出0号位图像 |
| D        | debug output | no param       | 输出调试信息  |

### 调试模式启动

XXX.elf 	-s 1 -w 1920 -h 1080 -p scar_detect_01 -f 0 -D

启动程序。

### 发布版本启动

XXX			-s 1 -w 1920 -h 1080 -p scar_detect_01 -f 0    >/dev/null 2>&1 &