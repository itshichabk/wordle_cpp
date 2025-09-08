#include "Game.h"
#include "Console.h"

int main()
{
	Console console;
	Game game(&console);

	game.play();

	return 0;
}
