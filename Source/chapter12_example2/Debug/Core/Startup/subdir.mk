################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Core/Startup/startup_stm32f746nghx.s 

OBJS += \
./Core/Startup/startup_stm32f746nghx.o 

S_DEPS += \
./Core/Startup/startup_stm32f746nghx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Startup/%.o: ../Core/Startup/%.s Core/Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m7 -g3 -DDEBUG -c -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter12_example2/Src/MiddleWare/container" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter12_example2/Src/MiddleWare/FreeRTOS-Kernel" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter12_example2/Src/MiddleWare/FreeRTOS-Kernel/include" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter12_example2/Src/MiddleWare/FreeRTOS-Kernel/portable/GCC/ARM_CM4F" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter12_example2/Src/MiddleWare/FreeRTOS-Kernel/portable/MemMang" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter12_example2/Src/App" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter12_example2/Src/BSP" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter12_example2/Src/BSP/BSP_Led" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter12_example2/Src/BSP/BSP_RTC" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter12_example2/Src/BSP/BSP_USART" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter12_example2/Src/BSP/BSP_Water_Sensor" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter12_example2/Src/Driver/Devices/ds3234" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter12_example2/Src/Driver/Components/dio" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter12_example2/Src/Driver/Components/spi" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter12_example2/Src/Driver/Components/Usart" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter12_example2/Src/Common" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter12_example2/Src/MiddleWare/printf" -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Core-2f-Startup

clean-Core-2f-Startup:
	-$(RM) ./Core/Startup/startup_stm32f746nghx.d ./Core/Startup/startup_stm32f746nghx.o

.PHONY: clean-Core-2f-Startup

