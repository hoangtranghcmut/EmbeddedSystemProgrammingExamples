################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/MiddleWare/printf/printf.c 

OBJS += \
./Src/MiddleWare/printf/printf.o 

C_DEPS += \
./Src/MiddleWare/printf/printf.d 


# Each subdirectory must supply rules for building sources it contributes
Src/MiddleWare/printf/%.o Src/MiddleWare/printf/%.su Src/MiddleWare/printf/%.cyclo: ../Src/MiddleWare/printf/%.c Src/MiddleWare/printf/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DSTM32F746xx -DUSE_FULL_LL_DRIVER -DHSE_VALUE=25000000 -DHSE_STARTUP_TIMEOUT=100 -DLSE_STARTUP_TIMEOUT=5000 -DLSE_VALUE=32768 -DEXTERNAL_CLOCK_VALUE=12288000 -DHSI_VALUE=16000000 -DLSI_VALUE=32000 -DVDD_VALUE=3300 -DPREFETCH_ENABLE=0 -DART_ACCELERATOR_ENABLE=0 -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter12_example2/Src/MiddleWare/container" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter12_example2/Src/MiddleWare/FreeRTOS-Kernel" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter12_example2/Src/MiddleWare/FreeRTOS-Kernel/include" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter12_example2/Src/MiddleWare/FreeRTOS-Kernel/portable/GCC/ARM_CM4F" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter12_example2/Src/MiddleWare/FreeRTOS-Kernel/portable/MemMang" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter12_example2/Src/App" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter12_example2/Src/BSP" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter12_example2/Src/BSP/BSP_Led" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter12_example2/Src/BSP/BSP_RTC" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter12_example2/Src/BSP/BSP_USART" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter12_example2/Src/BSP/BSP_Water_Sensor" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter12_example2/Src/Driver/Devices/ds3234" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter12_example2/Src/Driver/Components/dio" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter12_example2/Src/Driver/Components/spi" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter12_example2/Src/Driver/Components/Usart" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter12_example2/Src/Common" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter12_example2/Src/MiddleWare/printf" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-MiddleWare-2f-printf

clean-Src-2f-MiddleWare-2f-printf:
	-$(RM) ./Src/MiddleWare/printf/printf.cyclo ./Src/MiddleWare/printf/printf.d ./Src/MiddleWare/printf/printf.o ./Src/MiddleWare/printf/printf.su

.PHONY: clean-Src-2f-MiddleWare-2f-printf

