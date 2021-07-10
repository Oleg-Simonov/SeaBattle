#include "PlacingState.h"

PlacingState::PlacingState(std::vector<State*>* statesPointer) : State(statesPointer)
{
	this->helpTextBackground.setFillColor(sf::Color(70, 70, 70, 175));
	this->helpTextBackground.setPosition(685.f, 443.f);
	this->helpTextBackground.setSize(sf::Vector2f(470.f, 180.f));

	//init font
	if (!this->font.loadFromFile("Fonts\\font.ttf"))	MessageBox(0, (LPCWSTR)L"Font error PlacingState", (LPCWSTR)L"Error message", 0);
	
	//init text
	headerText.setFont(font);
	headerText.setCharacterSize(30);
	headerText.setPosition(sf::Vector2f(430, 30));
	headerText.setString("Place your ships on the map");

	helpText.setFont(font);
	helpText.setCharacterSize(15);
	helpText.setPosition(sf::Vector2f(700, 450));
	std::stringstream ss;
	ss << "   1) In order to place ships on map click left mouse button on one\nof your ships and drag it on the map where you want place it.\n   In order to change direction of the ship press \"Space\"\n\n" <<
		"   2) If it is possible to place the ship in chosen area, the ship will be\npainted ingreen color, otherwise the ship will be painted in red color.\n\n" <<
		"   3) If you chose area for ship and the ship is painted in green color,\n click left mouse button again.";
	helpText.setString(ss.str());

	yourShipsText.setFont(font);
	yourShipsText.setCharacterSize(21);
	yourShipsText.setPosition(sf::Vector2f(100, 430));
	yourShipsText.setString("Your ships:");

	//init ships for placing
	this->initOutMapShips();

	//init buttons
	this->buttons["START_GAME"] = new Button(500, 40, 215, 55,
		&this->font, "Start game!",
		sf::Color(255, 50, 50, 200), sf::Color(255, 0, 0, 200), sf::Color(0, 0, 255, 200));

	this->buttons["RANDOM"] = new Button(830, 130, 170, 50,
		&this->font, "Randomize",
		sf::Color(0, 101, 151, 200), sf::Color(0, 102, 255, 200), sf::Color(0, 0, 255, 200));

	this->buttons["AGAIN"] = new Button(830, 230, 170, 50,
		&this->font, "Place again",
		sf::Color(0, 101, 151, 200), sf::Color(0, 102, 255, 200), sf::Color(0, 0, 255, 200));

	this->buttons["QUIT"] = new Button(830, 330, 170, 50,
		&this->font, "Quit",
		sf::Color(0, 101, 151, 200), sf::Color(0, 102, 255, 200), sf::Color(0, 0, 255, 200));

	//init sounds
	if (!soundBufferPlacing.loadFromFile("Resources\\Sounds\\placing.wav")) MessageBox(0, (LPCWSTR)L"Sound soundBufferPlacing error", (LPCWSTR)L"Error message", 0);
	this->soundPlacing.setBuffer(soundBufferPlacing);
	this->soundPlacing.setVolume(15.f);

	if (!soundBufferFlipShip.loadFromFile("Resources\\Sounds\\ShipFlip.wav")) MessageBox(0, (LPCWSTR)L"Sound soundBufferFlipShip error", (LPCWSTR)L"Error message", 0);
	this->soundFlipShip.setBuffer(soundBufferFlipShip);
	this->soundFlipShip.setVolume(35.f);

	//std::cout << "CONSTR______END______Placing" << std::endl;
}

PlacingState::~PlacingState()
{ 
	for (auto it : this->buttons)
		delete it.second;
	//std::cout << "DESTR____________Placing" << std::endl;
}

void PlacingState::initOutMapShips()
{
	int distance = 0;
	int shipsForRandPlacing[5];
	shipsForRandPlacing[0] = 4;	//1 deck
	shipsForRandPlacing[1] = 3; //2 deck
	shipsForRandPlacing[2] = 2; //3 deck
	shipsForRandPlacing[3] = 1; //4 deck
	shipsForRandPlacing[4] = 0; //5 deck

	this->outMapShipsTable.resize(shipsForRandPlacing[0] + shipsForRandPlacing[1] + shipsForRandPlacing[2] + shipsForRandPlacing[3] + shipsForRandPlacing[4]);

	for (int i = 4, j = 0; i >= 0; i--)
	{
		while (shipsForRandPlacing[i])
		{
			//init outMapShipsTable
			this->outMapShipsTable[j].setFillColor(sf::Color(51, 51, 51, 0));
			this->outMapShipsTable[j].setOutlineThickness(1);
			this->outMapShipsTable[j].setPosition((float)(100 + distance - 2.5), (float)(470 - 3.5));
			this->outMapShipsTable[j].setSize(sf::Vector2f(33.f, (float)((i + 1) * 27 + i + 7)));
			j++;

			//init outMapShip
			outMapShip.emplace_back(100 + distance, 470, i + 1);
			distance = distance + 34;
			shipsForRandPlacing[i]--;
		}
	}
}

