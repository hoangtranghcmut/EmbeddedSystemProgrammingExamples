################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Core/Startup/startup_stm32f407vgtx.s 

OBJS += \
./Core/Startup/startup_stm32f407vgtx.o 

S_DEPS += \
./Core/Startup/startup_stm32f407vgtx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Startup/%.o: ../Core/Startup/%.s Core/Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter12_example1/Src/MiddleWare/Common" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter12_example1/Src/BSP/BSP_USART" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter12_example1/Src/BSP" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter12_example1/Src/MiddleWare/Console" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter12_example1/Src/App" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter12_example1/Src/MiddleWare/container" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter12_example1/Src/MiddleWare/Common/ports/stm32f4xx" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter12_example1/Src/Driver/Components/Usart" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter12_example1/Src/BSP/BSP_Led" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter12_example1/Src/Driver/Components/dio" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter12_example1/Src/Driver/Components/spi" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter12_example1/Src/Driver/Devices/ds3234" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter12_example1/Src/BSP/BSP_RTC" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter12_example1/Src/BSP/BSP_Water_Sensor" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter12_example1/Src/MiddleWare/FreeRTOS-Kernel/portable/GCC/ARM_CM4F" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter12_example1/Src/MiddleWare/FreeRTOS-Kernel/include" -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Core-2f-Startup

clean-Core-2f-Startup:
	-$(RM) ./Core/Startup/startup_stm32f407vgtx.d ./Core/Startup/startup_stm32f407vgtx.o

.PHONY: clean-Core-2f-Startup

