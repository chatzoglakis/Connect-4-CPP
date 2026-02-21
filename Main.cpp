#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <limits>

#include "Board.h"

struct player {
	std::string name;
	char chip;
};

void playerVsPlayer(Board& board) {
	std::string name;

	std::cout << "player 1, enter your name: ";
	std::cin >> name;
	player p1 = { name, 'x' };

	std::cout << "player 2, enter your name: ";
	std::cin >> name;
	player p2 = { name, 'o' };

	bool p1_start = rand() % 2;
	player curr_player;

	curr_player = (p1_start) ? p1 : p2;

	while (true) {
		int col;
		std::cout << curr_player.name << ", choose column: ";
		std::cin >> col;

		if (board.placeChip(curr_player.chip, col - 1)) {
			board.printBoard();
		}	
		else {
			std::cout << "Try again\n";
			continue;
		}
			

		if (board.checkWin(curr_player.chip)) {
			std::cout << curr_player.name << " has won";
			return;
		}

		if (board.isFull()) {
			std::cout << "GAME OVER. It's a draw\n";
			return;
		}

		curr_player = (curr_player.chip == 'x') ? p2 : p1;
	}
}

int minimax(Board& board, const bool is_maximizing_player, int depth = 0) {
	if (board.checkWin('x'))
		return -100;
	if (board.checkWin('o'))
		return 100;
	if (board.isFull())
		return 0;
	if (depth == 4)
		return board.evaluate('o');

	int best_val{};
	int value{};

	if (is_maximizing_player) {
		best_val = -1000;
		for (Board& move : board.availableMoves('o')) {
			value = minimax(move, false, depth+1);
			best_val = std::max(best_val, value);
		}
		return best_val;
	}
	else {
		best_val = 1000;
		for (Board& move : board.availableMoves('x')) {
			value = minimax(move, true, depth+1);
			best_val = std::min(best_val, value);
		}
		return best_val;
	}
}

void playerVsAi(Board& board) {
	std::string name;
	std::cout << "player, enter your name: ";
	std::cin >> name;
	player p1 = { name, 'x' };
	player p2 = { "AI", 'o' };

	bool p1_start = rand() % 2;
	player curr_player;

	curr_player = (p1_start) ? p1 : p2;

	while (true) {
		int col{};
		if (curr_player.name == p1.name) {
			
			std::cout << curr_player.name << ", choose column: ";
			std::cin >> col;
		}
		else {
			int best_val = -1000;
			int best_col = -1;
			int cols = board.getCols();

			for (int i{}; i < cols; i++) {
				if (!board.fullCol(i)) {
					Board next_board(board.getRows(), board.getCols(), board.getBoard());
					next_board.placeChip(p2.chip, i);

					int value = minimax(next_board, false);
					
					if (value > best_val) {
						best_val = value;
						best_col = i;
					}
				}
			}
			col = best_col + 1;
			std::cout << "AI chose column " << col << '\n';
		}

		if (board.placeChip(curr_player.chip, col - 1))
			board.printBoard();
		else
			continue;

		if (board.checkWin(curr_player.chip)) {
			std::cout << "GAME OVER. " << curr_player.name << " has won\n";
			return;
		}

		if (board.isFull()) {
			std::cout << "GAME OVER. It's a draw\n";
			return;
		}

		curr_player = (curr_player.chip == 'x') ? p2 : p1;
	}
}

int getDimension(const std::string& text) {
	int size;

	while (true) {
		std::cout << text;
		std::cin >> size;

		if (std::cin.fail() || size < 5 || size > 9) {
			std::cout << "Enter a positive integer from 5 to 9\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else {
			return size;
		}
	}
}

int main() {
	srand(time(nullptr));
	int rows, cols;

	rows = getDimension("enter the number of rows (5-9): ");
	cols = getDimension("enter the number of columns (5-9): ");

	int mode{};
	while (mode != 1 && mode != 2) {
		std::cout << "Choose mode (1 = player vs player, 2 = player vs AI): ";
		std::cin >> mode;
	}

	Board board(rows, cols);
	board.printBoard();

	if (mode == 1)
		playerVsPlayer(board);
	else
		playerVsAi(board);

	return 0;
}