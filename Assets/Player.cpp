#include "Player.h"

Player::Player(D3DGraphics& gfx, KeyboardClient &kbd, GameState &state, bool &doubleJump)
	:
	gfx(&gfx),
	kbd(&kbd),
	playerX(0),
	playerY(0),
	keyPressed(false),
	state(&state),
	doubleJump(&doubleJump)
{
}


void Player::Run(int nRows)
{
	if(*state == RESET)
	{
		StateChange(); // just moves x and y back to 0 because the map will resize
	}

	this->nRows=nRows;
	DrawPlayer();
	MovePlayer();
	
}

void Player::DrawPlayer()
{
	const int size = MAPHEIGHT/nRows;

	const int midPoint = size/2;
	const int height = size/30;


	for (int i = midPoint-height; i<=midPoint+height;i++)
	{
		for (int j=height; j < size-height; j++)
		{
			if(j<midPoint-height*2)
			{
				gfx->PutPixel(playerX*size+j, playerY*size+i, D3DCOLOR_XRGB(255,130,0));
			}
			else if (j>midPoint - height-1 && j < midPoint +height+1)
			{
				gfx->PutPixel(playerX*size+j, playerY*size+i, D3DCOLOR_XRGB(255,130,0));
			}
			else if (j > midPoint +height*2)
			{
				gfx->PutPixel(playerX*size+j, playerY*size+i, D3DCOLOR_XRGB(255,130,0));
			}

			if (j <midPoint-height*2)
			{
				gfx->PutPixel(playerX*size+i, playerY*size+j, D3DCOLOR_XRGB(255,130,0));
			}
			else if (j > midPoint+height*2)
			{
				gfx->PutPixel(playerX*size+i, playerY*size+j, D3DCOLOR_XRGB(255,130,0));
			}

		}
	}
}


void Player::MovePlayer()
{
	// Normal movement
	if(kbd->KeyIsPressed(VK_UP) && playerY !=0 && !keyPressed && (!kbd->KeyIsPressed('N') || *doubleJump==false ))
	{
		playerY--;
		keyPressed = true;
	}
	else if(kbd->KeyIsPressed(VK_DOWN) && playerY !=nRows-1 && !keyPressed && (!kbd->KeyIsPressed('N') || *doubleJump==false ))
	{
		playerY++;
		keyPressed = true;
	}
	else if(kbd->KeyIsPressed(VK_LEFT) && playerX !=0 && !keyPressed && (!kbd->KeyIsPressed('N') || *doubleJump==false ))
	{
		playerX--;
		keyPressed = true;
	}
	else if(kbd->KeyIsPressed(VK_RIGHT) && playerX !=nRows-1 && !keyPressed && (!kbd->KeyIsPressed('N') || *doubleJump==false ))
	{
		playerX++;
		keyPressed = true;
	}
	
	// Double Jump
	else if(kbd->KeyIsPressed(VK_UP) && playerY !=0 && !keyPressed && kbd->KeyIsPressed('N') && *doubleJump==true)
	{
		playerY-=2;
		if(playerY<0)
		{
			playerY=0;
		}
		keyPressed = true;
	}
	else if(kbd->KeyIsPressed(VK_DOWN) && playerY !=nRows-1 && !keyPressed && kbd->KeyIsPressed('N') && *doubleJump==true)
	{
		playerY+=2;
		if(playerY>nRows)
		{
			playerY=nRows;
		}
		keyPressed = true;
	}
	else if(kbd->KeyIsPressed(VK_LEFT) && playerX !=0 && !keyPressed && kbd->KeyIsPressed('N') && *doubleJump==true)
	{
		playerX-=2;
		if(playerX<0)
		{
			playerX=0;
		}
		keyPressed = true;
	}
	else if(kbd->KeyIsPressed(VK_RIGHT) && playerX !=nRows-1 && !keyPressed && kbd->KeyIsPressed('N') && *doubleJump==true)
	{
		playerX+=2;
		if(playerX>nRows)
		{
			playerX=nRows;
		}
		keyPressed = true;
	}
	else if (!kbd->KeyIsPressed(VK_UP) && !kbd->KeyIsPressed(VK_DOWN) && 
			!kbd->KeyIsPressed(VK_LEFT) && !kbd->KeyIsPressed(VK_RIGHT))
	{
		keyPressed = false;
	}
	 

}

void Player::StateChange()
{
	playerX=0;
	playerY=0;
}


int Player::GetPlayerX()
{
	return playerX;
}

int Player::GetPlayerY()
{
	return playerY;
}

