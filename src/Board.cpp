#include <iostream>
#include <vector>

#include "../include/Board.h"

Board::Board(const int rows, const int cols) {
	this->rows = rows;
	this->cols = cols;

	for (int i{}; i < rows; i++) {
		std::vector<char> row;
		for (int j{}; j < cols; j++) {
			row.push_back('-');
		}
		game_board.push_back(row);
	}
}

Board::Board(const int rows, const int cols, const array2d& game_board) {
	this->rows = rows;
	this->cols = cols;
	this->game_board = game_board;
}

//places a chip in the board, return true if successfull, false if column is full or out of bounds
bool Board::placeChip(const char chip, const int col) {

	if (isOutOfBounds(col)) 
		return false;
	

	if (fullCol(col))
		return false;
	

	for (int i = rows - 1; i > -1; i--) {
		if (game_board[i][col] == '-') {
			game_board[i][col] = chip;
			return true;
		}
	}

	return false;
}

bool Board::isOutOfBounds(const int col) {
	return col < 0 || col > cols;
}

bool Board::fullCol(const int col) {
	return game_board[0][col] != '-';
}

bool Board::checkHorizontalWin(const char chip) {

	for (std::vector<char> row : game_board) {
		int count{};
		for (char cell : row) {
			if (cell == chip)
				count++;
			else
				count = 0;

			if (count == 4)
				return true;
		}
	}

	return false;
}

bool Board::checkVerticalWin(const char chip) {

	for (int i{}; i < cols; i++) {
		int count{};
		for (int j{}; j < rows; j++) {
			if (game_board[j][i] == chip)
				count++;
			else
				count = 0;

			if (count == 4)
				return true;
		}
	} 

	return false;
}

bool Board::checkDiagonalWin(const char chip) {
	for (int i{}; i < rows - 3; i++) {
		for (int j{}; j < cols - 3; j++) {
			if (game_board[i][j] == chip &&
				game_board[i + 1][j + 1] == chip &&
				game_board[i + 2][j + 2] == chip &&
				game_board[i + 3][j + 3] == chip)
				return true;
		}
	}

	for (int i{}; i < rows - 3; i++) {
		for (int j{3}; j < cols; j++) {
			if (game_board[i][j] == chip &&
				game_board[i + 1][j - 1] == chip &&
				game_board[i + 2][j - 2] == chip &&
				game_board[i + 3][j - 3] == chip)
				return true;
		}
	}

	return false;
}

bool Board::checkWin(const char chip) {
	return (checkVerticalWin(chip) || checkHorizontalWin(chip) || checkDiagonalWin(chip));
}

void Board::printBoard() {
	for (int i{}; i < rows; i++) {
		std::cout << '|';

		for (int j{}; j < cols; j++) {
			std::cout << game_board[i][j];

			if (j != cols - 1)
				std::cout << " ";
		}

		std::cout << "| \n";
	}

	for (int i{}; i < cols * 2 + 1; i++) {
		std::cout << "-";
	}
	std::cout << "\n ";

	for (int i{}; i < cols; i++) {
		std::cout << i + 1 <<  " ";
	}
	std::cout << '\n';
}

int Board::getRows() {
	return rows;
}

int Board::getCols() {
	return cols;
}

array2d Board::getBoard() {
	return game_board;
}

bool Board::isFull() {
	for (int i{}; i < cols; i++) {
		if (!fullCol(i)) {
			return false;
		}
	}
	return true;
}

std::vector<Board> Board::availableMoves(const char chip) {
	std::vector<Board> moves;

	for (int i{}; i < cols; i++) {
		if (!this->fullCol(i)) {
			Board new_board(rows, cols, this->getBoard());
			new_board.placeChip(chip, i);
			moves.push_back(new_board);
		}
	}
	return moves;
}

//auxilliary function for evaluate()
int evaluateWindow(const std::vector<char>& window, const char chip) {
	char opponent_chip = (chip == 'o') ? 'x' : 'o';

	int score{};
	int chip_count{};
	int empty_count{};
	int opp_count{};

	for (char cell : window) {
		if (cell == chip)
			chip_count++;
		else if (cell == opponent_chip)
			opp_count++;
		else
			empty_count++;
	}

	if (chip_count == 4)
		return 100;
	else if (chip_count == 3 && empty_count == 1)
		return 5;
	else if (chip_count == 2 && empty_count == 2)
		return 2;
	else if (opp_count == 3 && empty_count == 1)
		return -80;

	return 0;
}

int Board::evaluate(const char chip) {
	int score{};
	
	//horizontal windows
	for (int r{}; r < rows; r++) {
		std::vector<char> row_array = game_board[r];
		for (int c{}; c < cols - 3; c++) {
			std::vector<char> window;
			for (int i = 0; i < 4; i++) window.push_back(row_array[c + i]);
			score += evaluateWindow(window, chip);
		}
	}

	//vertical windows
	for (int c{}; c < cols; c++) {
		for (int r{}; r < rows - 3; r++) {
			std::vector<char> window;
			for (int i{}; i < 4; i++) window.push_back(game_board[r + i][c]);
			score += evaluateWindow(window, chip);
		}
	}

	//diagonal (positive slope)
	for (int r = 0; r < rows - 3; r++) {
		for (int c = 0; c < cols - 3; c++) {
			std::vector<char> window;
			for (int i = 0; i < 4; i++) window.push_back(game_board[r + i][c + i]);
			score += evaluateWindow(window, chip);
		}
	}

	//diagonal (negative slope)
	for (int r = 0; r < rows - 3; r++) {
		for (int c = 0; c < cols - 3; c++) { // Start cols logic depends on your implementation
			std::vector<char> window;
			for (int i = 0; i < 4; i++) window.push_back(game_board[r + 3 - i][c + i]);
			score += evaluateWindow(window, chip);
		}
	}
	
	return score;
}