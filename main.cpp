#include <iostream>
#include "Game.h"
#include "Singleton.h"



int main()
{
	//init rand
	std::srand(static_cast<unsigned>(time(nullptr)));

	//game initialisation
	Game& game = Game::getInstance();


	ScoreObserver scoreObserver;
	game.addObserver(&scoreObserver);
	game.run();
	// Run the game loop
	game.run();
	return 0;
}