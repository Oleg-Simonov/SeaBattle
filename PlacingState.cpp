#include "PlacingState.h"

PlacingState::PlacingState(std::stack<State*>* statesPointer) : State(statesPointer)
{
	//init var
	clickFlags.mouseLeft = false;
	clickFlags.space = false;
	clickFlags.startButton = false;
	clickFlags.againlButton = false;
	clickFlags.toMainMenuButton = false;

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

	//init buttons
	this->buttons2["START_GAME"] = new Button(100, 500, 150, 50,
		&this->font, "Start game!",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	this->buttons2["AGAIN"] = new Button(100, 600, 150, 50,
		&this->font, "Start placing again",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	this->buttons2["TO_MAIN_MENU"] = new Button(100, 700, 150, 50,
		&this->font, "To main menu",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
}

PlacingState::~PlacingState()
{
	for (auto it : this->buttons2)
		delete it.second;
}

void PlacingState::update(sf::RenderWindow* targetWindow)
{	
	//mouse poll----------------------------------------------------
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !this->clickFlags.mouseLeft) // передний фронт
	{

		for (int i = 0; i < this->outMapShip.size(); i++)
		{
			//if cursor hover over the ship, we will grab it
			if (this->outMapShip[i].shape.getGlobalBounds().contains((float)sf::Mouse::getPosition(*targetWindow).x, (float)sf::Mouse::getPosition(*targetWindow).y) && this->outMapShip[i].getGrab() == false)
			{
				this->outMapShip[i].setGrab(true);
			}
			//if placing has been successful, we will lessen quantity of unplacing ships
			else if (this->outMapShip[i].getGrab() == true && playerMap.placeShip(this->outMapShip[i], targetWindow))
			{
				std::cout << "grabgfdgdfgdgdfgdfgd " << this->outMapShip.size() << std::endl;
				this->outMapShip.erase(this->outMapShip.begin() + i);
			}
			//else we revert the ship to initial position
			else
			{
				this->outMapShip[i].setGrab(false);

			}
		}

		clickFlags.mouseLeft = true;
	}

	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->clickFlags.mouseLeft) // задний фронт
	{
		clickFlags.mouseLeft = false;
	}

	//space poll----------------------------------------------------
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !this->clickFlags.space)
	{
		for (int i = 0; i < this->outMapShip.size(); i++)
			if (this->outMapShip[i].getGrab()) this->outMapShip[i].setDirection();

		this->clickFlags.space = true;
	}

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->clickFlags.space)
	{
		this->clickFlags.space = false;
	}

	

	if (buttons2["START_GAME"]->isPressed() && !this->clickFlags.startButton)
	{
		if(this->outMapShip.size() == 0)	this->statesPointer->push(new GameState(statesPointer, &playerMap));

		else
		{
			clock.restart();
			this->infoText.setPosition(550, 550);
			infoText.setString("Place your ships on the map!");
		}

		this->clickFlags.startButton = true;
	}

	if (!buttons2["START_GAME"]->isPressed() && this->clickFlags.startButton)
	{
		this->clickFlags.startButton = false;
	}

	if (buttons2["AGAIN"]->isPressed() && !this->clickFlags.againlButton)
	{
		this->playerMap.clearMap();
		this->outMapShip.clear();

		outMapShip.emplace_back(750, 50, 4);
		outMapShip.emplace_back(800, 50, 3);
		outMapShip.emplace_back(850, 50, 2);
		outMapShip.emplace_back(900, 50, 1);
		outMapShip.emplace_back(950, 50, 1);

		this->clickFlags.againlButton = true;
	}

	if (!buttons2["AGAIN"]->isPressed() && this->clickFlags.againlButton)
	{
		this->clickFlags.againlButton = false;
	}

	if (buttons2["TO_MAIN_MENU"]->isPressed() && !this->clickFlags.toMainMenuButton)
	{
		this->endState = true;

		this->clickFlags.toMainMenuButton = true;
	}

	if (!buttons2["TO_MAIN_MENU"]->isPressed() && this->clickFlags.toMainMenuButton)
	{
		this->clickFlags.toMainMenuButton = false;
	}

	playerMap.updateMap(targetWindow);
	for (int i = 0; i < this->outMapShip.size(); i++)
		outMapShip[i].update(targetWindow);

	this->mouseUpdatePosition(targetWindow);

	for(auto it : this->buttons2)
		it.second->update(sf::Vector2f((float)this->mousePosWindow.x, (float)this->mousePosWindow.y));

	if (clock.getElapsedTime().asSeconds() > 3)
		infoText.setString("");
	//std::cout << buttons["START_GAME"]->isPressed() << std::endl;
}

void PlacingState::render(sf::RenderWindow* targetWindow)
{
	targetWindow->draw(infoText);
	playerMap.renderMap(targetWindow);
	for (int i = 0; i < this->outMapShip.size(); i++)
		outMapShip[i].render(targetWindow);

	for (auto it : this->buttons2)
		it.second->render(targetWindow);
}
