| 地址   | 变量            | 说明                                                         |
| ------ | --------------- | ------------------------------------------------------------ |
| X"100" | arm_rst_sd      | 模块复位，先发’1’再给’0’  建议在每次启动前进行复位           |
| X"101" | sd_mode         | Bit0：全局模式  Bit1：行检测模式  Bit2：列检测模式  ‘1’使能该模式  全零则上传原始图像 |
| X"102" | arm_sd_start_en | 使能一帧图象处理，先发’1’再给’0’                             |
| X"104" | mask_addr_H     | 蒙版高地址位，0~7                                            |
| X"105" | mask_addr_L     | 蒙版低地址位，0~47                                           |
| X"109" | ddr3_base_addr  | /                                                            |
| X"10A" | sd_montage_en   | '0'奇异点检测结果不拼接，'1'检测结果拼接                     |
| X"110" | ko_up           | 全局 - 上门限系数，整数  4 bit，小数 4 bit  值为X”FF”时，则该门限失效（下同） |
| X"111" | ko_down         | 全局 - 下门限系数，整数  4 bit，小数 4 bit                   |
| X"112" | kr_up           | 行检测 - 上门限系数，整数  4 bit，小数 4 bit                 |
| X"113" | kr_down         | 行检测 - 下门限系数，整数  4 bit，小数 4 bit                 |
| X"114" | kc_up           | 列检测 - 上门限系数，整数  4 bit，小数 4 bit                 |
| X"115" | kc_down         | 列检测 - 下门限系数，整数  4 bit，小数 4 bit                 |

