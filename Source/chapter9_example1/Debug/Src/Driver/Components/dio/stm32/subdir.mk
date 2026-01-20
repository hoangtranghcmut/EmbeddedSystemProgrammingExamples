################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/Driver/Components/dio/stm32/do.c 

OBJS += \
./Src/Driver/Components/dio/stm32/do.o 

C_DEPS += \
./Src/Driver/Components/dio/stm32/do.d 


# Each subdirectory must supply rules for building sources it contributes
Src/Driver/Components/dio/stm32/%.o Src/Driver/Components/dio/stm32/%.su Src/Driver/Components/dio/stm32/%.cyclo: ../Src/Driver/Components/dio/stm32/%.c Src/Driver/Components/dio/stm32/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F407xx -DUSE_FULL_LL_DRIVER -DHSE_VALUE=25000000 -DHSE_STARTUP_TIMEOUT=100 -DLSE_STARTUP_TIMEOUT=5000 -DLSE_VALUE=32768 -DEXTERNAL_CLOCK_VALUE=12288000 -DHSI_VALUE=16000000 -DLSI_VALUE=32000 -DVDD_VALUE=3300 -DPREFETCH_ENABLE=1 -DINSTRUCTION_CACHE_ENABLE=1 -DDATA_CACHE_ENABLE=1 -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter9_example1/Src/MiddleWare/Common" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter9_example1/Src/BSP/BSP_USART" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter9_example1/Src/BSP" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter9_example1/Src/MiddleWare/Console" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter9_example1/Src/App" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter9_example1/Src/MiddleWare/container" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter9_example1/Src/MiddleWare/Common/ports/stm32f4xx" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter9_example1/Src/Driver/Components/Usart" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter9_example1/Src/BSP/BSP_Led" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter9_example1/Src/Driver/Components/dio" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-Driver-2f-Components-2f-dio-2f-stm32

clean-Src-2f-Driver-2f-Components-2f-dio-2f-stm32:
	-$(RM) ./Src/Driver/Components/dio/stm32/do.cyclo ./Src/Driver/Components/dio/stm32/do.d ./Src/Driver/Components/dio/stm32/do.o ./Src/Driver/Components/dio/stm32/do.su

.PHONY: clean-Src-2f-Driver-2f-Components-2f-dio-2f-stm32