void PlacingState::update(sf::RenderWindow* targetWindow)
{	
	this->mouseUpdatePosition(targetWindow);

	for (auto it : this->buttons)
		it.second->update(this->mousePosWindowf);

	if (this->outMapShip.size() == 0)
	{
		headerText.setString("");
		this->buttons["START_GAME"]->setVisible(1);
	}
	else
	{
		this->buttons["START_GAME"]->setVisible(0);
		headerText.setString("Place your ships on the map");
	}
	
	while (targetWindow->pollEvent(sfEvent))
	{
		//std::cout << sfEvent.type << std::endl;

		if (this->sfEvent.type == sf::Event::EventType::Closed)
			targetWindow->close();

		else if (this->sfEvent.type == sfEvent.MouseButtonPressed && this->sfEvent.mouseButton.button == sf::Mouse::Button::Left)
		{
			//playerMap.placeShip(this->outMapShip[0], targetWindow);
			//std::cout << "MouseButtonPressed" << std::endl;
			for (size_t i = 0; i < this->outMapShip.size(); i++)
			{
				//if cursor hover over the ship, we will grab it
				if (this->outMapShip[i].shape.getGlobalBounds().contains(this->mousePosWindowf) && this->outMapShip[i].getGrab() == false)
				{
					this->outMapShip[i].setGrab(true);
				}
				//if placing has been successful, we will lessen quantity of unplacing ships
				else if (this->outMapShip[i].getGrab() == true && playerMap.placeShip(this->outMapShip[i]))
				{
					this->outMapShip.erase(this->outMapShip.begin() + i);
					this->soundPlacing.play();
				}
				//else we revert the ship to initial position
				else
				{
					this->outMapShip[i].setGrab(false);
				}
			}

			if (buttons["START_GAME"]->isPressed() && this->outMapShip.size() == 0)
			{
				this->statesPointer->push_back(new GameState(statesPointer, &playerMap));
				return; // return is required for speed up change state. Otherwise there is a petty bug when you press "Start game" button many times very fast 
			}
				

			if (buttons["RANDOM"]->isPressed())
			{
				//this->playerMap.randomPlace();
				this->playerMap.clearMap();
				this->playerMap.randomPlace(4, 3, 2, 1, 0);
				outMapShip.clear();
				this->soundPlacing.play();
			}

			if (buttons["AGAIN"]->isPressed())
			{
				this->playerMap.clearMap();
				this->outMapShip.clear();
				this->initOutMapShips();
				this->soundPlacing.play();
			}

			if (buttons["QUIT"]->isPressed())
				this->endState = -1;
		}

		else if (this->sfEvent.type == sfEvent.KeyPressed && this->sfEvent.key.code == sf::Keyboard::Space)
		{
			for (size_t i = 0; i < this->outMapShip.size(); i++)
			{
				if (this->outMapShip[i].getGrab())
				{
					this->outMapShip[i].setDirection();
					this->soundFlipShip.play();
				}
			}
		}
	}

	playerMap.updateMap(this->mousePosWindowf);

	//calculate color for ship: if it is not possible to place, the ship will be red color
	for (size_t shipCounter = 0; shipCounter < this->outMapShip.size(); shipCounter++)
	{
		if(this->playerMap.getChosenField().i == -1) outMapShip[shipCounter].update(targetWindow, -1);
		else 
		{
			this->playerMap.calcProhibitedZone(outMapShip[shipCounter].getDirection(), outMapShip[shipCounter].getDeckAmount());
			outMapShip[shipCounter].update(targetWindow, this->playerMap.getProhibitedZoneIJ(this->playerMap.getChosenField()));
		}
	}
}

void PlacingState::render(sf::RenderWindow* targetWindow)
{
	targetWindow->draw(this->backgroundSprite);
	targetWindow->draw(this->headerText);
	targetWindow->draw(this->helpTextBackground);
	targetWindow->draw(this->helpText);
	targetWindow->draw(this->yourShipsText);
	

	playerMap.renderMap(targetWindow);

	for (size_t i = 0; i < this->outMapShipsTable.size(); i++)
		targetWindow->draw(this->outMapShipsTable[i]);

	for (size_t i = 0; i < this->outMapShip.size(); i++)
		outMapShip[i].render(targetWindow);

	for (auto it : this->buttons)
		it.second->render(targetWindow);
}