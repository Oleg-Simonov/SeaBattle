#include "GameState.h"

GameState::GameState(std::stack<State*>* statesPointer) : State(statesPointer)

{
	//init font
	if (!this->font.loadFromFile("Fonts\\font.ttf"))	std::cout << "Font error" << std::endl; //should be refined

	//init text
	infoText.setFont(font);
	infoText.setCharacterSize(21);
	infoText.setPosition(sf::Vector2f(35, 370));
	infoText.setString("Hellovfvgfdfffffffffffffffffff");

	//init ships for placing
	outMapShip.emplace_back(750, 50, 4);
	outMapShip.emplace_back(800, 50, 3);
	outMapShip.emplace_back(850, 50, 2);
	outMapShip.emplace_back(900, 50, 1);
	outMapShip.emplace_back(950, 50, 1);
}

GameState::~GameState()
{
}

void GameState::update(sf::RenderWindow* targetWindow)
{
	//mouse poll----------------------------------------------------

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !this->mouseLeftFrontEdge) // передний фронт
	{
		//размещение
		for (int i = 0; i < this->outMapShip.size(); i++)
		{

			if (this->outMapShip[i].shape.getGlobalBounds().contains((float)sf::Mouse::getPosition(*targetWindow).x, (float)sf::Mouse::getPosition(*targetWindow).y) && this->outMapShip[i].getGrab() == false)
			{
				this->outMapShip[i].setGrab(true);
			}

			else if (this->outMapShip[i].getGrab() == true && playerMap.placeShip(this->outMapShip[i], targetWindow))
			{
				std::cout << "grabgfdgdfgdgdfgdfgd " << this->outMapShip.size() << std::endl;
				this->outMapShip.erase(this->outMapShip.begin() + i);
			}

			else
			{
				this->outMapShip[i].setGrab(false);

			}
		}

		mouseLeftFrontEdge = true;
	}

	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->mouseLeftFrontEdge) // передний фронт
	{
		//std::cout << "gfdg " << std::endl;
		mouseLeftFrontEdge = false;
	}

//space poll----------------------------------------------------
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->spaceFrontEdge == false && this->spaceBackEdge == false)
	{
		for (int i = 0; i < this->outMapShip.size(); i++)
			if (this->outMapShip[i].getGrab()) this->outMapShip[i].setDirection();

		this->spaceFrontEdge = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) == 0 && this->spaceFrontEdge == true && this->spaceBackEdge == false)
	{
		this->spaceBackEdge = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->spaceFrontEdge == true && this->spaceBackEdge == true)
	{
		for (int i = 0; i < this->outMapShip.size(); i++)
			if (this->outMapShip[i].getGrab()) this->outMapShip[i].setDirection();

		this->spaceFrontEdge = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) == 0 && this->spaceFrontEdge == false && this->spaceBackEdge == true)
	{
		this->spaceBackEdge = false;
	}

	//std::cout << "mouseLeftFrontEdge = " << spaceFrontEdge << "   mouseLeftBackEdge = " << spaceBackEdge << "   Mouse = " << sf::Keyboard::isKeyPressed(sf::Keyboard::Space) << std::endl;




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
	playerMap.updateMap(targetWindow);
	for (int i = 0; i < this->outMapShip.size(); i++)
		outMapShip[i].update(targetWindow);

	this->mouseUpdatePosition(targetWindow);
}

void GameState::render(sf::RenderWindow* targetWindow)
{
	targetWindow->draw(infoText);
	playerMap.renderMap(targetWindow);
	enemyMap.renderMap(targetWindow);
	for (int i = 0; i < this->outMapShip.size(); i++)
		outMapShip[i].render(targetWindow);

}
