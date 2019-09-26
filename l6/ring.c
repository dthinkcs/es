#include <LPC17xx.h>
void delay(unsigned int); // for delay

int main(void)
{
	unsigned int i, j, valueSet;
	
	SystemInit();
	SystemCoreClockUpdate();

	
	// GPIO Configuration
	LPC_PINCON->PINSEL0 &= 0xFF0000FF;
	// FIODIR Configuration
	LPC_GPIO0->FIODIR |= 0x0FF0;
	while (1) 
	{
		valueSet = 1 << 7;
		for (i = 0; i < 8; i++)
		{
			// send output via FIOPIN 
			LPC_GPIO0->FIOPIN = valueSet << 4; // STARTLED
			valueSet = (valueSet >> 1); // SIZE 
			delay(50000);
		}
	}
}
 
void delay(unsigned int n) 
{
	unsigned int i = 0;
	for (i = 0; i < n; i++);
}

 
