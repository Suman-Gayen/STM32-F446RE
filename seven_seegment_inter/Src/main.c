
#include <stdint.h>
#include "stm32f446xx.h"

//example
/*
 * data = 3E = 00111110
 * 		0x01 = 00000001
 * 		   & = 00000000
 *  */
void PrintData(unsigned char data){
	// Bit 0 => a,   a = PA10
	if((data & 0x01) == 0x01){ GPIOA->ODR |= (1<<10);    }// 0x01 = 00000001
	else 				   { GPIOA->ODR &= (~(1<<10)); }

	// Bit 1 => b, 	 b = PB3
	if((data & 0x02) == 0x02){ GPIOB->ODR |= (1<<3);    }  // 0x02 = 00000010
	else 				   { GPIOB->ODR &= (~(1<<3)); }

	// Bit 2 => c,  c = PB5
	if((data & 0x04) == 0x04){ GPIOB->ODR |= (1<<5);    }  // 0x04 = 000000100
	else 				   { GPIOB->ODR &= (~(1<<5)); }

	// Bit 3 => d,  d = PB4
	if((data & 0x08) == 0x08){ GPIOB->ODR |= (1<<4);    }  // 0x08 = 00001000
	else 				   { GPIOB->ODR &= (~(1<<4)); }

	// Bit 4 => e,  e = PB10
	if((data & 0x10) == 0x10){ GPIOB->ODR |= (1<<10);    } // 0x10 = 00010000
	else 				   { GPIOB->ODR &= (~(1<<10)); }

	// Bit 5 => f,  f = PA8
	if((data & 0x20) == 0x20){ GPIOA->ODR |= (1<<8);    }  // 0x20 = 00100000
	else 				   { GPIOA->ODR &= (~(1<<8)); }

	// Bit 6 => g,   g = PA9
	if((data & 0x40) == 0x40){ GPIOA->ODR |= (1<<9);     } // 0x40 = 01000000
	else 				   { GPIOA->ODR &= (~(1<<9)); }

	// Bit 7 => dp,   dp= PC7
	if((data & 0x80) == 0x80){ GPIOC->ODR |= (1<<7);     } // 0x80= 10000000
	else 				   { GPIOC->ODR &= (~(1<<7)); }

}
void delay(long d){
	while(--d);
}

int main(void)
{
	// enable clock on GPIOA, GPIOB, GPIOC
	/*
	 * all seven segment terminals must be made o/p
	 * a = PA10
	 * b = PB3
	 * c = PB5
	 * d = PB4
	 * e = PB10
	 * f = PA8
	 * g = PA9
	 * dp= PC7
	 * */
	RCC->AHB1ENR = RCC->AHB1ENR | (1<<0) | (1<<1) | (1<<2);
	GPIOA->MODER = GPIOA->MODER | (1<<20)| (1<<18) | (1<<16);
	GPIOB->MODER = GPIOB->MODER | (1<<6) | (1<<10) | (1<<8) | (1<<20);
	GPIOC->MODER = GPIOC->MODER | (1<<14);


	while(1)
	{
		//COMMON CATHOD
		// 0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7c, 0x07, 0x7f, 0x6f
		PrintData(0x3F);
		delay(500000);delay(500000);
		PrintData(0x06);
		delay(500000);delay(500000);
		PrintData(0x5b);
		delay(500000);delay(500000);
		PrintData(0x4f);
		delay(500000);delay(500000);
		PrintData(0x66);
		delay(500000);delay(500000);
		PrintData(0x6d);
		delay(500000);delay(500000);
		PrintData(0x7c);
		delay(500000);delay(500000);
		PrintData(0x07);
		delay(500000);delay(500000);
		PrintData(0x7f);
		delay(500000);delay(500000);
		PrintData(0x6f);
		delay(500000);delay(500000);

	}
}
