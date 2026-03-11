
#include <stdint.h>
#include "stm32f446xx.h"

int main(void)
{
	// PA5 - Timer compare mode of Timer -> AF1
	// GPIOA clock enable
	RCC->AHB1ENR |= (1<<0);

	// PA5 alternate function mode select
	GPIOA->MODER |= (1<<11);
	GPIOA->MODER &= (~(1<<10));

	// Config PA5 as TIM2 CH1 AF1
	GPIOA->AFR[0] |= (1<<20);
	GPIOA->AFR[0] &= (~(1<<21));
	GPIOA->AFR[0] &= (~(1<<22));
	GPIOA->AFR[0] &= (~(1<<23));


	// TIM2 clock enable
	RCC->APB1ENR |= (1<<0);
	// Toggle on match of Timer ARR and CNT Register
	TIM2->CCMR1 |= (1<<4) | (1<<5);
	TIM2->CCMR1 &= (~(1<<6));
	// Output compare signal on
	TIM2->CCER |= (1<<0);
	// Freq of TImer to be 1kHZ
	TIM2->PSC = 16000-1;
	// Configure the match to happen at 1 sec
	//TimePeriod TIM2 =1/1000HZ = 1mS
	TIM2->ARR = 1000-1;
	// On time 1000ms + off time 1000ms = 2000ms = 1/2000ms = 500mHZ
	// Timer CNT register to be 0
	TIM2->CNT = 0;
	// Turn ON Timer
	TIM2->CR1 |= (1<<0);

	while(1){

	}
}
