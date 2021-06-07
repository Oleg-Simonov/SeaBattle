#include "Map.h"

//Map for player
Map::Map() : prohibitedZone(10, std::vector<int>(10, 0))
{
	std::cout << std::endl;
	std::cout << "----------Map Construcror1----------" << std::endl;

	this->deck1 = 1;
	this->deck2 = 1;
	this->deck3 = 1;
	this->deck4 = 1;
	this->deck5 = 1;

	int coorI = 0;
	int coorJ = 0;
	bool dir = 1;

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
			this->map[i][j].shapeForPlayer.setPosition(sf::Vector2f(30.f + j * 29, 50.f + i * 29));
		}
	}
	
/*this->ships.emplace_back(3, 7, false, 5);
this->ships.emplace_back(1, 1, true, 3);
this->ships.emplace_back(4, 1, true, 4);
this->ships.emplace_back(7, 2, true, 3);
this->ships.emplace_back(9, 0, false, 1);*/

/*
this->ships.emplace_back(5, 0, true, 5);
this->ships.emplace_back(5, 5, true, 1);
this->ships.emplace_back(5, 5, true, 1);
this->ships.emplace_back(5, 5, true, 1);
this->ships.emplace_back(5, 5, false, 1);*/

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

int Map::getMapValue(int i, int j) const
{
	return this->map[i][j].value;
}

/*sf::RectangleShape Map::getMapValue(int i, int j) const
{
	return this->map[i][j].shapeForDebug;
}*/

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

