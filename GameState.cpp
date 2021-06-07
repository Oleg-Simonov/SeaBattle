#include "GameState.h"

GameState::GameState(std::stack<State*>* statesPointer, Map* playerMap) : State(statesPointer)

{
	srand(static_cast<unsigned int>(time(0)));
	//init var
	this->clickFlags.mouseLeft = false;
	this->dirCounter = 0;
	this->needComeBack = 0;

	//this->playerMap = playerMap;
	this->playerMap = new Map();
	this->playerMove = true;

	//init font
	if (!this->font.loadFromFile("Fonts\\font.ttf"))	std::cout << "Font error" << std::endl; //should be refined

	//init text
	infoText.setFont(font);
	infoText.setCharacterSize(21);
	infoText.setPosition(sf::Vector2f(35, 370));
	//infoText.setString("Hellovfvgfdfffffffffffffffffff");
}

GameState::~GameState()
{
	delete this->playerMap;
}

void GameState::coordCalc()
{
	//filling array with possible coordinates for strike
	nonRepeatVector.clear();
	for (int i = 0; i < this->playerMap->getSizeI() * this->playerMap->getSizeJ(); i++)
	{
		int coorj = i % 10;
		int coori = (i - coorj) / 10;
		int mapValue = this->playerMap->getMapValue(coori, coorj);

		if (mapValue == 0 || mapValue == 1)
			this->nonRepeatVector.push_back(i);
	}

	/*for (int i = 0; i < this->nonRepeatVector.size(); i++)
	{
		std::cout << this->nonRepeatVector[i] << std::endl;
	}*/

	int randomCoor = rand() % this->nonRepeatVector.size();

	coorOfStrike.j = nonRepeatVector[randomCoor] % 10;
	coorOfStrike.i = (nonRepeatVector[randomCoor] - coorOfStrike.j) / 10;

	//nonRepeatVector.clear();
}

void GameState::coordCalc(int coorI, int coorJ)
{
	coorOfStrike.j = coorJ;
	coorOfStrike.i = coorI;
}

void GameState::botAttack(sf::RenderWindow* targetWindow, int coorI, int coorJ)
{
	coordCalc(coorI, coorJ);
	std::cout << "coorOfStrike i = " << coorOfStrike.i << " coorOfStrike j = " << coorOfStrike.j << std::endl;
	switch (this->playerMap->attack(targetWindow, coorI, coorJ))
	{
	case 0:
		std::cout << " Miss! " << std::endl;
		this->playerMove = 1;
		break;
	case 1:
		std::cout << " Damaged! " << std::endl;
		this->damagedDecks.push_back(coorOfStrike);
		break;
	case 2:
		std::cout << " Destroyed! " << std::endl;
		this->damagedDecks.clear();
		break;
	default:
		break;
	}
}

bool GameState::checkField(int coorI, int coorJ) //this function check whether make sense strike into area with coor I, J or not
{
	if (!(coorI < 0 || coorI >= this->playerMap->getSizeI() || coorJ < 0 || coorJ >= this->playerMap->getSizeJ()))
	{
		for (int i = 0; i < this->nonRepeatVector.size(); i++)
		{
			//std::cout << this->nonRepeatVector[i] << std::endl;
			if (this->nonRepeatVector[i] == coorI * 10 + coorJ)
				return 1;
		}
	}
	//std::cout << "qwer: " << coorI * 10 + coorJ << std::endl;
	return 0;
}

