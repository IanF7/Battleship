#include <iostream>
#include <string>
#include <cstdlib>
#include "Ship.h"
#include "Game.h"

using namespace std;


//declare methods
int** buildBoard();
void displayBoard(int** player);
int** placePlayerShips(int** player, Ship* ships[]);
int** placeEnemyShips(int** enemy, Ship* ships[]);


//main method
int main()
{
	//creates 2 2D integer arrays using buildBoard method
	int** playerAttackBoard = buildBoard();
	int** playerShipBoard = buildBoard();
	int** enemyAttackBoard = buildBoard();
	int** enemyShipBoard = buildBoard();

	//creates necessary ships for player and enemy (code was adding enemy and player ships to the same vector so there
	//are 2 sets), vector<pair<int, int>> used to store ship coordinates)
	Ship* carrierP = new Ship("Carrier", 5, 5, vector<pair<int, int>>());
	Ship* battleshipP = new Ship("Battleship", 4, 4, vector<pair<int, int>>());
	Ship* cruiserP = new Ship("Cruiser", 3, 3, vector<pair<int, int>>());
	Ship* submarineP = new Ship("Submarine", 3, 3, vector<pair<int, int>>());
	Ship* destroyerP = new Ship("Destroyer", 2, 2, vector<pair<int, int>>());

	Ship* carrierE = new Ship("Carrier", 5, 5, vector<pair<int, int>>());
	Ship* battleshipE = new Ship("Battleship", 4, 4, vector<pair<int, int>>());
	Ship* cruiserE = new Ship("Cruiser", 3, 3, vector<pair<int, int>>());
	Ship* submarineE = new Ship("Submarine", 3, 3, vector<pair<int, int>>());
	Ship* destroyerE = new Ship("Destroyer", 2, 2, vector<pair<int, int>>());

	//creates arrays to store ships in
	Ship* playerShips[] = { carrierP, battleshipP, cruiserP, submarineP, destroyerP };
	Ship* enemyShips[] = { carrierE, battleshipE, cruiserE, submarineE, destroyerE };

	//seeds random number generator
	srand((unsigned)(time(NULL)));
	//cplaces enemy and player ships on respective boards
	enemyShipBoard = placeEnemyShips(enemyShipBoard, enemyShips);
	displayBoard(enemyShipBoard);
	cout << endl;
	displayBoard(playerShipBoard);
	cout << endl;
	playerShipBoard = placePlayerShips(playerShipBoard, playerShips);

	//creates variables to control while loop and track game progress
	int playerShipCount = 5;
	int enemyShipCount = 5;
	bool recentMiss = true;
	//creates variables for enemy AI to properly target ships
	int lastXHit = -1;
	int lastYHit = -1;
	int hitDirection = 0;
	bool gameOver = false;
	Game game;

	cout << "----------------------------------------" << endl;
	cout << "---------------Start Game---------------" << endl;
	cout << "----------------------------------------" << endl;
	cout << endl;

	//runs while gameOber is false
	while (!gameOver)
	{
		//displays player's current boards
		cout << "ATTACK BOARD" << endl;
		displayBoard(playerAttackBoard);
		cout << endl;
		cout << "SHIP BOARD" << endl;
		displayBoard(playerShipBoard);
		cout << endl;
		cout << "----------------------------------------" << endl;
		//runs the player's turn then the enemy's turn
		game.playerTurn(playerAttackBoard, enemyShipBoard, enemyShips, enemyShipCount);
		game.enemyTurn(playerShipBoard, playerShips, enemyAttackBoard, playerShipCount, 
			recentMiss, lastYHit, lastXHit, hitDirection);
		//if either enemy or player runs out of ships, sets gameOver to true and prints out results
		if (enemyShipCount == 0)
		{
			gameOver = true;
			cout << "PLAYER WINS!" << endl;
		}
		else if (playerShipCount == 0)
		{
			gameOver = true;
			cout << "ENEMY WINS!" << endl;
		}
		cout << "----------------------------------------" << endl;
		cout << endl;
	}
}


//buildBoard method that returns a 2D int array
int** buildBoard()
{
	//creates a new 2D int array and populates every entry with 0
	int** board = new int* [10];
	for (int i = 0; i < 10; i++)
	{
		board[i] = new int[10];
		for (int j = 0; j < 10; j++)
		{
			board[i][j] = 0;
		}
	}
	return board;
}


//displayBoard method that takes in a 2D int array and returns void
void displayBoard(int** player)
{
	//prints out position key for x values
	cout << "    ";
	for (int i = 0; i < 10; i++)
	{
		printf("%d ", i);
	}
	cout << endl;
	cout << endl;
	//displays rest of the board
	for (int i = 0; i < 10; i++)
	{
		//prints out position key for y values
		printf("%d   ", i);
		//displays board with different symbols depending on value of index of board
		for (int j = 0; j < 10; j++)
		{
			if (player[i][j] == 0)
			{
				cout << "- ";
			}
			else if (player[i][j] == 1)
			{
				cout << "# ";
			}
			else if (player[i][j] == 2)
			{
				cout << "X ";
			}
			else if (player[i][j] == 3)
			{
				cout << "O ";
			}
		}
		cout << endl;
	}
}


