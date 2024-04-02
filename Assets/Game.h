/****************************************************************************************** 
 *	Chili DirectX Framework Version 12.10.21											  *	
 *	Game.h																				  *
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
#pragma once


#include "D3DGraphics.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Sound.h"
#include "Timer.h"
#include "FrameTimer.h"
#include "Menu.h"
#include "Map.h"
#include "Player.h"
#include "Enemy.h"




class Game
{
public:
	Game( HWND hWnd,KeyboardServer& kServer,const MouseServer& mServer );
	~Game();
	void Go();
private:
	void ComposeFrame();

	void GoCountdown();
	void SetDeathSquare();
	void CheckDeathSquare();


private:
	D3DGraphics gfx;
	KeyboardClient kbd;
	MouseClient mouse;
	DSound audio;
	
	GameState state;
	Upgrade upgrade;
	
	int nRows;
	int nKills;
	int nEnemies;
	int nLevels;
	float maxTime;
	bool doubleJump;

	Timer goTime;
	float goCountdown;
	Sprite Countdown;

	bool* deathSquare;
	int nDeathSquares;


	Menu menu;
	Enemy enemy;
	Player player;
	Map map;




};