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

	void placeMines();
	void placeRandomMines(double mineRatio);
	void placeDebugMines();

	bool isValidIndex(int row, int col) const {
		return row >= 0 && row < height && col >= 0 && col < width;
	}

public:
	// Constructors
	MinesweeperBoard() : MinesweeperBoard(7, 5, GameMode::EASY) {}

	MinesweeperBoard(int width, int height, GameMode mode)
		: width(width), height(height), gameMode(mode) {
		// Initialize the board
		board.resize(height, std::vector<std::shared_ptr<Field>>(width));
		for (int row = 0; row < height; ++row) {
			for (int col = 0; col < width; ++col) {
				board[row][col] = std::make_shared<Field>(Field{ false, false, false });
			}
		}

		// Place mines on the board based on the game mode
		placeMines();
	}

	~MinesweeperBoard() = default;

	// Getter functions
	int getWidth() const { return width; }
	int getHeight() const { return height; }

	// Accessor functions
	std::shared_ptr<Field>& getField(int row, int col) {
		if (!isValidIndex(row, col)) {
			throw std::out_of_range("Invalid row or column index");
		}
		return board[row][col];
	}

	const std::shared_ptr<Field>& getField(int row, int col) const {
		if (!isValidIndex(row, col)) {
			throw std::out_of_range("Invalid row or column index");
		}
		return board[row][col];
	}

	void debug_display() const {
		// Display the column numbers
		std::cout << "    ";
		for (int col = 0; col < width; ++col) {
			std::cout << std::setw(4) << col;
		}
		std::cout << std::endl;

		// Display the board
		for (int row = 0; row < height; ++row) {
			std::cout << std::setw(2) << row << " ";
			for (int col = 0; col < width; ++col) {
				std::cout << "[" << (board[row][col]->hasMine ? "M" : ".") << (board[row][col]->isRevealed ? "r" : ".") << (board[row][col]->hasFlag ? "f" : ".") << "]";
			}
			std::cout << std::endl;
		}
	}

private:
	void placeMines() {
		// Place mines based on the game mode
		switch (gameMode) {
		case GameMode::EASY:
			placeRandomMines(0.1);
			break;
		case GameMode::NORMAL:
			placeRandomMines(0.2);
			break;
		case GameMode::HARD:
			placeRandomMines(0.3);
			break;
		case GameMode::DEBUG:
			placeDebugMines();
			break;
		}
	}

	void placeRandomMines(double mineRatio) {
		// Place mines randomly on the board
		int numMines = static_cast<int>(width * height * mineRatio);
		for (int i = 0; i < numMines; ++i) {
			int row, col;
			do {
				row = rand() % height;
				col = rand() % width;
			} while (board[row][col]->hasMine);
			board[row][col]->hasMine = true;
		}
	}

	void placeDebugMines() {
		// Place mines in a specific pattern for debug mode
		for (int row = 0; row < height; ++row) {
			for (int col = 0; col < width; ++col) {
				if (row == col || row == 0 || (col == 0 && row % 2 == 0)) {
					board[row][col]->hasMine = true;
				}
			}
		}
	}
};