#include "Map.h"

//Map for player
Map::Map()
{
	std::cout << std::endl;
	std::cout << "----------Map Construcror1----------" << std::endl;

	this->shipsAmount = 0;
	this->mapSizeI = 10;
	this->mapSizeJ = 10;
	//this->ships.reserve(5);

	this->map.resize(mapSizeI);
	for (int i = 0; i < this->mapSizeI; i++)
	{
		this->map[i].resize(mapSizeJ);
		for (int j = 0; j < this->mapSizeJ; j++)
		{
			this->map[i][j].value = 0;
			this->map[i][j].shapeForPlayer.setSize(sf::Vector2f(27.f, 27.f));
			this->map[i][j].shapeForPlayer.setFillColor(sf::Color::Blue);
			this->map[i][j].shapeForPlayer.setOutlineThickness(1.f);
			this->map[i][j].shapeForPlayer.setOutlineColor(sf::Color::Black);
			this->map[i][j].shapeForPlayer.setPosition(sf::Vector2f(30.f + j * 29, 50.f + i * 29));
		}
	}

	std::cout << std::endl;
	this->getMapValue();
	std::cout << "enemyMap Ship quantity = " << this->getShipsAmount() << std::endl;
	std::cout << std::endl;

	std::cout << "----------Map Construcror1 END----------" << std::endl;
	std::cout << std::endl;
}

Map::Map(bool enemy)
{
	std::cout << std::endl;
	std::cout << "----------Map Construcror2----------" << std::endl;

	this->shipsAmount = 0;
	this->mapSizeI = 10;
	this->mapSizeJ = 10;
	this->ships.reserve(5);

	this->map.resize(mapSizeI);
	for (int i = 0; i < this->mapSizeI; i++)
	{
		this->map[i].resize(mapSizeJ);
		for (int j = 0; j < this->mapSizeJ; j++)
		{
			this->map[i][j].value = 0;

			this->map[i][j].shapeForPlayer.setSize(sf::Vector2f(27.f, 27.f));
			this->map[i][j].shapeForPlayer.setFillColor(sf::Color::Blue);
			this->map[i][j].shapeForPlayer.setOutlineThickness(1.f);
			this->map[i][j].shapeForPlayer.setOutlineColor(sf::Color::Black);
			this->map[i][j].shapeForPlayer.setPosition(sf::Vector2f(430.f + j * 29, 50.f + i * 29));

			this->map[i][j].shapeForDebug.setSize(sf::Vector2f(27.f, 27.f));
			this->map[i][j].shapeForDebug.setFillColor(sf::Color::Blue);
			this->map[i][j].shapeForDebug.setOutlineThickness(1.f);
			this->map[i][j].shapeForDebug.setOutlineColor(sf::Color::Black);
			this->map[i][j].shapeForDebug.setPosition(sf::Vector2f(430.f + j * 29, 550.f + i * 29));
		}
	}
	//Карта 1
	/*this->ships.emplace_back(1, 3, true, 5);
	this->ships.emplace_back(5, 3, true, 3);
	this->ships.emplace_back(1, 1, false, 3);
	this->ships.emplace_back(8, 8, true, 2);
	this->ships.emplace_back(8, 6, false, 1);

	this->placeShip(ships[0]);
	this->placeShip(ships[1]);
	this->placeShip(ships[2]);
	this->placeShip(ships[3]);
	this->placeShip(ships[4]);*/
	
	//Карта 2
	this->ships.emplace_back(0, 0, false, 5);
	this->ships.emplace_back(0, 2, false, 1);
	this->ships.emplace_back(7, 0, true, 2);
	this->ships.emplace_back(5, 6, true, 3);
	this->ships.emplace_back(9, 0, true, 4);

	this->placeShip(ships[0]);
	this->placeShip(ships[1]);
	this->placeShip(ships[2]);
	this->placeShip(ships[3]);
	this->placeShip(ships[4]);


	//this->currentShipsAmount = this->shipsAmount;
	this->currentShipsAmount = this->ships.size();
	/*this->placeShip(Ship::Ship(1, 3, true, 5));
	this->placeShip(Ship::Ship(5, 3, true, 3));
	this->placeShip(Ship::Ship(1, 1, false, 3));
	this->placeShip(Ship::Ship(8, 8, true, 2));
	this->placeShip(Ship::Ship(8, 6, false, 1));*/

	std::cout << std::endl;
	this->getMapValue();
	std::cout << "enemyMap Ship quantity = " << this->getShipsAmount() << std::endl;
	std::cout << std::endl;

	std::cout << "----------Map Construcror2 END----------" << std::endl;
	std::cout << std::endl;
}

int Map::getSizeI() const
{
	return mapSizeI;
}

int Map::getSizeJ() const
{
	return mapSizeI;
}

