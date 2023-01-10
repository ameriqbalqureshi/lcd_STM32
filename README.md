# lcd_STM32
STM32 Library for Character LCD HD44780 both 4 and 8 bits modes
HD44780 character LCD is one of the most common LCD used by hobbyists and prototype engineering projects. One of reasons behind this is easy interfacing and widespread availability. Driving the LCD needs some LCD specific commands and procedures that are usually implemented as middleware in the form of a Library or a driver. Many popular compilers and integrated development environments usually bundle a library with their package as value added includes. However, many professional type IDEs like CubeIDE for STM32 does not provide such a library with its package. Most developers therefore have to get it from third parties (like this one) or write their own.
The library consists of two files:
1.	Lcd.c
2.	Lcd.h
You need to import or copy these files into your project folder. In STM32CubeIDE project folder the lcd.c file should be imported into src folder:
<your project>\Core\Src
And the lcd.h file into:
<tour project>\Core\Inc
Once these are copied the Library and its functions are accessed by including the lcd.h file in the source code.
Example Code:
lcdSetup(GPIOA, GPIO_PIN_8, GPIO_PIN_9,lcd4Bit, 0, 0, 0, 0, GPIO_PIN_4, GPIO_PIN_5, GPIO_PIN_6, GPIO_PIN_7);
lcdInit();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  lcdCommand(lcdClear);
	  lcdString("**MIKROTRONICS**");
	  lcdSetCursor(1, 3);
	  lcdString("LCD Library");
	  HAL_Delay(3000);
	  lcdCommand(lcdClear);
	  lcdString("Int Numbers:");
	  for(int i=0; i< 20;i++)
	  {
		  lcdSetCursor(1, 0);lcdWriteInt("%d", i);
		  lcdSetCursor(1, 3);lcdWriteInt("%02d", i);
		  lcdSetCursor(1,6);lcdWriteInt("%03d",i-20);
		  lcdSetCursor(1, 10);lcdWriteInt("0X%X", i);
		  HAL_Delay(500);
	  }
	  lcdCommand(lcdClear);
	  lcdString("Float Cursor OFF");
	  lcdCommand(lcdCursorOFF);
	  for(float i=0;i<3;i+=0.1)
	  {
		  lcdSetCursor(1, 0);lcdWriteFloat("%f", i);
		  lcdSetCursor(1, 10);lcdWriteFloat("%1.2f",i);
		  HAL_Delay(200);
	  }
	  lcdCommand(lcdClear);
	  lcdString("Screen Shift");
	  lcdSetCursor(1, 0);lcdString("A Quick Brown Fox Jumps over the Lazy Dog");
	  HAL_Delay(500);
	  for(int i=0;i<32;i++)
	  {
		  lcdCommand(lcdShiftLeft);
		  HAL_Delay(300);
	  }

