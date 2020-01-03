#pragma once

#include <iostream>
#include <string>

class Dictionary;

const int boardSize = 4;

class GameBoard
{
	public:
		GameBoard(void);

		void printOn(std::ostream& o) const;

		void wordFinder(const Dictionary& dictionary) const;

    private:
		bool containsWord(const std::string& word) const;

		bool containsWord(const std::string& word, 
			const std::string& board, int x, int y) const;

		// just have 16 characters 
		// in order across each row, then on to next row
		std::string m_board;
};

std::ostream& operator<<(std::ostream& o, const GameBoard& board);

