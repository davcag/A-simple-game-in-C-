#include "Enemy.h"
#include <cstdlib>
#include <time.h>

Enemy::Enemy(D3DGraphics &gfx, GameState &state, KeyboardClient &kbd, Upgrade &upgrade, int nKills, int &nEnemies, int &nRows, int nLevels, float maxTime, bool &doubleJump)
	:
	gfx(&gfx),
	state(&state),
	kbd(&kbd),
	nKills(nKills),
	nEnemies(&nEnemies),
	nRows(&nRows),
	nLevels(nLevels),
	aliveEnemies(0),
	eX(NULL),
	eY(NULL),
	enemyState(NULL),
	upgrade(&upgrade),
	killHolder(nKills),
	maxTime(maxTime),
	spacePressed(false),
	levelCounter(0),
	enemyIncrease(0),
	deathSquare(NULL)
	{
		LoadFont( &fixedSys,fontSurf,"Fonts\\fixedsys16x28.bmp",16,28,32 );

		SetShop(doubleJump);
		enemiesToDraw=nEnemies;
		srand((unsigned int)time(NULL));
		eX = new int [enemiesToDraw];
		eY = new int [enemiesToDraw];
		enemyState = new bool [nRows * nRows];
		eTime = new float [nRows * nRows];
		timer = new Timer [nRows * nRows];

		for (int i =0; i < nRows * nRows; i++)
		{
			enemyState[i]=false;
			eTime[i]=0.0f;
		}
	}

Enemy::~Enemy()
{
	delete [] eX;
	delete [] eY;
	delete [] enemyState;
	delete [] eTime;
	delete [] timer;
	eX=NULL;
	eY=NULL;
	enemyState=NULL;
	eTime = NULL;
	timer = NULL;
}

void Enemy::Run(int playerX, int playerY)
{
	this->playerX = playerX;
	this->playerY = playerY;
	
	if(*state==PLAY)
	{
	CreateEnemy();
	KillEnemy();
	CheckGameState();
	}
	
	else if(*state==CONTINUE)
	{
		if (levelCounter < nLevels-1)
		{
			NextLevel();
		}
		else
		{
			*state=FINISHED;
		}
	}
	else if (*state==SHOP)
	{
		RunShop(maxTime,*nEnemies,gfx,fixedSys, upgrade);
	}
}


void Enemy::CreateEnemy()
{
	//creates 1st enemies, other enemies are created in KillEnemy();
	for (; aliveEnemies<enemiesToDraw ; aliveEnemies++)
	{
		CreateEnemy(eX[aliveEnemies], eY[aliveEnemies]);
		StartTime(eX[aliveEnemies], eY[aliveEnemies]);
	}

	if (nKills != 0)
	{
		for (int i=0; i<enemiesToDraw; i++)
		{
			DrawEnemy(eX[i],eY[i]);
			PrintTime(eX[i],eY[i]);
		}
	}	
}

void Enemy::KillEnemy()
{	
	for (int i =0; i<enemiesToDraw; i++)
	{
		if (kbd->KeyIsPressed(VK_SPACE) && eX[i]==playerX && eY[i] == playerY && nKills!=0 && spacePressed==false)
		{
			nKills--;
			AddEnemyMoney(levelCounter);
			StopTime (eX[i], eY[i]);
			if(nKills!=0)
			{
			CreateEnemy(eX[i], eY[i]);
			}
			spacePressed=true;	
		}
		else if(!kbd->KeyIsPressed(VK_SPACE) && spacePressed==true)
		{
			spacePressed=false;
		}		
	}
}


void Enemy::CreateEnemy(int &eX, int &eY)
{
	eX= rand()%(*nRows);
	eY= rand()%(*nRows);

	int index= eX+eY* (*nRows);

	if(!GetEnemyState(eX, eY) && deathSquare[index]==false )
	{
		SetEnemyState(eX, eY, true);
		StartTime(eX, eY);
	}
	else
	{
		CreateEnemy(eX, eY); // if the place is taken repeat
	}
}

void Enemy::NextLevel()
{
	levelCounter++;
	killHolder+=5; // nKills always goes back to 0 so this is how i increase it for each level
	enemyIncrease+=3;
	if ((enemyIncrease+*nEnemies)<1)
	{
		enemiesToDraw=1;
	}
	else
	{
		enemiesToDraw=enemyIncrease+*nEnemies;
	}
	(*nRows)++;
	nKills=killHolder;
	aliveEnemies=0;


	eX = new int [enemiesToDraw];
	eY = new int [enemiesToDraw];
	enemyState = new bool [(*nRows) * (*nRows)];
	eTime = new float [(*nRows) * (*nRows)];
	timer = new Timer [(*nRows) * (*nRows)];

	for (int i =0; i < (*nRows) * (*nRows); i++)
	{
		enemyState[i]=false;
		eTime[i]=0.0f;
	}

	*state=COUNTDOWN; 

}

