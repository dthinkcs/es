#include<LPC17xx.h>
#include<stdio.h>
//#include"AN_LCD.h"
#define Ref_Vtg 3.300
#define Full_Scale 0xFFF //12 bit ADC

unsigned char vtg[7],dval[7];
unsigned char Msg3[] = {"IP:"};
unsigned char Msg4[] = {"ADC OUTPUT:"};
 long adc_temp1=0,adc_temp2=0,adc_temp=0;
unsigned int i;
float in_vtg;
//LCD part
#define RS_CTRL 0x08000000 //P0.27
#define EN_CTRL 0x10000000 //P0.28
#define DT_CTRL 0x07800000 //P0.23 to P0.26 data lines
void lcd_init(void);
void wr_cn(void);
void clr_disp(void);
void delay_lcd(unsigned int);
void lcd_com(void);
void wr_dn(void);
void lcd_data(void);
void clear_ports(void);
void lcd_puts(unsigned char *);

unsigned long int temp1=0, temp2=0 ,temp;

int main(void)
{


SystemInit();
SystemCoreClockUpdate();

LPC_SC->PCONP |= (1<<15); //Power for GPIO block
lcd_init();
LPC_PINCON->PINSEL3 |= 0x30000000; //P1.30 as AD0.4
LPC_PINCON->PINSEL3 |= 0xC0000000; //P1.31 as AD0.5
LPC_SC->PCONP |= (1<<12)|(1<<15); //enable the peripheral ADC
SystemCoreClockUpdate();
//1st line
temp1 = 0x80;
lcd_com();
delay_lcd(800);
lcd_puts(&Msg3[0]);
//2nd line
temp1 = 0xC0;
lcd_com();
delay_lcd(800);
lcd_puts(&Msg4[0]);
while(1)
{
	LPC_ADC->ADCR = (1<<4)|(1<<21)|(1<<24);//0x01200001; //AD0.4 start conversion 
	while(!(LPC_ADC->ADGDR & 1<<31));
			adc_temp1 = LPC_ADC->ADDR4;
	for(i=0;i<2000;i++);
	LPC_ADC->ADCR = (1<<5)|(1<<21)|(1<<24);//0x01200001; //AD0.5 start conversion 
		while(!(LPC_ADC->ADGDR & 1<<31));	
			adc_temp2 = LPC_ADC->ADDR5;

		adc_temp = adc_temp2 - adc_temp1;
	if(adc_temp < 0)
		adc_temp = -adc_temp;
	
	adc_temp = adc_temp & 0xFFFF;
	in_vtg = (((float)adc_temp * (float)Ref_Vtg))/((float)Full_Scale); //calculating input analog
	
	//voltage
	sprintf(vtg,"%3.2fV",in_vtg);
	//convert the readings into string to display on LCD
	sprintf(dval,"%x",adc_temp);
	for(i=0;i<2000;i++);
	
	temp1 = 0x8A;
	lcd_com();
	delay_lcd(800);
	lcd_puts(&vtg[0]);
	
	temp1 = 0xCB;
	lcd_com();
	delay_lcd(800);
	lcd_puts(&dval[0]);
	
for(i=0;i<20000;i++); //delay for conversion
	for(i=0;i<7;i++)
	vtg[i] = dval[i] = 0x00;
	adc_temp = 0;
	in_vtg = 0;
}


}//main()

//lcd initialization
void lcd_init()
{
/* Ports initialized as GPIO */
	LPC_PINCON->PINSEL3 &= 0xFC003FFF; //P0.23 to P0.28
/* Setting the directions as output */
	LPC_GPIO0->FIODIR |= DT_CTRL;
	LPC_GPIO0->FIODIR |= RS_CTRL;
	LPC_GPIO0->FIODIR |= EN_CTRL;
	clear_ports();
	delay_lcd(3200);
	temp2 = (0x30<<19);
	wr_cn();
	delay_lcd(30000);
	temp2 = (0x30<<19);
	wr_cn();
	delay_lcd(30000);
	temp2 = (0x30<<19);
	wr_cn();
	delay_lcd(30000);
	temp2 = (0x20<<19);
	wr_cn();
	delay_lcd(30000);
	temp1 = 0x2C;
	lcd_com();
	delay_lcd(30000);
	temp1 = 0x0C;
	lcd_com();
	delay_lcd(800);
	temp1 = 0x06;
	lcd_com();
	delay_lcd(800);
	temp1 = 0x01;

	lcd_com();
	delay_lcd(10000);
	temp1 = 0x80;
	lcd_com();
	delay_lcd(800);
	return;
}
void lcd_com(void)
{
	temp2 = temp1 & 0xf0;//move data (26-8+1) times : 26 - HN
	//place, 4 - Bits
	temp2 = temp2 << 19; //data lines from 23 to 26
	wr_cn();
	temp2 = temp1 & 0x0f; //26-4+1
	temp2 = temp2 << 23;
	wr_cn();
	delay_lcd(1000);
	return;
}
// command nibble o/p routine
void wr_cn(void) //write command reg
{
	clear_ports();
	LPC_GPIO0->FIOPIN = temp2; // Assign the value to the data
	//lines
	LPC_GPIO0->FIOCLR = RS_CTRL; // clear bit RS
	LPC_GPIO0->FIOSET = EN_CTRL; // EN=1
	delay_lcd(25);
	LPC_GPIO0->FIOCLR = EN_CTRL; // EN =0
	return;
}
// data o/p routine which also outputs high nibble first
// and lower nibble next
void lcd_data(void)
{
	temp2 = temp1 & 0xf0;
	temp2 = temp2 << 19;
	wr_dn();
	temp2= temp1 & 0x0f;

	temp2= temp2 << 23;
	wr_dn();
	delay_lcd(1000);
	return;
}
// data nibble o/p routine
void wr_dn(void)
{
	clear_ports();
	LPC_GPIO0->FIOPIN = temp2; // Assign the value to the
	//data lines
	LPC_GPIO0->FIOSET = RS_CTRL; // set bit RS
	LPC_GPIO0->FIOSET = EN_CTRL; // EN=1
	delay_lcd(25);
	LPC_GPIO0->FIOCLR = EN_CTRL; // EN =0
	return;
}
void delay_lcd(unsigned int r1)
{
	unsigned int r;
	for(r=0;r<r1;r++);
	return;
}
void clr_disp(void)
{
	temp1 = 0x01;
	lcd_com();
	delay_lcd(10000);
	return;
}
void clear_ports(void)
{
/* Clearing the lines at power on */
	LPC_GPIO0->FIOCLR = DT_CTRL; //Clearing data lines
	LPC_GPIO0->FIOCLR = RS_CTRL; //Clearing RS line
	LPC_GPIO0->FIOCLR = EN_CTRL; //Clearing Enable line
	return;
}

void lcd_puts(unsigned char *buf1)
{
	unsigned int i=0;
	while(buf1[i]!='\0')
	{
	temp1 = buf1[i];
	lcd_data();
	i++;
	if(i==16)
	{
		temp1 = 0xc0;
		lcd_com();
	}
	}
return;
}
