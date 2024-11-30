#include <iostream>
#include "Game.h"


int main()
{
	//init rand
	std::srand(static_cast<unsigned>(time(nullptr)));


	//game initialisation
	Game game;
	game.run();
	return 0;
}