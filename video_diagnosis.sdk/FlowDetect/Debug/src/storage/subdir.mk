################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/storage/circular_queue.c \
../src/storage/dma2mem.c 

OBJS += \
./src/storage/circular_queue.o \
./src/storage/dma2mem.o 

C_DEPS += \
./src/storage/circular_queue.d \
./src/storage/dma2mem.d 


# Each subdirectory must supply rules for building sources it contributes
src/storage/%.o: ../src/storage/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Linux gcc compiler'
	arm-xilinx-linux-gnueabi-gcc -Wall -O0 -g3 -I"G:\TEST-PROJECT\video_diagnosis.sdk.ex\FlowDetect\src\uCOS" -c -fmessage-length=0 -MT"$@" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


