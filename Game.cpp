#include "Game.h"

Game::Game()
{
	//init window
	this->videoMode.width = 1100;
	this->videoMode.height = 900;
	this->window = new sf::RenderWindow(videoMode, "SeaBattle");
	//this->window->setFramerateLimit(60);

	//init font
	if (!this->font.loadFromFile("Fonts\\font.ttf"))	std::cout << "Font error" << std::endl;

	//init text
	infoText.setFont(font);
	infoText.setCharacterSize(21);
	infoText.setPosition(sf::Vector2f(35, 370));
	infoText.setString("Hellovfvgfdfffffffffffffffffff");

	//outMapShip.resize(this->shipAmount);

	outMapShip.emplace_back(750, 50, 4);
	outMapShip.emplace_back(800, 50, 3);
	outMapShip.emplace_back(850, 50, 2);
	outMapShip.emplace_back(900, 50, 1);
	outMapShip.emplace_back(950, 50, 1);

	std::cout << "Game Construcror" << std::endl;
	std::cout << "---------" << std::endl;
	std::cout << std::endl;
}

Game::~Game()
{
	delete this->window;
	this->window = nullptr;
}

bool Game::getWindowStatus() const
{
	return this->window->isOpen();
}

void Game::update()
{
	//mouse poll----------------------------------------------------


	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !this->mouseLeftFrontEdge) // передний фронт
	{
		
		for (int i = 0; i < this->outMapShip.size(); i++)
		{

			if (this->outMapShip[i].shape.getGlobalBounds().contains((float)sf::Mouse::getPosition(*window).x, (float)sf::Mouse::getPosition(*window).y) && this->outMapShip[i].getGrab() == false)
			{
				this->outMapShip[i].setGrab(true);
			}

			else if (this->outMapShip[i].getGrab() == true && playerMap.placeShip(this->outMapShip[i], window))
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




		/*if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->mouseLeftFrontEdge == false && this->mouseLeftBackEdge == false) // передний фронт
		{
			for (int i = 0; i < this->outMapShip.size(); i++)
				this->outMapShip[i].setGrab(window);
			this->mouseLeftFrontEdge = true;
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) == 0 && this->mouseLeftFrontEdge == true && this->mouseLeftBackEdge == false)
		{
			this->mouseLeftBackEdge = true;
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->mouseLeftFrontEdge == true && this->mouseLeftBackEdge == true)
		{

			for (int i = 0; i < this->outMapShip.size(); i++)
			{
				
				this->outMapShip[i].setGrab(window);
				if (this->outMapShip[i].getGrab() == true)
				{
					if (playerMap.placeShip(this->outMapShip[i], window))
						this->outMapShip.erase(this->outMapShip.begin() + i);
					else
					{
						std::cout << i <<"  size =  " << this->outMapShip.size() << std::endl;
						std::cout << outMapShip[i].getWindowCoorX() << "  size =  " << outMapShip[i].getWindowCoorY() << std::endl;
						//outMapShip[i].setWindowCoorX(750.f + 50.f * i);
						//outMapShip[i].setWindowCoorY(50.f);
					}
					//std::cout << "size =  " << this->outMapShip.size() << std::endl;
					
				}
				
			}

			this->mouseLeftFrontEdge = false;
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) == 0 && this->mouseLeftFrontEdge == false && this->mouseLeftBackEdge == true)
		{
			this->mouseLeftBackEdge = false;
		}
	//std::cout << "mouseLeftFrontEdge = " << mouseLeftFrontEdge << "   mouseLeftBackEdge = " << mouseLeftBackEdge << "   Mouse = " << sf::Mouse::isButtonPressed(sf::Mouse::Left) << std::endl;
	*/


		//space poll----------------------------------------------------
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->spaceFrontEdge == false && this->spaceBackEdge == false)
		{
			for (int i = 0; i < this->outMapShip.size(); i++)
				if(this->outMapShip[i].getGrab()) this->outMapShip[i].setDirection();

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


	//poll events----------------------------------------------------
	while (this->window->pollEvent(event))
	{
		switch (this->event.type)
		{
		case sf::Event::EventType::Closed:
			this->window->close();
			break;

		case sf::Event::EventType::KeyPressed:
			/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				this->window->close();

			else */if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				//enemyMap.getMapValue();
				playerMap.getMapValue();
				std::cout << std::endl;
			}
			break;

		//case sf::Event::EventType::MouseButtonPressed:
		case sf::Event::EventType::MouseButtonPressed:
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				enemyMap.attack(window);
			}
			break;

		default:
			break;
		}
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

	enemyMap.updateMap(window, 1);
	playerMap.updateMap(window);
	for (int i = 0; i < this->outMapShip.size(); i++)
		outMapShip[i].update(window);
}

void Game::render()
{
	
	this->window->clear();

	this->window->draw(infoText);
	playerMap.renderMap(window);
	enemyMap.renderMap(window);
	for (int i = 0; i < this->outMapShip.size(); i++)
		outMapShip[i].render(window);

	this->window->display();
}




