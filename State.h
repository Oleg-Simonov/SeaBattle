#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stack>
#include <sstream>
#include "Map.h"
#include "Button.h"

class State
{
private:
protected:

	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;

	std::stack<State*>* statesPointer;
	sf::Vector2i mousePosWindow;
	sf::Clock clock;

	int endState;

public:
	State(std::stack<State*>* states);
	~State();

	const int getEndState() const;
	void mouseUpdatePosition(sf::RenderWindow* targetWindow);
	virtual void update(sf::RenderWindow* targetWindow = nullptr) = 0;
	virtual void render(sf::RenderWindow* targetWindow = nullptr) = 0;
};

