
#include <stdint.h>
#include "stm32f446xx.h"


void delay(long d){
	while(--d);
}
//example
/*
 * data = 3E = 00111110
 * 		0x01 = 00000001
 * 		   & = 00000000
 *  */
void PrintData(unsigned char data){
	// Bit 4 => d4,  d4 = PB10
	if((data & 0x10) == 0x10){ GPIOB->ODR |= (1<<10);    } // 0x10 = 00010000
	else 				   { GPIOB->ODR &= (~(1<<10)); }

	// Bit 5 => d5,  d5 = PA8
	if((data & 0x20) == 0x20){ GPIOA->ODR |= (1<<8);    }  // 0x20 = 00100000
	else 				   { GPIOA->ODR &= (~(1<<8)); }

	// Bit 6 => d6,   d6 = PA9
	if((data & 0x40) == 0x40){ GPIOA->ODR |= (1<<9);     } // 0x40 = 01000000
	else 				   { GPIOA->ODR &= (~(1<<9)); }

	// Bit 7 => d7,   d7= PC7
	if((data & 0x80) == 0x80){ GPIOC->ODR |= (1<<7);     } // 0x80= 10000000
	else 				   { GPIOC->ODR &= (~(1<<7)); }

}
/* passing data to data register of LCD
 * printing data to LCD */
void LCD_Data(unsigned char data){
	PrintData(data); 					 // Pass the 8-bit data to data line's of LCD
	GPIOA->ODR = GPIOA->ODR & (~(1<<7)); // Drive R/W line of LCD to be low ( rw = PA7)
	GPIOB->ODR = GPIOB->ODR | (1<<6);    // Drive RS line of LCD to be HIGH (rs = PB6)
	GPIOA->ODR = GPIOA->ODR | (1<<6);	 // Drive EN line of LCD to be HIGH (en = PA6)
	delay(6000);						 // delay
	GPIOA->ODR = GPIOA->ODR & (~(1<<6)); // Drive EN line of LCD to be LOW
	PrintData(data<<4); 					 // Pass the 8-bit data to data line's of LCD
	GPIOA->ODR = GPIOA->ODR & (~(1<<7)); // Drive R/W line of LCD to be low ( rw = PA7)
	GPIOB->ODR = GPIOB->ODR | (1<<6);    // Drive RS line of LCD to be HIGH (rs = PB6)
	GPIOA->ODR = GPIOA->ODR | (1<<6);	 // Drive EN line of LCD to be HIGH (en = PA6)
	delay(6000);						 // delay
	GPIOA->ODR = GPIOA->ODR & (~(1<<6)); // Drive EN line of LCD to be LOW
}
/* passing data to Instruction register of LCD
 * pass commands to LCD */
void LCD_Commond(unsigned char commond){
	PrintData(commond);                  	 // Pass the 8-bit data to data line's of LCD
	GPIOA->ODR = GPIOA->ODR & (~(1<<7)); // Drive R/W line of LCD to be low ( rw = PA7)
	GPIOB->ODR = GPIOB->ODR & (~(1<<6)); // Drive RS line of LCD to be low (rs = PB6)
	GPIOA->ODR = GPIOA->ODR | (1<<6);    // Drive EN line of LCD to be HIGH (en = PA6)
	delay(6000); 						 // delay
	GPIOA->ODR = GPIOA->ODR & (~(1<<6)); // Drive EN li
	PrintData(commond<<4);                  	 // Pass the 8-bit data to data line's of LCD
	GPIOA->ODR = GPIOA->ODR & (~(1<<7)); // Drive R/W line of LCD to be low ( rw = PA7)
	GPIOB->ODR = GPIOB->ODR & (~(1<<6)); // Drive RS line of LCD to be low (rs = PB6)
	GPIOA->ODR = GPIOA->ODR | (1<<6);    // Drive EN line of LCD to be HIGH (en = PA6)
	delay(6000); 						 // delay
	GPIOA->ODR = GPIOA->ODR & (~(1<<6)); // Drive EN line of LCD to be LOW
}
// Printing word of data to LCD
void LCD_String(char *str, unsigned char length){
	// LCD DATA function in loop for printing string or word of data to LCD
	unsigned char i;
	for(i=0; i<=length; i++){
		LCD_Data(i);
	}

}
// Initializing the LCD at first instance
void LCD_Init(void){
	LCD_Commond(0x28); // Configure lcd in 16 row
	LCD_Commond(0x06); // auto increment cursor  left to right
	LCD_Commond(0x0C); // display on, cursor off
	LCD_Commond(0x01); // clear screen
}
int main(void)
{
		// enable clock on GPIOA, GPIOB, GPIOC
		/*
		 * all seven segment terminals must be made o/p
		 * d0 = PA10
		 * d1 = PB3
		 * d2 = PB5
		 * d3 = PB4
		 * d4 = PB10
		 * d5 = PA8
		 * d6 = PA9
		 * d7 = PC7
		 *
		 * en = PA6
		 * rw = PA7
		 * rs = PB6
		 * */
		RCC->AHB1ENR = RCC->AHB1ENR | (1<<0) | (1<<1) | (1<<2);
		// d0, d5, d6
		GPIOA->MODER = GPIOA->MODER | (1<<20) | (1<<18) | (1<<16);
		GPIOA->MODER = GPIOA->MODER & (~(1<<21)) & (~(1<<19)) & (~(1<<17));
		// d1, d2, d3, d4
		GPIOB->MODER = GPIOB->MODER | (1<<6) | (1<<10) | (1<<8) | (1<<20);
		GPIOB->MODER = GPIOB->MODER & (~(1<<7)) & (~(1<<11)) & (~(1<<9) & (1<<21));
		// d7
		GPIOC->MODER = GPIOC->MODER | (1<<14);
		GPIOC->MODER = GPIOC->MODER & (~(1<<15));
		// en, rw
		GPIOA->MODER = GPIOA->MODER  | (1<<12)| (1<<14);
		GPIOA->MODER = GPIOA->MODER & (~(1<<13)) & (~(1<<15));
		// rs
		GPIOB->MODER = GPIOB->MODER  | (1<<12);
		GPIOB->MODER = GPIOB->MODER & (~(1<<13));

		LCD_Init();

		while(1)
		{
			LCD_Commond(0x80);
			LCD_String("EMBEDDED", 8);
			LCD_Commond(0xC0);
			LCD_String("SYSTEM", 6);
		}
}
