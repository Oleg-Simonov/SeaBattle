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
	sf::Font font;

	std::vector<State*>* statesPointer;
	sf::Vector2i mousePosWindowi;
	sf::Vector2f mousePosWindowf;
	sf::Clock clock;
	sf::Event sfEvent;

	int endState;

public:
	State(std::vector<State*>* states);
	virtual ~State();

	const int getEndState() const;
	void mouseUpdatePosition(sf::RenderWindow* targetWindow);
	virtual void update(sf::RenderWindow* targetWindow = nullptr) = 0;
	virtual void render(sf::RenderWindow* targetWindow = nullptr) = 0;
};

