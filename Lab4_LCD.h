/*
 * Lab4_LCD.h
 * Created on: Oct 21, 2013
 * Author: C15Colin.Busho
 * Version 1- Adapted from Capt Branchflower
 * Description- Functions to write on an LCD
 */

#ifndef LAB4_LCD_H_
#define LAB4_LCD_H_

void initSPI();

void LCDinit();

void LCDclear();

void cursorToLineTwo();

void cursorToLineOne();

void writeChar(char asciiChar);

void writeString(char string[], char stringLength);

void scrollString(char string[], char stringLength);

#endif /* LAB4_LCD_H_ */
