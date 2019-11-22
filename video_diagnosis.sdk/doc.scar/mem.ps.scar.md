# PS MEMORY

## MEMORY  ADDR

USE LINUX  mmap() to use this memory  

| 属性     | value                    | size |
| -------- | ------------------------ | ---- |
| 内存位置 | 0x0000 0000~0x3FFF FFFFF | 1GB  |
|          |                          |      |
|          |                          |      |

## MEMORY DEFINE

| physical address start | physical address end | frame.size | property |        |
| ---------------------- | -------------------- | ---------- | -------- | ------ |
| 0x0000 0000            | 0x1DFF FFFF          | unused     | unused   |        |
| 0x1e00 0000            | 0x1FFF FFFF          | 0x200 0000 | 32MB     | PL->PS |
| 0x2000 0000            | 0x207F FFFF          | 0x80 0000  | 8MB      | PS->PL |
| 0x2080 0000            | 0x3FFF FFFFF         | unused     | unused   |        |