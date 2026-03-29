#pragma once

#include <vector>

using array2d = std::vector<std::vector<char>>;

class Board {
private:
	int cols;
	int rows;
	array2d game_board;

	bool isOutOfBounds(const int col);
	bool checkHorizontalWin(const char chip);
	bool checkVerticalWin(const char chip);
	bool checkDiagonalWin(const char chip);

public:
	Board(int rows, int cols);
	Board(const int rows, const int cols, const array2d& game_board);
	void printBoard();
	bool placeChip(const char chip, const int col);
	bool checkWin(const char chip);
	bool fullCol(const int col);
	bool isFull();
	array2d getBoard();
	std::vector<Board> availableMoves(const char chip);
	int evaluate(const char chip); \
	int getRows();
	int getCols();
};