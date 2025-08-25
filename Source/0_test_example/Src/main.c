#include <stdint.h>
#include "stm32f4xx.h"
uint16_t i = 0;
uint16_t	add1(uint16_t	i)
{
	uint16_t	temp;
	temp = i+1;
	return temp;
}
int main()
{
	while(1) {
		i = add1(i);
}
}
