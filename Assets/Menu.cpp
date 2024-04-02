#include "Menu.h"


Menu::Menu(D3DGraphics &gfx, MouseClient &mouse, GameState& state, Upgrade &upgrade, const int xIn, const int yIn )
	:
	xIn(xIn),
	yIn(yIn),
	gfx(&gfx),
	mouse(&mouse),
	state (&state),
	upgrade (&upgrade),
	inactiveButton (D3DCOLOR_XRGB(0,0,0)),
	activeButton (D3DCOLOR_XRGB(255,0,0)),
	leftPressed(false),
	win(false),
	lose(false),
	finished(false),
	upgradeState(false)
	{
		LoadFont(&fixedSys,fontSurf, "Fonts\\Fixedsys16x28.bmp",16,28,32);	
	}




void Menu::Run()
{
	DrawMenu();
	StateChange();
	MouseCheck();
}

void Menu::DrawMenu()
{
	if (*state == MENU)
	{
		// play button
		for (int y=0; y < MITEMHEIGHT; y++)
		{
			for (int x=0; x<MITEMWIDTH; x++)
			{
				gfx->PutPixel(xIn+x,yIn+y,MITEMCOLOR);
			}
		}

		// check if mouse is over button
		if(mouse->GetMouseX() > xIn && mouse->GetMouseX() < xIn+MITEMWIDTH &&
			mouse->GetMouseY() > yIn && mouse->GetMouseY() < yIn+MITEMHEIGHT)
		{
			DrawText(xIn, yIn,"PLAY",activeButton);
		}
		else
		{
			DrawText(xIn, yIn,"Play",inactiveButton);
		}



		// options button;
		for (int y=0; y < MITEMHEIGHT; y++)
		{
			for (int x=0; x<MITEMWIDTH; x++)
			{
				gfx->PutPixel(xIn+x,yIn+y+100,MITEMCOLOR);
			}
		}
		if(mouse->GetMouseX() > xIn && mouse->GetMouseX() < xIn+MITEMWIDTH &&
			mouse->GetMouseY() > yIn+100 && mouse->GetMouseY() < yIn+MITEMHEIGHT+100)
		{
			DrawText(xIn-22, yIn+100,"OPTIONS",activeButton);
		}
		else
		{
			DrawText(xIn-22, yIn+100,"Options",inactiveButton);
		}


		// quit button
		for (int y=0; y < MITEMHEIGHT; y++)
		{
			for (int x=0; x<MITEMWIDTH; x++)
			{
				gfx->PutPixel(xIn+x,yIn+y+200,MITEMCOLOR);
			}
		}
		if(mouse->GetMouseX() > xIn && mouse->GetMouseX() < xIn+MITEMWIDTH &&
			mouse->GetMouseY() > yIn+200 && mouse->GetMouseY() < yIn+MITEMHEIGHT+200)
		{
			DrawText(xIn, yIn+200,"QUIT",activeButton);
		}
		else
		{
			DrawText(xIn, yIn+200,"Quit",inactiveButton);
		}
	}
	else if(*state==PLAY || *state==WIN || *state==LOSE || *state == FINISHED)
	{
		
		// back button
		for (int y=0; y < MITEMHEIGHT; y++)
		{
			for (int x=0; x<BACKWIDTH; x++)
			{
				gfx->PutPixel(xIn+x+385,yIn+y+385,MITEMCOLOR);
			}
		}

		if(mouse->GetMouseX() > xIn+385 && mouse->GetMouseX() < xIn+ 385 +BACKWIDTH &&
			mouse->GetMouseY() > yIn+385 && mouse->GetMouseY() < yIn+ 385 +MITEMHEIGHT)
		{
			DrawText(xIn+305, yIn+385,"BACK",activeButton);
		}
		else
		{
			DrawText(xIn+305, yIn+385,"Back",inactiveButton);
		}


		// continue button
		if(*state==WIN)
		{	
			// continue button
			for (int y=0; y < MITEMHEIGHT; y++)
			{
				for (int x=0; x<BACKWIDTH; x++)
				{
					gfx->PutPixel(xIn+x+385,yIn+y+315,MITEMCOLOR);
				}
			}

		
			if(mouse->GetMouseX() > xIn+385 && mouse->GetMouseX() < xIn+ 385 +BACKWIDTH &&
				mouse->GetMouseY() > yIn+315 && mouse->GetMouseY() < yIn+ 315 +MITEMHEIGHT)
			{
				DrawText(xIn+275, yIn+315,"CONTINUE",activeButton);
			}
			else
			{
				DrawText(xIn+275, yIn+315,"Continue",inactiveButton);
			}

			// shop button
			for (int y=0; y < MITEMHEIGHT; y++)
			{
				for (int x=0; x<BACKWIDTH; x++)
				{
					gfx->PutPixel(xIn+x+385,yIn+y+245,MITEMCOLOR);
				}
			}

			if(mouse->GetMouseX() > xIn+385 && mouse->GetMouseX() < xIn+ 385 +BACKWIDTH &&
				mouse->GetMouseY() > yIn+245 && mouse->GetMouseY() < yIn+ 245 +MITEMHEIGHT)
			{
				DrawText(xIn+307, yIn+245,"SHOP",activeButton);
			}
			else
			{
				DrawText(xIn+307, yIn+245,"Shop",inactiveButton);
			}

		}
		else if(*state==LOSE ||*state == FINISHED) 
		{
			

			// reset button
			for (int y=0; y < MITEMHEIGHT; y++)
			{
				for (int x=0; x<BACKWIDTH; x++)
				{
					gfx->PutPixel(xIn+x+385,yIn+y+315,MITEMCOLOR);
				}
			}

		
			if(mouse->GetMouseX() > xIn+385 && mouse->GetMouseX() < xIn+ 385 +BACKWIDTH &&
				mouse->GetMouseY() > yIn+315 && mouse->GetMouseY() < yIn+ 315 +MITEMHEIGHT)
			{
				DrawText(xIn+300, yIn+315,"RESET",activeButton);
			}
			else
			{
				DrawText(xIn+300, yIn+315,"Reset",inactiveButton);
			}


			// shop button
			for (int y=0; y < MITEMHEIGHT; y++)
			{
				for (int x=0; x<BACKWIDTH; x++)
				{
					gfx->PutPixel(xIn+x+385,yIn+y+245,MITEMCOLOR);
				}
			}

			if(mouse->GetMouseX() > xIn+385 && mouse->GetMouseX() < xIn+ 385 +BACKWIDTH &&
				mouse->GetMouseY() > yIn+245 && mouse->GetMouseY() < yIn+ 245 +MITEMHEIGHT)
			{
				DrawText(xIn+307, yIn+245,"SHOP",activeButton);
			}
			else
			{
				DrawText(xIn+307, yIn+245,"Shop",inactiveButton);
			}
		}

	}
	else if (*state == OPTIONS)
	{
		// text
		DrawText(xIn-200, yIn,"YOUR ONLY OPTION IS RETREAT!!!",inactiveButton);
		// back button
		for (int y=0; y < MITEMHEIGHT; y++)
		{
			for (int x=0; x<BACKWIDTH; x++)
			{
				gfx->PutPixel(xIn+x+385,yIn+y+385,MITEMCOLOR);
			}
		}

		if(mouse->GetMouseX() > xIn+385 && mouse->GetMouseX() < xIn+ 385 +BACKWIDTH &&
			mouse->GetMouseY() > yIn+385 && mouse->GetMouseY() < yIn+ 385 +MITEMHEIGHT)
		{
			DrawText(xIn+305, yIn+385,"BACK",activeButton);
		}
		else
		{
			DrawText(xIn+305, yIn+385,"Back",inactiveButton);
		}
		//
	}
	else if (*state == QUIT)
	{
		DrawText(xIn-200, yIn,"ARE YOU SURE YOU WANT TO QUIT?",inactiveButton);
		

		//yes
		for (int y=0; y < MITEMHEIGHT; y++)
		{
			for (int x=0; x < YNWIDTH; x++)
			{
				gfx->PutPixel(xIn+x+50,yIn+y+80,MITEMCOLOR);
			}
		}

		if(mouse->GetMouseX() > xIn+50 && mouse->GetMouseX() < xIn + 50 +YNWIDTH &&
			mouse->GetMouseY() > yIn+80 && mouse->GetMouseY() < yIn+ 80 +MITEMHEIGHT)
		{
			DrawText(xIn-58, yIn+80,"YES",activeButton);
		}
		else
		{
			DrawText(xIn-58, yIn+80,"yes",inactiveButton);	
		}
	

	//no
		for (int y=0; y < MITEMHEIGHT; y++)
		{
			for (int x=0; x<YNWIDTH; x++)
			{
				gfx->PutPixel(xIn+x+170,yIn+y+80,MITEMCOLOR);
			}
		}
		if(mouse->GetMouseX() > xIn+170 && mouse->GetMouseX() < xIn + 170 +YNWIDTH &&
			mouse->GetMouseY() > yIn+80 && mouse->GetMouseY() < yIn+ 80 +MITEMHEIGHT)
		{
			DrawText(xIn+69, yIn+80,"NO",activeButton);
		}
		else
		{
			DrawText(xIn+69, yIn+80,"no",inactiveButton);	
		}

		DrawText(xIn+333, yIn+410,"pls no",inactiveButton);
	}
	else if (*state == SHOP)
	{
		// time++
		for (int y=0; y < MITEMHEIGHT; y++)
		{
			for (int x=0; x<MITEMWIDTH; x++)
			{
				gfx->PutPixel(xIn+x,yIn+y,MITEMCOLOR);
			}
		}
		if(mouse->GetMouseX() > xIn && mouse->GetMouseX() < xIn+MITEMWIDTH &&
			mouse->GetMouseY() > yIn && mouse->GetMouseY() < yIn+MITEMHEIGHT)
		{
			DrawText(xIn-120, yIn,"TIME++",activeButton);
		}
		else
		{
			DrawText(xIn-120, yIn,"Time++",inactiveButton);
		}


		// Enemy--
		for (int y=0; y < MITEMHEIGHT; y++)
		{
			for (int x=0; x<MITEMWIDTH; x++)
			{
				gfx->PutPixel(xIn+x,yIn+y+75,MITEMCOLOR);
			}
		}
		if(mouse->GetMouseX() > xIn && mouse->GetMouseX() < xIn+MITEMWIDTH &&
			mouse->GetMouseY() > yIn+75 && mouse->GetMouseY() < yIn+MITEMHEIGHT+75)
		{
			DrawText(xIn-120, yIn+75,"ENEMY--",activeButton);
		}
		else
		{
			DrawText(xIn-120, yIn+75,"Enemy--",inactiveButton);
		}

		// Double jump
		for (int y=0; y < MITEMHEIGHT; y++)
		{
			for (int x=0; x<MITEMWIDTH; x++)
			{
				gfx->PutPixel(xIn+x,yIn+y+150,MITEMCOLOR);
			}
		}
		if(mouse->GetMouseX() > xIn && mouse->GetMouseX() < xIn+MITEMWIDTH &&
			mouse->GetMouseY() > yIn+150 && mouse->GetMouseY() < yIn+MITEMHEIGHT+150)
		{
			DrawText(xIn-120, yIn+150,"DOUBLE JUMP",activeButton);
			DrawText(xIn-120, yIn+200,"If the \"N\" key is pressed",D3DCOLOR_XRGB(0,0,0));
			DrawText(xIn-120, yIn+250,"the player moves 2 places",D3DCOLOR_XRGB(0,0,0));
		}
		else
		{
			DrawText(xIn-120, yIn+150,"Double jump",inactiveButton);
		}

		// back button
		for (int y=0; y < MITEMHEIGHT; y++)
		{
			for (int x=0; x<BACKWIDTH; x++)
			{
				gfx->PutPixel(xIn+x+385,yIn+y+385,MITEMCOLOR);
			}
		}

		if(mouse->GetMouseX() > xIn+385 && mouse->GetMouseX() < xIn+ 385 +BACKWIDTH &&
			mouse->GetMouseY() > yIn+385 && mouse->GetMouseY() < yIn+ 385 +MITEMHEIGHT)
		{
			DrawText(xIn+305, yIn+385,"BACK",activeButton);
		}
		else
		{
			DrawText(xIn+305, yIn+385,"Back",inactiveButton);
		}
	}
	
}

