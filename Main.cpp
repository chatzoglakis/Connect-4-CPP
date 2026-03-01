#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <limits>

#include "Game.h"

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

	Game game(board);
	if (mode == 1)
		game.playerVsPlayer();
	else
		game.playerVsAi();

	return 0;
}