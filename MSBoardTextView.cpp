#include "Minesweeperboard.h"
#include "MSBoardTextView.h"
#include <iomanip>
#include <iostream>

MSBoardTextView::MSBoardTextView(const MinesweeperBoard& board) : board(board) {}

void MSBoardTextView::display() const {
	// Display column numbers
	std::cout << std::setw(1) << "";
	for (int j = 0; j < board.getBoardWidth(); ++j) {
		std::cout << std::setw(3) << j;
	}
	std::cout << std::endl;

	// Display board rows
	for (int i = 0; i < board.getBoardHeight(); ++i) {
		std::cout << std::setw(1) << i << " ";
		for (int j = 0; j < board.getBoardWidth(); ++j) {
			std::cout << std::setw(0) << "[";
			char representation = board.getFieldInfo(i, j);
			std::cout << std::setw(0) << representation;
			std::cout << std::setw(0) << "]";
		}
		std::cout << std::endl;
	}
}
