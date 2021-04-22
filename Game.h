#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"
#include <sstream>
#include <vector>
#include "OutMapShip.h"

class Game
{
private:
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event event;
	sf::Font font;
	sf::Text infoText;
	bool mouseLeftFrontEdge, mouseLeftBackEdge;
	bool spaceFrontEdge, spaceBackEdge;

	Map playerMap, enemyMap = Map(1);

	std::vector<OutMapShip> outMapShip;

public:
	

	Game();
	~Game();

	bool getWindowStatus() const;

	void update();
	void render();

};

