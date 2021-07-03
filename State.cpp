#include "State.h"

State::State(std::vector<State*>* statesPointer)
{
	if (!this->backgroundTexture.loadFromFile("Resources\\Backgrounds\\MainMenuPict.jpg")) std::cout << "textureProblem" << std::endl;
	else this->backgroundSprite.setTexture(backgroundTexture);

	this->endState = 0;

	this->statesPointer = statesPointer;
}

State::~State()
{
}

const int State::getEndState() const
{
	return this->endState;
}

void State::mouseUpdatePosition(sf::RenderWindow* targetWindow)
{
	this->mousePosWindow = sf::Mouse::getPosition(*targetWindow);
	//std::cout << mousePosWindow.x << " " << mousePosWindow.y << std::endl;
}
