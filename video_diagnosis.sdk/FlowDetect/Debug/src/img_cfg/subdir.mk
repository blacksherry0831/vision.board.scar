################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/img_cfg/img_cfg.c 

OBJS += \
./src/img_cfg/img_cfg.o 

C_DEPS += \
./src/img_cfg/img_cfg.d 


# Each subdirectory must supply rules for building sources it contributes
src/img_cfg/%.o: ../src/img_cfg/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Linux gcc compiler'
	arm-xilinx-linux-gnueabi-gcc -Wall -O0 -g3 -I"G:\TEST-PROJECT\video_diagnosis.sdk.ex\FlowDetect\src\uCOS" -c -fmessage-length=0 -MT"$@" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


