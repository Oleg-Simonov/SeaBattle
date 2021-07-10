#include <cstdlib>
#include <ctime> 
#include "Game.h"
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup") //remove the console from release version

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