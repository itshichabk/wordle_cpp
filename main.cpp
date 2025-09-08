#include "Game.h"
#include "Console.h"

int main()
{
	//Game game;
	//game.play();

	Console console;
	Game game(&console);

	game.play();

	return 0;
}
