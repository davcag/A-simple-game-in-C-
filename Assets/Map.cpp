#include "Map.h"

Map::Map(D3DGraphics &gfx)
	:
	gfx(&gfx)
{

}



void Map::DrawMap( int nRow, bool *deathSquare)
{
	rowSize=MAPHEIGHT/nRow;
	for (int i = 0; i<nRow; i++)
	{
		for (int j=0;j<nRow; j++)
		{
			int index = i + j*nRow;

			if (deathSquare[index]==false)
			{
				DrawBlueSquare(rowSize*i,rowSize*j,rowSize);
			}
			else if (deathSquare[index]==true)
			{
				DrawRedSquare(rowSize*i,rowSize*j,rowSize);
			}
		}
	}
}

void Map::DrawFakeMap( int nRow)
{
	rowSize=MAPHEIGHT/nRow;
	for (int i = 0; i<nRow; i++)
	{
		for (int j=0;j<nRow; j++)
		{
			DrawBlueSquare(rowSize*i,rowSize*j,rowSize);
		}
	}
}


void Map::DrawBlueSquare(int x, int y,int size)
{
	for (int i=5; i<size-5; i++)
	{
		for (int j=5; j<size-5; j++)
		{
			gfx->PutPixel(x+i,y+j,D3DCOLOR_XRGB(0,0,255));
		}
	}
}


void Map::DrawRedSquare(int x, int y,int size)
{
	for (int i=5; i<size-5; i++)
	{
		for (int j=5; j<size-5; j++)
		{
			gfx->PutPixel(x+i,y+j,D3DCOLOR_XRGB(255,0,0));
		}
	}
}

