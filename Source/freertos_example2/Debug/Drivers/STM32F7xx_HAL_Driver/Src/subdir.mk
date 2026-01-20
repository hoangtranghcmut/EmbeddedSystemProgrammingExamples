################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_dma.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_exti.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_gpio.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_rcc.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_usart.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_utils.c 

OBJS += \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_dma.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_exti.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_gpio.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_rcc.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_usart.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_utils.o 

C_DEPS += \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_dma.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_exti.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_gpio.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_rcc.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_usart.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_utils.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/STM32F7xx_HAL_Driver/Src/%.o Drivers/STM32F7xx_HAL_Driver/Src/%.su Drivers/STM32F7xx_HAL_Driver/Src/%.cyclo: ../Drivers/STM32F7xx_HAL_Driver/Src/%.c Drivers/STM32F7xx_HAL_Driver/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DSTM32F746xx -DUSE_FULL_LL_DRIVER -DHSE_VALUE=25000000 -DHSE_STARTUP_TIMEOUT=100 -DLSE_STARTUP_TIMEOUT=5000 -DLSE_VALUE=32768 -DEXTERNAL_CLOCK_VALUE=12288000 -DHSI_VALUE=16000000 -DLSI_VALUE=32000 -DVDD_VALUE=3300 -DPREFETCH_ENABLE=0 -DART_ACCELERATOR_ENABLE=0 -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1 -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/freertos_example2/Middlewares/Third_Party/printf" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/freertos_example2/src/BSP" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-STM32F7xx_HAL_Driver-2f-Src

clean-Drivers-2f-STM32F7xx_HAL_Driver-2f-Src:
	-$(RM) ./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_dma.cyclo ./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_dma.d ./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_dma.o ./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_dma.su ./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_exti.cyclo ./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_exti.d ./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_exti.o ./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_exti.su ./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_gpio.cyclo ./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_gpio.d ./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_gpio.o ./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_gpio.su ./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_rcc.cyclo ./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_rcc.d ./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_rcc.o ./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_rcc.su ./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_usart.cyclo ./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_usart.d ./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_usart.o ./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_usart.su ./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_utils.cyclo ./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_utils.d ./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_utils.o ./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_utils.su

.PHONY: clean-Drivers-2f-STM32F7xx_HAL_Driver-2f-Src

