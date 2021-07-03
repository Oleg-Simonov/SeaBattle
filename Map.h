#pragma once
#include <vector>
#include <iostream>
#include <string> 
#include <SFML/Graphics.hpp>
#include "Ship.h"
#include "OutMapShip.h"
#include "MapCoord.h"
//#define DEBUG_MAP

class PieceOfMap;

class Map
{
private:

	class PieceOfMap
	{
	public:
		int value;
		sf::RectangleShape shape;

		PieceOfMap();
		~PieceOfMap();
	};

	int mapSizeI, mapSizeJ;
	int currentShipsAmount, shipsAmount;
	MapCoord chosenField;

	sf::Font font;

	std::vector<sf::Text> text12345;
	std::vector<sf::Text> textABCDE;
	sf::Text textWhoseMap;

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
	Map(float coorWindX, float coorWindY, bool enemy = 0);
	~Map();

	//getters
	int getSizeI() const;
	int getSizeJ() const;
	void getMapValue() const;
	int getMapValue(int i, int j) const;
	int getShipsAmount() const;
	int getCurrentShipsAmount() const;
	int getProhibitedZoneIJ(const MapCoord& mapCoord);
	const MapCoord& getChosenField() const;

	//functions
	void showProhibitedZone();
	void calcProhibitedZone(bool dir, int deckAmount, bool isMidAvailable = 0);
	bool calcCoordinanes(bool dir, int deckAmount, bool isMidAvailable = 0);
	void randomPlace();
	void placeShip(const Ship& ship);
	bool placeShip(const OutMapShip& ship);
	int attack(const MapCoord& mapCoord); //if attackI and attackJ are exist then computer attacks player's map
	void clearMap();

	void updateMap(const sf::RenderWindow* window, bool enemyMap = 0);
	void renderMap(sf::RenderWindow* targetWindow) const;
};

