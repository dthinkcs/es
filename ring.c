#include <LPC17xx.h>
void delay(unsigned int); // for delay

int main(void)
{
	unsigned int i, j, valueSet;
	
	SystemInit();
	SystemCoreClockUpdate();

	valueSet = 0;
	// GPIO Configuration
	LPC_PINCON->PINSEL0 &= 0xFF0000FF;
	// FIODIR Configuration
	LPC_GPIO0->FIODIR |= 0x0FF0;
	while (1) 
	{
		for (i = 0; i < 8; i++)
		{
			// send output via FIOPIN 
			LPC_GPIO0->FIOPIN = valueSet << 4; // STARTLED
			valueSet = (valueSet >> 1) + (1 << 7); // SIZE 
			delay(10000);
		}
		
		for (i = 0; i < 8; i++)
		{
			LPC_GPIO0->FIOPIN = valueSet << 4; 
			valueSet = valueSet >> 1;
			delay(10000);
		}
	}
}
 
void delay(unsigned int n) 
{
	unsigned int i = 0;
	for (i = 0; i < n; i++);
}
