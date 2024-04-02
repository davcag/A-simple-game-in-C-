#pragma once

#include "D3DGraphics.h"
#include "Keyboard.h"
#include "Player.h"
#include "Menu.h"
#include "EnemyTimer.h"
#include "Timer.h"
#include "Shop.h"

#define MAPHEIGHT 600

class Enemy: public Shop
{
public:
	Enemy(D3DGraphics &gfx, GameState &state, KeyboardClient &kbd, Upgrade &upgrade, int nKills, int &nEnemies, int &nRows, int nLevels, float maxTime, bool &doubleJump);
	~Enemy();
	void Run ( int playerX, int playerY);
	void Reset (int nKills);
	void PrintStats();
	void SetDeathSquare(bool* deathSquare);

private:
	void DrawEnemy(int eX, int eY);
	void CreateEnemy();
	void KillEnemy();
	void SetEnemyState(int eX, int eY, bool state);
	bool GetEnemyState(int eX, int eY);
	void CreateEnemy(int &eX, int &eY);
	void NextLevel();
	void CheckGameState();
	void PrintTime(int eX, int eY);
	void StartTime(int eX, int eY);
	void StopTime(int eX, int eY);
	

private:
	int aliveEnemies;
	int *nEnemies;
	int *nRows;
	int nLevels;
	int nKills;
	int playerX;
	int playerY;
	int* eX;
	int* eY;
	bool* enemyState;
	int levelCounter;
	int enemiesToDraw;
	int enemyIncrease;
	
	GameState* state;
	Upgrade* upgrade;
	int killHolder;
	bool spacePressed;

	bool* deathSquare;


	float *eTime;
	float maxTime;
	Timer *timer;
	


	D3DGraphics* gfx;
	KeyboardClient* kbd;



	// font stuff
	Font fixedSys;
	D3DCOLOR fontSurf[ 512 * 84 ];
};