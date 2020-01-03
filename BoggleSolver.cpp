
// BoggleSolver, by Peter Thelander
// 2009-02-25

#include "stdafx.h"
#include "GameBoard.h"
#include "Dictionary.h"
#include <iostream>
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	cout << "Boggle Solver, by Peter Thelander" << endl << endl;

	GameBoard gameBoard;

	cout << gameBoard << endl;

	Dictionary dictionary("wordlist.txt");

	gameBoard.wordFinder(dictionary);

	return 0;
}