void Map::getMapValue() const
{
		for (int i = 0; i < this->mapSizeI; i++)
		{
			for (int j = 0; j < this->mapSizeJ; j++)
			{
				std::cout << map[i][j].value << "\t";
			}
			std::cout << std::endl;
		}
}

sf::RectangleShape Map::getMapValue(int i, int j) const
{
	return this->map[i][j].shapeForDebug;
}

int Map::getShipsAmount() const
{
	return this->shipsAmount;
}

int Map::getCurrentShipsAmount() const
{
	return this->currentShipsAmount;
}

std::vector<Ship>::const_iterator Map::getShips() const
{
	return this->ships.begin();
}

void Map::updateMap(const sf::RenderWindow* window)
{

	for (int i = 0; i < this->getSizeI(); i++)
	{
		for (int j = 0; j < this->getSizeJ(); j++)
		{
			if (this->map[i][j].shapeForPlayer.getGlobalBounds().contains((float)sf::Mouse::getPosition(*window).x, (float)sf::Mouse::getPosition(*window).y))
				this->map[i][j].shapeForPlayer.setFillColor(sf::Color::Cyan);

			else if (this->map[i][j].value == 2) this->map[i][j].shapeForPlayer.setFillColor(sf::Color::Red);

			else if (this->map[i][j].value == 1) this->map[i][j].shapeForPlayer.setFillColor(sf::Color::White);

			else if (this->map[i][j].value == 3) this->map[i][j].shapeForPlayer.setFillColor(sf::Color::Green);

			else this->map[i][j].shapeForPlayer.setFillColor(sf::Color::Blue);
		}
	}
}

void Map::updateMap(const sf::RenderWindow* window, bool enemy)
{

	for (int i = 0; i < this->getSizeI(); i++)
	{
		for (int j = 0; j < this->getSizeJ(); j++)
		{
			if (this->map[i][j].shapeForPlayer.getGlobalBounds().contains((float)sf::Mouse::getPosition(*window).x, (float)sf::Mouse::getPosition(*window).y))
				this->map[i][j].shapeForPlayer.setFillColor(sf::Color::Cyan);

			else if (this->map[i][j].value == 2) this->map[i][j].shapeForPlayer.setFillColor(sf::Color::Red);

			else if (this->map[i][j].value == 3) this->map[i][j].shapeForPlayer.setFillColor(sf::Color::Green);

			else this->map[i][j].shapeForPlayer.setFillColor(sf::Color::Blue);
		}
	}

	for (int i = 0; i < this->getSizeI(); i++)
	{
		for (int j = 0; j < this->getSizeJ(); j++)
		{
			if(this->map[i][j].shapeForDebug.getGlobalBounds().contains((float)sf::Mouse::getPosition(*window).x, (float)sf::Mouse::getPosition(*window).y))
				this->map[i][j].shapeForDebug.setFillColor(sf::Color::Cyan);

			else if (this->map[i][j].value == 2) this->map[i][j].shapeForDebug.setFillColor(sf::Color::Red);
			
			else if (this->map[i][j].value == 1) this->map[i][j].shapeForDebug.setFillColor(sf::Color::White);

			else if (this->map[i][j].value == 3) this->map[i][j].shapeForDebug.setFillColor(sf::Color::Green);

			else this->map[i][j].shapeForDebug.setFillColor(sf::Color::Blue);
		}
	}
}

void Map::renderMap(sf::RenderWindow* targetWindow) const
{
	for (int i = 0; i < this->getSizeI(); i++)
	{
		for (int j = 0; j < this->getSizeJ(); j++)
		{
			targetWindow->draw(this->map[i][j].shapeForPlayer);
			targetWindow->draw(this->map[i][j].shapeForDebug);
		}
	}
}

void Map::placeShip(const Ship& ship) //for computer's ships
{
	if (ship.getDirection() == true) //горизонтально
	{
		for (int i = ship.getJ(); i < ship.getJ() + ship.getDeckAmount(); i++)
		{
			this->map[ship.getI()][i].value = 1;
			this->map[ship.getI()][i].shapeForDebug.setFillColor(sf::Color::White);
		}
	}
	else // вертикально
	{
		for (int i = ship.getI(); i < ship.getI() + ship.getDeckAmount(); i++)
		{
			this->map[i][ship.getJ()].value = 1;
			this->map[i][ship.getJ()].shapeForDebug.setFillColor(sf::Color::White);
		}
	}
	this->shipsAmount++;
}

