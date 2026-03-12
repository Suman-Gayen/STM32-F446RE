
#include <stdint.h>
#include "stm32f446xx.h"

#define baudrate 115200
#define sys_clk 16000000
uint8_t data;

int main(void)
{
	// USART PA2 - Tx
	// USART PA3 - Rx
	RCC->CR |= (1<<0);
	RCC->AHB1ENR |= (1<<0);                           // Enable GPIOA clock
	RCC->APB1ENR |= (1<<17);                          // Enable USART2 clock

	GPIOA->MODER |= (1<<5);
	GPIOA->MODER &= (~(1<<4));                        //	Configure GPIOA alternate function FOR PA2

	GPIOA->MODER |= (1<<7);
	GPIOA->MODER &= (~(1<<6));   					  //	Configure GPIOA alternate function FOR PA3

	GPIOA->AFR[0] |= (1<<8) | (1<<9) | (1<<10);
	GPIOA->AFR[0] &= (~(1<<11));					  // Alternate function select mode to be UART Tx channel | 0111: AF7

	GPIOA->AFR[0] |= (1<<12) | (1<<13) | (1<<14);
	GPIOA->AFR[0] &= (~(1<<15));					  // Alternate function select mode to be UART Rx channel | 0111: AF7

	USART2->BRR = ((sys_clk+(baudrate/2U))/baudrate); // Boudrate of USART2 to be 115200

	USART2->CR1 |= (1<<13); 						  // USART UE Enable
	USART2->CR1 |= (1<<3) | (1<<2);              	  // USART Tx Enable

	USART2->CR1 |= (1<<5); 							  // Rx Interrupt Enable
	NVIC_EnableIRQ(USART2_IRQn);					  // USART2 is Enabled in NVIC controller

	while(1){
/*=====>1. Polling Method =============*/
//		while(!(USART2->SR & (1U<<5))){} 			  // wait for Tx buffer emptiness
//		data = USART2->DR;              			  // Receive a byte of data in UART bus
//		while(!(USART2->SR & (1U<<7))){} 			  // wait for Tx buffer emptiness
//		USART2->DR = data;              			  // Write byte to USART2 bus
	}
}
/*=====>2. Interrupt Method | ISR =====*/
void USART2_IRQHandler(void){
	while(!(USART2->SR & (1U<<5))){} 				  // wait for Tx buffer emptiness
	data = USART2->DR;              				  // Receive a byte of data in UART bus
	while(!(USART2->SR & (1U<<7))){} 				  // wait for Tx buffer emptiness
	USART2->DR = data;              				  // Write byte to USART2 bus
}

