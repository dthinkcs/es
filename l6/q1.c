#include<LPC17xx.h>

unsigned int i,j;
unsigned long LED = 0x00000000;
unsigned int x=0;

int main(void)
{
	SystemInit();
	SystemCoreClockUpdate();
	
	LPC_PINCON -> PINSEL0 &= 0xFF0000FF;
	LPC_GPIO0 -> FIODIR |= 0x00000FF0;
	//LED = 1<<4;
	while(1)
	{
		LED = 0x00000000;
		x = 0;
    // increment x
		for( x= 0; x<=0xFF ; x++){
			LED = x<<4;
			LPC_GPIO0->FIOPIN = LED; // show LED valueAKA x << 4
			for(j = 0; j<90000; j++);
		}
		
	}
}
