#pragma once
#include <sstream>
#include <vector>
#include "State.h"
#include "GameState.h"
#include "PlacingState.h"

class Game
{
private:
	sf::RenderWindow* window;
	sf::VideoMode videoMode;

	std::vector<State*> states;

	int currentState;

public:
	
	Game();
	~Game();

	bool getWindowStatus() const;

	void update();
	void render();

};

