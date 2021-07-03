#include "Map.h"

Map::PieceOfMap::PieceOfMap()
{
	this->value = 0;
	this->shape.setSize(sf::Vector2f(27.f, 27.f));
	this->shape.setFillColor(sf::Color(0,153,255,200));
	this->shape.setOutlineThickness(1.f);
	this->shape.setOutlineColor(sf::Color::Black);
	this->shape.getPosition();
}

Map::PieceOfMap::~PieceOfMap()
{
}

Map::Map(float coorWindX, float coorWindY, bool enemy) : prohibitedZone(10, std::vector<int>(10, 0))
{
#ifdef DEBUG_MAP
	std::cout << std::endl;
	std::cout << "----------Map Construcror1----------" << std::endl;
#endif
	//init font
	if (!this->font.loadFromFile("Fonts\\font.ttf"))	std::cout << "FontMap error" << std::endl; //should be refined
	
	//init var
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
			this->map[i][j].shape.setPosition(sf::Vector2f(coorWindX + textSize + j * scale, coorWindY + (textSize + 5) + i * scale));
		}

		//init texts
		text12345[i].setFont(font);
		text12345[i].setCharacterSize(textSize);
		text12345[i].setPosition(sf::Vector2f(coorWindX, this->map[i][0].shape.getPosition().y + 3));
		text12345[i].setString(std::to_string(i));

		textABCDE[i].setFont(font);
		textABCDE[i].setCharacterSize(textSize);
		textABCDE[i].setPosition(sf::Vector2f(this->map[0][i].shape.getPosition().x + 7, coorWindY));
		char ch = 65 + i;
		textABCDE[i].setString(ch);
	}

	textWhoseMap.setFont(font);
	textWhoseMap.setCharacterSize(21);
	textWhoseMap.setPosition(sf::Vector2f(coorWindX, this->map[0][0].shape.getPosition().y - 55));
	textWhoseMap.setString("Your map:");
	
	if (enemy)
	{
		this->randomPlace();
		textWhoseMap.setString("Enemy's map:");
	}

#ifdef DEBUG_MAP
	std::cout << std::endl;
	this->getMapValue();
	std::cout << "enemyMap Ship quantity = " << this->getShipsAmount() << std::endl;
	std::cout << std::endl;

	std::cout << "----------Map Construcror1 END----------" << std::endl;
	std::cout << std::endl;
#endif
}

