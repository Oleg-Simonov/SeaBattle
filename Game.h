#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"
#include <sstream>
#include <vector>
#include <stack>
#include "OutMapShip.h"
#include "State.h"
#include "GameState.h"
#include "PlacingState.h"
#include "MainMenuState.h"

class Game
{
private:
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event sfEvent;

	std::stack<State*> states;

public:
	

	Game();
	~Game();

	bool getWindowStatus() const;

	void update();
	void render();

};

