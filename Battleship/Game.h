#include "Ship.h"
#pragma once

class Game
{
private:
	int playerShipCount;
	int enemyShipCount;
public:
	void playerTurn(int** playerAttackBoard, int** enemyShipBoard, Ship* enemyShips[], int& enemyShipCount);
	void enemyTurn(int** playerShipBoard, Ship* playerShips[], int** enemyAttackBoard, int& playerShipCount, 
		bool& recentMiss, int& lastYHit, int& lastXHit, int& hitDirection);
};

