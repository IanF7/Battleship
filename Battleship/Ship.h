#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Ship
{

private:
	string shipName;
	int size;
	int hits;
	vector<pair<int, int>>coords;

public:
	Ship();
	Ship(string shipName, int size, int hits, vector<pair<int, int>>coords);
	string getShipName() const;
	void setShipName(string shipName);
	int getSize() const;
	void setSize(int size);
	int getHits() const;
	void setHits(int hits);
	pair<int, int> getCoords(int index);
	void setCoords(int x, int y);
};

