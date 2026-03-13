
#include <stdint.h>
#include "stm32f446xx.h"

void delay(){
	for(int i=0;i<50000;i++);
}
int main(void)
{
	RCC->AHB1ENR |= (1<<0);
	RCC->APB1ENR |= (1<<0);      //	Enable clocks (GPIOA + TIM2)
	GPIOA->MODER |= (1<<11);
	GPIOA->MODER &= (~(1<<10));  //	Configure PA5 alternate function
	GPIOA->AFR[0] |= (1<<20);
	GPIOA->AFR[0] &= (~(1<<21)) & (~(1<<22)) & (~(1<<23));

	TIM2->PSC = (160-1);
	TIM2->ARR = (1000-1);        //	Configure timer prescaler and period

	TIM2->CCMR1 |= (1<<6) | (1<<5);
	TIM2->CCMR1 &= (~(1<<4)); //	Set PWM mode 110
	TIM2->CCMR1 |=  (1 << 3);   // Enable preload

	TIM2->CCER  |= (1<<0);   //	Enable channel output
	TIM2->CR1 |= (1<<7); // Auto-Reload Preload Enable for PWM stability
	TIM2->CR1 |= (1<<0);     //	Start timer
	while(1){
		for(int i=0; i<1000; i++){
			TIM2->CCR1 = i;  // 50% duty cycle //	Set duty cycle register
			delay();
		}
		for(int i=1000; i>0; i--){
			TIM2->CCR1 = i;  // 50% duty cycle //	Set duty cycle register
			delay();
		}

	}
}
