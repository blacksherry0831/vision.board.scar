################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/axi/axi_api.c \
../src/axi/axi_fpga_ctrl.c 

OBJS += \
./src/axi/axi_api.o \
./src/axi/axi_fpga_ctrl.o 

C_DEPS += \
./src/axi/axi_api.d \
./src/axi/axi_fpga_ctrl.d 


# Each subdirectory must supply rules for building sources it contributes
src/axi/%.o: ../src/axi/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Linux gcc compiler'
	arm-xilinx-linux-gnueabi-gcc -Wall -O0 -g3 -I"G:\TEST-PROJECT\video_diagnosis.sdk.ex\FlowDetect\src\uCOS" -c -fmessage-length=0 -MT"$@" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


