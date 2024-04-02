#include "EnemyTimer.h"
#include <stdio.h>


EnemyTimer::EnemyTimer(D3DGraphics &gfx, float maxTime)
	:
	timer(),
	gfx(&gfx),
	maxTime(maxTime)
	{
		LoadFont( &fixedSys,fontSurf,"Fonts\\fixedsys16x28.bmp",16,28,32 );
	}


	void EnemyTimer::StartTime()
	{
		timer.StartWatch();
	}

	void EnemyTimer::StopTime()
	{
		timer.StopWatch();
		float time=0.0f;
	}

	float EnemyTimer::GetTime()
	{
		
		return (maxTime - time);
	}

	void EnemyTimer::PrintTime()
	{
		float time = timer.GetTimeMilli() / 1000.0f;
		float printTime = maxTime - time;
		char buffer[64];
		sprintf(buffer,"%f",printTime);
		gfx->DrawString(buffer,eX,eY,&fixedSys,D3DCOLOR_XRGB(255,255,255));

	}