void GameState::ArtificInt(sf::RenderWindow* targetWindow)
{
	//the first random shot, but we don't shoot in area where we shot before.
	coordCalc();
	if (this->damagedDecks.size() == 0)
	{
		std::cout << " 000 " << std::endl;

		/*if(this->playerMap->getCurrentShipsAmount() == 5)
		coordCalc(5, 7);
		else if (this->playerMap->getCurrentShipsAmount() == 4)
			coordCalc(1, 1);
		else*/
		botAttack(targetWindow, coorOfStrike.i, coorOfStrike.j);
	}
	//the ship has been damaged, we aproximatly know coordinates where could be a deck, we should strike next to it. 
	//In general case, we have four direction for continue attack. Now we should determine direction of ship.
	else if (this->damagedDecks.size() == 1)
	{
		std::cout << " 111 " << std::endl;

		if (checkField(damagedDecks[0].i - 1, damagedDecks[0].j))
			botAttack(targetWindow, damagedDecks[0].i - 1, damagedDecks[0].j);

		else if (checkField(damagedDecks[0].i + 1, damagedDecks[0].j))
			botAttack(targetWindow, damagedDecks[0].i + 1, damagedDecks[0].j);

		else if (checkField(damagedDecks[0].i, damagedDecks[0].j - 1))
			botAttack(targetWindow, damagedDecks[0].i, damagedDecks[0].j - 1);

		else if (checkField(damagedDecks[0].i, damagedDecks[0].j + 1))
			botAttack(targetWindow, damagedDecks[0].i, damagedDecks[0].j + 1);

		else std::cout << "How did it happen?" << std::endl;
	}
	//we've determined direction of the ship. Now we should finish it off.
	else
	{
		std::cout << " 222 " << std::endl;
		int sizeDD = this->damagedDecks.size() - 1;

		//horizontal ship------------------------------------------------------------------------------------
		if (damagedDecks[0].i == damagedDecks[1].i)
		{
			if (checkField(damagedDecks[sizeDD].i, damagedDecks[sizeDD].j - 1))
				botAttack(targetWindow, damagedDecks[sizeDD].i, damagedDecks[sizeDD].j - 1);

			else
			{
				if (checkField(damagedDecks[0].i, damagedDecks[0].j + 1))
					botAttack(targetWindow, damagedDecks[0].i, damagedDecks[0].j + 1);

				else if (checkField(damagedDecks[sizeDD].i, damagedDecks[sizeDD].j + 1))
					botAttack(targetWindow, damagedDecks[sizeDD].i, damagedDecks[sizeDD].j + 1);

				else std::cout << "How did it happen3?" << std::endl;
			}
		}
		//vertical ship--------------------------------------------------------------------------------------
		else if (damagedDecks[0].j == damagedDecks[1].j)
		{
			if (checkField(damagedDecks[sizeDD].i - 1, damagedDecks[sizeDD].j))
				botAttack(targetWindow, damagedDecks[sizeDD].i - 1, damagedDecks[sizeDD].j);
			else
			{

				if (checkField(damagedDecks[0].i + 1, damagedDecks[0].j))
					botAttack(targetWindow, damagedDecks[0].i + 1, damagedDecks[0].j);

				else if (checkField(damagedDecks[sizeDD].i + 1, damagedDecks[sizeDD].j))
					botAttack(targetWindow, damagedDecks[sizeDD].i + 1, damagedDecks[sizeDD].j);

				else std::cout << "How did it happen4?" << std::endl;
			}
		}
		else std::cout << "How did it happen6?" << std::endl;
	}
}



