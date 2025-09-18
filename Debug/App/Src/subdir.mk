################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/Src/App_TrafficLight.c 

OBJS += \
./App/Src/App_TrafficLight.o 

C_DEPS += \
./App/Src/App_TrafficLight.d 


# Each subdirectory must supply rules for building sources it contributes
App/Src/%.o App/Src/%.su App/Src/%.cyclo: ../App/Src/%.c App/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"/home/archlinux/STM32CubeIDE/workspace_1.19.0/traffic_task/App/Inc" -I"/home/archlinux/STM32CubeIDE/workspace_1.19.0/traffic_task/Cfg/Inc" -I"/home/archlinux/STM32CubeIDE/workspace_1.19.0/traffic_task/ECUAL/Inc" -I"/home/archlinux/STM32CubeIDE/workspace_1.19.0/traffic_task/Std" -I"/home/archlinux/STM32CubeIDE/workspace_1.19.0/traffic_task/Utils" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-App-2f-Src

clean-App-2f-Src:
	-$(RM) ./App/Src/App_TrafficLight.cyclo ./App/Src/App_TrafficLight.d ./App/Src/App_TrafficLight.o ./App/Src/App_TrafficLight.su

.PHONY: clean-App-2f-Src

