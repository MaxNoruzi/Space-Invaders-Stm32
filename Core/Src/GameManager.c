/*
 * Manager.c
 *
 *  Created on: Jan 28, 2023
 *      Author: mo_n1
 */
#include "GameManager.h"
#include "Lcd.h"
#include <main.h>
#include <stdlib.h>
#include <Buzzer.h>
extern UART_HandleTypeDef huart1;

void arrangeScreen(){
	if(screenMode ==PLAY){
		if(playScreenFirstTime){
			clear();
			playScreenFirstTime=0;
			if(gameMode ==BOSS)
			paintBoss();
		}
		if(playerMove!=NONE){
			movePlayerInBoard();
		}
			moveArrows();

switch (gameMode) {
	case EASY:
		if(timerTicked%25 ==0){
			moveEnemies();
		}
		break;
	case MEDIUM:
		if(timerTicked%15 ==0){

			moveEnemies();
		}
			break;
	case HARD:
		if(timerTicked%5 ==0){
			moveEnemies();
		}
			break;
	case BOSS:
		if(timerTicked%15 ==0){
			int randomNumber = rand() % 2;
			clearBoss();
			moveBoss(randomNumber);
			paintBoss();
			clearBoss();
			moveBoss(2);
			paintBoss();
			board[bossPosition[0]-2][bossPosition[1]].isEnemyArrow=1;
				}

	default:
		break;
}
		timerTicked++;
	}
	else if(screenMode ==GAMEINFO){
		if(screenAlreadyShowed==0){
			clear();
			screenAlreadyShowed=1;
		}
		showGameInfo();
	}
	else{
		if(screenAlreadyShowed==0){
			switch( screenMode )
					{
						case BEGIN:

								beginScreen();

								break;
						case MENU:
							showMenu();
							Start_Melody();

							break;
						case ENTERNAME:
							enterYourName();
						break;
						case OPTIONS:
							chooseDifficulty();
							break;

							break;
						case FINISH:
							finishScreen();
							break;
						default:

							break;
					}
			screenAlreadyShowed=1;
							}



	}

}

