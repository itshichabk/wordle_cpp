#include <curses.h>
#include <curl/curl.h>
#include <string>

#ifndef _WIN32
#include <cstring>
#endif

size_t WriteCallback(char* contents, size_t size, size_t nmemb, void* userp)
{
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

std::string getRandomWord()
{
	CURL* curl = curl_easy_init();

	if (curl)
	{
		CURLcode res;
		std::string strBuffer;

		curl_easy_setopt(curl, CURLOPT_URL, "https://random-word-api.vercel.app/api?words=1&length=5");
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &strBuffer);

		res = curl_easy_perform(curl);

		if (res == CURLE_OK)
		{
			std::string strRandomWord = strBuffer.substr(2, 5);
			return strRandomWord;
		}

		curl_easy_cleanup(curl);
	}

	return "Error";

}

int main()
{
	initscr();
	start_color();
	resize_term(25, 80);

	std::string strWord = getRandomWord();

	//const char strWord[] = getRandomWord();
	const int nRounds = 6;
	const int nCharacters = 5;

	char* strInput = new char[nCharacters + 1];

	// grid (colors)
	//  0: unset (no color)
	//  1: wrong place (yellow)
	//  2: correct (green)

	init_pair(0, COLOR_WHITE, COLOR_BLACK);
	init_pair(1, COLOR_BLACK, COLOR_YELLOW);
	init_pair(2, COLOR_BLACK, COLOR_GREEN);

	int** pnGrid = new int* [nRounds];

	for (int i = 0; i < nRounds; i++)
	{
		pnGrid[i] = new int[nCharacters];

		for (int j = 0; j < nCharacters; j++)
		{
			pnGrid[i][j] = 0;
		}
	}

	for (int i = 0; i < nRounds; i++)
	{
		move(i, 0);
		printw("_____");
		refresh();
	}

	refresh();

	bool bHasWon = false;

	for (int i = 0; i < nRounds; i++)
	{
		do
		{
			move(i, 0);
			printw("_____");
			refresh();
			move(i, 0);
			getnstr(strInput, nCharacters);
		}
		while (strlen(strInput) != nCharacters);

		for (int j = 0; j < nCharacters; j++)
		{
			if (strWord[j] == strInput[j])
			{
				pnGrid[i][j] = 2;
			}
			else
			{
				for (int k = 0; k < nCharacters; k++)
				{
					if (strWord[k] == strInput[j])
					{
						pnGrid[i][j] = 1;
						break;
					}
				}
			}
		}

		move(i, 0);

		int nCorrectLetters = 0;

		for (int j = 0; j < nCharacters; j++)
		{
			addch(strInput[j] | COLOR_PAIR(pnGrid[i][j]));

			if (pnGrid[i][j] == 2)
			{
				nCorrectLetters++;
			}
		}

		if (nCorrectLetters == nCharacters)
		{
			bHasWon = true;
			break;
		}

		beep();
	}

	move(24, 0);
	
	if (bHasWon)
	{
		flash();
		printw("YOU WON!!!!");
	}
	else
	{
		printw("YOU LOST!!!! The word was %s.", strWord.c_str());
	}

	refresh();
	getch();

	endwin();
	return 0;
}
