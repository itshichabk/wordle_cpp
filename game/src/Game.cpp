#include "Game.h"

const int Game::nRounds     = 6;
const int Game::nCharacters = 5;
const std::string Game::strWordUrl = "https://random-word-api.vercel.app/api?words=1&length=5";

Game::Game()
{
	_strInput = new char[nCharacters + 1];
	_bHasWon = false;
	_nCurrentRound = 0;

	initConsole();
}

Game::~Game()
{
	clear();
	endwin();

	_strWord = "";
	delete _strInput;

	_bHasWon = false;
}

void Game::getRandomWord()
{
	HttpRequest req("https://random-word-api.vercel.app/api?words=1&length=5");

	if (req.getResultCode() == CURLcode::CURLE_OK)
	{
		req.perform();

		if (req.getSuccess())
		{
			_strWord = req.getBuffer().substr(2, 5);
		}
	}
}

void Game::getInput()
{
	do
	{
		move(_nCurrentRound, 0);

		for (int i = 0; i < nCharacters; i++)
		{
			addch('_');
		}

		refresh();
		move(_nCurrentRound, 0);

		getnstr(_strInput, nCharacters);
	}
	while (strlen(_strInput) != nCharacters);
}

void Game::checkInput()
{
	for (int i = 0; i < nCharacters; i++)
	{
		if (_strWord[i] == _strInput[i])
		{
			_grid[_nCurrentRound][i] = Grid::CORRECT;
		}
		else
		{
			for (int j = 0; j < nCharacters; j++)
			{
				if (_strWord[j] == _strInput[i])
				{
					_grid[_nCurrentRound][i] = Grid::WRONG_SPOT;
					break;
				}
			}
		}
	}

	_bHasWon = _grid.isRowCorrect(_nCurrentRound);
}

void Game::colorInput()
{
	move(_nCurrentRound, 0);

	for (int i = 0; i < nCharacters; i++)
	{
		addch(_strInput[i] | COLOR_PAIR(_grid[_nCurrentRound][i]));
	}
}

void Game::initConsole()
{
	initscr();
	start_color();
	resize_term(25, 80);

	init_pair(Grid::INCORRECT,  COLOR_WHITE, COLOR_BLACK);
	init_pair(Grid::WRONG_SPOT, COLOR_BLACK, COLOR_YELLOW);
	init_pair(Grid::CORRECT,    COLOR_BLACK, COLOR_GREEN);
}

void Game::play()
{
	getRandomWord();

	if (_strWord.empty())
	{
		printw("Error when fetching random word. The game cannot continue.");
	}
	else
	{
		_grid.print();

		for (_nCurrentRound = 0; _nCurrentRound < nRounds; _nCurrentRound++)
		{
			playRound();

			if (_bHasWon)
			{
				break;
			}
		}

		result();
	}

	getch();
}

void Game::playRound()
{
	getInput();

	checkInput();
	colorInput();
}

void Game::result() const
{
	std::string strMessage;

	if (_bHasWon)
	{
		strMessage = "You won!!!!";
		flash();
	}
	else
	{
		strMessage = "You lost... the word was " + _strWord;
	}

	move(24, 0);

	printw("%s", strMessage.c_str());
	refresh();
}

std::string Game::getWord() const
{
	return _strWord;
}