//placePlayerShips method that takes in a 2D int array, a Ship array of pointers, and returns a 2D int array
int** placePlayerShips(int** player, Ship* ships[])
{
	//creates necessary variables for code
	int shipStartX;
	int shipStartY;
	int shipDirection;
	int lowerBounds = -1;
	int upperBounds = 10;
	//used to check if a ship overlaps with another ship
	bool overlap;

	//runs for everyship the user has
	for (int i = 0; i < 5; i++)
	{
		//resets inputs
		shipStartX = 0;
		shipStartY = 0;
		shipDirection = 0;
		overlap = false;

		//displays current ship's data
		cout << "Ship: " << ships[i]->getShipName() << " size: " << ships[i]->getSize() << endl;
		//prompts user to enter in ship's starting x and y coords and direction of ship
		cout << "Enter ship's starting x position: ";
		cin >> shipStartX;
		//used to check if input is an integer or not to fix game crashing
		while (cin.fail())
		{
			cout << "Please enter a valid input" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Enter ship's starting x position: ";
			cin >> shipStartX;
		}
		cout << "\nEnter ship's starting y position: ";
		cin >> shipStartY;
		//used to check if input is an integer or not to fix game crashing
		while (cin.fail())
		{
			cout << "Please enter a valid input" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Enter ship's starting y position: ";
			cin >> shipStartY;
		}
		cout << "\nEnter the direction the ship is facing (1 = up, 2 = right, 3 = down, 4 = left): ";
		cin >> shipDirection;
		//used to check if input is an integer or not to fix game crashing
		while (cin.fail())
		{
			cout << "Please enter a valid input" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "\nEnter the direction the ship is facing (1 = up, 2 = right, 3 = down, 4 = left): ";
			cin >> shipDirection;
		}

		//if direction entered is 1(up)
		if (shipDirection == 1 && shipStartY - ships[i]->getSize() >= lowerBounds)
		{
			//checks position ship will be occupying for if a ship already exists there
			for (int y = shipStartY; y > shipStartY - ships[i]->getSize(); y--)
			{
				//if a ship is found in any of the spots the current ship will be placed, sets overlap to true
				if (player[y][shipStartX] == 1)
				{
					overlap = true;
				}
			}
			//will populate position of ship on board with 1's if overlap is false
			if (!overlap)
			{
				for (int y = shipStartY; y > shipStartY - ships[i]->getSize(); y--)
				{
					player[y][shipStartX] = 1;
					ships[i]->setCoords(y, shipStartX);
				}
				cout << endl;
				cout << endl;
				displayBoard(player);
				cout << endl;
			}
			//prompts user to enter new coords/direction since a ship already exists in that spot
			else
			{
				cout << "A ship is already placed here. Please enter a valid position" << endl;
				i--;
				cout << endl;
			}
		}
		//if direction entered is 2(right)
		else if (shipDirection == 2 && shipStartX + ships[i]->getSize() <= upperBounds)
		{
			//checks position ship will be occupying for if a ship already exists there
			for (int x = shipStartX; x < shipStartX + ships[i]->getSize(); x++)
			{
				//if a ship is found in any of the spots the current ship will be placed, sets overlap to true
				if (player[shipStartY][x] == 1)
				{
					overlap = true;
				}
			}
			//will populate position of ship on board with 1's if overlap is false
			if (!overlap)
			{
				for (int x = shipStartX; x < shipStartX + ships[i]->getSize(); x++)
				{
					player[shipStartY][x] = 1;
					ships[i]->setCoords(shipStartY, x);
				}
				cout << endl;
				displayBoard(player);
				cout << endl;
			}
			//prompts user to enter new coords/direction since a ship already exists in that spot
			else
			{
				cout << "A ship is already placed here. Please enter a valid position" << endl;
				i--;
				cout << endl;
			}
		}
		//if direction entered is 3(down)
		else if (shipDirection == 3 && shipStartY + ships[i]->getSize() <= upperBounds)
		{
			//checks position ship will be occupying for if a ship already exists there
			for (int y = shipStartY; y < shipStartY + ships[i]->getSize(); y++)
			{
				//if a ship is found in any of the spots the current ship will be placed, sets overlap to true
				if (player[y][shipStartX] == 1)
				{
					overlap = true;
				}
			}
			//will populate position of ship on board with 1's if overlap is false
			if (!overlap)
			{
				for (int y = shipStartY; y < shipStartY + ships[i]->getSize(); y++)
				{
					player[y][shipStartX] = 1;
					ships[i]->setCoords(y, shipStartX);
				}
				cout << endl;
				displayBoard(player);
				cout << endl;
			}
			//prompts user to enter new coords/direction since a ship already exists in that spot
			else
			{
				cout << "A ship is already placed here. Please enter a valid position" << endl;
				i--;
				cout << endl;
			}
		}
		//if direction entered is 4(left)
		else if (shipDirection == 4 && shipStartX - ships[i]->getSize() >= lowerBounds)
		{
			//checks position ship will be occupying for if a ship already exists there
			for (int x = shipStartX; x > shipStartX - ships[i]->getSize(); x--)
			{
				if (player[shipStartY][x] == 1)
				{
					overlap = true;
				}
			}
			//will populate position of ship on board with 1's if overlap is false
			if (!overlap)
			{
				for (int x = shipStartX; x > shipStartX - ships[i]->getSize(); x--)
				{
					player[shipStartY][x] = 1;
					ships[i]->setCoords(shipStartY, x);
				}
				cout << endl;
				displayBoard(player);
				cout << endl;
			}
			//prompts user to enter new coords/direction since a ship already exists in that spot
			else
			{
				cout << "A ship is already placed here. Please enter a valid position" << endl;
				i--;
				cout << endl;
			}
		}
		//if the direction entered is invalid or the ship goes out of bounds, prompts user to enter in new values
		else
		{
			cout << "Input is invalid. Please enter a valid number" << endl;
			i--;
			cout << endl;
		}
	}
	return player;
}

