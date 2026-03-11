
#include <stdint.h>
#include "stm32f446xx.h"
volatile unsigned int timestamp = 0;
int main(void)
{
	// PA5 - Output Capture Channel => Timer compare mode of Timer -> AF1 -> TIM2_CH1
		RCC->AHB1ENR |= (1<<0);// GPIOA clock enable
		// PA5 alternate function mode select
		GPIOA->MODER |= (1<<11);
		GPIOA->MODER &= (~(1<<10));
		// Config PA5 as TIM2 CH1 AF1
		GPIOA->AFR[0] |= (1<<20);
		GPIOA->AFR[0] &= (~(1<<21));
		GPIOA->AFR[0] &= (~(1<<22));
		GPIOA->AFR[0] &= (~(1<<23));
		RCC->APB1ENR |= (1<<0); // TIM2 clock enable
		// Toggle on match of Timer ARR and CNT Register
		TIM2->CCMR1 |= (1<<4) | (1<<5);
		TIM2->CCMR1 &= (~(1<<6));
		TIM2->CCER |= (1<<0); // Output compare signal on
		TIM2->PSC = 16000-1; // Freq of TImer to be 1kHZ
		// Configure the match to happen at 1 sec
		TIM2->ARR = 1000-1; //TimePeriod TIM2 =1/1000HZ = 1mS
		// On time 1000ms + off time 1000ms = 2000ms = 1/2000ms = 500mHZ
		TIM2->CNT = 0; // Timer CNT register to be 0
		TIM2->CR1 |= (1<<0); // Turn ON Timer
		/*Pulses of 500mHZ is generated*/


		// PA6 - Input Capture Channel => AF2 -> TIM3_CH1

		//PA6 Altemate function mode select
		GPIOA->MODER |= (1<<13);
		GPIOA->MODER &= (~(1<<12));
		//set PA6 mode as TIM3_CH1
		GPIOA->AFR[0] |= (1<<25);
		GPIOA->AFR[0] &= (~(1<<24)) & (~(1<<26)) & (~(1<<27));
		RCC->APB1ENR |= (1<<1); //enable clock for TIM3
		TIM3->PSC = 1600-1;//set prescalar for TIM3_Freq = 16000000/1600 = 10000 HZ
		//set CH1 to I/P capture
		TIM3->CCMR1 |= (1<<0);
		TIM3->CCMR1 &= (~(1<<0));
		//set CH1 to capture at every rising edge
		TIM3->CCER |= (1<<0);
		TIM3->CCER &= (~(1<<1)) & (~(1<<3));

		TIM3->CR1 |= (1<<0); //enable TIM3



		while(1){
			// WAIT UTIL RAISING EDGE IS CAPTURED
			while (!(TIM3->SR & (1<<0)))
				timestamp = TIM3->CCR1;
		}
		return 0;

}
