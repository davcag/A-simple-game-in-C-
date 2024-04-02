#pragma once

#include "Timer.h"
#include "D3DGraphics.h"

class EnemyTimer
{
public:
	EnemyTimer(D3DGraphics &gfx, float maxTime);
	void StartTime();
	float GetTime();
	void PrintTime(int eX, int eY);

private:
	void StopTime();


private:
	Timer timer;
	D3DGraphics* gfx;
	float time;
	float maxTime;

	Font fixedSys;
	D3DCOLOR fontSurf[ 512 * 84 ];

};