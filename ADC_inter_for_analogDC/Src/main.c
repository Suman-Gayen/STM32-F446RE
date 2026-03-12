

#include <stdint.h>
#include "stm32f446xx.h"

uint32_t ADC_DATA = 0;
int main(void)
{
//	ADC module - ADC1
//	ADC channel - PA1
	RCC->CR |= (1<<0);
	RCC->AHB1ENR |= (1<<0);          // Enable GPIOA clock
	GPIOA->MODER |= (1<<2) | (1<<3); //	Enable GPIOA as analog output
	RCC->APB2ENR |= (1<<8);          // Enable ADC clocks
	ADC1->CR2 &= (~(1<<0)); 		 // ADC OFF
	ADC1->SQR3 |= (1<<0); 			 // Start conversion sequence
	ADC1->SQR1 = 0X0000;			 // setting no of conversion length to be 1 (single channel) // for 1 conversion
	ADC1->CR2 |= (1<<0); 			 // ADC ON
	ADC1->CR2 |= (1<<1); 			 // Start ADC conversion
	ADC1->CR1 |= (1<<5);             // Interrupt enable for EOC
	NVIC_EnableIRQ(ADC_IRQn);
	ADC1->CR2 |= (1<<30); 			 // Start ADC conversion
	while(1){
//      Polling Method
//		while(! ( ADC1->SR & (1<<1))){} // wait for the End of conversion to complete (EOC)
//		ADC_DATA = ADC1->DR; 			// Read ADC_DR converted result
	}

}
// Interrupt Method | ISR | Interrupt subroutine
void ADC_IRQHandler (){
	while(! ( ADC1->SR & (1<<1))){} // wait for the End of conversion to complete (EOC)
	ADC1->SR &= (~(1<<1));
	ADC_DATA = ADC1->DR; 			// Read ADC_DR converted result
}
