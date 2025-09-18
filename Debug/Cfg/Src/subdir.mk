################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Cfg/Src/ECUAL_LCD_Cfg.c 

OBJS += \
./Cfg/Src/ECUAL_LCD_Cfg.o 

C_DEPS += \
./Cfg/Src/ECUAL_LCD_Cfg.d 


# Each subdirectory must supply rules for building sources it contributes
Cfg/Src/%.o Cfg/Src/%.su Cfg/Src/%.cyclo: ../Cfg/Src/%.c Cfg/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"/home/archlinux/STM32CubeIDE/workspace_1.19.0/traffic_task/App/Inc" -I"/home/archlinux/STM32CubeIDE/workspace_1.19.0/traffic_task/Cfg/Inc" -I"/home/archlinux/STM32CubeIDE/workspace_1.19.0/traffic_task/ECUAL/Inc" -I"/home/archlinux/STM32CubeIDE/workspace_1.19.0/traffic_task/Std" -I"/home/archlinux/STM32CubeIDE/workspace_1.19.0/traffic_task/Utils" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Cfg-2f-Src

clean-Cfg-2f-Src:
	-$(RM) ./Cfg/Src/ECUAL_LCD_Cfg.cyclo ./Cfg/Src/ECUAL_LCD_Cfg.d ./Cfg/Src/ECUAL_LCD_Cfg.o ./Cfg/Src/ECUAL_LCD_Cfg.su

.PHONY: clean-Cfg-2f-Src