void Map::calcProhibitedZone(int deckAmount)
{
	std::cout << "na4alo" << std::endl;

	//calculate prohibited zone-------------------------------------------
	for (int i = 0; i < this->prohibitedZone.size(); i++)
	{
		for (int j = 0; j < this->prohibitedZone.size(); j++)
		{
			this->prohibitedZone[i][j] = 0;
			std::cout << this->prohibitedZone[i][j] << " ";
		}
		std::cout << std::endl;
	}
	
	std::cout << std::endl;

	dir = rand() % 2; //0 - vertical, 1 - horizontal
	/*if (this->ships.size())
	{
		dir = 0;
	}
	else dir = 1;*/
	

	
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
		for (int shipCounter = 0; shipCounter < this->ships.size(); shipCounter++)
		{
			int coorShipHeadI = this->ships[shipCounter].getI();
			int coorShipHeadJ = this->ships[shipCounter].getJ();

			//prohibited zone around ship
			if (this->ships[shipCounter].getDirection()) //ship [i] is horizontal
			{
				for (int deckCounter = 0; deckCounter < this->ships[shipCounter].getDeckAmount(); deckCounter++)
				{
					for (int i = coorShipHeadI - 1; i <= coorShipHeadI + 1; i++)
					{
						for (int j = coorShipHeadJ - 1 + deckCounter; j <= coorShipHeadJ + 1 + deckCounter; j++)
						{
							this->prohibitedZone[coorShipHeadI][coorShipHeadJ + deckCounter] = 2;
							if (i >= 0 && i < this->mapSizeI && j >= 0 && j < this->mapSizeJ && this->prohibitedZone[i][j] == 0) this->prohibitedZone[i][j] = 1;
						}
					}
				}

				for (int i = coorShipHeadI - 1; i <= coorShipHeadI + 1 && i >= 0 && i < this->mapSizeI; i++)
				{
					for (int j = coorShipHeadJ - 1; j >= coorShipHeadJ - deckAmount && j >= 0 && j < this->mapSizeJ; j--)
					{
						std::cout << "i = " << i << "j = " << j << std::endl;

						//if (i >= 0 && i < this->mapSizeI && j >= 0 && j < this->mapSizeJ) 
						this->prohibitedZone[i][j] = 7;

					}
				}
			}
			else //ship [i] is vertical
			{
				for (int deckCounter = 0; deckCounter < this->ships[shipCounter].getDeckAmount(); deckCounter++)
				{
					for (int i = coorShipHeadI - 1 + deckCounter; i <= coorShipHeadI + 1 + deckCounter; i++)
					{
						for (int j = coorShipHeadJ - 1; j <= coorShipHeadJ + 1; j++)
						{
							this->prohibitedZone[coorShipHeadI + deckCounter][coorShipHeadJ] = 2;
							if (i >= 0 && i < this->mapSizeI && j >= 0 && j < this->mapSizeJ && this->prohibitedZone[i][j] == 0) this->prohibitedZone[i][j] = 1;
						}
					}
				}

				for (int i = coorShipHeadI - 1; i <= coorShipHeadI + this->ships[shipCounter].getDeckAmount() /*&& i >= 0 && i < this->mapSizeI*/; i++)
				{
					for (int j = coorShipHeadJ - 1; j >= coorShipHeadJ - deckAmount /*&& j >= 0 && j < this->mapSizeJ*/; j--)
					{
						std::cout << "i = " << i << "j = " << j << std::endl;

						if (i >= 0 && i < this->mapSizeI && j >= 0 && j < this->mapSizeJ) 
						this->prohibitedZone[i][j] = 7;

					}
				}
			}
		}
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
		for (int shipCounter = 0; shipCounter < this->ships.size(); shipCounter++)
		{
			int coorShipHeadI = this->ships[shipCounter].getI();
			int coorShipHeadJ = this->ships[shipCounter].getJ();

			//prohibited zone around ship
			if (this->ships[shipCounter].getDirection()) //ship [i] is horizontal
			{
				for (int deckCounter = 0; deckCounter < this->ships[shipCounter].getDeckAmount(); deckCounter++)
				{
					for (int i = coorShipHeadI - 1; i <= coorShipHeadI + 1; i++)
					{
						for (int j = coorShipHeadJ - 1 + deckCounter; j <= coorShipHeadJ + 1 + deckCounter; j++)
						{
							this->prohibitedZone[coorShipHeadI][coorShipHeadJ + deckCounter] = 2;
							if (i >= 0 && i < this->mapSizeI && j >= 0 && j < this->mapSizeJ && this->prohibitedZone[i][j] == 0) this->prohibitedZone[i][j] = 1;
						}
					}
				}

				for (int i = coorShipHeadI - 1; i >= coorShipHeadI - deckAmount; i--)
				{
					for (int j = coorShipHeadJ - 1; j <= coorShipHeadJ + this->ships[shipCounter].getDeckAmount(); j++)
					{
						std::cout << "i = " << i << "j = " << j << std::endl;

						if (i >= 0 && i < this->mapSizeI && j >= 0 && j < this->mapSizeJ) 
						this->prohibitedZone[i][j] = 7;

					}
				}
			}
			else //ship [i] is vertical
			{
				for (int deckCounter = 0; deckCounter < this->ships[shipCounter].getDeckAmount(); deckCounter++)
				{
					for (int i = coorShipHeadI - 1 + deckCounter; i <= coorShipHeadI + 1 + deckCounter; i++)
					{
						for (int j = coorShipHeadJ - 1; j <= coorShipHeadJ + 1; j++)
						{
							this->prohibitedZone[coorShipHeadI + deckCounter][coorShipHeadJ] = 2;
							if (i >= 0 && i < this->mapSizeI && j >= 0 && j < this->mapSizeJ && this->prohibitedZone[i][j] == 0) this->prohibitedZone[i][j] = 1;
						}
					}
				}

				for (int i = coorShipHeadI - 1; i >= coorShipHeadI - deckAmount; i--)
				{
					for (int j = coorShipHeadJ - 1; j <= coorShipHeadJ + 1; j++)
					{
						std::cout << "i = " << i << "j = " << j << std::endl;

						if (i >= 0 && i < this->mapSizeI && j >= 0 && j < this->mapSizeJ)
							this->prohibitedZone[i][j] = 7;

					}
				}
			}
		}


	}

	for (int j = 0; j < this->prohibitedZone.size(); j++)
	{
		for (int k = 0; k < this->prohibitedZone.size(); k++)
		{
			std::cout << this->prohibitedZone[j][k] << " ";
		}
		std::cout << std::endl;
	}

	//calculate coordinates of head of ship-------------------------------

	this->nonRepeatVector.clear();

	for (int i = 0; i < this->prohibitedZone.size(); i++)
	{
		for (int j = 0; j < this->prohibitedZone.size(); j++)
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
	}
	else
	{
		dir = !dir;
		std::cout << " YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY" << std::endl;
	}
		
		

			/*int coorShipHeadI = this->ships[i].getI();
			int coorShipHeadJ = this->ships[i].getJ();
			for (int j = 0; j < this->ships[i].getDeckAmount(); j++)
			{
				this->prohibitedZone[coorShipHeadI][coorShipHeadJ] = 2;

				if (coorShipHeadI - 1 >= 0 && coorShipHeadJ - 1 >= 0 && this->map[coorShipHeadI - 1][coorShipHeadJ - 1].value == 0) this->prohibitedZone[coorShipHeadI - 1][coorShipHeadJ - 1] = 1;

				if (coorShipHeadI + 1 < this->mapSizeI && coorShipHeadJ - 1 >= 0 && this->map[coorShipHeadI + 1][coorShipHeadJ - 1].value == 0) this->prohibitedZone[coorShipHeadI + 1][coorShipHeadJ - 1] = 1;

				if (coorShipHeadI - 1 >= 0 && coorShipHeadJ + 1 < this->mapSizeJ && this->map[coorShipHeadI - 1][coorShipHeadJ + 1].value == 0) this->prohibitedZone[coorShipHeadI - 1][coorShipHeadJ + 1] = 1;

				if (coorShipHeadI + 1 < this->mapSizeI && coorShipHeadJ + 1 < this->mapSizeJ && this->map[coorShipHeadI + 1][coorShipHeadJ + 1].value == 0) this->prohibitedZone[coorShipHeadI + 1][coorShipHeadJ + 1] = 1;


				if (coorShipHeadI - 1 >= 0 && this->map[coorShipHeadI - 1][coorShipHeadJ].value == 0) this->prohibitedZone[coorShipHeadI - 1][coorShipHeadJ] = 1;

				if (coorShipHeadI + 1 < this->mapSizeI && this->map[coorShipHeadI + 1][coorShipHeadJ].value == 0) this->prohibitedZone[coorShipHeadI + 1][coorShipHeadJ] = 1;

				if (coorShipHeadJ - 1 >= 0 && this->map[coorShipHeadI][coorShipHeadJ - 1].value == 0) this->prohibitedZone[coorShipHeadI][coorShipHeadJ - 1] = 1;

				if (coorShipHeadJ + 1 < this->mapSizeJ && this->map[coorShipHeadI][coorShipHeadJ + 1].value == 0) this->prohibitedZone[coorShipHeadI][coorShipHeadJ + 1] = 1;

				std::cout << "i = " << i << "j = " << j << std::endl;
				if (this->ships[i].getDirection())
				{
					for (int i = coorShipHeadI - 1; i <= coorShipHeadI + 1; i++)
					{
						for (int j = coorShipHeadJ - 1; j > coorShipHeadJ - deckAmount; j--)
						{
							std::cout << "i = " << i << "j = " << j << std::endl;

							if (i >= 0 && i < this->mapSizeI && j >= 0 && j < this->mapSizeJ) this->prohibitedZone[i][j] = 1;

						}
					}

					//for (int j = coorShipHeadJ; j < this->ships[i].getDeckAmount() + coorShipHeadJ; j++)
					//{
					//	for (int k = 2; k <= deckAmount; k++)
					//	{
					//		if (coorShipHeadI - k >= 0)
					//		{
					//			this->prohibitedZone[coorShipHeadI - k][coorShipHeadJ] = 1;
					//			if (coorShipHeadJ - 1 >= 0) this->prohibitedZone[coorShipHeadI - k][coorShipHeadJ - 1] = 1;
					//			if (coorShipHeadJ + 1 < this->mapSizeJ) this->prohibitedZone[coorShipHeadI - k][coorShipHeadJ + 1] = 1;
					//		}
					//	}
					//}

					coorShipHeadJ++;
				}
				else
				{
					for (int j = coorShipHeadI; j < this->ships[i].getDeckAmount() + coorShipHeadI; j++)
					{
						for (int k = 2; k <= deckAmount; k++)
						{
							if (coorShipHeadJ - k >= 0)
							{
								this->prohibitedZone[coorShipHeadI][coorShipHeadJ - k] = 1;
								if (coorShipHeadI - 1 >= 0) this->prohibitedZone[coorShipHeadI - 1][coorShipHeadJ - k] = 1;
								if (coorShipHeadI + 1 < this->mapSizeJ) this->prohibitedZone[coorShipHeadI + 1][coorShipHeadJ - k] = 1;
							}
						}
					}
					coorShipHeadI++;
				}
			}*/






	/*for (int i = 0; i < this->nonRepeatVector.size(); i++)
	{
		std::cout << i << " " << this->nonRepeatVector[i] << std::endl;
	}*/

	/*int randomCoor = rand() % this->nonRepeatVector.size();

	coorOfStrike.j = nonRepeatVector[randomCoor] % 10;
	coorOfStrike.i = (nonRepeatVector[randomCoor] - coorOfStrike.j) / 10;


	coorI = rand() % 10;
	coorJ = rand() % 10;
	dir = rand() % 2; //0 - vertical, 1 - horizontal,

	//coorI = 3;
	//coorJ = 3;
	//dir = 0;

	if (dir && coorJ > 5) coorJ = coorJ - 4;
	else if (coorI > 5) coorI = coorI - 4;

	this->ships.emplace_back(coorI, coorJ, dir, deckAmount);
	this->placeShip(*(ships.end() - 1));*/

}

