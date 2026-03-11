
#include <stdint.h>
#include "stm32f446xx.h"
void delay(long d){
	TIM2->CNT = 0;
	while(TIM2->CNT < d);
}
int main(void)
{
	RCC->CR |= (1<<0);
	RCC->AHB1ENR |= (1<<0);
	GPIOA->MODER |= (1<<10);
	GPIOA->OTYPER |= 0X0000;
	GPIOA->OSPEEDR |= 0X00000000;
	// Turn on clock for timer 2
	RCC->APB1ENR |= (1<<0);
	// Disable Timer Counter
	TIM2->CR1 &= (1<<0);
	// Calculate and load Prescalar value
	/* Prescalar = timeperiod = one tick of timer =>
	 * System Clock = 16mHZ = Timer = 16 mHZ
	 * pre = 1600 = 16000000/16000 = 1 kHZ = Timer = 1/1kHZ = 1ms*/
	TIM2->PSC = (16000-1);
	// load auto-reload value ARR value
	TIM2->ARR = 1000;
	// Turn on the timer counter
	TIM2->CR1 |= (1<<0);
	while(1){
		GPIOA->ODR ^= (1<<5);
		delay(1000);
	}
}

