#pragma once

class MinesweeperBoard;

class MSBoardTextView {
public:
	MSBoardTextView(const MinesweeperBoard& board); // Constructor with board reference
	void display() const;                          // Method to display the board

private:
	const MinesweeperBoard& board;                 // Reference to the MinesweeperBoard object
};