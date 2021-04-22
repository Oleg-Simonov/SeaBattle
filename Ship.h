#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
//#include "Game.h"

class Coordinates;

class Ship
{
	

private:
	int x, y, deckAmount, hp, shipID;
	bool direction;
	bool grab; // used for draging ship to the player map
	
	class Coordinates
	{
	public:
		int i, j;
		bool isItDestroed; // contains information about deck of ship: was it destroyed or not. If deck is destroyed - true.
		sf::RectangleShape shape;
		Coordinates(int i, int j);
	};

	std::vector<Coordinates> coordinates;

public:
	Ship(int x, int y, bool direction, int deckAmount);
	Ship(const Ship& other);
	Ship(float windowCoorX, float windowCoorY, int deckAmount);
	~Ship();

	static int shipCounter;

	int getI() const;
	int getJ() const;
	bool getDirection() const;
	int getDeckAmount() const;
	int getShipID() const;
	int getShipHp() const;
	void getDataForLog();
	bool getGrabShip() const;
	std::vector<Coordinates>::const_iterator getCoordinates() const;

	void setDeckAmount(int newDeckAmount); // no use
	void setGrabShip(sf::RenderWindow* window);
	void setDirection();

	int isItDamage(int attakI, int attakJ);
	void lessenHp();
	

	void updateShip(sf::RenderWindow* window);
	void renderShip(sf::RenderWindow* window) const;
};

