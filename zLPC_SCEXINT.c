#include <LPC17XX.H>
int main(void)
{
	SystemInit();
	SystemCoreClockUpdate();
	LPC_PINCON->PINSEL4=01<<20; // function 1  for input
  
	LPC_GPIO0->FIODIR|=01<<11; // for output
  
	LPC_SC->EXTMODE=0X1;
	LPC_SC->EXTPOLAR=0X1;
	NVIC_EnableIRQ(EINT0_IRQn);
	while(1);
}
void EINT0_IRQHandler(void)
{
	LPC_SC->EXTINT=0X1;
	LPC_GPIO0->FIOPIN=~LPC_GPIO0->FIOPIN;
}


LPC_TIM0->CTCR = 00;
TCR = 02;

MR1 = 499;
MCR = 0x10;
EMR = 0x80;
PR = 02;

TCR = 01;
