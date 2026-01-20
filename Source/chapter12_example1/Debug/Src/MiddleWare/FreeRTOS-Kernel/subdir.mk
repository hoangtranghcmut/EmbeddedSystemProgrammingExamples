################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/MiddleWare/FreeRTOS-Kernel/croutine.c \
../Src/MiddleWare/FreeRTOS-Kernel/event_groups.c \
../Src/MiddleWare/FreeRTOS-Kernel/list.c \
../Src/MiddleWare/FreeRTOS-Kernel/queue.c \
../Src/MiddleWare/FreeRTOS-Kernel/stream_buffer.c \
../Src/MiddleWare/FreeRTOS-Kernel/tasks.c \
../Src/MiddleWare/FreeRTOS-Kernel/timers.c 

OBJS += \
./Src/MiddleWare/FreeRTOS-Kernel/croutine.o \
./Src/MiddleWare/FreeRTOS-Kernel/event_groups.o \
./Src/MiddleWare/FreeRTOS-Kernel/list.o \
./Src/MiddleWare/FreeRTOS-Kernel/queue.o \
./Src/MiddleWare/FreeRTOS-Kernel/stream_buffer.o \
./Src/MiddleWare/FreeRTOS-Kernel/tasks.o \
./Src/MiddleWare/FreeRTOS-Kernel/timers.o 

C_DEPS += \
./Src/MiddleWare/FreeRTOS-Kernel/croutine.d \
./Src/MiddleWare/FreeRTOS-Kernel/event_groups.d \
./Src/MiddleWare/FreeRTOS-Kernel/list.d \
./Src/MiddleWare/FreeRTOS-Kernel/queue.d \
./Src/MiddleWare/FreeRTOS-Kernel/stream_buffer.d \
./Src/MiddleWare/FreeRTOS-Kernel/tasks.d \
./Src/MiddleWare/FreeRTOS-Kernel/timers.d 


# Each subdirectory must supply rules for building sources it contributes
Src/MiddleWare/FreeRTOS-Kernel/%.o Src/MiddleWare/FreeRTOS-Kernel/%.su Src/MiddleWare/FreeRTOS-Kernel/%.cyclo: ../Src/MiddleWare/FreeRTOS-Kernel/%.c Src/MiddleWare/FreeRTOS-Kernel/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F407xx -DUSE_FULL_LL_DRIVER -DHSE_VALUE=25000000 -DHSE_STARTUP_TIMEOUT=100 -DLSE_STARTUP_TIMEOUT=5000 -DLSE_VALUE=32768 -DEXTERNAL_CLOCK_VALUE=12288000 -DHSI_VALUE=16000000 -DLSI_VALUE=32000 -DVDD_VALUE=3300 -DPREFETCH_ENABLE=1 -DINSTRUCTION_CACHE_ENABLE=1 -DDATA_CACHE_ENABLE=1 -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter12_example1/Src/MiddleWare/Common" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter12_example1/Src/BSP/BSP_USART" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter12_example1/Src/BSP" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter12_example1/Src/MiddleWare/Console" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter12_example1/Src/App" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter12_example1/Src/MiddleWare/container" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter12_example1/Src/MiddleWare/Common/ports/stm32f4xx" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter12_example1/Src/Driver/Components/Usart" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter12_example1/Src/BSP/BSP_Led" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter12_example1/Src/Driver/Components/dio" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter12_example1/Src/Driver/Components/spi" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter12_example1/Src/Driver/Devices/ds3234" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter12_example1/Src/BSP/BSP_RTC" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter12_example1/Src/BSP/BSP_Water_Sensor" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter12_example1/Src/MiddleWare/FreeRTOS-Kernel/portable/GCC/ARM_CM4F" -I"D:/PROJECT/BOOK_EXAMPLE/Book_Example_Repos/Source/chapter12_example1/Src/MiddleWare/FreeRTOS-Kernel/include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-MiddleWare-2f-FreeRTOS-2d-Kernel

clean-Src-2f-MiddleWare-2f-FreeRTOS-2d-Kernel:
	-$(RM) ./Src/MiddleWare/FreeRTOS-Kernel/croutine.cyclo ./Src/MiddleWare/FreeRTOS-Kernel/croutine.d ./Src/MiddleWare/FreeRTOS-Kernel/croutine.o ./Src/MiddleWare/FreeRTOS-Kernel/croutine.su ./Src/MiddleWare/FreeRTOS-Kernel/event_groups.cyclo ./Src/MiddleWare/FreeRTOS-Kernel/event_groups.d ./Src/MiddleWare/FreeRTOS-Kernel/event_groups.o ./Src/MiddleWare/FreeRTOS-Kernel/event_groups.su ./Src/MiddleWare/FreeRTOS-Kernel/list.cyclo ./Src/MiddleWare/FreeRTOS-Kernel/list.d ./Src/MiddleWare/FreeRTOS-Kernel/list.o ./Src/MiddleWare/FreeRTOS-Kernel/list.su ./Src/MiddleWare/FreeRTOS-Kernel/queue.cyclo ./Src/MiddleWare/FreeRTOS-Kernel/queue.d ./Src/MiddleWare/FreeRTOS-Kernel/queue.o ./Src/MiddleWare/FreeRTOS-Kernel/queue.su ./Src/MiddleWare/FreeRTOS-Kernel/stream_buffer.cyclo ./Src/MiddleWare/FreeRTOS-Kernel/stream_buffer.d ./Src/MiddleWare/FreeRTOS-Kernel/stream_buffer.o ./Src/MiddleWare/FreeRTOS-Kernel/stream_buffer.su ./Src/MiddleWare/FreeRTOS-Kernel/tasks.cyclo ./Src/MiddleWare/FreeRTOS-Kernel/tasks.d ./Src/MiddleWare/FreeRTOS-Kernel/tasks.o ./Src/MiddleWare/FreeRTOS-Kernel/tasks.su ./Src/MiddleWare/FreeRTOS-Kernel/timers.cyclo ./Src/MiddleWare/FreeRTOS-Kernel/timers.d ./Src/MiddleWare/FreeRTOS-Kernel/timers.o ./Src/MiddleWare/FreeRTOS-Kernel/timers.su

.PHONY: clean-Src-2f-MiddleWare-2f-FreeRTOS-2d-Kernel

