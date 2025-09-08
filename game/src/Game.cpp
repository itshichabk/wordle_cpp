#include "Game.h"

const int Game::nRounds     = GAME_ROUNDS;
const int Game::nCharacters = GAME_CHARS;
const std::string Game::strWordUrl = GAME_API_URL;

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
	_grid.moveToRow(_nCurrentRound);

	do
	{
		wgetnstr(_win.getWIN(), _strInput, nCharacters);

		if (strlen(_strInput) != nCharacters)
		{
			_grid.printRow(_nCurrentRound);
		}
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

void Game::init()
{
	_strInput = new char[nCharacters + 1];
	_bHasWon = false;
	_nCurrentRound = 0;
}

void Game::play()
{
	getRandomWord();

	if (_strWord.empty())
	{
		_win.printColor("Error when fetching random word.\nThe game cannot continue.", COLOR_BLACK, COLOR_RED);
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

	wgetch(_win.getWIN());
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
		_win.printColor(_strWord.c_str(), COLOR_WHITE, COLOR_RED, true, _win.getHeight() - 1);
	}

}

std::string Game::getWord() const
{
	return _strWord;
}
