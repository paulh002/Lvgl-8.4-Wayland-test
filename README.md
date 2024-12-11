# Raspberry PI LVGL 8.4 Wayland test
This is a test project to test Wayland drivers for LVGL 8.4
The wayland drivers are taken from lvgl/lv_driver  repository but these are ment to support lvgl 9.x
To use them for lvgl 8.4 some small adjustments have been make
1) define lv_malloc and lv_free these are named differently in lvgl 8.4
2) Added wayland.h include file to ssm.c 
3) Settings in lv_conf.h and lv_driver_conf.h
4) Add keyboard_group group to wayland create window. This is necessary for v8 keyboard support.

The resolution is set to 800x480 color depth is 32. 
Memory management is set to custom (normal linux malloc)
Custom tick is set
Loglevel is TRACE

In lv_driver/wayland is a seperate CMakeList.txt for creating the protocol files for wayland. 
In this repo the protocol files are already created. 