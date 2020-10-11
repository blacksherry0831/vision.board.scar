| value | char         | cmd00    | cmd01                          | param        | resp    |
| ----- | ------------ | -------- | ------------------------------ | ------------ | ------- |
| 0x00  |              |          | CT_START; CT_OK                |              |         |
| 0x01  |              |          | CT_STOP; CT_ERROR              |              |         |
| 0x02  |              |          | ; CT_NONE                      |              |         |
| ...   | ...          | ...      | ...                            | ...          | ...     |
| 0x10  |              |          | CT_START_00                    | WM_DIFF_IMG  |         |
| 0x11  |              |          | CT_STOP_00                     |              |         |
| ...   | ...          | ...      | ...                            | ...          | ...     |
| 0x20  |              |          | CT_START_01                    | WM_ORG_IMG   |         |
| 0x21  |              |          | CT_STOP_01                     |              |         |
| ...   | ...          | ...      | ...                            | ...          | ...     |
| 0x40  |              |          |                                | WM_SIZE_CUT  |         |
| 0x41  | A            |          |                                |              |         |
| 0x42  | B            |          |                                |              |         |
| 0x43  | C            |          |                                |              |         |
| 0x44  | D            |          |                                |              |         |
| 0x45  | E            |          |                                |              |         |
| 0x46  | F            |          | CT_IMG_FRAME                   |              |         |
| 0x47  | G            |          |                                |              |         |
| 0x48  | H            |          |                                |              |         |
| 0x49  | I            | CT_IMG   |                                |              |         |
| 0x4A  | J            |          |                                |              |         |
| 0x4B  | K            |          | CT_IMG_MASK_CHANGE             |              |         |
| 0x4C  | L            |          |                                |              |         |
| 0x4D  | M            |          | CT_IMG_MODE_CHANGE             |              |         |
| 0X4E  | N            |          |                                |              |         |
| 0x4F  | O            |          |                                |              |         |
| 0x50  | P            |          |                                |              |         |
| 0x51  | Q            |          |                                |              |         |
| 0x52  | R            |          | CT_IMG_RECT                    |              |         |
| 0x53  | S            |          |                                |              |         |
| 0x54  | T            |          |                                |              |         |
| 0x55  | U            |          |                                |              |         |
| 0x56  | V            |          |                                |              |         |
| 0x57  | W            |          |                                |              |         |
| 0x58  | X            |          |                                |              |         |
| 0x59  | Y            |          |                                |              |         |
| 0x5A  | Z            |          |                                |              |         |
| ...   | ...          | ...      | ...                            | ...          | ...     |
| 0x61  | a            |          |                                |              |         |
| 0x62  | b            |          | CT_BEAT                        |              |         |
| 0x63  | c            | CT_CTRL  |                                |              |         |
| 0x64  | d            |          |                                |              |         |
| 0x65  | e            |          |                                |              |         |
| 0x66  | f            |          |                                |              |         |
| 0x67  | g            |          |                                |              |         |
| 0x68  | h            | CT_HEART |                                |              |         |
| 0x69  | i            |          |                                |              |         |
| 0x6A  | j            |          |                                |              |         |
| 0x6B  | k            |          |                                |              |         |
| 0x6C  | l            |          |                                |              |         |
| 0x6D  | m            |          |                                |              |         |
| 0x6E  | n            |          |                                |              | HB_NONE |
| 0x6F  | o            |          |                                |              |         |
| 0x70  | p            |          |                                |              |         |
| 0x71  | q            | CT_QUERY |                                |              |         |
| 0x72  | r            | CT_RESP  |                                |              | HB_RESP |
| 0x73  | s            |          |                                |              |         |
| 0x74  | t            |          |                                |              |         |
| 0x75  | u            |          |                                |              |         |
| 0x76  | v            |          |                                |              |         |
| 0x77  | w            |          |                                |              |         |
| 0x78  | x            |          |                                |              |         |
| 0x79  | y            |          |                                |              |         |
| 0x7A  | z            |          |                                |              |         |
| ...   | ...          | ...      | ...                            | ...          | ...     |
| 0x7F  | DEL (delete) |          |                                |              |         |
| 0x80  |              |          |                                | WM_SIZE_FULL |         |
| ...   | ...          | ...      | ...                            | ...          | ...     |
| 0xA0  |              |          | CT_LIFE_CIRCLE_DEADLINE        |              |         |
| 0xA1  |              |          | CT_VERSION                     |              |         |
| ...   | ...          | ...      | ...                            | ...          | ...     |
| 0xB0  |              |          | CT_IMG_CVT_00                  |              |         |
| 0xB1  |              |          | CT_IMG_CVT_01                  |              |         |
| 0xB2  |              |          | CT_IMG_CVT_00_NUM              |              |         |
| ...   | ...          | ...      | ...                            | ...          | ...     |
| 0xD1  |              |          | CT_IMG_OUTSIDE_FIRST_FRAME_NUM |              |         |
| ...   | ...          | ...      | ...                            | ...          | ...     |
| 0xF1  |              |          | CT_IMG_SIGMA_UP_CHANGE         |              |         |
| 0xF2  |              |          | CT_IMG_SIGMA_DOWN_CHANGE       |              |         |
| ...   | ...          | ...      | ...                            | ...          | ...     |