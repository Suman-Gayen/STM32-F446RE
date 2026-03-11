
#include <stdint.h>
#include "stm32f446xx.h"
void delay(long d){
	while(--d);
}
int main(void)
{
	RCC->AHB1ENR |= (1<<0);
	GPIOA->MODER |= (1<<10);


	SysTick->CTRL |= (1<<0) | (1<<1) | (1<<2);
//	SysTick->LOAD = (16000000-1); // 1 Second
	SysTick->LOAD = (1600000-1);  // 100 ms
	while(1){
		/* 100 ms on + 100 ms off pulse in PA5 = Total Time period 200ms
		 * freq = 1/200 = 1000/200 = 5HZ */
	}

}
void SysTick_Handler(void){
	GPIOA->ODR ^= (1<<5);
}