void keySelected(int selectedkey){

	switch( selectedkey )
	{
		case 1:
			if(screenMode !=PLAY)screenAlreadyShowed=0;
			switch( screenMode )
			{
				case BEGIN:

					screenMode =MENU;

						break;
				case MENU:
					Pause_Melody();
					screenMode =GAMEINFO;

					break;
				case GAMEINFO:
					screenMode =MENU;
					break;
				case ENTERNAME:
				screenMode =OPTIONS;
				break;
				case OPTIONS:
					gameMode = EASY;
					sprintf(data2,"game started in easy mode\n");
					HAL_UART_Transmit(&huart1, data2, 26 , 1000);
					playerDamage=7;
					screenMode =PLAY;
					playScreenFirstTime=1;
					break;
				case PLAY:
					playerMove=LEFT;
					break;
				case FINISH:
							//todo
					break;
				default:

					break;
			}

			break;
		case 2:
			if(screenMode !=PLAY)screenAlreadyShowed=0;
			switch( screenMode ){
			case MENU:
				Pause_Melody();
				screenMode =ENTERNAME;
				break;
			case OPTIONS:
				gameMode = MEDIUM;
				playerDamage=5;
				screenMode =PLAY;
				playScreenFirstTime=1;
				sprintf(data2,"game started in medium mode\n");
				HAL_UART_Transmit(&huart1, data2, 28 , 1000);
				break;
			case PLAY:
				board[1][playerPosition].isPlayerArrow=1;

				break;

			}
			break;
		case 3:
			if(screenMode !=PLAY)screenAlreadyShowed=0;
					switch( screenMode ){
					case OPTIONS:
						gameMode = HARD;
						playerDamage=3;
						screenMode =PLAY;
						playScreenFirstTime=1;
						sprintf(data2,"game started in hard mode\n");
						HAL_UART_Transmit(&huart1, data2, 26 , 1000);
						break;
					case PLAY:
						playerMove=RIGHT;
						break;

					}
			break;
		case 4:
			if(screenMode==OPTIONS){
				HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, 1);
				gameMode = BOSS;
				playerDamage=5;
				screenMode =PLAY;
				playScreenFirstTime=1;
				Boss_melody();
				sprintf(data2,"game started in boss mode\n");
				HAL_UART_Transmit(&huart1, data2, 26 , 1000);

			}
			break;
		default:

			break;
	}

}
void moveArrows(){
int seenArrows [8][2];
int count=0;
	for (int i = 0; i < 20; ++i) {
		for (int j = 0; j <4; ++j) {
			if (board[i][j].isPlayerArrow==1){
				for(int p=0 ;p<count;p++ ){
					if(seenArrows[p][0]==i && seenArrows[p][1]==j){
					goto firstLoop;
					}
				}
				setCursor(i, j);
				print(" ");
				if(i<19){
					setCursor(i+1, j);
					if(board[i+1][j].isEnemy){
						if(gameMode !=BOSS){
							board[i+1][j].isEnemy=0;
							print(" ");
							deadAliens++;
						}
						else {
							bossDamage--;
						}
						if(gameMode!=BOSS)
						Hit_Sound(1);

						sprintf(data2,"3 enemies left babe\n");
						switch (gameMode) {
						case EASY:
							if(15 -deadAliens ==3){
								HAL_UART_Transmit(&huart1, data2, 20 , 1000);
							}
							break;
						case MEDIUM:
							if(25 -deadAliens ==3){
								HAL_UART_Transmit(&huart1, data2, 20 , 1000);
							}
							break;
						case HARD:
							if(35 -deadAliens ==3){
								HAL_UART_Transmit(&huart1, data2, 20 , 1000);
							}
							break;


						}
						checkFinish();
					}
					else {
						write(2);
						board[i+1][j].isPlayerArrow=1;
						seenArrows[count][0]=i+1;
						seenArrows[count][1]=j;
						count++;
					}
				}
				board[i][j].isPlayerArrow=0;
			}
			else if(board[i][j].isEnemyArrow==1){
				for(int p=0 ;p<count;p++ ){
				if(seenArrows[p][0]==i && seenArrows[p][1]==j){
				goto firstLoop;
					}
				}
				setCursor(i, j);
				print(" ");
				if(i>0){
						setCursor(i-1, j);
						if((i-1) ==0 && playerPosition ==j ){
							playerDamage--;
							if(gameMode!=BOSS)
							Hit_Sound(0);
							if(playerDamage==1){
								sprintf(data2,"one shot and you are done\n");
								HAL_UART_Transmit(&huart1, data2, 26 , 1000);
							}
							checkFinish();
						}
						else{
							write(4);
							board[i-1][j].isEnemyArrow=1;
							seenArrows[count][0]=i+1;
							seenArrows[count][1]=j;
							count++;
						}
				}
				board[i][j].isEnemyArrow=0;
			}
			firstLoop:;
		}
	}
}
void movePlayerInBoard(){
	switch (playerMove) {
		case LEFT:
				setCursor(0, playerPosition);
				print(" ");
				if(playerPosition!=0){
					playerPosition--;

				}else{
					playerPosition=3;
				}
				setCursor(0, playerPosition);
									write(0);
					break;
		case RIGHT:
			setCursor(0, playerPosition);
			print(" ");
			if(playerPosition!=3){
					playerPosition++;
							}
			else{
				playerPosition=0;
			}
			setCursor(0, playerPosition);
			write(0);
					break;
		default:
			break;
	}
	playerMove=NONE;
}
void moveEnemies(){
	 int randomColoumn = rand() % 4;
	for (int i = 0; i < 4; i++) {
		for (int j = 19; j >=0; j--) {
			if (board[j][i].isEnemy!=1){
				if(board[j][i].isPlayerArrow){
					board[j][i].isPlayerArrow=0;
					setCursor(j, i);
					print(" ");
					deadAliens++;
				}
				else{
					if(j ==0){
						screenMode=FINISH;
						goto endOftwoLoop;
					}
					board[j][i].isEnemy=1;
					setCursor(j, i);
					write(1);
					if(i==randomColoumn){
						board[j-1][i].isEnemyArrow=1;
						setCursor(j-1, i);
						write(4);

					}
				}
				break;
		}
		}
}
endOftwoLoop:;
}
void checkFinish(){
	switch (gameMode) {
		case EASY:
			if((deadAliens>=15) || (playerDamage <=0)){
				playerWon=(deadAliens>=15);
				screenMode =FINISH;
			}
			break;
		case MEDIUM:
			if((deadAliens>=25) || (playerDamage <=0)){
				playerWon=(deadAliens>=15);
				screenMode =FINISH;
						}
		break;
		case HARD:
			if((deadAliens>=35) || (playerDamage <=0)){
				playerWon=(deadAliens>=15);
				screenMode =FINISH;
						}
		break;
		case BOSS:
			if((bossDamage<=0) || (playerDamage <=0)){
				playerWon=(bossDamage<=0);
				screenMode =FINISH;
			}
			break;
		default:
			break;
	}

}
void clearBoss(){
	board[bossPosition[0]][bossPosition[1]].isEnemy=0;
	setCursor(bossPosition[0], bossPosition[1]);
	print(" ");
	board[bossPosition[0]-1][bossPosition[1]].isEnemy=0;
	setCursor(bossPosition[0]-1, bossPosition[1]);
	print(" ");
	board[bossPosition[0]][bossPosition[1]-1].isEnemy=0;
	setCursor(bossPosition[0], bossPosition[1]-1);
	print(" ");
	board[bossPosition[0]][bossPosition[1]+1].isEnemy=0;
	setCursor(bossPosition[0], bossPosition[1]+1);
	print(" ");
	board[bossPosition[0]+1][bossPosition[1]].isEnemy=0;
	setCursor(bossPosition[0]+1, bossPosition[1]);
	print(" ");
}
void paintBoss(){
	board[bossPosition[0]][bossPosition[1]].isEnemy=1;
	setCursor(bossPosition[0], bossPosition[1]);
	write(1);
	board[bossPosition[0]-1][bossPosition[1]].isEnemy=1;
	setCursor(bossPosition[0]-1, bossPosition[1]);
	write(1);
	board[bossPosition[0]][bossPosition[1]-1].isEnemy=1;
	setCursor(bossPosition[0], bossPosition[1]-1);
	write(1);
	board[bossPosition[0]][bossPosition[1]+1].isEnemy=1;
	setCursor(bossPosition[0], bossPosition[1]+1);
	write(1);
	board[bossPosition[0]+1][bossPosition[1]].isEnemy=1;
	setCursor(bossPosition[0]+1, bossPosition[1]);
	write(1);
}
void moveBoss(int a){
	switch (a) {
		case 0:
			//right
			if(bossPosition[1]<2)
			bossPosition[1]++;
			break;
		case 1:
			//left
			if(bossPosition[1]>1)
			bossPosition[1]--;
			break;
		case 2:
			//down
			bossPosition[0]--;


			break;

		default:
			break;
	}





}