Map::~Map()
{
#ifdef DEBUG_MAP
	std::cout << "----------MAP DESTR--------" << std::endl;
#endif
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

const MapCoord& Map::getChosenField() const
{
	return chosenField;
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

int Map::getProhibitedZoneIJ(const MapCoord& mapCoord)
{
	//std::cout << mapCoord.i << " " << mapCoord.j << std::endl;
	if (mapCoord.i >= 0 && mapCoord.i < this->mapSizeI  && mapCoord.j >=0 && mapCoord.j < this->mapSizeJ)
		return this->prohibitedZone[mapCoord.i][mapCoord.j];
	else return -1;
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

void Map::calcProhibitedZone(bool dir, int deckAmount, bool isMidAvailable)
{
	//calculate prohibited zone-------------------------------------------
	for (size_t i = 0; i < this->prohibitedZone.size(); i++)
	{
		for (size_t j = 0; j < this->prohibitedZone.size(); j++)
		{
				this->prohibitedZone[i][j] = 0;
		}
	}

	for (size_t i = 0; i < this->prohibitedZone.size(); i++)
	{
		for (size_t j = 0; j < this->prohibitedZone.size(); j++)
		{
			if (isMidAvailable == 0)
			{
				if (dir)
				{
					if(i > 1 && i < mapSizeI - 2)
					this->prohibitedZone[i][j] = 9;
				}
				else 
				{
					if (j > 1 && j < mapSizeJ - 2)
					this->prohibitedZone[i][j] = 9;
				}
			}
			else
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

bool Map::calcCoordinanes(bool dir, int deckAmount, bool isMidAvailable)
{
#ifdef DEBUG_MAP
	std::cout << "na4alo" << " dir = " << dir <<  std::endl;
#endif
	calcProhibitedZone(dir, deckAmount, isMidAvailable);


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
		int coorJ = nonRepeatVector[randomNunber] % 10;
		int coorI = (nonRepeatVector[randomNunber] - coorJ) / 10;
#ifdef DEBUG_MAP
		std::cout << " nonRepeatVector = " << nonRepeatVector[randomNunber] << " coorI = " << coorI << " j = " << coorJ << std::endl;
#endif
		this->ships.emplace_back(coorI, coorJ, dir, deckAmount);
		this->placeShip(*(ships.end() - 1));
		return 1;
	}
	else return 0;
}

void Map::randomPlace()
{
	int shipsForRandPlacing[5];
	shipsForRandPlacing[0] = 4;	//1 deck
	shipsForRandPlacing[1] = 3; //2 deck
	shipsForRandPlacing[2] = 2; //3 deck
	shipsForRandPlacing[3] = 1; //4 deck
	shipsForRandPlacing[4] = 0; //5 deck

	this->clearMap();

	for (int i = 4; i >= 0; i--)
	{
		while (shipsForRandPlacing[i])
		{
			int dir = rand() % 2; //0 - vertical, 1 - horizontal
			shipsForRandPlacing[i]--;
			if (i)
			{
				if (!calcCoordinanes(dir, i + 1))
				{
					if (!calcCoordinanes(!dir, i + 1))
					{
#ifdef DEBUG_MAP
						std::cout << "Placing ERROR " << i + 1 << std::endl;
#endif
						i = 0;
						break;
					}
				}
			}
			else
			{
				if (!calcCoordinanes(!dir, i + 1, 1))
				{
#ifdef DEBUG_MAP
					std::cout << "Placing ERROR " << i + 1 << std::endl;
#endif
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

bool Map::placeShip(const OutMapShip& outMapShip) //for player's ships
{
	if (this->chosenField.i == -1) return 0;
	else
	{
		this->calcProhibitedZone(outMapShip.getDirection(), outMapShip.getDeckAmount(), 1);
		if (this->prohibitedZone[this->chosenField.i][this->chosenField.j] == 0)
		{
			this->ships.emplace_back(this->chosenField.i, this->chosenField.j, outMapShip.getDirection(), outMapShip.getDeckAmount());
			this->placeShip(*(ships.end() - 1));
			return 1;
		}
		else return 0;
	}
	return 0;
}


int Map::attack(const MapCoord& mapCoord)
{
	
	//return 0 - if miss;
	//return 1 - if the ship has been damaged;
	//return 2 - if the ship has been destroyed;
	//return -1 - incorrect parametrs;
	if (mapCoord.i == -1) return (-1);//out of range check		

	switch (this->map[mapCoord.i][mapCoord.j].value)
	{
		case 1: //gotcha
			for (size_t shipCounter = 0; shipCounter < this->ships.size(); shipCounter++)
			{
				if (this->ships[shipCounter].isItDamage(mapCoord.i, mapCoord.j)) //which ship has been damaged?
				{
					this->map[mapCoord.i][mapCoord.j].value = 2;

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
										if (this->map[i][j].value == 0) this->map[i][j].value = 3;
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
						return 2;
					}
				}
			}
			return 1;

		case 0: //miss
			this->map[mapCoord.i][mapCoord.j].value = 3;
			return 0;
		case 2: //attack the same field second time
		case 3: //attack the same field second time
			return 0;
	}
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

void Map::updateMap(const sf::RenderWindow* window, bool enemyMap)
{
	//determination Chosen Map Field in depending on cursor location

	chosenField.i = -1;
	chosenField.j = -1;

	for (int i = 0; i < this->getSizeI(); i++)
	{
		for (int j = 0; j < this->getSizeJ(); j++)
		{
			if (this->map[i][j].shape.getGlobalBounds().contains((float)sf::Mouse::getPosition(*window).x, (float)sf::Mouse::getPosition(*window).y))
			{
				this->map[i][j].shape.setFillColor(sf::Color::Cyan);
				chosenField.i = i;
				chosenField.j = j;
			}

			else if (this->map[i][j].value == 2) this->map[i][j].shape.setFillColor(sf::Color(255, 0, 0, 230));

			else if (this->map[i][j].value == 1 && enemyMap == 0) this->map[i][j].shape.setFillColor(sf::Color(255, 255, 255, 230));

			else if (this->map[i][j].value == 3) this->map[i][j].shape.setFillColor(sf::Color(0, 255, 0, 230));

			else
			{
				this->map[i][j].shape.setFillColor(sf::Color(0, 102, 255, 230));
			}

		}
	}

	//std::cout << "shipHeadI " << chosenField.i << "   shipHeadJ " << chosenField.j << std::endl;
}

void Map::renderMap(sf::RenderWindow* targetWindow) const
{
	targetWindow->draw(textWhoseMap);

	for (int i = 0; i < this->getSizeI(); i++)
	{
		targetWindow->draw(this->text12345[i]);
		targetWindow->draw(this->textABCDE[i]);
		for (int j = 0; j < this->getSizeJ(); j++)
		{
			targetWindow->draw(this->map[i][j].shape);
		}
	}
}
