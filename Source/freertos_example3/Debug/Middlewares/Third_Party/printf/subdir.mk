################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/printf/printf.c 

OBJS += \
./Middlewares/Third_Party/printf/printf.o 

C_DEPS += \
./Middlewares/Third_Party/printf/printf.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/printf/%.o Middlewares/Third_Party/printf/%.su Middlewares/Third_Party/printf/%.cyclo: ../Middlewares/Third_Party/printf/%.c Middlewares/Third_Party/printf/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DSTM32F746xx -DUSE_FULL_LL_DRIVER -DHSE_VALUE=25000000 -DHSE_STARTUP_TIMEOUT=100 -DLSE_STARTUP_TIMEOUT=5000 -DLSE_VALUE=32768 -DEXTERNAL_CLOCK_VALUE=12288000 -DHSI_VALUE=16000000 -DLSI_VALUE=32000 -DVDD_VALUE=3300 -DPREFETCH_ENABLE=0 -DART_ACCELERATOR_ENABLE=0 -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1 -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/freertos_example3/Middlewares/Third_Party/printf" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/freertos_example3/src/BSP" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-printf

clean-Middlewares-2f-Third_Party-2f-printf:
	-$(RM) ./Middlewares/Third_Party/printf/printf.cyclo ./Middlewares/Third_Party/printf/printf.d ./Middlewares/Third_Party/printf/printf.o ./Middlewares/Third_Party/printf/printf.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-printf

