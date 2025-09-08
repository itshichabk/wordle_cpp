#include "Game.h"

const int Game::nRounds     = GAME_ROUNDS;
const int Game::nCharacters = GAME_CHARS;
const std::string Game::strWordUrl = GAME_API_URL;

Game::Game(Console* console) : 
	_win(console, "Wordle", 20, 40, true),
	_grid(&_win)
{
	_colorPairIdx[0] = console->getColorPairIdx(COLOR_WHITE, COLOR_BLACK);
	_colorPairIdx[1] = console->getColorPairIdx(COLOR_BLACK, COLOR_YELLOW);
	_colorPairIdx[2] = console->getColorPairIdx(COLOR_BLACK, COLOR_GREEN);

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
	do
	{
		_win.move(_nCurrentRound, 0);

		for (int i = 0; i < nCharacters; i++)
		{
			_win.print("_");
		}

		_win.refresh();
		_win.move(_nCurrentRound, 0);

		wgetnstr(_win.getWIN(), _strInput, nCharacters);
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
	_win.move(_nCurrentRound, 0);

	for (int i = 0; i < nCharacters; i++)
	{
		int nValue = _grid[_nCurrentRound][i];

		_win.printColor(_strInput[i], _colorPairIdx[nValue]);
	}
}

void Game::init()
{
	_strInput = new char[nCharacters + 1];
	_bHasWon = false;
	_nCurrentRound = 0;

	//initConsole();
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
		_win.printColor("Error when fetching random word. The game cannot continue.", COLOR_BLACK, COLOR_RED);
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

void Game::result()
{
	curs_set(0);
	std::string strMsg;

	if (_bHasWon)
	{
		strMsg = "You won!!!!";
		flash();
	}
	else
	{
		strMsg = "You lost... the word was " + _strWord;
	}

	_win.print(strMsg, _win.getHeight() - 1, 0);

	/*move(24, 0);

	printw("%s", strMessage.c_str());
	refresh();*/
}

std::string Game::getWord() const
{
	return _strWord;
}
