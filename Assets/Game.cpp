/****************************************************************************************** 
 *	Chili DirectX Framework Version 12.10.21											  *	
 *	Game.cpp																			  *
 *	Copyright 2012 PlanetChili.net														  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "Game.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <float.h>

Game::Game( HWND hWnd,KeyboardServer& kServer,const MouseServer& mServer )
:	gfx( hWnd ),
	audio( hWnd ),
	kbd( kServer ),
	mouse( mServer ),
	state (MENU),
	upgrade(NOTHING),
	doubleJump(false),
	menu (gfx, mouse, state, upgrade, 250, 150),
	map (gfx),
	player(gfx,kbd,state, doubleJump),
	nLevels(6),
	nKills (5),
	nRows(3),
	nEnemies(2),
	maxTime(6.0f),
	nDeathSquares(0),
	deathSquare(NULL),
	enemy(gfx, state, kbd, upgrade, nKills, nEnemies, nRows, nLevels,maxTime, doubleJump),
	goCountdown(0.0f)
	
{
	srand((unsigned int) time(NULL));
}

Game::~Game()
{
	delete [] deathSquare;
	deathSquare=NULL;
}

void Game::Go()
{
	
	gfx.BeginFrame();
	ComposeFrame();
	gfx.EndFrame();

}

void Game::ComposeFrame()
{
	menu.Run();


	if (state == PLAY || state==WIN || state==CONTINUE || state == LOSE ||state==RESET || state == SHOP)
	{
		int playerX=player.GetPlayerX();
		int playerY=player.GetPlayerY();

		if (state==PLAY)
		{
			map.DrawMap(nRows, deathSquare);
		}

		if (state!=SHOP && state!=PLAY)
		{
			map.DrawFakeMap(nRows);
		}

		enemy.Run(playerX, playerY);

		if (!(state==SHOP))
		{
		player.Run(nRows);
		}
		
		if (state==RESET)
		{
			enemy.Reset(nKills);// resets everything back to original value
		}
		enemy.PrintStats();
		
		if (state==PLAY)
		{
			CheckDeathSquare();
		}

	}

	if (state==WIN)
	{
		menu.DrawText(100, 150,"YOU WON!!!",D3DCOLOR_XRGB(0,255,0));
	}
	else if (state == LOSE)
	{
		menu.DrawText(60, 150,"LOL YOU LOST!!!",D3DCOLOR_XRGB(255,0,0));
	}
	else if (state == FINISHED)
	{
		menu.DrawText(80, 150,"YOU FINISHED THE GAME!!!",D3DCOLOR_XRGB(0,255,0));
		menu.DrawText(-70, 200,"BUT I'M SURE YOU JUST GOT LUCKY THIS TIME!!!",D3DCOLOR_XRGB(0,255,0));
	}

	if (state==COUNTDOWN)
	{
		GoCountdown();
		enemy.PrintStats();
	}

	
	if (state == COUNTDOWN || state==WIN || state == LOSE ||state == FINISHED)
	{
		SetDeathSquare();
	}
	

}




void Game::GoCountdown()
{
	if (goCountdown==0.0f)
	{
		goTime.StartWatch();
	}

	goCountdown=goTime.GetTimeMilli()/1000.0f;

	if(goCountdown<1.0f)
	{
		LoadSprite(&Countdown, "Fonts\\3.bmp",190,80,D3DCOLOR(0x60));
		gfx.DrawSprite(205,205,&Countdown);
	}
	else if (goCountdown<2.0f)
	{
		LoadSprite(&Countdown, "Fonts\\2.bmp",190,80,D3DCOLOR(0x60));
		gfx.DrawSprite(205,205,&Countdown);
	}
	else if (goCountdown<3.0f)
	{
		LoadSprite(&Countdown, "Fonts\\1.bmp",190,80,(0x60));
		gfx.DrawSprite(205,205,&Countdown);
	}
	else if (goCountdown<4.0f)
	{
		LoadSprite(&Countdown, "Fonts\\GO!.bmp",190,80,D3DCOLOR(0x60));
		gfx.DrawSprite(205,205,&Countdown);
	}
	else if (goCountdown>4.0f)
	{
		goTime.StopWatch();	
		goCountdown=0.0f;
		state=PLAY; 
	} 

}


void Game::SetDeathSquare()
{
	if (state==WIN || state==LOSE)
	{
		delete [] deathSquare;
		deathSquare=NULL;
	}

	if (state==LOSE || state == FINISHED)
	{
		nDeathSquares=0;
	}


	if (state == COUNTDOWN && deathSquare == NULL)
	{
		nDeathSquares++;
		deathSquare= new bool [nRows*nRows];
		for (int i=0; i<nRows*nRows; i++)
		{
			deathSquare[i]=false;
		}

		for (int i=0; i<nDeathSquares; i++)
		{
			int x = rand() % (nRows*nRows);

			int playerIndex=player.GetPlayerX()+player.GetPlayerY()*nRows;

			if (deathSquare[x]==true || x==playerIndex)
			{
				i--;
			}
			else
			{
			deathSquare[x] = true;
			}
		}

		enemy.SetDeathSquare(deathSquare);

	}

}


void Game::CheckDeathSquare()
{
	int index = player.GetPlayerX() + player.GetPlayerY() * nRows;

	if (deathSquare[index]==true)
	{
		state=LOSE;
	}
}