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

	int mapSizeI, mapSizeJ;
	int currentShipsAmount, shipsAmount;

	std::vector<std::vector<PieceOfMap>> map; // array which contains information about actions in certain point of map: 
											  //0 - there ware no any action, 
											  //1 - ship has been placed in this area;
	                                          //2 - deck of ship was destroyed.
											  //3 - area which can't contan any ship
	std::vector<Ship> ships;

public:
	Map();
	Map(bool enemy);

	int getSizeI() const;
	int getSizeJ() const;
	void getMapValue() const;
	sf::RectangleShape getMapValue(int i, int j) const;
	int getShipsAmount() const;
	int getCurrentShipsAmount() const;
	std::vector<Ship>::const_iterator getShips() const;
	
	void placeShip(const Ship& ship);
	bool placeShip(const OutMapShip& ship, const sf::RenderWindow* window);
	void attack(const sf::RenderWindow* window);


	void updateMap(const sf::RenderWindow* window);
	void updateMap(const sf::RenderWindow* window, bool enemy);
	void renderMap(sf::RenderWindow* targetWindow) const;
};

