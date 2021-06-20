#include "Map.h"

//Map for player
Map::Map(float coorWindX, float coorWindY, bool enemy) : prohibitedZone(10, std::vector<int>(10, 0))
{
	std::cout << std::endl;
	std::cout << "----------Map Construcror1----------" << std::endl;

	//init font
	if (!this->font.loadFromFile("Fonts\\font.ttf"))	std::cout << "FontMap error" << std::endl; //should be refined
	
	int coorI = 0;
	int coorJ = 0;
	bool dir = 1;

	this->shipsAmount = 0;
	this->mapSizeI = 10;
	this->mapSizeJ = 10;
	this->ships.reserve(15);

	int scale = 29;
	int textSize = 17;

	this->text12345.resize(mapSizeI);
	this->textABCDE.resize(mapSizeJ);
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
			this->map[i][j].shapeForPlayer.setPosition(sf::Vector2f(coorWindX + textSize + j * scale, coorWindY + (textSize + 5) + i * scale));
			this->map[i][j].shapeForPlayer.getPosition();
		}

		text12345[i].setFont(font);
		text12345[i].setCharacterSize(textSize);
		text12345[i].setPosition(sf::Vector2f(coorWindX, this->map[i][0].shapeForPlayer.getPosition().y + 3));
		text12345[i].setString(std::to_string(i));

		textABCDE[i].setFont(font);
		textABCDE[i].setCharacterSize(textSize);
		textABCDE[i].setPosition(sf::Vector2f(this->map[0][i].shapeForPlayer.getPosition().x + 7, coorWindY));
		char ch = 65 + i;
		textABCDE[i].setString(ch);
	}

	//	//Карта 1
	if (enemy)
	{
		this->randomPlace();
		/*this->ships.emplace_back(1, 3, true, 5);
		this->ships.emplace_back(5, 3, true, 3);
		this->ships.emplace_back(1, 1, false, 3);
		this->ships.emplace_back(8, 8, true, 2);
		this->ships.emplace_back(8, 6, false, 1);

		this->placeShip(ships[0]);
		this->placeShip(ships[1]);
		this->placeShip(ships[2]);
		this->placeShip(ships[3]);
		this->placeShip(ships[4]);

		this->currentShipsAmount = this->shipsAmount;*/
	}

	
	/*
	this->ships.emplace_back(2, 0, true, 5);
this->ships.emplace_back(0, 0, true, 4);
this->ships.emplace_back(9, 1, true, 3);
this->ships.emplace_back(7, 5, true, 2);
this->ships.emplace_back(5, 9, false, 1);

this->placeShip(ships[0]);
this->placeShip(ships[1]);
this->placeShip(ships[2]);
this->placeShip(ships[3]);
this->placeShip(ships[4]);

this->currentShipsAmount = this->ships.size();*/

	std::cout << std::endl;
	this->getMapValue();
	std::cout << "enemyMap Ship quantity = " << this->getShipsAmount() << std::endl;
	std::cout << std::endl;

	std::cout << "----------Map Construcror1 END----------" << std::endl;
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
	std::cout << "-rfr-" << std::endl;
		for (int i = 0; i < this->mapSizeI; i++)
		{
			for (int j = 0; j < this->mapSizeJ; j++)
			{
				std::cout << map[i][j].value << "\t";
			}
			std::cout << std::endl;
		}
}

int Map::getMapValue(int i, int j) const
{
	return this->map[i][j].value;
}

int Map::getShipsAmount() const
{
	return this->shipsAmount;
}

int Map::getCurrentShipsAmount() const
{
	return this->currentShipsAmount;
}

int Map::getProhibitedZoneIJ(int i, int j) const
{
	//std::cout << i << " " << j << std::endl;
	if (i >= 0 && i < this->mapSizeI  && j >=0 && j < this->mapSizeJ)
		return this->prohibitedZone[i][j];
	else return -1;
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
}

void Map::renderMap(sf::RenderWindow* targetWindow) const
{
	for (int i = 0; i < this->getSizeI(); i++)
	{
		targetWindow->draw(this->text12345[i]);
		targetWindow->draw(this->textABCDE[i]);
		for (int j = 0; j < this->getSizeJ(); j++)
		{
			targetWindow->draw(this->map[i][j].shapeForPlayer);
		}
	}
}