bool Map::placeShip(const OutMapShip& outMapShip, const sf::RenderWindow* window) //for player's ships
{
	//determination ship's coordinates in depending on cursor location
	int shipHeadI = 1000;
	int shipHeadJ = 1000;

	for (int i = 0; i < this->getSizeI(); i++)
	{
		for (int j = 0; j < this->getSizeJ(); j++)
		{
			if (this->map[i][j].shapeForPlayer.getGlobalBounds().contains((float)sf::Mouse::getPosition(*window).x, (float)sf::Mouse::getPosition(*window).y))
			{
				shipHeadI = i;
				shipHeadJ = j;
				std::cout << "shipHeadI " << shipHeadI << "   shipHeadJ " << shipHeadJ << std::endl;
			}
		}
	}

	if ((shipHeadI < this->getSizeI()) && (shipHeadJ < this->getSizeJ())) //out of range protection
	{
		if (outMapShip.getDirection() == true) //горизонтально
		{
			if (shipHeadJ + outMapShip.getDeckAmount() <= this->getSizeJ()) //out of range protection
			{
				for (int j = shipHeadJ; j < shipHeadJ + outMapShip.getDeckAmount(); j++)
				{
					this->map[shipHeadI][j].value = 1;
					this->map[shipHeadI][j].shapeForPlayer.setFillColor(sf::Color::White);
				}
			}
			else return false;
		}
		else // вертикально
		{
			if (shipHeadI + outMapShip.getDeckAmount() <= this->getSizeI()) //out of range protection
			{
				for (int i = shipHeadI; i < shipHeadI + outMapShip.getDeckAmount(); i++)
				{
					this->map[i][shipHeadJ].value = 1;
						this->map[i][shipHeadJ].shapeForPlayer.setFillColor(sf::Color::White);
				}
			}
			else return false;
		}
		return true;
		this->shipsAmount++;
	}
	else return false;
	
}

void Map::attack(const sf::RenderWindow* window) 
{
	//determination ship's coordinates in depends on cursor location
	int attackI = 1000;
	int attackJ = 1000;

	for (int i = 0; i < this->getSizeI(); i++)
	{
		for (int j = 0; j < this->getSizeJ(); j++)
		{
			if (this->map[i][j].shapeForPlayer.getGlobalBounds().contains((float)sf::Mouse::getPosition(*window).x, (float)sf::Mouse::getPosition(*window).y))
			{
				attackI = i;
				attackJ = j;
				std::cout << "attackI " << attackI << "   attackj " << attackJ << std::endl;
			}
		}
	}

	if ((attackI < this->getSizeI()) && attackJ < this->getSizeJ())
	{
		for (int i = 0; i < this->ships.size(); i++)
		{
			if ((this->ships[i].isItDamage(attackI, attackJ)) /*&& (attackI < this->getSizeI()) && (attackJ < this->getSizeJ())*/)
			{
				this->map[attackI][attackJ].value = 2;
				if (this->ships[i].getShipHp() == 0)
				{
					this->currentShipsAmount--;

					//fixation area where another ship can't be

					for (int j = 0; j < this->ships[i].getDeckAmount(); j++)
					{
						int currentCoordI = (this->ships[i].getCoordinates() + j)->i;
						int currentCoordJ = (this->ships[i].getCoordinates() + j)->j;

						std::cout << j << " " << this->ships[i].getDeckAmount() << std::endl;

						if (currentCoordI - 1 >= 0             && currentCoordJ - 1 >= 0                                                                )   map[currentCoordI - 1] [currentCoordJ - 1].value = 3;

						if (currentCoordI - 1 >= 0                                                   && map[currentCoordI - 1][currentCoordJ].value != 2)   map[currentCoordI - 1] [currentCoordJ].value = 3;

						if (currentCoordI - 1 >= 0             && currentCoordJ + 1 < this->mapSizeJ                                                    )   map[currentCoordI - 1] [currentCoordJ + 1].value = 3;

						if (                                      currentCoordJ + 1 < this->mapSizeJ && map[currentCoordI][currentCoordJ + 1].value != 2)   map[currentCoordI][currentCoordJ + 1].value = 3;

						if (currentCoordI + 1 < this->mapSizeI && currentCoordJ + 1 < this->mapSizeJ                                                    )   map[currentCoordI + 1][currentCoordJ + 1].value = 3;

						if (currentCoordI + 1 < this->mapSizeI                                       && map[currentCoordI + 1][currentCoordJ].value != 2)   map[currentCoordI + 1][currentCoordJ].value = 3;

						if (currentCoordI + 1 < this->mapSizeI && currentCoordJ - 1 >= 0                                                                )   map[currentCoordI + 1][currentCoordJ - 1].value = 3;

						if (                                      currentCoordJ - 1 >= 0 &&             map[currentCoordI][currentCoordJ - 1].value != 2)   map[currentCoordI][currentCoordJ - 1].value = 3;
					}
				}
				std::cout << "you have hit " << i << " ship" << std::endl;
			}
			else
				if ((map[attackI][attackJ].value == 0) && (attackI < this->getSizeI()) && (attackJ < this->getSizeJ()))
				{
					this->map[attackI][attackJ].value = 3;
					std::cout << "you haven't hit" << i << std::endl;
				}
				std::cout << "you haven't hit" << i << std::endl;
		}
	}
}

Map::PieceOfMap::PieceOfMap()
{
}

Map::PieceOfMap::~PieceOfMap()
{
}