void Menu::StateChange()
{
	if (*state == MENU)
	{
		if(mouse->GetMouseX() > xIn && mouse->GetMouseX() < xIn+MITEMWIDTH &&
			mouse->GetMouseY() > yIn && mouse->GetMouseY() < yIn+MITEMHEIGHT && 
			mouse->LeftIsPressed() && !leftPressed)
		{
			if (win == true)
			{
				*state = WIN;
				win = false;
			}
			else if (lose == true)
			{
				*state = LOSE;
				lose = false;
			}
			else if (finished == true)
			{
				*state = FINISHED;
				finished = false;
			}
			else
			{
			*state = COUNTDOWN;
			}
		}
		if(mouse->GetMouseX() > xIn && mouse->GetMouseX() < xIn+MITEMWIDTH &&
			mouse->GetMouseY() > yIn+100 && mouse->GetMouseY() < yIn+MITEMHEIGHT+100 && 
			mouse->LeftIsPressed() && !leftPressed)
		{
			*state = OPTIONS;
		}
		if(mouse->GetMouseX() > xIn && mouse->GetMouseX() < xIn+MITEMWIDTH &&
			mouse->GetMouseY() > yIn+200 && mouse->GetMouseY() < yIn+MITEMHEIGHT+200 && 
			mouse->LeftIsPressed() && !leftPressed)
		{
			*state = QUIT;
		}

	}
	else if (*state == PLAY || *state == WIN ||*state == LOSE || *state == FINISHED)
	{
		if(mouse->GetMouseX() > xIn+385 && mouse->GetMouseX() < xIn+ 385 +BACKWIDTH &&
			mouse->GetMouseY() > yIn+385 && mouse->GetMouseY() < yIn+ 385 +MITEMHEIGHT && 
			mouse->LeftIsPressed() && !leftPressed)
		{
			if (*state==WIN)
			{
				win=true;
			}
			else if (*state==LOSE)
			{
				lose=true;
			}
			else if (*state == FINISHED)
			{
				finished=true;
			}

			*state = MENU;

		}
		if (*state == WIN || *state == LOSE || *state == FINISHED)
		{
			// continue
			if (*state==WIN)
			{
				if(mouse->GetMouseX() > xIn+385 && mouse->GetMouseX() < xIn+ 385 +BACKWIDTH &&
				   mouse->GetMouseY() > yIn+315 && mouse->GetMouseY() < yIn+ 315 +MITEMHEIGHT && 
				   mouse->LeftIsPressed() && !leftPressed)
				{
					*state=CONTINUE;
				}
			}

	
			//RESET
			if (*state == LOSE || *state == FINISHED)
			{
				if(mouse->GetMouseX() > xIn+385 && mouse->GetMouseX() < xIn+ 385 +BACKWIDTH &&
				   mouse->GetMouseY() > yIn+315 && mouse->GetMouseY() < yIn+ 315 +MITEMHEIGHT && 
				   mouse->LeftIsPressed() && !leftPressed)
				{
					*state=RESET;
				}
			}

			//shop
			if(mouse->GetMouseX() > xIn+385 && mouse->GetMouseX() < xIn+ 385 +BACKWIDTH &&
			   mouse->GetMouseY() > yIn+245 && mouse->GetMouseY() < yIn+ 245 +MITEMHEIGHT && 
			   mouse->LeftIsPressed() && !leftPressed)
			{
				
				if (*state==WIN)
				{
					win=true;
				}
				else if (*state==LOSE)
				{
					lose=true;
				}
				else if (*state == FINISHED)
				{
					finished=true;
				}
				*state=SHOP;


			}
		}
		
	}
	else if (*state == OPTIONS)
	{
		if(mouse->GetMouseX() > xIn+385 && mouse->GetMouseX() < xIn+ 385 +BACKWIDTH &&
			mouse->GetMouseY() > yIn+385 && mouse->GetMouseY() < yIn+ 385 +MITEMHEIGHT && 
			mouse->LeftIsPressed() && !leftPressed)
		{
			*state = MENU;
		}
	}
	else if (*state == QUIT)
	{
		if(mouse->GetMouseX() > xIn+50 && mouse->GetMouseX() < xIn + 50 +YNWIDTH &&
			mouse->GetMouseY() > yIn+80 && mouse->GetMouseY() < yIn+ 80 +MITEMHEIGHT && 
			mouse->LeftIsPressed() && !leftPressed)
		{
			PostQuitMessage(0);
		}
		else if(mouse->GetMouseX() > xIn+170 && mouse->GetMouseX() < xIn + 170 +YNWIDTH &&
			    mouse->GetMouseY() > yIn+80 && mouse->GetMouseY() < yIn+ 80 +MITEMHEIGHT && 
				mouse->LeftIsPressed() && !leftPressed)
		{
			*state = MENU;
		}
		
	}
	else if (*state == SHOP)
	{
		// time ++
		if(mouse->GetMouseX() > xIn && mouse->GetMouseX() < xIn+MITEMWIDTH &&
			mouse->GetMouseY() > yIn && mouse->GetMouseY() < yIn+MITEMHEIGHT && 
			mouse->LeftIsPressed() && !leftPressed && !upgradeState)
		{
			*upgrade = TIMEUP;
			upgradeState=true;
		} 
		// enemy --
		else if(mouse->GetMouseX() > xIn && mouse->GetMouseX() < xIn+MITEMWIDTH &&
			mouse->GetMouseY() > yIn+75 && mouse->GetMouseY() < yIn+MITEMHEIGHT+75 && 
			mouse->LeftIsPressed() && !leftPressed && !upgradeState)
		{
			*upgrade = ENEMYDOWN;
			upgradeState=true;
		}
		// double jump
		else if(mouse->GetMouseX() > xIn && mouse->GetMouseX() < xIn+MITEMWIDTH &&
			mouse->GetMouseY() > yIn+150 && mouse->GetMouseY() < yIn+MITEMHEIGHT+150 && 
			mouse->LeftIsPressed() && !leftPressed && !upgradeState)
		{
			*upgrade = DOUBLEJUMP;
			upgradeState=true;
		}
		else
		{
			*upgrade = NOTHING;
			upgradeState=false;
		}


		// back button 
		if(mouse->GetMouseX() > xIn+385 && mouse->GetMouseX() < xIn+ 385 +BACKWIDTH &&
			mouse->GetMouseY() > yIn+385 && mouse->GetMouseY() < yIn+ 385 +MITEMHEIGHT && 
			mouse->LeftIsPressed() && !leftPressed)
		{
			if (win == true)
			{
				*state = WIN;
				win = false;
			}
			else if (lose == true)
			{
				*state = LOSE;
				lose = false;
			}
			else if (finished == true)
			{
				*state = FINISHED;
				finished = false;
			}
		}
	}

}


void Menu::DrawText(int x, int y, const char* string, D3DCOLOR color )
{
	// this was supposed to be something way cooler but i cant 
	// remember what i wanted to make
	gfx->DrawString(string,TEXTOFFX+x,TEXTOFFY+y,&fixedSys,color);
}

void Menu::MouseCheck()
{
	if (mouse->LeftIsPressed())
	{
		leftPressed = true;
	}
	else if (!mouse->LeftIsPressed())
	{
		leftPressed = false;
	}

}