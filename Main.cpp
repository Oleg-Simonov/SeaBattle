#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Ship.h"
#include "Map.h"
#include "Game.h"


int Ship::shipCounter = 0;

int main()
{

	Game game;

	while (game.getWindowStatus())
	{
		game.update();
		game.render();
	}
}