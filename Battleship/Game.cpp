#include <cstdlib>
#include "Game.h"

//playerTurn function that takes in a two 2D int arrays of pointers, a Ship array of pointers, and an
//address reference to enemyShipCount
void Game::playerTurn(int** playerAttackBoard, int** enemyShipBoard, Ship* enemyShips[], int& enemyShipCount)
{
	//creates integers to store attack coordinates
	int xAttack = -1;
	int yAttack = -1;
	//runs while user input is not in specified range of board
	while ((xAttack < 0 || xAttack > 9) || (yAttack < 0 || yAttack > 9))
	{
		//prompts user to enter in values
		cout << "Enter the x attack coordinate: ";
		cin >> xAttack;
		//used to check if input is an integer or not to fix game crashing
		while (cin.fail())
		{
			cout << "Please enter a valid input" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Enter the x attack coordinate: ";
			cin >> xAttack;
		}
		cout << endl;
		cout << "Enter the y attack coordinate: ";
		cin >> yAttack;
		//used to check if input is an integer or not to fix game crashing
		while (cin.fail())
		{
			cout << "Please enter a valid input" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Enter the y attack coordinate: ";
			cin >> yAttack;
		}
		cout << endl;
	}
	//if the player lands a hit (when index at enemyBoard is 1)
	if (enemyShipBoard[yAttack][xAttack] == 1)
	{
		cout << "YOU HIT!" << endl;
		//updates values on boards to 2 (signifies a spot has been hit)
		enemyShipBoard[yAttack][xAttack] = 2;
		playerAttackBoard[yAttack][xAttack] = 2;
		//nested for loop to compare coordinate hit with ship positions to determine current hits left of each ship
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < enemyShips[i]->getSize(); j++)
			{
				if (enemyShips[i]->getCoords(j).first == yAttack && enemyShips[i]->getCoords(j).second == xAttack)
				{
					//subtracts 1 from current hits of the hit ship
					enemyShips[i]->setHits(enemyShips[i]->getHits() - 1);
					//if hits of the current ship is 0, prints out that ship was sunk and decreases enemyShipCount by 1
					if (enemyShips[i]->getHits() == 0)
					{
						cout << "ENEMY'S " << enemyShips[i]->getShipName() << " WAS SUNK!" << endl;
						cout << endl;
						enemyShipCount--;
					}
					
				}
			}
		}
	}
	//if the player misses (when index at enemyBoard is 0)
	else if (enemyShipBoard[yAttack][xAttack] == 0)
	{
		cout << " YOU MISS!" << endl;
		//updates boards to label spot as missed
		enemyShipBoard[yAttack][xAttack] = 3;
		playerAttackBoard[yAttack][xAttack] = 3;
	}
	//checks if the player has already hit that spot (when index is 2(hit) or 3(missed))
	else if (playerAttackBoard[yAttack][xAttack] == 2 || playerAttackBoard[yAttack][xAttack] == 3)
	{
		cout << "You've already tried this space, try again." << endl;
		//re-runs method
		playerTurn(playerAttackBoard, enemyShipBoard, enemyShips, enemyShipCount);
	}
}

