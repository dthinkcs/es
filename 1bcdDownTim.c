#include <LPC17xx.h>
int dig_values[] = {9,9,9,9};
unsigned int dig_sel = 0;
unsigned int i;
unsigned int idx;
unsigned char seven_seg[10]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
unsigned int shift[] = {0<<23,1<<23,2<<23,3<<23};
void timer_init()
{
	LPC_TIM0->TCR=0X02;
	LPC_TIM0->MR0=999999;
	LPC_TIM0->PR=0X02;
	LPC_TIM0->CTCR=0X00;
	LPC_TIM0->MCR=0X02;
	LPC_TIM0->EMR=0X20;
	LPC_TIM0->TCR=0X01;
}
void display(void)
{
	int x=0;
	for(x=0;x<4;x++)
	{
		LPC_GPIO1->FIOPIN=shift[x];
		LPC_GPIO0->FIOPIN=seven_seg[dig_values[x]]<<4;
		for(i=0;i<500;i++);
		LPC_GPIO0->FIOPIN=00<<4;
	}
}
int main(void)
{
	LPC_PINCON->PINSEL0&=0XFF0000FF;
	LPC_PINCON->PINSEL3&=0XFFC03FFF;
	LPC_GPIO0->FIODIR = 0X00000FF0;
	LPC_GPIO1->FIODIR = 0X07800000;
	timer_init();
	while(1)
	{
		if(LPC_TIM0->EMR&0X01){
			/* BUG BUG BUG
			dig_values[0]--;
			if(dig_values[0] == 0)
			{
				dig_values[1]--;
				dig_values[0] = 9;
				if(dig_values[1] == 0)
				{
					dig_values[2]--;
					dig_values[1] = 9;
					if(dig_values[2] == 0)
					{
						dig_values[3]--;
						dig_values[2] = 9;
						if(dig_values[3] == 0)
						{	
							dig_values[0] = 9;
							dig_values[1] = 9;
							dig_values[2] = 9;
							dig_values[3] = 9;
						}
					}
				}
			}*/
			// DECREMENT
			for (idx = 0; idx < 4; idx++) {
				dig_values[idx]--;
				if (dig_values[idx] == -1) {
						dig_values[idx] = 9;
				} else {
					break;
				}
			}
		LPC_TIM0->EMR=0X20;
		}
		display();
	}
}
