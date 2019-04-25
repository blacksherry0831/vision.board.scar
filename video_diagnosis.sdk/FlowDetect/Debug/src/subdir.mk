################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/axi.c \
../src/axi_base.c \
../src/axi_map.c \
../src/base.c \
../src/helloworld.c \
../src/init_destory.c \
../src/life_cycle.c \
../src/msg_queue.c \
../src/msg_sysV_queue.c \
../src/server_iptables.c \
../src/task_flow.c \
../src/tcp_server.c \
../src/telnet_my.c \
../src/thread_fpga_cvt.c \
../src/timer.c \
../src/type.c 

OBJS += \
./src/axi.o \
./src/axi_base.o \
./src/axi_map.o \
./src/base.o \
./src/helloworld.o \
./src/init_destory.o \
./src/life_cycle.o \
./src/msg_queue.o \
./src/msg_sysV_queue.o \
./src/server_iptables.o \
./src/task_flow.o \
./src/tcp_server.o \
./src/telnet_my.o \
./src/thread_fpga_cvt.o \
./src/timer.o \
./src/type.o 

C_DEPS += \
./src/axi.d \
./src/axi_base.d \
./src/axi_map.d \
./src/base.d \
./src/helloworld.d \
./src/init_destory.d \
./src/life_cycle.d \
./src/msg_queue.d \
./src/msg_sysV_queue.d \
./src/server_iptables.d \
./src/task_flow.d \
./src/tcp_server.d \
./src/telnet_my.d \
./src/thread_fpga_cvt.d \
./src/timer.d \
./src/type.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Linux gcc compiler'
	arm-xilinx-linux-gnueabi-gcc -Wall -O0 -g3 -I"G:\TEST-PROJECT\video_diagnosis.sdk.ex\FlowDetect\src\uCOS" -c -fmessage-length=0 -MT"$@" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


