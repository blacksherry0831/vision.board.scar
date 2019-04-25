################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/hw_module/dma.c 

OBJS += \
./src/hw_module/dma.o 

C_DEPS += \
./src/hw_module/dma.d 


# Each subdirectory must supply rules for building sources it contributes
src/hw_module/%.o: ../src/hw_module/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Linux gcc compiler'
	arm-xilinx-linux-gnueabi-gcc -Wall -O0 -g3 -I"G:\TEST-PROJECT\video_diagnosis.sdk.ex\FlowDetect\src\uCOS" -c -fmessage-length=0 -MT"$@" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


