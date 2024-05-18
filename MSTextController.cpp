/*
 * Copyright 2024 Israel Owolabi
 *
 * Licensed under the MIT License.
 * See LICENSE file in the project root for full license information.
 */

#include "MSTextController.h"

void MSTextController::play() {
	int width, height;
	GameMode mode;

	std::cout << "Welcome to Minesweeper!" << std::endl;
	std::cout << "Choose board size (width height): ";
	std::cin >> width >> height;

	std::cout << "Choose game mode (0 - Easy, 1 - Normal, 2 - Hard): ";
	int modeInt;
	std::cin >> modeInt;
	mode = static_cast<GameMode>(modeInt);

	board = MinesweeperBoard::MinesweeperBoard(width, height, mode);
	MSBoardTextView view(board);


	while (board.getGameState() == GameState::RUNNING) {
		view.display();
		int row, col;
		std::cout << "\n Enter row and column to reveal (or -1 -1 to exit): ";
		std::cin >> col >> row;

		if (row == -1 && col == -1) {
			break;
		}

		board.revealField(row, col);
	}

	view.display();
	std::cout << "Game over! Final state: " << board.getGameState() << std::endl;
}
