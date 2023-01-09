/*
 * lcd.c
 *
 *  Created on: Jan 4, 2023
 *      Author: Amer Iqbal
 *      Driver for character LCD HD44780 display
 */
#include "lcd.h"
#include <stdio.h>
GPIO_TypeDef	* lcdPort;			// GPIO Port for LCD
uint16_t		lcdPins[10];		// [0]=RS, [1]=En, [2..9] data
enum lcdType	lcdMode;			// 4 or 8 bits
void lcdSetup(GPIO_TypeDef * Port,uint16_t RS,uint16_t E, enum lcdType mode, uint16_t D0,uint16_t D1,uint16_t D2,uint16_t D3,uint16_t D4,uint16_t D5,uint16_t D6,uint16_t D7)
{
	lcdPort=Port;
	lcdPins[0]=RS;
	lcdPins[1]=E;
	if(mode==Lcd8Bit)
	{
		lcdPins[2]=D0;
		lcdPins[3]=D1;
		lcdPins[4]=D2;
		lcdPins[5]=D3;
		lcdPins[6]=D4;
		lcdPins[7]=D5;
		lcdPins[8]=D6;
		lcdPins[9]=D7;
		lcdMode=Lcd8Bit;
	}
	else
	{
		lcdPins[6]=D4;
		lcdPins[7]=D5;
		lcdPins[8]=D6;
		lcdPins[9]=D7;
		lcdMode=lcd4Bit;

	}

}
void lcdEnable(void)
{
	HAL_GPIO_WritePin(lcdPort, lcdPins[1], GPIO_PIN_SET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(lcdPort, lcdPins[1], GPIO_PIN_RESET);
}

void lcdWrite4BitsOnly(uint8_t data)
{
	uint8_t hnibble;
	hnibble=(data >> 4) & 0x0F;
	for(int i=0;i<4;i++)
		{
			if(hnibble & (1<<i))
				HAL_GPIO_WritePin(lcdPort, lcdPins[i+6], GPIO_PIN_SET);			// lcdPins[i+2]=1
			else
				HAL_GPIO_WritePin(lcdPort, lcdPins[i+6], GPIO_PIN_RESET);
		}
	lcdEnable();


}
void lcdWrite(uint8_t data)
{
	if(lcdMode==Lcd8Bit)
	{
	for(int i=0;i<8;i++)
	{
		if(data & (1<<i))
			HAL_GPIO_WritePin(lcdPort, lcdPins[i+2], GPIO_PIN_SET);			// lcdPins[i+2]=1
		else
			HAL_GPIO_WritePin(lcdPort, lcdPins[i+2], GPIO_PIN_RESET);
	}
	lcdEnable();
	}
	else		// 4 bit mode 8 bits of data writing two nibbles
		{
			uint8_t highnibble;
			uint8_t lownibble;
			lownibble=data & 0x0F;
			highnibble= (data >> 4) & 0x0F;
				for(int i=0;i<4;i++)
				{
					if(highnibble & (1<<i))
						HAL_GPIO_WritePin(lcdPort, lcdPins[i+6], GPIO_PIN_SET);			// lcdPins[i+2]=1
					else
						HAL_GPIO_WritePin(lcdPort, lcdPins[i+6], GPIO_PIN_RESET);
				}
				lcdEnable();
				for(int i=0;i<4;i++)
				{
					if(lownibble & (1<<i))
						HAL_GPIO_WritePin(lcdPort, lcdPins[i+6], GPIO_PIN_SET);			// lcdPins[i+2]=1
					else
						HAL_GPIO_WritePin(lcdPort, lcdPins[i+6], GPIO_PIN_RESET);
				}
				lcdEnable();


			}

	}



void lcdCommand(uint8_t command)
{
	HAL_GPIO_WritePin(lcdPort, lcdPins[0], GPIO_PIN_RESET);		//	RS=0
	lcdWrite(command);
}

void lcdInit(void)
{
	if(lcdMode==Lcd8Bit)
	{
		lcdCommand(0x30);
		HAL_Delay(10);
		lcdCommand(0x30);
		HAL_Delay(10);
		lcdCommand(0x30);
		HAL_Delay(10);
		lcdCommand(0x38);
		HAL_Delay(10);
		lcdCommand(0x0E);
		HAL_Delay(10);
	}
	else
	{
		lcdWrite4BitsOnly(0x20);	// 0b00100000
		HAL_Delay(10);
		lcdCommand(0x2C);			// 0b00101100
		HAL_Delay(10);
		lcdCommand(0x0E);			// 0b00001110
		HAL_Delay(10);
	}

}

void lcdChar(char character)
{
	HAL_GPIO_WritePin(lcdPort, lcdPins[0], GPIO_PIN_SET);		//	RS=1
	lcdWrite(character);
}

void lcdString(char * string)
{
	while(*string)
		lcdChar(*string++);
}

void lcdSetCursor(uint8_t row, uint8_t col)
{
	HAL_GPIO_WritePin(lcdPort, lcdPins[0], GPIO_PIN_RESET);	// RS=0;
	switch (row)
	{
	case 0:
		lcdWrite(0x80+col); break;
	case 1:
		lcdWrite(0xC0+col); break;
	}
}

void lcdWriteInt(char * format, uint32_t number )
{
	char buffer[20];
	sprintf(buffer,format,number);
	lcdString(buffer);
}

void lcdWriteFloat(char * format, double number )
{
	char buffer[20];
	sprintf(buffer,format,number);
	lcdString(buffer);
}