void GameState::update(sf::RenderWindow* targetWindow)
{
	if (this->playerMove == false)
	{
		ArtificInt(targetWindow);
	}




	/*
	if (checkField(damagedDecks[sizeDD].i, damagedDecks[sizeDD].j - 1))
	{
		coordCalc(damagedDecks[sizeDD].i, damagedDecks[sizeDD].j - 1);
		botAttack(targetWindow);
	}
	else
	{

		if (checkField(damagedDecks[0].i, damagedDecks[0].j + 1))
		{
			coordCalc(damagedDecks[0].i, damagedDecks[0].j + 1);
			botAttack(targetWindow);
		}
		else if (checkField(damagedDecks[sizeDD].i, damagedDecks[sizeDD].j + 1))
		{
			coordCalc(damagedDecks[sizeDD].i, damagedDecks[sizeDD].j + 1);
			botAttack(targetWindow);
		}
		else std::cout << "How did it happen3?" << std::endl;
	}
			}
			//vertical ship---------------------------------------------------------------------------------------------------
			else if (damagedDecks[0].j == damagedDecks[1].j)
			{
			if (checkField(damagedDecks[sizeDD].i - 1, damagedDecks[sizeDD].j))
			{
				coordCalc(damagedDecks[sizeDD].i - 1, damagedDecks[sizeDD].j);
				botAttack(targetWindow);
			}
			else
			{

				if (checkField(damagedDecks[0].i + 1, damagedDecks[0].j))
				{
					coordCalc(damagedDecks[0].i + 1, damagedDecks[0].j);
					botAttack(targetWindow);
				}
				else if (checkField(damagedDecks[sizeDD].i + 1, damagedDecks[sizeDD].j))
				{
					coordCalc(damagedDecks[sizeDD].i + 1, damagedDecks[sizeDD].j);
					botAttack(targetWindow);
				}
				else std::cout << "How did it happen4?" << std::endl;
			}
			}
			else std::cout << "How did it happen6?" << std::endl;
			*/





/*
	std::cout << " 222 " << std::endl;
	coordCalc();
	int sizeDD = this->damagedDecks.size() - 1;
	//	case 1: //the ship has been damaged, we aproximatly know coordinates where could be a deck, we should strike next to it. In general case, we have four direction for continue attack 
	//horizontal ship------------------------------------------------------------------------------------
	if (damagedDecks[0].i == damagedDecks[1].i)
	{
		if (damagedDecks[sizeDD].j - 1 >= 0 || this->needComeBack == 1)
		{

			if (this->needComeBack == 0)
			{
				if (checkField(damagedDecks[sizeDD].i, damagedDecks[sizeDD].j - 1) == 1)
				{
					coordCalc(damagedDecks[sizeDD].i, damagedDecks[sizeDD].j - 1);
					this->needComeBack = botAttack(targetWindow);
				}
				else
					this->needComeBack = 1;
				//std::cout << "How did it happen2?" << std::endl;
			}
			else if (this->needComeBack == 1)
			{
				int i = 1;
				while (checkField(damagedDecks[sizeDD].i, damagedDecks[sizeDD].j + i) != 1)
				{
					i++;
				}
				if (checkField(damagedDecks[sizeDD].i, damagedDecks[sizeDD].j + i) == 1)
				{
					coordCalc(damagedDecks[sizeDD].i, damagedDecks[sizeDD].j + i);
					botAttack(targetWindow);
				}
				else std::cout << "How did it happen4?" << std::endl;
			}
			else std::cout << "How did it happen5?" << std::endl;

		}
		else this->needComeBack = 1;
	}
	//vertical ship---------------------------------------------------------------------------------------------------
	else if (damagedDecks[0].j == damagedDecks[1].j)
	{
		if (damagedDecks[sizeDD].i - 1 >= 0 || this->needComeBack == 1)
		{

			if (this->needComeBack == 0)
			{
				if (checkField(damagedDecks[sizeDD].i - 1, damagedDecks[sizeDD].j) == 1)
				{
					coordCalc(damagedDecks[sizeDD].i - 1, damagedDecks[sizeDD].j);
					this->needComeBack = botAttack(targetWindow);
				}
				else
					this->needComeBack = 1;
				//std::cout << "How did it happen2?" << std::endl;
			}
			else if (this->needComeBack == 1)
			{
				int i = 1;
				while (checkField(damagedDecks[sizeDD].i + i, damagedDecks[sizeDD].j) != 1)
				{
					i++;
				}
				if (checkField(damagedDecks[sizeDD].i + i, damagedDecks[sizeDD].j) == 1)
				{
					coordCalc(damagedDecks[sizeDD].i + i, damagedDecks[sizeDD].j);
					botAttack(targetWindow);
				}
				else std::cout << "How did it happen4?" << std::endl;
			}
			else std::cout << "How did it happen5?" << std::endl;

		}
		else this->needComeBack = 1;
	}
	else std::cout << "How did it happen6?" << std::endl;
		}

		*/













	//mouse poll----------------------------------------------------
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !this->clickFlags.mouseLeft)
	{
		//std::cout << this->nonRepeatRandNumber() << std::endl;
		if(this->playerMove)
			this->playerMove = this->enemyMap.attack(targetWindow);

		this->clickFlags.mouseLeft = true;
	}

	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->clickFlags.mouseLeft)
	{
		this->clickFlags.mouseLeft = false;
	}

	//Text update------------------------------------------------------
	std::stringstream ss;
	ss << "Enemy ships remain: " << enemyMap.getCurrentShipsAmount() << " out of " << enemyMap.getShipsAmount() << "\n"
		<< "Enemy ship " << 0 << " HP: " << enemyMap.getShips()->getShipHp() << " out of " << enemyMap.getShips()->getDeckAmount() << "\n"
		<< "Enemy ship " << 1 << " HP: " << (enemyMap.getShips() + 1)->getShipHp() << " out of " << (enemyMap.getShips() + 1)->getDeckAmount() << "\n"
		<< "Enemy ship " << 2 << " HP: " << (enemyMap.getShips() + 2)->getShipHp() << " out of " << (enemyMap.getShips() + 2)->getDeckAmount() << "\n"
		<< "Enemy ship " << 3 << " HP: " << (enemyMap.getShips() + 3)->getShipHp() << " out of " << (enemyMap.getShips() + 3)->getDeckAmount() << "\n"
		<< "Enemy ship " << 4 << " HP: " << (enemyMap.getShips() + 4)->getShipHp() << " out of " << (enemyMap.getShips() + 4)->getDeckAmount() << "\n"
		;
	this->infoText.setString(ss.str());

	//std::cout << sf::Mouse::getPosition(*window).x << "   " << sf::Mouse::getPosition(*window).y << std::endl;

	enemyMap.updateMap(targetWindow, 1);
	playerMap->updateMap(targetWindow);
}

void GameState::render(sf::RenderWindow* targetWindow)
{
	targetWindow->draw(infoText);
	playerMap->renderMap(targetWindow);
	enemyMap.renderMap(targetWindow);

}

GameState::CoordinatesOfStrike::CoordinatesOfStrike()
{
	this->i = 1000;
	this->j = 1000;
}

GameState::CoordinatesOfStrike::CoordinatesOfStrike(int i, int j)
{
	this->i = i;
	this->j = j;
}
