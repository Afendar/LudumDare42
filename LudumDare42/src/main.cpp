#include "Game.h"

int main()
{
	Game* game = Game::getInstance();
	game->run();

	system("PAUSE");

	return EXIT_SUCCESS;
}