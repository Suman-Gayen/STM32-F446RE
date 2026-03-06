
#include <stdint.h>


int main(void)
{
	uint32_t *pRCCAHB1ENR = (uint32_t *)(0x40023800 + 0x30);
	*pRCCAHB1ENR |= 0x01;
	uint32_t *pGPIOAMODE  = (uint32_t *)(0x40020000);
	*pGPIOAMODE &= 0xFFFFF3FF; //1111 1111 1111 1111 1111 0011 1111 1111
	*pGPIOAMODE |= 0x01 << 10;
	uint32_t *pGPIOAODR  = (uint32_t *)(0x40020000 + 0x14);
	*pGPIOAODR |= 0x01 << 5;

}
