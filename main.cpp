#include <iostream>
#include "Game.h"


int main()
{
	//init rand
	std::srand(static_cast<unsigned>(time(NULL)));


	//initializare game
	Game game;
	game.run();
	return 0;
}