void Map::showProhibitedZone()
{
	for (size_t i = 0; i < this->prohibitedZone.size(); i++)
	{
		for (size_t j = 0; j < this->prohibitedZone.size(); j++)
		{
			std::cout << this->prohibitedZone[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void Map::calcProhibitedZone(bool dir, int deckAmount)
{
	//calculate prohibited zone-------------------------------------------
	for (size_t i = 0; i < this->prohibitedZone.size(); i++)
	{
		for (size_t j = 0; j < this->prohibitedZone.size(); j++)
		{
			this->prohibitedZone[i][j] = 0;
			//std::cout << this->prohibitedZone[i][j] << " ";
		}
		//std::cout << std::endl;
	}

	//std::cout << std::endl;

	if (dir) //new ship is gonna be horizontal
	{
		//prohibited zone by bounds of map
		for (int i = 0; i < this->mapSizeI; i++)
		{
			for (int j = this->mapSizeJ - deckAmount + 1; j < this->mapSizeJ; j++)
			{
					this->prohibitedZone[i][j] = 9;
			}
		}

		//prohibited zone by ships
		for (size_t shipCounter = 0; shipCounter < this->ships.size(); shipCounter++)
		{
			int coorShipHeadI = this->ships[shipCounter].getI();
			int coorShipHeadJ = this->ships[shipCounter].getJ();

			if (this->ships[shipCounter].getDirection()) //ship [i] is horizontal
			{
				for (int i = coorShipHeadI - 1; i <= coorShipHeadI + 1; i++)
				{
					for (int j = coorShipHeadJ + this->ships[shipCounter].getDeckAmount(); j >= coorShipHeadJ - deckAmount; j--)
					{
						if (i >= 0 && i < this->mapSizeI && j >= 0 && j < this->mapSizeJ && this->prohibitedZone[i][j] != 2) this->prohibitedZone[i][j] = 1;
						
						//if (i == coorShipHeadI && j == coorShipHeadJ) for (int k = coorShipHeadJ; k < coorShipHeadJ + this->ships[shipCounter].getDeckAmount(); k++) this->prohibitedZone[i][k] = 2; //for debug (determination of ship position)
					}
				}
			}
			else //ship [i] is vertical
			{
				for (int i = coorShipHeadI - 1; i <= coorShipHeadI + this->ships[shipCounter].getDeckAmount(); i++)
				{
					for (int j = coorShipHeadJ + 1 ; j >= coorShipHeadJ - deckAmount; j--)
					{
						if (i >= 0 && i < this->mapSizeI && j >= 0 && j < this->mapSizeJ && this->prohibitedZone[i][j] != 2) this->prohibitedZone[i][j] = 1;

						//if (i == coorShipHeadI && j == coorShipHeadJ) for (int k = coorShipHeadI; k < coorShipHeadI + this->ships[shipCounter].getDeckAmount(); k++) this->prohibitedZone[k][j] = 2; //for debug (determination of ship position)
					}
				}
			}
		}
		//showProhibitedZone(); // for debug
	}
	else //new ship is gonna be vertical--------------------------------------------------------------------------------------------------------------------------------------------
	{
		//prohibited zone by bounds of map
		for (int i = this->mapSizeJ - deckAmount + 1; i < this->mapSizeI; i++)
		{
			for (int j = 0; j < this->mapSizeJ; j++)
			{
				this->prohibitedZone[i][j] = 9;
			}
		}

		//prohibited zone by ships
		for (size_t shipCounter = 0; shipCounter < this->ships.size(); shipCounter++)
		{
			int coorShipHeadI = this->ships[shipCounter].getI();
			int coorShipHeadJ = this->ships[shipCounter].getJ();

			if (this->ships[shipCounter].getDirection()) //ship [i] is horizontal
			{
				for (int i = coorShipHeadI + 1; i >= coorShipHeadI - deckAmount; i--)
				{
					for (int j = coorShipHeadJ - 1; j <= coorShipHeadJ + this->ships[shipCounter].getDeckAmount(); j++)
					{
						if (i >= 0 && i < this->mapSizeI && j >= 0 && j < this->mapSizeJ && this->prohibitedZone[i][j] != 2) this->prohibitedZone[i][j] = 1;

						//if (i == coorShipHeadI && j == coorShipHeadJ) for (int k = coorShipHeadJ; k < coorShipHeadJ + this->ships[shipCounter].getDeckAmount(); k++) this->prohibitedZone[i][k] = 2; //for debug (determination of ship position)
					}
				}
			}
			else //ship [i] is vertical
			{
				for (int i = coorShipHeadI + this->ships[shipCounter].getDeckAmount(); i >= coorShipHeadI - deckAmount; i--)
				{
					for (int j = coorShipHeadJ - 1; j <= coorShipHeadJ + 1; j++)
					{
						if (i >= 0 && i < this->mapSizeI && j >= 0 && j < this->mapSizeJ && this->prohibitedZone[i][j] != 2) this->prohibitedZone[i][j] = 1;

						if (i == coorShipHeadI && j == coorShipHeadJ) for (int k = coorShipHeadI; k < coorShipHeadI + this->ships[shipCounter].getDeckAmount(); k++) this->prohibitedZone[k][j] = 2; //for debug (determination of ship position)
					}
				}
			}
		}
		//showProhibitedZone(); // for debug
	}
}

bool Map::calcCoordinanes(bool dir, int deckAmount)
{
	std::cout << "na4alo" << " dir = " << dir << std::endl;

	calcProhibitedZone(dir, deckAmount);


	//calculate coordinates of head of ship-------------------------------
	this->nonRepeatVector.clear();

	for (size_t i = 0; i < this->prohibitedZone.size(); i++)
	{
		for (size_t j = 0; j < this->prohibitedZone.size(); j++)
		{
			if (this->prohibitedZone[i][j] == 0)
			{
				this->nonRepeatVector.push_back(i * 10 + j);
				//std::cout << i << " " << *(this->nonRepeatVector.end()-1) << std::endl;
			}
		}
	}

	if (this->nonRepeatVector.size())
	{
		int randomNunber = rand() % this->nonRepeatVector.size();
		coorJ = nonRepeatVector[randomNunber] % 10;
		coorI = (nonRepeatVector[randomNunber] - coorJ) / 10;

		std::cout << " nonRepeatVector = " << nonRepeatVector[randomNunber] << " coorI = " << coorI << " j = " << coorJ << std::endl;

		//if (dir && coorJ > 5) coorJ = coorJ - 4;
		//else if (coorI > 5) coorI = coorI - 4;

		this->ships.emplace_back(coorI, coorJ, dir, deckAmount);
		this->placeShip(*(ships.end() - 1));
		return 1;
	}
	else return 0;
}

void Map::randomPlace()
{
	int shipsForRandPlacing[5];
	shipsForRandPlacing[0] = 3;	//1 deck
	shipsForRandPlacing[1] = 3; //2 deck
	shipsForRandPlacing[2] = 2; //3 deck
	shipsForRandPlacing[3] = 1; //4 deck
	shipsForRandPlacing[4] = 0; //5 deck

	this->clearMap();

	for (int i = 4; i >= 0; i--)
	{
		while (shipsForRandPlacing[i])
		{
			std::cout << "sum " << shipsForRandPlacing[0] + shipsForRandPlacing[1] + shipsForRandPlacing[2] + shipsForRandPlacing[3] + shipsForRandPlacing[4] << std::endl;
			int dir = rand() % 2; //0 - vertical, 1 - horizontal
			shipsForRandPlacing[i]--;
			if (!calcCoordinanes(dir, i + 1))
			{
				if (!calcCoordinanes(!dir, i + 1))
				{
					std::cout << "Placing ERROR " << i + 1 << std::endl;
					i = 0;
					break;
				}
			}
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
		}
	}
	else // вертикально
	{
		for (int i = ship.getI(); i < ship.getI() + ship.getDeckAmount(); i++)
		{
			this->map[i][ship.getJ()].value = 1;
		}
	}
	this->shipsAmount++;
	this->currentShipsAmount = this->shipsAmount;
}

bool Map::placeShip(const OutMapShip& outMapShip, const sf::RenderWindow* window) //for player's ships
{
	int number = this->determinationChosenMapField(window);

	if (number < 100)
	{
		this->calcProhibitedZone(outMapShip.getDirection(), outMapShip.getDeckAmount());
		int coorJ = number % 10;
		int coorI = (number - coorJ) / 10;
		if (this->prohibitedZone[coorI][coorJ] == 0)
		{
			this->ships.emplace_back(coorI, coorJ, outMapShip.getDirection(), outMapShip.getDeckAmount());
			this->placeShip(*(ships.end() - 1));
			return 1;
		}
		else return 0;
	}
	else return 0;
}


int Map::attack(int attackI, int attackJ)
{
	//return 0 - if miss;
	//return 1 - if the ship has been damaged;
	//return 2 - if the ship has been destroyed;

	if ((attackI < this->getSizeI()) && attackJ < this->getSizeJ()) //out of range check
	{
		for (size_t shipCounter = 0; shipCounter < this->ships.size(); shipCounter++)
		{
			if (this->ships[shipCounter].isItDamage(attackI, attackJ)) //has the ship been damaged?
			{
				this->map[attackI][attackJ].value = 2; //mark destroyed deck

				if (this->ships[shipCounter].getShipHp() == 0) //has the ship been destoyed?
				{
					this->currentShipsAmount--;

					//fixation area where another ship can't be
					int coorShipHeadI = this->ships[shipCounter].getI();
					int coorShipHeadJ = this->ships[shipCounter].getJ();

					if (this->ships[shipCounter].getDirection()) //horizontal
					{
						for (int i = coorShipHeadI - 1; i <= coorShipHeadI + 1; i++)
						{
							for (int j = coorShipHeadJ - 1; j <= coorShipHeadJ + this->ships[shipCounter].getDeckAmount(); j++)
							{
								if (i >= 0 && i < this->mapSizeI && j >= 0 && j < this->mapSizeJ)
								{
									if(this->map[i][j].value == 0) this->map[i][j].value = 3;
								}
									
							}
						}
					}
					else //vertical
					{
						for (int i = coorShipHeadI - 1; i <= coorShipHeadI + this->ships[shipCounter].getDeckAmount(); i++)
						{
							for (int j = coorShipHeadJ - 1; j <= coorShipHeadJ + 1; j++)
							{
								if (i >= 0 && i < this->mapSizeI && j >= 0 && j < this->mapSizeJ)
								{
									if (this->map[i][j].value == 0) this->map[i][j].value = 3;
								}
							}
						}
					}

					std::cout << "you have destroyed " << shipCounter << " ship" << std::endl;
					return 2;
				}
				else
				{
					std::cout << "you have damaged " << shipCounter << " ship" << std::endl;
					return 1;
				}
			}
			else if (map[attackI][attackJ].value == 0)
			{
				this->map[attackI][attackJ].value = 3;
				std::cout << "you haven't damaged " << shipCounter << std::endl;
				return 0;
			}
		}
	}
	else return 0;
}

void Map::clearMap()
{
	this->ships.clear();
	for (int i = 0; i < this->mapSizeI; i++)
	{
		this->map[i].resize(mapSizeJ);
		for (int j = 0; j < this->mapSizeJ; j++)
		{
			this->map[i][j].value = 0;
		}
	}
	this->shipsAmount = 0;
	this->currentShipsAmount = 0;
}

Map::PieceOfMap::PieceOfMap()
{
}

Map::PieceOfMap::~PieceOfMap()
{
}


int Map::determinationChosenMapField(const sf::RenderWindow* const window)
{
	//determination Chosen Map Field in depending on cursor location
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
				//std::cout << "shipHeadI " << shipHeadI << "   shipHeadJ " << shipHeadJ << std::endl;
			}
		}
	}

	return shipHeadI * 10 + shipHeadJ;
}

