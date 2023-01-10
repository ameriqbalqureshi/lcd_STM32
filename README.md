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
