#pragma once

#include "D3DGraphics.h"
#include "Menu.h"

class Shop
{
public:
	void AddEnemyMoney(int levelCounter);
	void AddLevelMoney(int levelCounter);
	int GetMoney();
	void SetShop(bool &doubleJump);
	void RunShop(float &maxTime, int &nEnemies, D3DGraphics* gfx, Font &fixedSys, Upgrade* upgrade);
	void ChangePrice(Upgrade* upgrade, float &maxTime, int &nEnemies);
protected:
	int timeUpCounter;
	int enemyDownCounter;
	bool* doubleJump;
private:
	int money;
	int timeUpMoney;
	int enemyDownMoney;
	int doubleJumpMoney;
};