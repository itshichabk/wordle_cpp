#include "Game.h"

CurlInstance* CurlInstance::_curlInstance = nullptr;

int main()
{
	Game game;
	game.play();

	return 0;
}
