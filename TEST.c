 #include <LPC17xx.h>
#include <stdio.h>
		int channel, a=0,b=0, result;
int main(void)
{
	unsigned long adc_temp;
	unsigned int i;

	
	SystemInit();
	SystemCoreClockUpdate();

	LPC_SC->PCONP |= (1<<12); 
	LPC_PINCON->PINSEL3 |= 0xF0000000;
	LPC_ADC->ADCR = 1<<4|(1<<5)|1<<16|(1<<21);
	LPC_PINCON->PINSEL0 |= 0; 
	LPC_GPIO0->FIODIR=7<<4;
	LPC_ADC->ADINTEN=1<<4|1<<5;
	NVIC_EnableIRQ(ADC_IRQn);
 // select channel 5, power ON, start conversion NOW
	while(1);
}

void ADC_IRQHandler()
{
	
	
	unsigned long x,y;
	for(x=0;x<500;x++);
	x=LPC_ADC->ADSTAT&3<<4;

	if(x&1<<4)
	{
		a=LPC_ADC->ADDR4;
	}
	
	if(x&1<<5)
	{
		b=LPC_ADC->ADDR5;
	}
	y=LPC_ADC->ADGDR;
	if(a>b)
			LPC_GPIO0->FIOPIN=1<<4;
	else if(a==b)
		LPC_GPIO0->FIOPIN=1<<5;
	else 
		LPC_GPIO0->FIOPIN=1<<6;
}
