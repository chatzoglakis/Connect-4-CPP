#pragma once

#include "../include/Board.h"

struct player {
	std::string name;
	char chip;
};

class Game {
private:
	Board board;

	int minimax(Board& board, const bool is_maximizing_player, int depth = 0);
public:
	Game(const Board& board);
	void playerVsPlayer();
	void playerVsAi();
};
