#include "State.h"

State::State(std::stack<State*>* statesPointer)
{

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