//placeEnemyShips method that takes in a 2D int array, a Ship array of pointers, and returns a 2D int array
int** placeEnemyShips(int** enemy, Ship* ships[])
{
	// creates necessary variables for code
	int shipStartX;
	int shipStartY;
	int shipDirection;
	int lowerBounds = -1;
	int upperBounds = 10;
	//used to check if a ship overlaps with another ship
	bool overlap;

	//runs for everyship the user has
	for (int i = 0; i < 5; i++)
	{
		//resets inputs
		shipStartX = rand() % 9;
		shipStartY = rand() % 9;
		shipDirection = rand() % 4 + 1;
		overlap = false;

		//if direction entered is 1(up)
		if (shipDirection == 1 && shipStartY - ships[i]->getSize() >= lowerBounds)
		{
			//checks position ship will be occupying for if a ship already exists there
			for (int y = shipStartY; y > shipStartY - ships[i]->getSize(); y--)
			{
				//if a ship is found in any of the spots the current ship will be placed, sets overlap to true
				if (enemy[y][shipStartX] == 1)
				{
					overlap = true;
				}
			}
			//will populate position of ship on board with 1's if overlap is false
			if (!overlap)
			{
				for (int y = shipStartY; y > shipStartY - ships[i]->getSize(); y--)
				{
					enemy[y][shipStartX] = 1;
					ships[i]->setCoords(y, shipStartX);
				}
			}
			//prompts user to enter new coords/direction since a ship already exists in that spot
			else
			{
				i--;
			}
		}
		//if direction entered is 2(right)
		else if (shipDirection == 2 && shipStartX + ships[i]->getSize() <= upperBounds)
		{
			//checks position ship will be occupying for if a ship already exists there
			for (int x = shipStartX; x < shipStartX + ships[i]->getSize(); x++)
			{
				//if a ship is found in any of the spots the current ship will be placed, sets overlap to true
				if (enemy[shipStartY][x] == 1)
				{
					overlap = true;
				}
			}
			//will populate position of ship on board with 1's if overlap is false
			if (!overlap)
			{
				for (int x = shipStartX; x < shipStartX + ships[i]->getSize(); x++)
				{
					enemy[shipStartY][x] = 1;
					ships[i]->setCoords(shipStartY, x);
				}
			}
			//prompts user to enter new coords/direction since a ship already exists in that spot
			else
			{
				i--;
			}
		}
		//if direction entered is 3(down)
		else if (shipDirection == 3 && shipStartY + ships[i]->getSize() <= upperBounds)
		{
			//checks position ship will be occupying for if a ship already exists there
			for (int y = shipStartY; y < shipStartY + ships[i]->getSize(); y++)
			{
				//if a ship is found in any of the spots the current ship will be placed, sets overlap to true
				if (enemy[y][shipStartX] == 1)
				{
					overlap = true;
				}
			}
			//will populate position of ship on board with 1's if overlap is false
			if (!overlap)
			{
				for (int y = shipStartY; y < shipStartY + ships[i]->getSize(); y++)
				{
					enemy[y][shipStartX] = 1;
					ships[i]->setCoords(y, shipStartX);
				}
			}
			//prompts user to enter new coords/direction since a ship already exists in that spot
			else
			{
				i--;
			}
		}
		//if direction entered is 4(left)
		else if (shipDirection == 4 && shipStartX - ships[i]->getSize() >= lowerBounds)
		{
			//checks position ship will be occupying for if a ship already exists there
			for (int x = shipStartX; x > shipStartX - ships[i]->getSize(); x--)
			{
				if (enemy[shipStartY][x] == 1)
				{
					overlap = true;
				}
			}
			//will populate position of ship on board with 1's if overlap is false
			if (!overlap)
			{
				for (int x = shipStartX; x > shipStartX - ships[i]->getSize(); x--)
				{
					enemy[shipStartY][x] = 1;
					ships[i]->setCoords(shipStartY, x);
				}
			}
			//prompts user to enter new coords/direction since a ship already exists in that spot
			else
			{
				i--;
			}
		}
		//if the direction entered is invalid or the ship goes out of bounds, prompts user to enter in new values
		else
		{
			i--;
		}
	}
	return enemy;
}



