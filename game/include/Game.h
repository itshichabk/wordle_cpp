#pragma once

#include <string>

#ifndef _WIN32
#include <cstring>
#endif

#include "Grid.h"
#include "CurlRequest.h"

class Game
{
public:
	static const int nRounds;
	static const int nCharacters;
	
	static const std::string strWordUrl;

private:
	Grid _grid;

	std::string _strWord;
	char* _strInput;

	int  _nCurrentRound;
	bool _bHasWon;

	void initConsole();
	void getRandomWord();

	void getInput();
	void checkInput();
	void colorInput();

	void playRound();
	void result() const;

public:
	Game();
	~Game();

	void play();

	std::string getWord() const;
};
