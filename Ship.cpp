#include "Ship.h"

Ship::Ship(int headShipI, int headShipJ, bool direction , int deckAmount) : headShipI(headShipI), headShipJ(headShipJ), direction(direction), deckAmount(deckAmount)
{
	this->hp = deckAmount;
	std::cout << "---ShipConstruktor---" << std::endl;

	this->coordinates.reserve(deckAmount);
	for (int i = 0; i < deckAmount; i++)
	{
		if (direction) this->coordinates.emplace_back(headShipI, headShipJ + i);

		else this->coordinates.emplace_back(headShipI + i, headShipJ);

		std::cout << this->coordinates[i].i << "   " << this->coordinates[i].j << std::endl;
	}
	std::cout << "cap" << this->coordinates.capacity() << " size" << this->coordinates.size() << std::endl;

	std::cout << "---ShipConstruktor END---" << std::endl;
}

Ship::~Ship()
{
	std::cout << "ShipDestruktor" << std::endl;
}

int Ship::getI() const
{
	return this->headShipI;
}

int Ship::getJ() const
{
	return this->headShipJ;
}

bool Ship::getDirection() const
{
	return this->direction;
}

int Ship::getDeckAmount() const
{
	return this->deckAmount;
}

int Ship::getShipHp() const
{
	return this->hp;
}

void Ship::getDataForLog()
{
	std::cout << " x = "<< this->headShipI <<
				 " y = " << this->headShipJ <<
				 " xp = " << this->hp <<
				 " dir = " << this->direction <<
				 " deckAmount = " << this->deckAmount << std::endl;
}

std::vector<Ship::Coordinates>::const_iterator Ship::getCoordinates() const
{
	return this->coordinates.begin();
}

int Ship::isItDamage(int attakI, int attakJ)
{

	/*for (int i = 0; i < this->deckAmount; i++)
	{
		if (this->direction) //horizontal
		{
			if (this->x == attakI && this->y + i == attakJ)
			{
				std::cout << " ATTTAKKKK GOR" << std::endl;
				return 1;
			}
			//else return 0;
		}
		else
		{
			if (this->x + i == attakI && this->y == attakJ)
			{
				std::cout << " ATTTAKKKK VERT" << std::endl;
				return 1;
			}
			//else return 0;
		}
		
	}
	return 0;*/
	for (int i = 0; i < this->deckAmount; i++)
	{
		if ((this->coordinates[i].i == attakI) && (this->coordinates[i].j == attakJ))
		{
			if (this->coordinates[i].isItDestroed == false)
			{
				hp--;
				this->coordinates[i].isItDestroed = true;
				return 1;
			}
			else return 0;
		}
	}
	return 0;
}

Ship::Coordinates::Coordinates(int i, int j)
{
	this->i = i;
	this->j = j;
	this->isItDestroed = false;


	
}
