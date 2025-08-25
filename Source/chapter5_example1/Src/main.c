#include <stdint.h>
#include "system_stm32f4xx.h"
#include "stm32f4xx.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#define PA0_ALIAS  (*(volatile uint32_t *)(0x42400280))
// Bật PA0
#define PA0_SET()  (PA0_ALIAS = 1)
// Tắt PA0
#define PA0_CLEAR()  (PA0_ALIAS = 0)
// Đọc trạng thái PA0 (trả về 1 nếu bật, 0 nếu tắt)
#define PA0_READ()  (PA0_ALIAS)


int main(void)
{
	SystemInit();
    /* Loop forever */
	GPIOD->ODR |= 0x0F;


	GPIOA->BSRR = (1 << 5); // Set PA5
	GPIOA->BSRR = (1 << 21); // Reset PA5
	PA0_SET();
	PA0_CLEAR() ;
	for(;;);
}




