#pragma once
#include "Minesweeperboard.h"
#include "MSBoardTextView.h"


class MSTextController {
public:
	MSTextController(MinesweeperBoard& board, MSBoardTextView& view) : board(board), view(view) {}

	void play();

private:
	MinesweeperBoard& board;
	MSBoardTextView& view;
};

