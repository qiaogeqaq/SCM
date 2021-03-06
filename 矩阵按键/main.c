#include "reg52.h"
#include "intrins.h"

#define GPIO_DIG P0
#define GPIO_KEY P1



typedef unsigned int uint16;
typedef unsigned int uint8;	   


uint8 code A_list[16] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,
							0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};

uint8 keyvalue;

int delay(uint16 i)					  //延时函数
{
	while(i--);
	return 0;
}

void keydown()
{
	int a = 0;
	GPIO_KEY = 0x0f;
	if(GPIO_KEY != 0x0f)
	{
		delay(1000);
		switch(GPIO_KEY)
		{
			case 0x07: keyvalue = 0;
			break;
			case 0x0b: keyvalue = 1;
			break;
			case 0x0d: keyvalue = 2;
			break;
			case 0x0e: keyvalue = 3;
			break;		
		} 

		GPIO_KEY = 0XF0;
		switch(GPIO_KEY)
		{
			case 0x70: keyvalue = keyvalue;
			break;
			case 0xb0: keyvalue = keyvalue+4;
			break;
			case 0xd0: keyvalue = keyvalue+8;
			break;
			case 0xe0: keyvalue = keyvalue+12;
			break;		
		} 
		while((a<50)&&(GPIO_KEY != 0xf0))
		{
			delay(1000);
			a++;
		}		
	}
}


							




int main(void)
{
	while(1)
	{
	 	keydown();
		GPIO_DIG = ~A_list[keyvalue];		 //这里使用静态数码管为共阳
	}

	return 0;
}