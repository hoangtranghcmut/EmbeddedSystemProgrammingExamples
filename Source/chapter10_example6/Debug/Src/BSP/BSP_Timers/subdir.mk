################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/BSP/BSP_Timers/bsp_timer.c 

OBJS += \
./Src/BSP/BSP_Timers/bsp_timer.o 

C_DEPS += \
./Src/BSP/BSP_Timers/bsp_timer.d 


# Each subdirectory must supply rules for building sources it contributes
Src/BSP/BSP_Timers/%.o Src/BSP/BSP_Timers/%.su Src/BSP/BSP_Timers/%.cyclo: ../Src/BSP/BSP_Timers/%.c Src/BSP/BSP_Timers/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F407xx -DUSE_FULL_LL_DRIVER -DHSE_VALUE=25000000 -DHSE_STARTUP_TIMEOUT=100 -DLSE_STARTUP_TIMEOUT=5000 -DLSE_VALUE=32768 -DEXTERNAL_CLOCK_VALUE=12288000 -DHSI_VALUE=16000000 -DLSI_VALUE=32000 -DVDD_VALUE=3300 -DPREFETCH_ENABLE=1 -DINSTRUCTION_CACHE_ENABLE=1 -DDATA_CACHE_ENABLE=1 -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter10_example6/Src/MiddleWare/Common" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter10_example6/Src/BSP/BSP_USART" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter10_example6/Src/BSP" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter10_example6/Src/MiddleWare/Console" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter10_example6/Src/App" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter10_example6/Src/MiddleWare/container" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter10_example6/Src/MiddleWare/Common/ports/stm32f4xx" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter10_example6/Src/Driver/Components/Usart" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter10_example6/Src/BSP/BSP_Led" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter10_example6/Src/Driver/Components/dio" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter10_example6/Src/Driver/Components/spi" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter10_example6/Src/Driver/Devices/ds3234" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter10_example6/Src/BSP/BSP_RTC" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter10_example6/Src/BSP/BSP_Water_Sensor" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter10_example6/Src/MiddleWare/SoftTimer" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-BSP-2f-BSP_Timers

clean-Src-2f-BSP-2f-BSP_Timers:
	-$(RM) ./Src/BSP/BSP_Timers/bsp_timer.cyclo ./Src/BSP/BSP_Timers/bsp_timer.d ./Src/BSP/BSP_Timers/bsp_timer.o ./Src/BSP/BSP_Timers/bsp_timer.su

.PHONY: clean-Src-2f-BSP-2f-BSP_Timers

