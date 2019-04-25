################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/uCOS/cpu.c \
../src/uCOS/mem_pool_fixed.c \
../src/uCOS/os_mem.c 

OBJS += \
./src/uCOS/cpu.o \
./src/uCOS/mem_pool_fixed.o \
./src/uCOS/os_mem.o 

C_DEPS += \
./src/uCOS/cpu.d \
./src/uCOS/mem_pool_fixed.d \
./src/uCOS/os_mem.d 


# Each subdirectory must supply rules for building sources it contributes
src/uCOS/%.o: ../src/uCOS/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Linux gcc compiler'
	arm-xilinx-linux-gnueabi-gcc -Wall -O0 -g3 -I"G:\TEST-PROJECT\video_diagnosis.sdk.ex\FlowDetect\src\uCOS" -c -fmessage-length=0 -MT"$@" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


