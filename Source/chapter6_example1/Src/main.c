#include "stm32f4xx.h"

volatile uint32_t msTicks = 0;  // Biến đếm thời gian

// ISR - Trình phục vụ ngắt SysTick
void SysTick_Handler(void) {
    msTicks++;  // Tăng biến đếm mỗi khi có ngắt SysTick
}

void SysTick_Init(uint32_t ticks) {
    // Đặt giá trị reload cho thanh ghi SysTick Reload Value Register (LOAD)
    // Giảm 1 vì SysTick đếm từ giá trị reload xuống 0
    SysTick->LOAD = ticks - 1;

    // Xóa giá trị hiện tại của thanh ghi SysTick Current Value Register (VAL)
    // để khởi động lại bộ đếm
    SysTick->VAL = 0;

    // Cấu hình thanh ghi SysTick Control and Status Register (CTRL)
    // - Bật bộ đếm SysTick (bit 0: ENABLE)
    // - Kích hoạt ngắt SysTick (bit 1: TICKINT)
    // - Chọn nguồn xung là AHB (bit 2: CLKSOURCE)
    SysTick->CTRL = (1UL << 0) |  // ENABLE: Bật bộ đếm
                    (1UL << 1) |  // TICKINT: Cho phép ngắt
                    (1UL << 2);   // CLKSOURCE: Nguồn xung AHB
}

// Hàm tạo trễ theo mili-giây
void delay_ms(uint32_t delay) {
    uint32_t start = msTicks;
    while ((msTicks - start) < delay);  // Chờ cho đủ thời gian trễ
}

int main(void) {
    // Khởi tạo SysTick với tần số 1ms
    SysTick_Init(SystemCoreClock / 1000);

    // Cấu hình GPIOA Pin 5 làm output (LED)
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;  // Bật clock cho GPIOA
    GPIOA->MODER |= (1 << 10); // MODER5 = 01 (Output)

    while (1) {
        GPIOA->ODR ^= (1 << 5);
        // Đảo trạng thái LED tại Pin 5
        delay_ms(1000);          // Trễ 1 giây
    }
}
