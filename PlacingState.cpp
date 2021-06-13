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
	headerText.setFont(font);
	headerText.setCharacterSize(21);
	headerText.setPosition(sf::Vector2f(230, 30));
	headerText.setString("Place your ships on the map");

	helpText.setFont(font);
	helpText.setCharacterSize(15);
	helpText.setPosition(sf::Vector2f(400, 310));
	std::stringstream ss;
	ss << "   1) In order to place ships on map click left mouse button on one\nof your ships and drag it on the map where you want place it.\n\n" <<
		"   2) If it is possible to place the ship in chosen area, the ship will be\npainted ingreen color, otherwise the ship will be painted in red color.\n\n" <<
		"   3) If you chose appropriate area for shipand the ship is\n painted in green color, click left mouse button again.";
	helpText.setString(ss.str());

	yourMapText.setFont(font);
	yourMapText.setCharacterSize(21);
	yourMapText.setPosition(sf::Vector2f(30, 40));
	yourMapText.setString("Your map:");

	yourShipsText.setFont(font);
	yourShipsText.setCharacterSize(21);
	yourShipsText.setPosition(sf::Vector2f(30, 430));
	yourShipsText.setString("Your ships:");


	//init ships for placing
	int distance = 0;
	int shipsForRandPlacing[5];
	shipsForRandPlacing[0] = 4;	//1 deck
	shipsForRandPlacing[1] = 3; //2 deck
	shipsForRandPlacing[2] = 2; //3 deck
	shipsForRandPlacing[3] = 1; //4 deck
	shipsForRandPlacing[4] = 0; //5 deck

	for (int i = 4; i >= 0; i--)
	{
		while (shipsForRandPlacing[i])
		{
			outMapShip.emplace_back(30 + distance, 470, i + 1);
			distance = distance + 33;
			shipsForRandPlacing[i]--;
		}
	}

	
	/*outMapShip.emplace_back(750, 50, 4);
	outMapShip.emplace_back(750 + distance, 50, 3);
	outMapShip.emplace_back(750, 50, 3);
	outMapShip.emplace_back(750, 50, 2);
	outMapShip.emplace_back(750, 50, 2);
	outMapShip.emplace_back(750, 50, 2);
	outMapShip.emplace_back(750, 50, 1);
	outMapShip.emplace_back(750, 50, 1);
	outMapShip.emplace_back(750, 50, 1);
	outMapShip.emplace_back(750, 50, 1);*/

	//init buttons
	this->buttons2["START_GAME"] = new Button(500, 100, 115, 35,
		&this->font, "Start game!",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	this->buttons2["RANDOM"] = new Button(500, 150, 115, 35,
		&this->font, "Place randomly",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	this->buttons2["AGAIN"] = new Button(500, 200, 115, 35,
		&this->font, "Place again",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	this->buttons2["TO_MAIN_MENU"] = new Button(500, 250, 115, 35,
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
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !this->clickFlags.mouseLeft) // �������� �����
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

	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->clickFlags.mouseLeft) // ������ �����
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
			//this->infoText.setPosition(550, 550);
			//infoText.setString("Place your ships on the map!");
		}

		this->clickFlags.startButton = true;
	}

	if (!buttons2["START_GAME"]->isPressed() && this->clickFlags.startButton)
	{
		this->clickFlags.startButton = false;
	}

	if (buttons2["RANDOM"]->isPressed() && !this->clickFlags.randomButton)
	{
		this->playerMap.randomPlace();
		outMapShip.clear();

		this->clickFlags.randomButton= true;
	}

	if (!buttons2["RANDOM"]->isPressed() && this->clickFlags.randomButton)
	{
		this->clickFlags.randomButton = false;
	}

	if (buttons2["AGAIN"]->isPressed() && !this->clickFlags.againlButton)
	{
		this->playerMap.clearMap();
		this->outMapShip.clear();

		//init ships for placing
		int distance = 0;
		int shipsForRandPlacing[5];
		shipsForRandPlacing[0] = 4;	//1 deck
		shipsForRandPlacing[1] = 3; //2 deck
		shipsForRandPlacing[2] = 2; //3 deck
		shipsForRandPlacing[3] = 1; //4 deck
		shipsForRandPlacing[4] = 0; //5 deck

		for (int i = 4; i >= 0; i--)
		{
			while (shipsForRandPlacing[i])
			{
				outMapShip.emplace_back(30 + distance, 470, i + 1);
				distance = distance + 33;
				shipsForRandPlacing[i]--;
			}
		}

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





	

	for (int shipCounter = 0; shipCounter < this->outMapShip.size(); shipCounter++)
	{
		int number = this->playerMap.determinationChosenMapField(targetWindow);

		//std::cout << chosenField[0] << " ----- " << chosenField[1] << std::endl;

		if(number > 100) outMapShip[shipCounter].update(targetWindow, -1);
		else 
		{
			this->playerMap.calcProhibitedZone(outMapShip[shipCounter].getDirection(), outMapShip[shipCounter].getDeckAmount());
			int coorJ = number % 10;
			int coorI = (number - coorJ) / 10;


			outMapShip[shipCounter].update(targetWindow, this->playerMap.getProhibitedZoneIJ(coorI, coorJ));
		}

	}
		

	this->mouseUpdatePosition(targetWindow);

	for(auto it : this->buttons2)
		it.second->update(sf::Vector2f((float)this->mousePosWindow.x, (float)this->mousePosWindow.y));

	//if (clock.getElapsedTime().asSeconds() > 3)
	//	infoText.setString("");
	//std::cout << buttons["START_GAME"]->isPressed() << std::endl;
}

void PlacingState::render(sf::RenderWindow* targetWindow)
{
	targetWindow->draw(headerText);
	targetWindow->draw(helpText);
	targetWindow->draw(yourMapText);
	targetWindow->draw(yourShipsText);

	playerMap.renderMap(targetWindow);
	for (int i = 0; i < this->outMapShip.size(); i++)
		outMapShip[i].render(targetWindow);

	for (auto it : this->buttons2)
		it.second->render(targetWindow);
}