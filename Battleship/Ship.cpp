#include "Ship.h"

//default constructor
Ship::Ship()
{
	shipName = "";
	size = 0;
	hits = 0;
}

//parameterized constructor
Ship::Ship(string shipName, int size, int hits, vector<pair<int, int>> coords)
{
	this->size = size;
	this->hits = hits;
	this->shipName = shipName;
}

//getters and setters for shipName
string Ship::getShipName() const
{
	return shipName;
}

void Ship::setShipName(string shipName)
{
	this->shipName = shipName;
}

//getters and setters for size
int Ship::getSize() const
{
	return size;
}

void Ship::setSize(int size)
{
	this->size = size;
}

//getters and setters for hits
int Ship::getHits() const
{
	return hits;
}

void Ship::setHits(int hits)
{
	this->hits = hits;
}

//getter for coords that returns coords at a specific index
pair<int, int> Ship::getCoords(int index)
{
	return coords[index];
}

//setter for coords
void Ship::setCoords(int y, int x)
{
	coords.push_back(make_pair(y, x));
}










