#pragma once
//#include <iostream>

class Ship
{
private:
	int headShipI, headShipJ, deckAmount, hp;
	bool direction;

public:
	Ship(int x, int y, bool direction, int deckAmount);
	~Ship();

	int getI() const;
	int getJ() const;
	int getDeckAmount() const;
	bool getDirection() const;
	int getShipHp() const;

	void turn(int mapSize);
	void reflect(int mapSize);
	int isItDamage(int attakI, int attakJ); //function checks whether the ship contains a deck with coordinates attakI and attakJ. If yes - lessens ships HP by 1 and returns 1, else - returns 0.
};

