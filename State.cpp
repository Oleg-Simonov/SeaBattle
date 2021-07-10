#include "State.h"

State::State(std::vector<State*>* statesPointer)
{
	if (!this->backgroundTexture.loadFromFile("Resources\\Backgrounds\\MainMenuPict.jpg")) std::cout << "textureProblem" << std::endl;
	else this->backgroundSprite.setTexture(backgroundTexture);

	this->endState = 0;
	this->statesPointer = statesPointer;

	//init font
	if (!this->font.loadFromFile("Resources\\Fonts\\font.ttf"))	MessageBox(0, (LPCWSTR)L"Font error State", (LPCWSTR)L"Error message", 0);
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
