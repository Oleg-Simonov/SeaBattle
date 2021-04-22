#include "Ship.h"

Ship::Ship(int x, int y, bool direction , int deckAmount) : x(x), y(y), direction(direction), deckAmount(deckAmount)
{
	grab = false;
	//this->isItChosen2 = false;
	shipCounter++;
	this->hp = deckAmount;
	this->shipID = shipCounter;
	std::cout << "---ShipConstruktor---" << std::endl;

	this->coordinates.reserve(deckAmount);
	for (int i = 0; i < deckAmount; i++)
	{
		if (direction)
			this->coordinates.emplace_back(x, y + i);
		else
			this->coordinates.emplace_back(x + i, y);

		this->coordinates[i].shape.setPosition(sf::Vector2f(750.f, 50.f + i * 29));
		this->coordinates[i].shape.setSize(sf::Vector2f(27.f, 27.f));
		this->coordinates[i].shape.setFillColor(sf::Color::White);
		this->coordinates[i].shape.setOutlineThickness(1.f);
		this->coordinates[i].shape.setOutlineColor(sf::Color::Black);

		std::cout << this->coordinates[i].i << "   " << this->coordinates[i].j << std::endl;
	}
	std::cout << "cap" << this->coordinates.capacity() << " size" << this->coordinates.size() << std::endl;

	std::cout << "---ShipConstruktor END---" << std::endl;
}

//construcror for player's ships
Ship::Ship(float windowCoorX, float windowCoorY, int deckAmount)
{
	grab = false;
	//this->isItChosen2 = false;
	x = 0;
	y = 0;
	direction = 0;
	this->deckAmount = deckAmount;

	shipCounter++;
	this->hp = deckAmount;
	this->shipID = shipCounter;
	std::cout << "---ShipConstruktor---" << std::endl;

	this->coordinates.reserve(deckAmount);
	for (int i = 0; i < deckAmount; i++)
	{
		if (direction)
			this->coordinates.emplace_back(x, y + i);
		else
			this->coordinates.emplace_back(x + i, y);

		this->coordinates[i].shape.setPosition(sf::Vector2f(windowCoorX, windowCoorY + i * 29));
		this->coordinates[i].shape.setSize(sf::Vector2f(27.f, 27.f));
		this->coordinates[i].shape.setFillColor(sf::Color::White);
		this->coordinates[i].shape.setOutlineThickness(1.f);
		this->coordinates[i].shape.setOutlineColor(sf::Color::Black);

		std::cout << this->coordinates[i].i << "   " << this->coordinates[i].j << std::endl;
	}
	std::cout << "cap" << this->coordinates.capacity() << " size" << this->coordinates.size() << std::endl;

	std::cout << "---ShipConstruktor END---" << std::endl;
}

Ship::Ship(const Ship& other) //this constructor has been created for learnt sake
{
	//this->isItChosen = other.isItChosen;
	this->x = other.x;
	this->y = other.y;
	this->direction = other.direction;
	this->deckAmount = other.deckAmount;
	this->hp = other.deckAmount;
	this->shipID = other.shipID;

	std::cout << "ShipCopyConstructor" << std::endl;
}

Ship::~Ship()
{
	std::cout << "ShipDestruktor" << std::endl;
}

int Ship::getI() const
{
	return this->x;
}

int Ship::getJ() const
{
	return this->y;
}

bool Ship::getDirection() const
{
	return this->direction;
}

int Ship::getDeckAmount() const
{
	return this->deckAmount;
}

int Ship::getShipID() const
{
	return this->shipID;
}

int Ship::getShipHp() const
{
	return this->hp;
}

void Ship::getDataForLog()
{
	std::cout << " xp = " << this->shipID <<
				 " x = "<< this->x <<
				 " y = " << this->y <<
				 " xp = " << this->hp <<
				 " dir = " << this->direction <<
				 " deckAmount = " << this->deckAmount << std::endl;
}

std::vector<Ship::Coordinates>::const_iterator Ship::getCoordinates() const
{
	return this->coordinates.begin();
}

bool Ship::getGrabShip() const
{
	return this->grab;
}

int Ship::isItDamage(int attakI, int attakJ)
{
	for (int i = 0; i < this->deckAmount; i++)
	{
		if ((this->coordinates[i].i == attakI) && (this->coordinates[i].j == attakJ))
		{
			if (this->hp > 0 && this->coordinates[i].isItDestroed == false)
			{
				hp--;
				this->coordinates[i].isItDestroed = true;
			}
			return true;
		}
	}
	return false;
}

void Ship::lessenHp()
{
	this->getDataForLog();

	if (this->hp > 0)
		this->hp--;

	this->getDataForLog();
}

void Ship::setDeckAmount(int newDeckAmount)
{
	this->deckAmount = newDeckAmount;
}

void Ship::updateShip(sf::RenderWindow* window)
{
	//std::cout << "dir= " << this->direction << std::endl;
		for (int i = 0; i < this->deckAmount; i++)
		{
				if (grab)
				{
					if (direction)
					{
						for (int j = 0; j < this->deckAmount; j++)
						{
							this->coordinates[j].shape.setFillColor(sf::Color::Cyan);
							this->coordinates[j].shape.setPosition((float)sf::Mouse::getPosition(*window).x - 15 + j * 29, (float)sf::Mouse::getPosition(*window).y - 15);
						}
						break;
					}
					else
					{
						for (int j = 0; j < this->deckAmount; j++)
						{
							this->coordinates[j].shape.setFillColor(sf::Color::Cyan);
							this->coordinates[j].shape.setPosition((float)sf::Mouse::getPosition(*window).x - 15, (float)sf::Mouse::getPosition(*window).y - 15 + j * 29);
						}
						break;
					}
				}
				else
					for (int j = 0; j < this->deckAmount; j++)
						this->coordinates[j].shape.setFillColor(sf::Color::White);


				if (this->coordinates[i].shape.getGlobalBounds().contains((float)sf::Mouse::getPosition(*window).x, (float)sf::Mouse::getPosition(*window).y))
				{
					for (int j = 0; j < this->deckAmount; j++)
					{
						this->coordinates[j].shape.setFillColor(sf::Color::Cyan);
					}
					break;
				}
				else
					for (int j = 0; j < this->deckAmount; j++)
						this->coordinates[j].shape.setFillColor(sf::Color::White);
		}
}

void Ship::setGrabShip(sf::RenderWindow* window)
{
	if (this->grab == false)
	{
		for (int i = 0; i < this->deckAmount; i++)
		{
			if (this->coordinates[i].shape.getGlobalBounds().contains((float)sf::Mouse::getPosition(*window).x, (float)sf::Mouse::getPosition(*window).y))
			{
				this->grab = true;
				break;
			}
		}
	}
	else
		this->grab = false;
}

void Ship::setDirection()
{
	std::cout << "dir= " << this->direction << std::endl;
	if (this->direction == false)
		this->direction = true;
	else
		this->direction = false;
	std::cout << "dir= " << this->direction << std::endl;
}

void Ship::renderShip(sf::RenderWindow* window) const
{
	for (int i = 0; i < this->deckAmount; i++)
		window->draw(this->coordinates[i].shape);
}

Ship::Coordinates::Coordinates(int i, int j)
{
	this->i = i;
	this->j = j;
	this->isItDestroed = false;


	
}
