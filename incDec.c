#include<LPC17xx.h>

unsigned long LED[] = {0x3F0, 0x060, 0x5B0, 0x4F0, 0x660, 0x6D0, 0x7D0, 0x070, 0x7F0, 0x6F0, 0x770, 0x7C0, 0x390, 0x5E0, 0x790, 0x710};
unsigned int j, in=0, s=0, dig0=0, dig1=0, dig2=0, dig3=0;

unsigned int digs[] = {9, 8, 7, 6}; // 6 7 8 9
void decByOne() {
	for (int i = 0; i < 4; i++) {
		digs[i]--;
		if (digs[i] == -1) {
			digs[i] = 0xF;
		} else {
			break;
		}
	}
}

void incByOne() {
	for (int i = 0; i < 4; i++) {
		digs[i]++;
		if (digs[i] == 0x10) {
			digs[i] = 0;
		} else {
			break;
		}
	}
}


int main(void)
{
	SystemInit();
	SystemCoreClockUpdate();
	
	LPC_PINCON->PINSEL0 &= 0xFF0000FF;
	LPC_PINCON->PINSEL3 &= 0XFFC03FFF;
	LPC_PINCON->PINSEL4 &= 0x00000000;
	LPC_GPIO0->FIODIRL |= 0x0FF0;
	LPC_GPIO1->FIODIRH |= 0x0780;
	LPC_GPIO2->FIODIR |= 0x00000000;
	LPC_GPIO0->FIOMASKL |= 0xF00F;
	LPC_GPIO1->FIOMASKH |= 0xF87F;
	
	while(1)
	{
		LPC_GPIO1->FIOPINH = 0x0000;
		LPC_GPIO0->FIOPINL = LED[dig0];
		for(j=0;j<100;j++);
		LPC_GPIO1->FIOPINH = 0xFFFF;
		
		LPC_GPIO1->FIOPINH = 0x0080;
		LPC_GPIO0->FIOPINL = LED[dig1];
		for(j=0;j<100;j++);
		LPC_GPIO1->FIOPINH = 0xFFFF;
		
		LPC_GPIO1->FIOPINH = 0x0100;
		LPC_GPIO0->FIOPINL = LED[dig2];
		for(j=0;j<100;j++);
		LPC_GPIO1->FIOPINH = 0xFFFF;
		
		LPC_GPIO1->FIOPINH = 0x0180;
		LPC_GPIO0->FIOPINL = LED[dig3];
		for(j=0;j<100;j++);
		LPC_GPIO1->FIOPINH = 0xFFFF;
		
		if(dig0==0x10)
		{
			dig0=0;
			dig1++;
		}
		if(dig0==-1 && dig1==0 && dig2==0 && dig3==0)
		{
			dig0=0xF;dig1=0xF;dig2=0xF;dig3=0xF;
		}
		if(dig0==-1)
		{
			dig0=0xF;
			dig1--;
		}
		if(dig1==0xF)
		{
			dig1=0;
			dig2++;
		}
		if(dig1==-1)
		{
			dig1=0xF;
			dig2--;
		}
		if(dig2==0xF)
		{
			dig2=0;
			dig3++;
		}
		if(dig2==-1)
		{
			dig2=0xF;
			dig3--;
		}
		if(dig3==0xF)
		{
			dig0=0;
			dig1=0;
			dig2=0;
			dig3=0;
		}
		if(dig3==-1)
		{
			dig0=0xF;dig1=0xF;dig2=0xF;
			dig3=0;
		}
	  in = LPC_GPIO2->FIOPIN0 & 0x01;
		for(j=0;j<10;j++);
		s++;
		if(s==200)
	  {
			if(in==0x00)
			  dig0--;
			else
				dig0++;
			s=0;
		}		
	}
}
