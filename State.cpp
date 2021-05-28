#include "State.h"

State::State(std::stack<State*>* statesPointer)
{
	endState = false;

	this->statesPointer = statesPointer;
}

State::~State()
{
}

const bool State::getEndState() const
{
	return this->endState;
}

void State::mouseUpdatePosition(sf::RenderWindow* targetWindow)
{
	this->mousePosWindow = sf::Mouse::getPosition(*targetWindow);
	//std::cout << mousePosWindow.x << " " << mousePosWindow.y << std::endl;
}
