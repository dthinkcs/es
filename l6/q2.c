#include<LPC17xx.h>

unsigned int i,j;
unsigned long LED = 0x00000000;
unsigned int x=0,flag = 0;
unsigned int keyPressed;

int main(void)
{
	SystemInit();
	SystemCoreClockUpdate();
	
	LPC_PINCON -> PINSEL0 &= 0xFF0000FF;
	LPC_GPIO0 -> FIODIR |= 0x00000FF0;
	
	LPC_PINCON -> PINSEL4 &= 0xFCFFFFFF;
	LPC_GPIO2 -> FIODIR &= 0xFFFFEFFF;
	//LED = 1<<4;
	while(1)
	{
		
		// if key pressed then switch
	  keyPressed = LPC_GPIO2->FIOPIN & (1 << 12);
		if(keyPressed)
		{
			/*
			if(flag == 1)
				flag = 0;
			else
				flag = 1;
		}
		if (flag == 0) {
			//inc();
			*/
			LED = x<<4;
			LPC_GPIO0->FIOPIN = LED;
			for(j = 0; j<90000; j++);
			x++;
			if(x==0xFF)
				x =0;
		}
		else {
			LED = x<<4;
			LPC_GPIO0->FIOPIN = LED;
			for(j = 0; j<90000; j++);
			if(x<=0)
				x =0xFF;
			x--;
		}
			
	}
}
