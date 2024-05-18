/*
 * Copyright 2024 Israel Owolabi
 *
 * Licensed under the MIT License.
 * See LICENSE file in the project root for full license information.
 */

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

