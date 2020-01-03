#include "StdAfx.h"
#include "GameBoard.h"
#include "Dictionary.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <vector>
using namespace std;

int Random(int range) // returns random value in [0..range)
{
	static bool seeded = false;
	if (!seeded)
	{
		seeded = true;
		srand((unsigned int)time(NULL));
	}

	double r = (double)rand() / ((double)RAND_MAX + 1.0) * range;

	return (int)r;
}

GameBoard::GameBoard(void)
{
    vector<string> dice;
	
	dice.push_back("AWOTOT");
	dice.push_back("BOAJBO");
	dice.push_back("HNZNHL");
	dice.push_back("ISTOES");
	dice.push_back("TSDIYT");
	dice.push_back("PSCAOH");
	dice.push_back("TYTLRE");
	dice.push_back("ERXIDL");
	dice.push_back("FSAFPK");
	dice.push_back("QUIHNM");
	dice.push_back("SNEIUE");
	dice.push_back("AEANGE");
	dice.push_back("RVTWEH");
	dice.push_back("TMUOIC");
	dice.push_back("WEENGH");
	dice.push_back("LYVRDE");

	for (int i = 0; i < boardSize*boardSize; i++)
	{
		int selectionNum = Random(dice.size());
        string selectedDie = dice[selectionNum];

		// remove the selected die, by copying the last one back 
		// to replace the selected one, and removing the last one
		dice[selectionNum] = dice.back();
		dice.pop_back();

		m_board += selectedDie[Random(selectedDie.size())];
    }
}

void GameBoard::printOn(ostream& o) const
{
    for (int y=0; y<boardSize; y++)
		o << m_board.substr(y*boardSize, boardSize) << endl;
}

// returns true if the word is on the board, starting at position (x, y)
bool GameBoard::containsWord(const string& word, const string& board, int x, int y) const
{
	bool result = false;

	bool dieMatch = (board[y*boardSize+x] == word[0]);

	// to match the 'Qu' die, a Q must be followed by a 'U'
	if (dieMatch && word[0] == 'Q')
		dieMatch = (word.size() >= 2) && (word[1] == 'U');

	if (dieMatch)
	{
		string wordTail = word.substr( (word[0] == 'Q') ? 2 : 1);

		if (wordTail.size() == 0)
		{
			// nothing left, we matched the entire word!
			result = true;
		}
		else
		{
			string boardTail = board;

			// can't use that die in this word anymore
			boardTail[y*boardSize+x] = ' ';

			// now look through neighbouring dice to match the rest of the word

			int startx = max(0, x-1);
			int starty = max(0, y-1);
			int endx = min(boardSize-1, x+1);
			int endy = min(boardSize-1, y+1);

			for (int newx = startx; newx <= endx && !result; newx++)
				for (int newy = starty; newy <= endy && !result; newy++)
					result = containsWord(wordTail, boardTail, newx, newy);
		}
	}

	return result;
}

// returns true if the word is on the board
bool GameBoard::containsWord(const string& word) const
{
	bool result = false;

	// check the whole board, for the whole word

	for (int x=0; x < boardSize && !result; x++)
		for (int y=0; y < boardSize && !result; y++)
			result = containsWord(word, m_board, x, y);

	return result;	
}

void GameBoard::wordFinder(const Dictionary& dictionary) const
{
	int score = 0;

	int points[9] = { 0, 0, 0, 1, 1, 2, 3, 5, 11 };

	for (size_t w = 0; w < dictionary.size(); w++)
	{
		string candidate = dictionary[w];

		if (containsWord(candidate))
		{
			cout << candidate << endl;

			score += points[min((int)candidate.size(), 8)];
		}
	}

	cout << "Total score = " << score << endl;
}

ostream& operator<<(ostream& o, const GameBoard& gameBoard)
{
    gameBoard.printOn(o);
	return o;
}

