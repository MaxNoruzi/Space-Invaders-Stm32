/*
 * Lcd.c
 *
 *  Created on: Jan 23, 2023
 *      Author: mo_n1
 */
#include "Lcd.h"
#include "Characters.h"
//#include "LiquidCrystal.h"
#include "main.h"
#include "TimeRtc.h"
#include "GameManager.h"
char timeStr[20];
char dateStr[30];
extern unsigned char data[20];
extern UART_HandleTypeDef huart1;
extern unsigned char data2[30];
void lcdInit(){

	 LiquidCrystal(GPIOD, GPIO_PIN_8, GPIO_PIN_9, GPIO_PIN_10, GPIO_PIN_11, GPIO_PIN_12, GPIO_PIN_13, GPIO_PIN_14);
	 begin(20, 4);
	 createChar(0, plane);
	 createChar(1, enemy);
	 createChar(2, arrow);
	 createChar(3, berserk);
	 createChar(4, enemyArrow);
	 screenMode=BEGIN;
}
void showString(char* str){
	print(str);
}
void beginScreen(){
	setCursor(0, 0);
		for(int i=0 ;i<20;i++){
			write(2);
		}
		 setCursor(0, 1);
		 print("SPACE INVADERS");
		 setCursor(0, 2);
		 for(int i=0 ;i<20;i++){
			 if(i%2==0)write(3);
			 else print(" ");
		 }
		 setCursor(0, 3);
		 for(int i=0 ;i<20;i++){
		 			 if(i%2!=0)write(3);
		 			 else  print(" ");
		 		 }
		 for (int positionCounter = 0; positionCounter < 5; positionCounter++) {
			 scrollDisplayRight();
			 		 HAL_Delay(350);
//			 		 scrollDisplayLeft();
		 		}
		 for (int positionCounter = 0; positionCounter < 5; positionCounter++) {
		 			// scroll one position left:
		 			scrollDisplayLeft();
		 			// wait a bit:
		 			HAL_Delay(350);
		 		}

}
void showMenu(){
	clear();
	setCursor(0, 0);
	print("you have 2 choices : ");
	setCursor(0, 1);
	print("Game Info -> 1 ");
	setCursor(0, 2);
	print("Begin The Game -> 2");

}
void showGameInfo(){
//	clear();
	setCursor(0, 0);
		print("MohammadH Noruzi ");
		setCursor(0, 1);
		print("AmirMahdi Chiti");
		setCursor(0, 2);
		updateTime();
		sprintf(timeStr, "%2d:%2d:%2d ", mytime.Hours, mytime.Minutes,
						mytime.Seconds);
		print(timeStr);
		sprintf(dateStr, "%d/%d/%d", mydate.Year, mydate.Month,
						mydate.Date);
		print(dateStr);
}
void enterYourName(){
	clear();
	setCursor(0, 0);
	print("Plz Enter Your Name:");
	setCursor(0, 1);
	print(data);


}
void chooseDifficulty(){

	clear();
	setCursor(0, 0);
	print("Easy -> 1");
	setCursor(0, 1);
	print("Medium -> 2 ");
	setCursor(0, 2);
	print("Hard -> 3");
	setCursor(0, 3);
	print("Boss -> A");
}
void finishScreen(){
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, 1);
	clear();
	setCursor(0, 0);
	HAL_UART_Transmit(&huart1, data, 9 , 1000);
	if(playerWon){
		sprintf(data2," you won with score :%d",deadAliens);
		HAL_UART_Transmit(&huart1, data2, 23 , 1000);
		print(data2);
	}
	else{
		sprintf(data2," you lost with score :%d",deadAliens);
		HAL_UART_Transmit(&huart1, data2, 24 , 1000);
		print(data2);
	}
	 for (int positionCounter = 0; positionCounter < 29; positionCounter++) {
			 scrollDisplayRight();
			 		 HAL_Delay(350);
//			 		 scrollDisplayLeft();
		 		}
		 for (int positionCounter = 0; positionCounter < 30; positionCounter++) {
		 			// scroll one position left:
		 			scrollDisplayLeft();
		 			// wait a bit:
		 			HAL_Delay(350);
		 		}

}
