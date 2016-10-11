#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>

#include "path.hpp"

struct TestResult
{
	int x;
	int y;
	bool boom;
};

class Board
{
private:
	int m_size_x;
	int m_size_y;
	bool** m_gameboard;

	void DeleteBoard();
    bool SquareIsValid(int x, int y);
    
public:
	Board(int size_x, int size_y, const char* board_data);
	Board(const Board& copy);
	~Board();
	Board& operator=(const Board& rhs);

	void OutputBoard();
	bool ReadSquare(int x, int y) const;

	TestResult PathIsCorrect(Path& path, int start_x = 0, int start_y = 0);
	TestResult EvaluatePathOnce(Path& path);
    bool LinkPointsWork(Path& path);
    
};

#endif // BOARD_HPP
