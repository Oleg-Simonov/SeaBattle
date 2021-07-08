#include "Ship.h"

Ship::Ship(int headShipI, int headShipJ, bool direction , int deckAmount) : headShipI(headShipI), headShipJ(headShipJ), direction(direction), deckAmount(deckAmount)
{
	//std::cout << "---ShipConstruktor---" << std::endl;
	this->hp = deckAmount;
	//std::cout << "---ShipConstruktor END---" << std::endl;
}

Ship::~Ship()
{
	//std::cout << "ShipDestruktor" << std::endl;
}

int Ship::getI() const
{
	return this->headShipI;
}

int Ship::getJ() const
{
	return this->headShipJ;
}

int Ship::getDeckAmount() const
{
	return this->deckAmount;
}

bool Ship::getDirection() const
{
	return this->direction;
}

int Ship::getShipHp() const
{
	return this->hp;
}

void Ship::turn(int mapSize)
{
	//turnededArray[i][j] = initialArray[size - 1 - j][i];
	//turnededArray[i][j] = initialArray[j][size - 1 - i];
	//turnededArray[i][j] = initialArray[j][size - 1 - i]; //counterclockwise
	if ((this->headShipJ <= mapSize / 2 || this->headShipJ >= mapSize / 2) && this->direction == 0)
	{
		int temp = this->headShipI;
		this->headShipI = mapSize - 1 - headShipJ;
		this->headShipJ = temp;
		this->direction = !this->direction;
	}
	else if ((this->headShipI >= mapSize / 2 || this->headShipI <= mapSize / 2) && this->direction == 1)
	{
		int temp = this->headShipI;
		this->headShipI = mapSize - this->deckAmount - headShipJ;
		this->headShipJ = temp;
		this->direction = !this->direction;
	}
}


void Ship::reflect(int mapSize)
{
	//reflectedArray[i][j] = initialArray[size - 1 - i][j];
	if (this->direction)
		this->headShipI = mapSize - 1 - this->headShipI;
	else
		this->headShipI = mapSize - (headShipI + this->deckAmount);
}

int Ship::isItDamage(int attakI, int attakJ)
{
	for (int i = 0; i < this->deckAmount; i++)
	{
		if (this->direction) //the ship is horizontal
		{
			if (this->headShipI == attakI && this->headShipJ + i == attakJ)
			{
				hp--;
				return 1;
			}
		}
		else //the ship is vertical
		{
			if (this->headShipI + i == attakI && this->headShipJ == attakJ)
			{
				hp--;
				return 1;
			}
		}
	}
	return 0;
}
