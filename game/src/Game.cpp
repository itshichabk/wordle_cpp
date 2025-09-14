#include <algorithm>
#include "Game.h"

/*const int Game::GAME_ROUNDS     = GAME_ROUNDS;
const int Game::GAME_CHARS = GAME_CHARS;
const std::string Game::strWordUrl = GAME_API_URL;*/

Game::Game(Console* console) : 
	_win(console, "Wordle", GAME_ROUNDS + 3, 50, true),
	_grid(&_win)
{
	init();
}

Game::~Game()
{
	clear();
	endwin();

	_strWord = "";

	_bHasWon = false;
}

void Game::getRandomWord()
{
	HttpRequest req(GAME_API_URL + std::to_string(GAME_CHARS));

	if (req.getResultCode() == CURLcode::CURLE_OK)
	{
		req.perform();

		if (req.getSuccess())
		{
			_strWord = req.getBuffer().substr(2, GAME_CHARS);
			std::transform(_strWord.begin(), _strWord.end(), _strWord.begin(), ::toupper);
		}
	}
}

void Game::getInput()
{
	do
	{
		_strInput = _grid.readInput(_nCurrentRound);

		if (_strInput.length() != GAME_CHARS)
		{
			_grid.printRow(_nCurrentRound);
		}
	}
	while (_strInput.length() != GAME_CHARS);
}

void Game::checkInput()
{
	for (int i = 0; i < GAME_CHARS; i++)
	{
		if (_strWord[i] == _strInput[i])
		{
			_grid[_nCurrentRound][i] = Grid::CORRECT;
		}
		else
		{
			for (int j = 0; j < GAME_CHARS; j++)
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

void Game::init()
{
	_bHasWon = false;
	_nCurrentRound = 0;
}

void Game::play()
{
	getRandomWord();

	if (_strWord.empty())
	{
		_win.printColor("Error when fetching random word.", COLOR_WHITE, COLOR_RED, true, 0);
		_win.printColor("The game cannot continue.", COLOR_WHITE, COLOR_RED, true, 1);
	}
	else
	{
		_grid.print();

		for (_nCurrentRound = 0; _nCurrentRound < GAME_ROUNDS; _nCurrentRound++)
		{
			playRound();

			if (_bHasWon)
			{
				break;
			}
		}

		result();
	}

	_win.getChar();
}

void Game::playRound()
{
	getInput();

	checkInput();
	_grid.printInputColor(_strInput, _nCurrentRound);
}

void Game::result()
{
	curs_set(0);
	std::string strMsg;

	_win.move(_win.getHeight() - 1, 0);

	if (_bHasWon)
	{
		_win.printColor("You won!!!!", COLOR_WHITE, COLOR_GREEN, true, _win.getHeight() - 2);
		flash();
	}
	else
	{
		_win.print("You lost... the word was:", true, _win.getHeight() - 2);
		_win.printColor(_strWord, COLOR_BLACK, COLOR_RED, true, _win.getHeight() - 1);
	}
}
