/*
 * lcd.h
 *
 *  Created on: Jan 4, 2023
 *      Author: Amer Iqbal
 *      Character LCD Driver
 */
#include "stm32f1xx.h"
#ifndef INC_LCD_H_
#define INC_LCD_H_
enum lcdType
{
	lcd4Bit,Lcd8Bit

};

#define lcdClear		0x01
#define lcdCursorOFF	0x0C
#define lcdCursorON		0x0E
#define lcdCursorBlink	0x0D
#define lcdCursorHome	0x02
#define lcdShiftRight	0x1C
#define lcdShiftLeft	0x18
#define lcdOFF			0x08


void lcdSetup(GPIO_TypeDef * lcdPort, uint16_t RS,uint16_t E,enum lcdType mode,uint16_t D0,uint16_t D1,uint16_t D2,uint16_t D3,uint16_t D4,uint16_t D5,uint16_t D6,uint16_t D7);
void lcdWrite(uint8_t data);
void lcdEnable(void);
void lcdCommand(uint8_t command);
void lcdInit(void);
void lcdChar(char character);
void lcdString(char * string);
void lcdSetCursor(uint8_t row, uint8_t col);
void lcdWriteInt(char * format, uint32_t number );
void lcdWriteFloat(char * format, double number );



#endif /* INC_LCD_H_ */
