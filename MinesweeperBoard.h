#pragma once

#include <array>
#include <iostream>
#include <memory> // Include for shared_ptr
#include <stdexcept>
#include <vector>

enum class GameMode { EASY, NORMAL, HARD, DEBUG };

// Represents a single field on the Minesweeper board
struct Field {
	bool hasMine;
	bool hasFlag;
	bool isRevealed;
};

class MinesweeperBoard {
private:
	int width;
	int height;
	std::vector<std::vector<std::shared_ptr<Field>>> board; // 2D vector of shared pointers to Field
	GameMode gameMode;


	bool isValidIndex(int row, int col) const {
		return row >= 0 && row < height && col >= 0 && col < width;
	}

public:
	// Constructors
	MinesweeperBoard();
	MinesweeperBoard(int width, int height, GameMode mode);

	~MinesweeperBoard();

	// Getter functions
	int getWidth() const { return width; }
	int getHeight() const { return height; }

	// Accessor functions


private:
	void initializeBoard();


};