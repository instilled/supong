
#include "utils.h"
#include "lcd.h"

/**
 * Make sure that you call SCU_Configuration before calling 
 * initLCD int your code.
 */		  
GPIO_InitTypeDef GPIO_InitStructure;
void initLCD()
{
/*config GPIO P8 LCD data 0..77*/
  SCU_APBPeriphClockConfig(__GPIO8,ENABLE);
  SCU_APBPeriphReset(__GPIO8,DISABLE);
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin= GPIO_Pin_All;
  GPIO_InitStructure.GPIO_Direction=GPIO_PinOutput;
  GPIO_InitStructure.GPIO_Type=GPIO_Type_PushPull;
  GPIO_InitStructure.GPIO_Alternate = GPIO_OutputAlt1; 
  GPIO_Init(GPIO8,&GPIO_InitStructure);

/*config GPIO P9 LCD control 0..2*/
  SCU_APBPeriphClockConfig(__GPIO9,ENABLE);
  SCU_APBPeriphReset(__GPIO9,DISABLE);
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin= GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Direction=GPIO_PinOutput;
  GPIO_InitStructure.GPIO_Type=GPIO_Type_PushPull;
  GPIO_InitStructure.GPIO_Alternate = GPIO_OutputAlt1; 
  GPIO_Init(GPIO9,&GPIO_InitStructure);

   /* Make all Port 7 LED pins output */
  GPIO_InitStructure.GPIO_Direction = GPIO_PinOutput;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All; 
  GPIO_InitStructure.GPIO_Type = GPIO_Type_PushPull ;
  //GPIO_InitStructure.GPIO_Alternate = GPIO_OutputAlt1;  //$DD was missing
  SCU->GPIOOUT[7] = 0x5555;
  GPIO_Init (GPIO7, &GPIO_InitStructure);
  
  lcd_init();
  lcd_clear();
  
}

void toggleGPIO7(u8 pin)
{
	BitAction cur = Bit_SET;
	switch (GPIO_ReadBit(GPIO7, pin))
	{
		case Bit_SET:
			cur = Bit_RESET;
			break;
		case Bit_RESET:
			cur = Bit_SET;
			break;
	}

	GPIO_WriteBit(GPIO7, pin, cur);
}

/**
 * Sleep for a given time.
 */
void sleep(u32 nCount)
{
  u32 j = 0;
  for(j = nCount; j != 0; j--);
}
