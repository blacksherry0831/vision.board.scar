# PL MEMORY

## SPACE BLOCK

| 属性     | value                    | size  |
| -------- | ------------------------ | ----- |
| 内存位置 | 0x4000 0000~0x7FFF FFFFF | 1GB   |
| 每块大小 | 0x800 0000               | 128MB |
| 块数     | 8                        | 8     |

| space block | physical address start | physical address end | size      |
| ----------- | ---------------------- | -------------------- | --------- |
| 0           | 0x4000 0000            | 0x47FF FFFF          | 0x8000000 |
| 1           | 0x4800 0000            | 0x4FFF FFFF          | 0x8000000 |
| 2           | 0x5000 0000            | 0x57FF FFFF          | 0x8000000 |
| 3           | 0x5800 0000            | 0x5FFF FFFF          | 0x8000000 |
| 4           | 0x6000 0000            | 0x67FF FFFF          | 0x8000000 |
| 5           | 0x6800 0000            | 0x6FFF FFFF          | 0x8000000 |
| 6           | 0x7000 0000            | 0x77FF FFFF          | 0x8000000 |
| 7           | 0x7800 0000            | 0x7FFF FFFFF         | 0x8000000 |

## SPACE FRAME

| space frame | physical address start | physical address end | frame.size | cal         | property |
| ----------- | ---------------------- | -------------------- | ---------- | ----------- | -------- |
| 0           | 0x4000 0000            | 0x40FD 1FFF          | 0xFD 2000  | 1920X1080X8 | 空白区   |
| 1           | 0x40FD 2000            | 0x411C C3FF          | 0x1FA400   | 1920X1080X1 | 原始图像 |
| 2           | 0x411C C400            | 0x413C 67FF          | 0x1FA400   | 1920X1080X1 | 灰度图   |
| 3           | 0x413C 6800            | 0x415C 0BFF          | 0x1FA400   | 1920X1080X1 | 蒙版图0  |
| 4           | 0x415C 0C00            | 0x417B AFFF          | 0x1FA400   | 1920X1080X1 | 蒙版图8  |
| 5           | 0x417B B000            | 0x419B 53FF          | 0x1FA400   | 1920X1080X1 | 蒙版图16 |
| 6           | 0x419B 5400            | 0x41BA F7FF          | 0x1FA400   | 1920X1080X1 | 蒙版图24 |
| 7           | 0x41BA F800            | 0x41DA 9BFF          | 0x1FA400   | 1920X1080X1 | 蒙版图32 |
| 8           | 0x41DA 9C00            | 0x41FA 3FFF          | 0x1FA400   | 1920X1080X1 | 蒙版图40 |
| 9           | 0x41FA 4000            | 0x4219 E3FF          | 0x1FA400   | 1920X1080X1 | 蒙版图48 |
| ...         | ...                    | ...                  | ...        |             |          |