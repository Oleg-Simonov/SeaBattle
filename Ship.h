#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
//#include "Game.h"

class Coordinates;

class Ship
{
private:
	int headShipI, headShipJ, deckAmount, hp;
	bool direction;
	
	class Coordinates
	{
	public:
		int i, j;
		bool isItDestroed; // contains information about deck of ship: was it destroyed or not. If deck is destroyed - true.

		Coordinates(int i, int j);
	};

	std::vector<Coordinates> coordinates;

public:
	Ship(int x, int y, bool direction, int deckAmount);
	~Ship();

	int getI() const;
	int getJ() const;
	bool getDirection() const;
	int getDeckAmount() const;
	int getShipHp() const;
	void getDataForLog();
	std::vector<Coordinates>::const_iterator getCoordinates() const;

	int isItDamage(int attakI, int attakJ);
};

