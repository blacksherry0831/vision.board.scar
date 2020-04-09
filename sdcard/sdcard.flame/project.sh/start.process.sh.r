/media/sdcard/project.run/deadline_server -s -D  >/dev/null 2>&1 &
#/media/sdcard/project.run/FlowDetect.1.8.crack -p outside0x	-s 255 -w 1920	-h 1080 -f 0  >/dev/null 2>&1 &


echo "#####################LD_LIBRARY_PATH###################################"
if [ -z $LD_LIBRARY_PATH ];
then
#echo "LD_LIBRARY_PATH is empty"
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/lib:/usr/lib:/media/opencv:/media/opencv/cairo:/media/opencv/gstreamer-1.0:/media/opencv/gdk-pixbuf-2.0/2.10.0/loaders:/media/opencv/gtk-3.0/3.0.0/printbackends
fi

#########################################################

#echo "####################flowDetect####################"
#/media/sdcard/project.run/FlowDetect -p scar_detect_01 -s 1 -w 1920 -h 1080 -f 0  >/dev/null 2>&1 &
/media/sdcard/project.run/FlowDetect -p scar_detect_01 -s 1 -w 1920 -h 1080 -f 0 -D >/dev/null 2>&1 &

#echo $LD_LIBRARY_PATH 

#echo "########################################" 
