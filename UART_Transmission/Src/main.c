
#include <stdint.h>
#include "stm32f446xx.h"
#define baudrate 115200
#define sys_clk 16000000
int main(void)
{
	// USART PA2
	RCC->CR |= (1<<0);
	RCC->AHB1ENR |= (1<<0); // Enable GPIOA clock
	RCC->APB1ENR |= (1<<17); // Enable USART2 clock
	GPIOA->MODER |= (1<<5);
	GPIOA->MODER &= (~(1<<4));   //	Configure GPIOA alternate function FOR PA2
	// Alternate function select mode to be UART Tx channel | 0111: AF7
	GPIOA->AFR[0] |= (1<<8) | (1<<9) | (1<<10);
	GPIOA->AFR[0] &= (~(1<<11));
	USART2->BRR = ((sys_clk+(baudrate/2U))/baudrate); // Boudrate of USART2 to be 115200

	USART2->CR1 |= (1<<13); // USART UE Enable
	USART2->CR1 |= (1<<3); // USART Tx Enable


	while(1){
		while(!(USART2->SR & (1<<7))){} // wait for Tx buffer emptiness
		USART2->DR = 'D';               // Write byte to USART2 bus
	}
}

