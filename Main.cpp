#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime> 


#include "Ship.h"
#include "Map.h"
#include "Game.h"

int main()
{
	srand(time(NULL));
	Game game;

	while (game.getWindowStatus())
	{
		game.update();
		game.render();
	}
}