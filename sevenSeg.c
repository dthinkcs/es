// single(1) seven segment updown
#include <lpc17xx.h>
void delay(unsigned int n);
unsigned char seven_seg[16] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71};

int main(void) 
{
	unsigned int i;
	SystemInit();
	SystemCoreClockUpdate();
	
	LPC_PINCON->PINSEL0 &= 0xff0000ff;
	LPC_GPIO0->FIODIR |= 0x00000ff0;
	
	// later decoder

	for (i = 0; 1 ; i = (i + 1) % 16)
	{
		LPC_GPIO0->FIOPIN = seven_seg[i] << 4;
   	delay(10000);
	}
}

void delay(unsigned int n) 
{
	unsigned int i = 0;
	for (i = 0; i < n; i++);
}
