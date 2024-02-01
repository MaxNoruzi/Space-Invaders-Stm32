/*
 * Manager.h
 *
 *  Created on: Jan 28, 2023
 *      Author: mo_n1
 */

#ifndef INC_GAMEMANAGER_H_
#define INC_GAMEMANAGER_H_
enum Screen {
  BEGIN,
  MENU,
  GAMEINFO,
  ENTERNAME,
  OPTIONS,
  PLAY,
  FINISH
};
enum GameMode{
EASY,
MEDIUM,
HARD,
BOSS
};
enum MovePlayer{
	NONE,
	RIGHT,
	LEFT
};
struct BoardUnit{
	int isEnemy;
	int isPlayerArrow;
	int isEnemyArrow;
	int damage;
};
enum GameMode gameMode;
enum Screen screenMode;
enum MovePlayer playerMove;
int playerPosition;
int bossPosition[2];
int bossDamage;
int screenAlreadyShowed;
int playScreenFirstTime;
int timerTicked;
int deadAliens;
int playerDamage;
int playerWon;
struct BoardUnit board[20][4];
unsigned char data2[30];
void arrangeScreen();
void keySelected(int selectedkey);
void clearBoss();
void paintBoss();
void moveBoss(int a);
#endif /* INC_GAMEMANAGER_H_ */
