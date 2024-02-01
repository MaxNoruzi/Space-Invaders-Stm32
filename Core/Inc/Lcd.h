/*
 * Lcd.h
 *
 *  Created on: Jan 23, 2023
 *      Author: mo_n1
 */

#ifndef INC_LCD_H_
#define INC_LCD_H_

void lcdInit();
void showString(char* str);
void beginScreen();
void showMenu();
void showGameInfo();
void enterYourName();
void chooseDifficulty();
void finishScreen();
#endif /* INC_LCD_H_ */
