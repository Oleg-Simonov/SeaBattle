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
	this->mousePosWindowi = sf::Mouse::getPosition(*targetWindow);
	this->mousePosWindowf.x = (float)mousePosWindowi.x;
	this->mousePosWindowf.y = (float)mousePosWindowi.y;
	//std::cout << mousePosWindowi.x << " " << mousePosWindowi.y << std::endl;
}
