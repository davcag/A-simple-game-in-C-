#include "Shop.h"

#include <stdio.h>



void Shop::AddEnemyMoney(int levelcounter)
{
	money = money + levelcounter + 1;
}

void Shop::AddLevelMoney(int levelcounter)
{
	money = money + 5 * (levelcounter+1);
}

int Shop::GetMoney()
{
	return money;
}

void Shop::SetShop(bool &doubleJump)
{
	money=0;
	timeUpCounter=0;
	enemyDownCounter=0;
	timeUpMoney=50;
	enemyDownMoney=20;
	doubleJumpMoney=500;
	this->doubleJump=&doubleJump;
}


void Shop::RunShop(float &maxTime, int &nEnemies, D3DGraphics* gfx, Font &fixedSys, Upgrade *upgrade)
{

	char buffer[64];
	sprintf(buffer,"%d",timeUpMoney);
	gfx->DrawString(buffer,470,162,&fixedSys,D3DCOLOR_XRGB(0,0,0));
	sprintf(buffer,"%d",enemyDownMoney);
	gfx->DrawString(buffer,470,237,&fixedSys,D3DCOLOR_XRGB(0,0,0));
	if (*doubleJump == false)
	{
	sprintf(buffer,"%d",doubleJumpMoney);
	gfx->DrawString(buffer,470,312,&fixedSys,D3DCOLOR_XRGB(0,0,0));
	}
	else
	{
	gfx->DrawString("MAX",470,312,&fixedSys,D3DCOLOR_XRGB(255,0,0));
	}

	ChangePrice(upgrade, maxTime, nEnemies);

}


void Shop::ChangePrice(Upgrade* upgrade, float &maxTime, int &nEnemies)
{
	if(*upgrade == TIMEUP && money>=timeUpMoney)
	{
		money-=timeUpMoney;
		timeUpMoney=timeUpMoney+50*(timeUpCounter+1);
		timeUpCounter++;
		maxTime++;
	}
	if(*upgrade == ENEMYDOWN && money>=enemyDownMoney)
	{
		money-=enemyDownMoney;
		enemyDownMoney=enemyDownMoney+20*(enemyDownCounter+1);
		enemyDownCounter++;
		nEnemies--;
	}
	if(*upgrade == DOUBLEJUMP && money>=doubleJumpMoney && *doubleJump==false)
	{
		money-=doubleJumpMoney;
		*doubleJump=true;
	}

}