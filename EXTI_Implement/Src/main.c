#include <stdint.h>
#include "stm32f446xx.h"


void delay(long d){
	while(--d);
}
int main(void)
{
	RCC->CR = RCC->CR | (1<<0);
	RCC->AHB1ENR = RCC->AHB1ENR | (1<<0);
	GPIOA->MODER = GPIOA->MODER |(1<<10);
	GPIOA->OTYPER = 0x0000;
	GPIOA->OSPEEDR = 0x00000000;


	// PC13 EXTI-> Pushbutton in nucleo fr46re
	// Enable the musk bit of Interrupt
	EXTI->IMR |= (1<<13);
	// SET THE TRIGGER CONFIGURATION OF EXTI
	EXTI->FTSR |= (1<<13);
	EXTI->RTSR &= (~(1<<13));
	// Enable clock for syscfg controller
	RCC->APB2ENR |= (1<<14);
	// Select the source i/p for EXTI
	SYSCFG->EXTICR[3] |= (1<<5); // Because switched is connected throw port C , that's FOR 0010: PC[5] pin
	// Enable the Interrupt
	NVIC_EnableIRQ(EXTI15_10_IRQn);
	// Set the priority for the Interrupt
	NVIC_SetPriority(EXTI15_10_IRQn,15);

	while(1)
	{

	}
}

void EXTI15_10_IRQHandler(){
	delay(50000);
	if(EXTI->PR & (1<<13)){
		EXTI->PR |= (1<<13);
	}
	GPIOA->ODR = GPIOA->ODR ^ (1<<5);
}


