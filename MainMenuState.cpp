#include "MainMenuState.h"

MainMenuState::MainMenuState(std::stack<State*>* statesPointer) : State(statesPointer)
{
	//init var
	clickFlags.mouseLeft = false;
	clickFlags.singleButton = false;
	clickFlags.multiplButton = false;
	clickFlags.optionButton = false;
	clickFlags.quitButton = false;

	//init font
	if (!this->font.loadFromFile("Fonts\\font.ttf"))	std::cout << "Font error" << std::endl; //should be refined

	//init text
	this->infoTextPos.x = 300.f;
	this->infoTextPos.y = 300.f;
	this->infoText.setFont(font);
	this->infoText.setCharacterSize(21);
	this->infoText.setPosition(infoTextPos);
	//infoText.setString("Hellovfvgfdfffffffffffffffffff");

	//init buttons
	this->buttons["SINGLE_PLAYER"] = new Button(100, 300, 150, 50,
		&this->font, "Single player",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	this->buttons["MULTIPLAYER"] = new Button(100, 400, 150, 50,
		&this->font, "Multiplayer",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	this->buttons["OPTIONS"] = new Button(100, 500, 150, 50,
		&this->font, "Options",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	this->buttons["QUIT"] = new Button(100, 600, 150, 50,
		&this->font, "Quit",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
}

MainMenuState::~MainMenuState()
{
	for (auto it : this->buttons)
		delete it.second;
}

void MainMenuState::update(sf::RenderWindow* targetWindow)
{
	
	if (buttons["SINGLE_PLAYER"]->isPressed() && !this->clickFlags.singleButton)
	{
		this->statesPointer->push(new PlacingState(statesPointer));

		this->clickFlags.singleButton = true;
	}

	if (!buttons["SINGLE_PLAYER"]->isPressed() && this->clickFlags.singleButton)
	{
		this->clickFlags.singleButton = false;
	}
	
	if (buttons["MULTIPLAYER"]->isPressed() && !this->clickFlags.multiplButton)
	{
		clock.restart();
		this->infoText.setPosition(infoTextPos);
		infoText.setString("Function is not evailable yet");

		this->clickFlags.multiplButton = true;
	}

	if (!buttons["MULTIPLAYER"]->isPressed() && this->clickFlags.multiplButton)
	{
		this->clickFlags.multiplButton = false;
	}

	if (buttons["QUIT"]->isPressed() && !this->clickFlags.quitButton)
	{
		endState = true;

		this->clickFlags.quitButton = true;
	}

	if (!buttons["QUIT"]->isPressed() && this->clickFlags.quitButton)
	{
		this->clickFlags.quitButton = false;
	}

	if (clock.getElapsedTime().asSeconds() > 3)
		infoText.setString("");

	this->mouseUpdatePosition(targetWindow);
	for (auto it : this->buttons)
		it.second->update(sf::Vector2f((float)this->mousePosWindow.x, (float)this->mousePosWindow.y));
}

void MainMenuState::render(sf::RenderWindow* targetWindow)
{
	targetWindow->draw(this->infoText);
	for (auto it : this->buttons)
		it.second->render(targetWindow);
}
