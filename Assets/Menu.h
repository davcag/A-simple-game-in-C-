#pragma once
#include "D3DGraphics.h"
#include "Mouse.h"



#define MITEMWIDTH 300
#define MITEMHEIGHT 50
#define BACKWIDTH 150
#define YNWIDTH 75
#define MITEMCOLOR (D3DCOLOR_XRGB(255,255,0))
#define TEXTOFFX  122
#define TEXTOFFY  12

enum GameState
{
	MENU,
	PLAY,
	OPTIONS,
	QUIT,
	WIN,
	LOSE,
	CONTINUE,
	RESET,
	FINISHED,
	SHOP,
	COUNTDOWN
};

enum Upgrade
{
	TIMEUP,
	ENEMYDOWN,
	DOUBLEJUMP,
	NOTHING
};




class Menu
{
public:
	Menu(D3DGraphics &gfx,MouseClient& mouse, GameState& state, Upgrade &upgrade, const int xIn, const int yIn  );
	void Run();
	void DrawText(int x, int y, const char* string, D3DCOLOR color );
	
private:
	void DrawMenu();
	void StateChange();
	void MouseCheck();
private:
	const int xIn;
	const int yIn;
	D3DGraphics* gfx;
	MouseClient* mouse;
	Font fixedSys;
	D3DCOLOR fontSurf[ 512 * 84 ];
	
	D3DCOLOR inactiveButton; // collor for option buttons;
	D3DCOLOR activeButton;
	bool button[3]; // checking if mouse is over buttons

	GameState* state;
	Upgrade* upgrade;

	bool leftPressed;
	bool upgradeState;

	bool win;
	bool lose;
	bool finished;
};