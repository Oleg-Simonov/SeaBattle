#include <cstdlib>
#include <ctime> 
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