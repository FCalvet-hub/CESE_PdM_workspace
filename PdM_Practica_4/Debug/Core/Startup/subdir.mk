################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Core/Startup/startup_stm32f401retx.s 

OBJS += \
./Core/Startup/startup_stm32f401retx.o 

S_DEPS += \
./Core/Startup/startup_stm32f401retx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Startup/%.o: ../Core/Startup/%.s Core/Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -I"C:/Users/fert2/Documents/Google Drive/Mi unidad/CESE 2023/Programacion de microcontroladores/CESE_PdM_workspace/PdM_Practica_4/Drivers/API" -I"C:/Users/fert2/Documents/Google Drive/Mi unidad/CESE 2023/Programacion de microcontroladores/CESE_PdM_workspace/PdM_Practica_4/Drivers/API/Inc" -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Core-2f-Startup

clean-Core-2f-Startup:
	-$(RM) ./Core/Startup/startup_stm32f401retx.d ./Core/Startup/startup_stm32f401retx.o

.PHONY: clean-Core-2f-Startup

