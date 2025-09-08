#pragma once

#ifndef _WIN32
#include <cstring>
#endif

#include <string>
#include "Console.h"
#include "Grid.h"
#include "HttpRequest.h"

constexpr int  GAME_ROUNDS    = 6;
constexpr int  GAME_CHARS     = 5;
constexpr char GAME_API_URL[] = "https://random-word-api.vercel.app/api?words=1&length=5";

class Game
{
public:
	static const int nRounds;
	static const int nCharacters;
	
	static const std::string strWordUrl;

private:
	Window _win;
	Grid _grid;

	std::string _strWord;
	char* _strInput;

	int  _nCurrentRound;
	bool _bHasWon;

	int _colorPairIdx[3];

	void init();
	void initConsole();
	void getRandomWord();

	void getInput();
	void checkInput();
	void colorInput();

	void playRound();
	void result();

public:
	Game(Console* console);
	~Game();

	void play();

	std::string getWord() const;
};
