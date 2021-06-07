#pragma once
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Ship.h"
#include "OutMapShip.h"

class PieceOfMap;

class Map
{
private:

	class PieceOfMap
	{
	public:
		int value;
		sf::RectangleShape shapeForPlayer;
		sf::RectangleShape shapeForDebug;

		PieceOfMap();
		~PieceOfMap();
	};


	int coorI, coorJ;
	bool dir;
	int deck1, deck2, deck3, deck4, deck5;
	int mapSizeI, mapSizeJ;
	int currentShipsAmount, shipsAmount;

	std::vector<std::vector<PieceOfMap>> map; // array which contains information about actions in certain point of map: 
											  //0 - there ware no any action, 
											  //1 - ship has been placed in this area;
	                                          //2 - deck of ship has been destroyed.
											  //3 - area which can't contan any ship

	//std::vector<std::vector<PieceOfMap>> prohibitedZone;

	std::vector<std::vector<int>> prohibitedZone;
	std::vector<int> nonRepeatVector;
	std::vector<Ship> ships;

public:
	Map();
	Map(bool enemy);

	int getSizeI() const;
	int getSizeJ() const;
	void getMapValue() const;
	int getMapValue(int i, int j) const;
	//sf::RectangleShape getMapValue(int i, int j) const;
	int getShipsAmount() const;
	int getCurrentShipsAmount() const;
	std::vector<Ship>::const_iterator getShips() const;

	void calcProhibitedZone(int dir);
	void randomPlace();
	void placeShip(int coorI, int coorJ, bool dir, int deckAmount);
	void placeShip(const Ship& ship);
	bool placeShip(const OutMapShip& ship, const sf::RenderWindow* window);
	int attack(const sf::RenderWindow* window, int attackI = 1000, int attackJ = 1000); //if attackI and attackJ are exist then computer attacks player's map
	void clearMap();

	void updateMap(const sf::RenderWindow* window);
	void updateMap(const sf::RenderWindow* window, bool enemy);
	void renderMap(sf::RenderWindow* targetWindow) const;
};

