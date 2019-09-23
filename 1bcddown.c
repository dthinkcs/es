#include <LPC17xx.h>
int dig_values[] = {9,9,9,9};  // change to int
unsigned int count = 0;
unsigned char flag=0;
unsigned int dig_sel = 0;
unsigned int i;
unsigned char seven_seg[10]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
unsigned int shift[] = {0<<23,1<<23,2<<23,3<<23};
void delay()
{
	if(count == 500)
	{
		flag=0xFF;
		count=0;
	}
	for(i=0;i<500;i++);
	count++;
}
void display(void)
{
	LPC_GPIO1->FIOPIN=shift[dig_sel];
	LPC_GPIO0->FIOPIN=seven_seg[dig_values[dig_sel]]<<4;
	for(i=0;i<500;i++);
	LPC_GPIO0->FIOPIN=00<<4;
		
}
int main(void)
{
	LPC_PINCON->PINSEL0&=0XFF0000FF;
	LPC_PINCON->PINSEL3&=0XFFC03FFF;
	LPC_GPIO0->FIODIR = 0X00000FF0;
	LPC_GPIO1->FIODIR = 0X07800000;
	while(1)
	{
		delay();
		if(dig_sel==4)
		{
			dig_sel = 0;
			flag=0xFF;
		}
		if(flag ==0xFF)
		{
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
			}
		}
		display();
		dig_sel++;
	}
}
