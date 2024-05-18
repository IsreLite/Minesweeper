#pragma once

#include "Minesweeperboard.h"
#include "MSBoardTextView.h"
#include <array>
#include <initializer_list>
#include <iostream>
#include <memory> // Include for shared_ptr
#include <stdexcept>
#include <tuple>
#include <vector>

enum class GameMode { EASY, NORMAL, HARD, DEBUG };
enum GameState { RUNNING, FINISHED_WIN, FINISHED_LOSS };

// Represents a single field on the Minesweeper board
struct Field {
	bool hasMine;
	bool hasFlag;
	bool isRevealed;
};

//template<typename T1, typename T2, typename T3, typename T4, typename T5>
//std::vector<std::tuple<T1, T2, T3, T4, T5>> createDefaultSpecificFields() {
//	return {
//		std::make_tuple(T1(0), T2(0), T3(true), T4(false), T5(false)),
//		std::make_tuple(T1(1), T2(1), T3(false), T4(false), T5(true)),
//		std::make_tuple(T1(0), T2(2), T3(true), T4(true), T5(false))
//	};
//}
//
//auto defaultSpecificField = createDefaultSpecificFields<int, int, bool, bool, bool>();

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

	//std::vector<std::tuple<int, int, bool, bool, bool>> defaultSpecificFields = defaultSpecificField;
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