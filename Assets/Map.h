#pragma once
#include "D3DGraphics.h"



#define MAPHEIGHT 600


class Map
{
public:
	Map (D3DGraphics &gfx);
	void DrawMap (int nRow, bool *deathSquare);
	void DrawFakeMap(int nRow);

private:
	void DrawBlueSquare(int x, int y, int size);
	void DrawRedSquare(int x, int y, int size);

private:
	int rowSize;
	D3DGraphics* gfx;


};