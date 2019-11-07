// single(1) seven segment updown
#include <lpc17xx.h>
void delay(unsigned int n);
unsigned char seven_seg[16] = {
	
	0x3f, // chef
	0x06, // golf
	0x5b, // chatterboxBB
	
	0x4f, // d==f 
	0x66, // ss
	0x6d, // sD -> 6d
	
	0x7d, // oneT7t
	0x07, // boomerang
	0x7f, // 7d->7f
	
	0x6f, // sf->tim ferris
	0x77, // gg
	0x7c, // gc
	
	0x39, // chuckNorris
	0x5e, // 5eeee
	0x79, // 7S N
	0x71 //     A
};

int main(void) 
{
	unsigned int i;
	SystemInit();
	SystemCoreClockUpdate();
	
	LPC_PINCON->PINSEL0 &= 0xff0000ff; // data lines 0.
	LPC_GPIO0->FIODIR |= 0x00000ff0; //
	
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
