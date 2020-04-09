#!/bin/sh -e

/media/sdcard/project.run/deadline_server -s -D  >/dev/null 2>&1 &

/media/sdcard/project.run/FlowDetect.elf -s 1 -w 1920 -h 1080 -p scar_detect_01 -f 0 -D >/dev/null 2>&1 &