//enemyTurn function that takes in a two 2D int arrays of pointers, a Ship array of pointers, and address references 
//to playerShipCount, recentMiss, lastYHit, lastXHit, and hitDirection
void Game::enemyTurn(int** playerShipBoard, Ship* playerShips[], int** enemyAttackBoard, int& playerShipCount, 
	bool& recentMiss, int& lastYHit, int& lastXHit, int& hitDirection)
{
	//creates ints for x and y attack coordinates and sets them to temporary values
	int xAttack = -1;
	int yAttack = -1;
	//checks if the enemy has missed on their previous turn, if so sets random attack coordinates
	if (recentMiss)
	{
		xAttack = rand() % 9;
		yAttack = rand() % 9;
	}
	//checks if enemy has hit on their previous turn
	else
	{
		//checks if there is another hit below last hit
		if (hitDirection == 0)
		{
			xAttack = lastXHit;
			yAttack = lastYHit + 1;
		}
		//checks if there is another hit on right of last hit
		else if (hitDirection == 1)
		{
			xAttack = lastXHit + 1;
			yAttack = lastYHit;
		}
		//checks if there is another hit above last hit
		else if (hitDirection == 2)
		{
			xAttack = lastXHit;
			yAttack = lastYHit - 1;
		}
		//checks if there is another hit on left of last hit
		else if (hitDirection == 3)
		{
			xAttack = lastXHit - 1;
			yAttack = lastYHit;
		}
		//done in case of senario when hitDirection exceeds 3
		else
		{
			xAttack = rand() % 9;
			yAttack = rand() % 9;
		}
		//checks if hit is in-bounds and if not resets to las position and updates hitDirection
		if ((xAttack < 0 || xAttack > 9) || (yAttack < 0 || yAttack > 9))
		{
			xAttack = lastXHit;
			yAttack = lastYHit;
			hitDirection++;
		}
	}
	//if the enemy lands a hit (when index at playerShipBoard is 1)
	if (playerShipBoard[yAttack][xAttack] == 1)
	{
		//prints out results
		cout << "Enemy Attacks at: (" << xAttack << ", " << yAttack << ") " << endl;
		cout << " ENEMY HIT!" << endl;
		//updates values to match results
		playerShipBoard[yAttack][xAttack] = 2;
		enemyAttackBoard[yAttack][xAttack] = 2;
		//stores location of hit and sets recentMiss to false
		lastXHit = xAttack;
		lastYHit = yAttack;
		recentMiss = false;
		//nested for loop to compare coordinate hit with ship positions to determine current hits left of each ship
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < playerShips[i]->getSize(); j++)
			{
				if (playerShips[i]->getCoords(j).first == yAttack && playerShips[i]->getCoords(j).second == xAttack)
				{
					//subtracts 1 from current hits of the hit ship
					playerShips[i]->setHits(playerShips[i]->getHits() - 1);
					//if hits of the current ship is 0, prints out that ship was sunk and decreases playerShipCount by 1
					if (playerShips[i]->getHits() == 0)
					{
						cout << "YOUR " << playerShips[i]->getShipName() << " WAS SUNK!" << endl;
						cout << endl;
						enemyShipCount--;
						//resets recentMiss and hitDirection so a new space can be targeted
						recentMiss = true;
						hitDirection = 0;
					}

				}
			}
		}
	}
	//if the enemy misses (when index at playerShipBoard is 0)
	else if (playerShipBoard[yAttack][xAttack] == 0)
	{
		//prints out results
		cout << "Enemy Attacks at: (" << xAttack << ", " << yAttack << ") " << endl;
		cout << "ENEMY MISS!" << endl;
		//checks if recentMiss is still true and if hitDirection is less than or equal to 3 (if all directions around
		//target haven't been tried yet) and if so updates hitDirection, otherwise resets recentMiss and hitDirection
		if (!recentMiss && hitDirection <= 3)
		{
			hitDirection++;
		}
		else
		{
			recentMiss = true;
			hitDirection = 0;
		}
		//updates boards to reflect miss
		playerShipBoard[yAttack][xAttack] = 3;
		enemyAttackBoard[yAttack][xAttack] = 3;
	}
	//checks if the enemy has already hit that spot (when index is 2(hit) or 3(missed))
	else if (enemyAttackBoard[yAttack][xAttack] == 2 || enemyAttackBoard[yAttack][xAttack] == 3)
	{
		//checks if recentMiss is still true and if hitDirection is less than or equal to 3 (if all directions around
		//target haven't been tried yet) and if so updates hitDirection
		if (!recentMiss && hitDirection <= 3)
		{
			hitDirection++;
		}
		//re-runs method
		enemyTurn(playerShipBoard, playerShips, enemyAttackBoard, playerShipCount, recentMiss, 
			lastYHit, lastXHit, hitDirection);
	}
}
