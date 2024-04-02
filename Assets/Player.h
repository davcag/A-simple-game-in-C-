#pragma once

#include "D3DGraphics.h"
#include "Keyboard.h"
#include "Menu.h"

#define MAPHEIGHT 600


class Player
{
public:
	Player(D3DGraphics& gfx, KeyboardClient& kbd, GameState &state, bool &doubleJump);	
	void Run(int nRows);
	int GetPlayerX();
	int GetPlayerY();



private:
	void DrawPlayer();
	void MovePlayer();
	void StateChange();

private:
	int playerX;
	int playerY;
	int nRows;
	bool keyPressed;
	GameState* state;
	bool* doubleJump;


	D3DGraphics* gfx;
	KeyboardClient* kbd;
};