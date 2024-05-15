#pragma once

#include "Minesweeperboard.h"
#include "MSBoardTextView.h"
#include <array>
#include <iostream>
#include <memory> // Include for shared_ptr
#include <stdexcept>
#include <vector>

enum class GameMode { EASY, NORMAL, HARD, DEBUG };
enum GameState { RUNNING, FINISHED_WIN, FINISHED_LOSS };

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
	GameState gameState;
	friend class Minesweeper3D;
	bool isFirstMove = 0;
	bool isValidIndex(int row, int col) const {
		return row >= 0 && row < height && col >= 0 && col < width;
	}


public:
	// Constructors
	MinesweeperBoard();
	MinesweeperBoard(int width, int height, GameMode mode);

	int remainingMineCount;
	// Define default specific fields
	std::vector<std::tuple<int, int, bool, bool, bool>> defaultSpecificFields = {
		{0, 0, true, false, false},
		{1, 1, false, false, true},
		{0, 2, true, true, false}
	};



	~MinesweeperBoard();
	// Setter functions

	void setGameState(GameState);

	// Getter functions

	int getBoardWidth() const { return width; }
	int getBoardHeight() const { return height; }

	int getMineCount() const;
	int countMines(int, int) const;

	bool isRevealed(int, int) const;

	bool hasFlag(int, int) const;

	void revealField(int, int);

	void toggleFlag(int, int);

	GameState getGameState() const;

	void testRevealFieldAndGetGameState();

	char getFieldInfo(int, int) const;

	// Utility functions
	void debug_display() const;


private:
	void initializeBoard();
	bool hasAtLeastOneCellRevealed();
	void setSpecificFields() const;
	void initializeAllFields();
	void placeMinesRandomly(int numMines);

};