void Map::randomPlace()
{
	this->deck1 = 0;
	this->deck2 = 0;
	this->deck3 = 0;
	this->deck4 = 0;
	this->deck5 = 4;

	this->clearMap();

	while(this->deck1 + this->deck2 + this->deck3 + this->deck4 + this->deck5)
	{
		std::cout << "sum "<< this->deck1 + this->deck2 + this->deck3 + this->deck4 + this->deck5 << std::endl;

		if (this->deck5)
		{
			this->calcProhibitedZone(5);
			
			this->deck5--;
		}

		else if (this->deck4)
		{
			this->deck4--;
		}

		else if (this->deck3)
		{
			this->deck3--;
		}

		else if (this->deck2)
		{
			this->deck2--;
		}

		else if (this->deck1)
		{
			this->deck1--;
		}

		else std::cout << "???" << std::endl;

	}
}

void Map::placeShip(int coorI, int coorJ, bool dir, int deckAmount)
{
	this->ships.emplace_back(coorI, coorJ, dir, deckAmount);
	this->placeShip(*(ships.end()-1));

		/*for (int i = 0; i < deckAmount; i++)
		{
			if (coorI - 1 >= 0 && coorJ - 1 >= 0 && this->map[coorI - 1][coorJ- 1].value == 0) this->map[coorI - 1][coorJ - 1].value = 3;

			if (coorI + 1 < this->mapSizeI && coorJ - 1 >= 0 && this->map[coorI + 1][coorJ - 1].value == 0) this->map[coorI + 1][coorJ - 1].value = 3;

			if (coorI - 1 >= 0 && coorJ + 1 < this->mapSizeJ && this->map[coorI - 1][coorJ + 1].value == 0) this->map[coorI - 1][coorJ + 1].value = 3;

			if (coorI + 1 < this->mapSizeI && coorJ + 1 < this->mapSizeJ && this->map[coorI + 1][coorJ + 1].value == 0) this->map[coorI + 1][coorJ + 1].value = 3;



			if (coorI - 1 >= 0 && this->map[coorI - 1][coorJ].value == 0) this->map[coorI - 1][coorJ].value = 3;

			if (coorI + 1 < this->mapSizeI && this->map[coorI + 1][coorJ].value == 0) this->map[coorI + 1][coorJ].value = 3;

			if (coorJ - 1 >= 0 && this->map[coorI][coorJ - 1].value == 0) this->map[coorI][coorJ - 1].value = 3;

			if (coorJ + 1 < this->mapSizeJ && this->map[coorI][coorJ + 1].value == 0) this->map[coorI][coorJ + 1].value = 3;
			
			if (dir)
			{
				coorJ++;
			}
			else
			{
				coorI++;
			}
		}*/
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


int Map::attack(const sf::RenderWindow* window, int attackI, int attackJ)
{
	//return 0 - if miss;
	//return 1 - if the ship has been damaged;
	//return 2 - if the ship has been destroyed;

	//determination ship's coordinates in depends on cursor location
	if (attackI == 1000 && attackJ == 1000)
	{
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
					std::cout << "you have destroyed " << i << " ship" << std::endl;
					return 2;
				}
				std::cout << "you have damaged " << i << " ship" << std::endl;
				return 1;
			}
			else
				//marking empty erea
				if ((map[attackI][attackJ].value == 0) && (attackI < this->getSizeI()) && (attackJ < this->getSizeJ()))
				{
					this->map[attackI][attackJ].value = 3;
					std::cout << "you haven't damaged " << i << std::endl;
					return 0;
				}
				//std::cout << "you haven't hit " << i << std::endl;
				//return 0;
		}
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
}

Map::PieceOfMap::PieceOfMap()
{
}

Map::PieceOfMap::~PieceOfMap()
{
}