void Enemy::CheckGameState()
{
	for (int i=0; i<(*nRows) * (*nRows); i++)
	{
		if (eTime[i] > maxTime)
		{
			*state=LOSE;
			delete [] eX;
			delete [] eY;
			delete [] enemyState;
			delete [] eTime;
			delete [] timer;
			eX=NULL;
			eY=NULL;
			enemyState=NULL;
			eTime = NULL;
			timer = NULL;
			break; // fucks up if i dont break because it keeps checking stuff i deleted
		}
	}


	if (nKills==0) // after all enemies are killed delete everything
	{
		AddLevelMoney(levelCounter);
		*state= WIN;
		delete [] eX;
		delete [] eY;
		delete [] enemyState;
		delete [] eTime;
		delete [] timer;
		eX=NULL;
		eY=NULL;
		enemyState=NULL;
		eTime = NULL;
		timer = NULL;
		
	}
}


void Enemy::Reset(int nKills)
{
	// reset everything to original value and change state to PLAY
	this->nKills=nKills;
	killHolder = nKills;
	
	if ((*nEnemies)<1)
	{
		enemiesToDraw=1;
	}
	else
	{
		enemiesToDraw=*nEnemies;
	}


	this->nEnemies=nEnemies;
	*nRows = (*nRows) - levelCounter;
	levelCounter=0;
	aliveEnemies=0;
	enemyIncrease=0;
	

	eX = new int [enemiesToDraw];
	eY = new int [enemiesToDraw];
	enemyState = new bool [(*nRows) * (*nRows)];
	eTime = new float [(*nRows) * (*nRows)];
	timer = new Timer [(*nRows) * (*nRows)];

	for (int i =0; i < (*nRows) * (*nRows); i++)
	{
		enemyState[i]=false;
		eTime[i]=0.0f;
	}

	*state=COUNTDOWN; 
}

void Enemy::DrawEnemy(int eX, int eY)
{
	const int size = MAPHEIGHT/ (*nRows);
	const int midPoint = size/2;
	const int rad=size*3/10;

	int index = eX + eY * (*nRows);
	int x = 256/maxTime; //if i multiply with this it should work even if the max time changes  
	
	
	gfx->DrawDisc(eX*size+midPoint,eY*size+midPoint,rad, 0+eTime[index]*x,255-eTime[index]*x,0);
}

void Enemy::SetEnemyState(int eX, int eY, bool state)
{
	int index = eX + eY * (*nRows);
	enemyState[index]=state;
}

bool Enemy::GetEnemyState(int eX, int eY)
{
	int index = eX + eY * (*nRows);
	return enemyState[index];
}




void Enemy::PrintTime(int eX, int eY)
{
	int index = eX + eY * (*nRows);
	const int size = MAPHEIGHT/ (*nRows);
	const int offset = size/40;

	float printTime = 0.0f;
	eTime[index] = timer[index].GetTimeMilli() / 1000.0f;
	
	if (maxTime > eTime[index]) // if timer goes less than 0 just print 0
	{
	printTime = maxTime - eTime[index];
	}


	char buffer[64];
	sprintf(buffer,"%.2f",printTime);
	gfx->DrawString(buffer,eX * size+offset,eY * size +offset,&fixedSys,D3DCOLOR_XRGB(255,255,255));
}


void Enemy::StartTime(int eX, int eY)
{
	int index = eX + eY * (*nRows);
	timer[index].StartWatch();
}


void Enemy::StopTime(int eX, int eY)
{
	int index = eX + eY * (*nRows);
	timer[index].StopWatch();
	eTime[index]=0.0f;
}

void Enemy::PrintStats()
{
	char buffer1[64];
	sprintf(buffer1,"Money:%d",GetMoney());
	gfx->DrawString(buffer1,600,10,&fixedSys,D3DCOLOR_XRGB(255,255,255));

	char buffer2[64];
	sprintf(buffer2,"Level:%d",levelCounter+1);
	gfx->DrawString(buffer2,600,50,&fixedSys,D3DCOLOR_XRGB(255,255,255));

	char buffer3[64];
	sprintf(buffer3,"Enemies:%d",nKills);
	gfx->DrawString(buffer3,600,90,&fixedSys,D3DCOLOR_XRGB(255,255,255));
}


void Enemy::SetDeathSquare(bool* deathSquare)
{
	this->deathSquare=deathSquare;
}