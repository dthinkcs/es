#include <LPC17XX.H>
#include <stdlib.h>

#define RS 27
#define E 28
#define DT 23
void EINT2_IRQHandler();
void write_number_lcd();
void lcd_write();
void port_write(void);
void delay(unsigned int );

unsigned char command[]={0x30,0x30,0x30,0x20,0x28,0x0C,0X06,0X01,0X80};
unsigned char msg[] = "123456";
unsigned int i,j,flag1,flag2,temp1,temp2,temp;

int main(void) {

	SystemInit();
	SystemCoreClockUpdate();
	
	// FOR LCD
	// FOR KEYRRESS 
	LPC_SC->EXTMODE = 0x01<<2;
	LPC_SC->EXTPOLAR = 0x01<<2;
	LPC_PINCON->PINSEL4 = 01 << 24;
	NVIC_EnableIRQ(EINT2_IRQn);
		LPC_PINCON->PINSEL1=00;
	LPC_GPIO0->FIODIR=(1<<RS|1<<E|0XF<<DT);

	flag1=0;
	for(j=0;j<9;j++)
	{
		temp1=command[j];
		lcd_write();
	}
	flag1=1;

	//for(j=0;j<15;j++) {
	//for(i = 0; i < 3; i++) {
	//	write_number_lcd();
	//}
	while(1); // IMPORTANT STEP
}

void EINT2_IRQHandler() {
	
	//delay(250000);
	write_number_lcd();
	LPC_SC->EXTINT = 1 << 2;
}

void write_number_lcd() {
	//time_t t;
	//srand((unsigned) time(&t));
	
	flag1 = 0;
	temp1 = 0x80;
	lcd_write();
	flag1 = 1;
	
	temp1 = msg[rand() % 6];
	lcd_write();
}

void lcd_write()
{
	// Initially be default 8 bit mode till 0x20 is sent
	flag2=(flag1==1)?0:((temp1==0x30)||(temp1==0x20))?1:0; // to find out whether both digits
	temp2=temp1&0xF0; // msb ex: 45 -> 40
	temp2>>=4; // 40 -> 4 temp2: stores the value to write
	port_write();
	
	if(!flag2) // if flag2 is 0 then 4 bit mode (both digits must be written msb lsb) 
	{
		temp2=temp1&0x0F; // lsb
		port_write();
	}
	delay(30000);
	
}

void port_write()
{
	//LPC_GPIO0->FIOPIN=0;
	LPC_GPIO0->FIOPIN=temp2<<DT;
	if(flag1==0) // command arr is getting written
		LPC_GPIO0->FIOCLR=1<<RS; // RS = 0
	else 
		LPC_GPIO0->FIOSET=1<<RS; // RS = 1 DATA IS BEING WRITTEN
	
	LPC_GPIO0->FIOSET=1<<E;
	delay(25);
	LPC_GPIO0->FIOCLR=1<<E;
	
	delay(1000);
}

void delay(unsigned int n)
{
	unsigned int i = 0;
	for(i=0;i<n;i++);
}



