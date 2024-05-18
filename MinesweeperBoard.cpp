/*
 * Copyright 2024 Israel Owolabi
 *
 * Licensed under the MIT License.
 * See LICENSE file in the project root for full license information.
 */

 // Minesweeper.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Minesweeperboard.h"
#include <array>
#include <iomanip>
#include <iostream>
#include <memory> 
#include <random>
#include <set>
#include <stdexcept>
#include <vector>

MinesweeperBoard::MinesweeperBoard() : width(7), height(5), gameMode(GameMode::EASY) {
	initializeBoard();
	std::cout << "I am default nonparametric constructor" << std::endl;
}

MinesweeperBoard::MinesweeperBoard(int w, int h, GameMode mode) : width(w), height(h), gameMode(mode) {
	std::cout << "I am parametric constructor" << std::endl;


	initializeBoard();
	if (mode == GameMode::DEBUG) {
		// Place mines as per DEBUG mode requirements
		// All the fields on diagonal should have mine
		// All fields in first row should have mine
		// Every second field in first column should have mine
		for (int i = 0; i < std::min(width, height); ++i) {
			board[i][i]->hasMine = true; // Diagonal
			board[0][i]->hasMine = true; // First row
			if (i % 2 == 0) {
				board[i][0]->hasMine = true; // Every second field in first column
			}
			//Reveal some fields to match debugging test
			//board[4][9]->isRevealed = true;
			//board[7][0]->isRevealed = true;

		}
	}
	else {
		// Calculate number of mines based on game mode
		int numMines = 0;
		switch (mode) {
		case GameMode::EASY:
			numMines = static_cast<int>(std::ceil(width * height * 0.1)); // 10% of board area
			break;
		case GameMode::NORMAL:
			numMines = static_cast<int>(width * height * 0.2); // 20% of board area
			break;
		case GameMode::HARD:
			numMines = static_cast<int>(width * height * 0.3); // 30% of board area
			break;
		default:
			break;
		}
		placeMinesRandomly(numMines);
	}
}

void MinesweeperBoard::initializeBoard() {
	// Initialize the board
	board.resize(height, std::vector<std::shared_ptr<Field>>(width));

	// Lambda function to initialize a field
	auto initializeField = [&](
		int row, int col, bool hasMine = false, bool hasFlag = false, bool isRevealed = false) {
			board[row][col] = std::make_shared<Field>(hasMine, hasFlag, isRevealed);
		};

	// Initialize all fields with default values
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			initializeField(i, j);
		}
	}
	//setSpecificFields();
}

void MinesweeperBoard::setSpecificFields() const {
	// Set specific fields if provided
	for (const auto& fieldData : defaultSpecificFields) {
		int row, col;
		bool hasMine, hasFlag, isRevealed;
		std::tie(row, col, hasMine, hasFlag, isRevealed) = fieldData;
		board[row][col]->hasMine = hasMine;
		board[row][col]->hasFlag = hasFlag;
		board[row][col]->isRevealed = isRevealed;
	}
}

void MinesweeperBoard::debug_display() const {
	//Display the board in debug mode format
	std::cout << std::setw(1) << "";
	for (int j = 0; j < width; ++j) {
		std::cout << std::setw(5) << j;
	}
	std::cout << std::endl;

	for (int i = 0; i < height; ++i) {
		std::cout << std::setw(2) << i << "|";
		for (int j = 0; j < width; ++j) {
			std::cout << "[";
			if (board[i][j]->hasMine) {
				std::cout << "M";
			}
			else {
				std::cout << ".";
			}
			if (board[i][j]->isRevealed) {
				std::cout << "r.";
			}
			else if (board[i][j]->hasFlag) {
				std::cout << ".f";
			}
			else {
				std::cout << "..";
			}
			std::cout << "]";
		}
		std::cout << std::endl;
	}
}
void MinesweeperBoard::placeMinesRandomly(int numMines) {
	std::random_device rd;
	std::uniform_int_distribution<> widthDist(0, width - 1);
	std::uniform_int_distribution<> heightDist(0, height - 1);
	std::set<std::pair<int, int>> minePositions;

	int minesPlaced = 0;
	while (minesPlaced < numMines) {
		std::mt19937 gen(rd()); // Seed the generator each time
		int row = heightDist(gen);
		int col = widthDist(gen);
		if (minePositions.insert(std::make_pair(row, col)).second) {
			board[row][col]->hasMine = true;
			minesPlaced++;
		}
	}
}

int MinesweeperBoard::getMineCount() const
{
	int mineCount = 0;
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			if (board[i][j]->hasMine) {
				mineCount++;
			}
		}
	}
	return mineCount;
}

int MinesweeperBoard::countMines(int row, int col) const {
	if (!isRevealed(row, col)) {
		return -1;
	}


	if (row < 0 || row >= this->height || col < 0 || col >= this->width) {
		return -1;
	}

	int mineCount = 0;
	for (int i = row - 1; i <= row + 1; ++i) {
		for (int j = col - 1; j <= col + 1; ++j) {
			if (i >= 0 && i < this->height && j >= 0 && j < this->width && board[i][j]->hasMine) {
				mineCount++;
			}
		}
	}

	if (board[row][col]->hasMine) {
		mineCount--;
	}

	return mineCount;
}

bool MinesweeperBoard::isRevealed(int row, int col) const {
	if (row < 0 || row >= height || col < 0 || col >= width) {
		return false;
	}

	return board[row][col]->isRevealed;
}

bool MinesweeperBoard::hasFlag(int row, int col) const {
	if (row < 0 || row >= height || col < 0 || col >= width) {
		return false;
	}

	if (isRevealed(row, col)) {
		return false;
	}

	return board[row][col]->hasFlag;
}

void MinesweeperBoard::toggleFlag(int row, int col) {
	if (row < 0 || row >= height || col < 0 || col >= width) {
		return;
	}

	if (isRevealed(row, col)) {
		return;
	}

	if (getGameState() != GameState::RUNNING) {
		return;
	}

	board[row][col]->hasFlag = !board[row][col]->hasFlag;
}

void MinesweeperBoard::revealField(int row, int col) {

	if (row < 0 || row >= height || col < 0 || col >= width) {
		return;
	}

	if (isRevealed(row, col)) {
		return;
	}

	if (hasFlag(row, col)) {
		return;
	}

	if (getGameState() != GameState::RUNNING) {
		return;
	}

	if (!board[row][col]->hasMine) {
		board[row][col]->isRevealed = true;
	}
	else if (board[row][col]->hasMine) {
		// Check if this is the first move
		isFirstMove = hasAtLeastOneCellRevealed();

		// On the first non-mine cell click, initialize the game board and set the game state to "played"
		if (!isFirstMove) {
			// First move, move the mine to another location
			int newRow, newCol;
			do {
				newRow = rand() % height;
				newCol = rand() % width;
			} while (board[newRow][newCol]->hasMine);
			board[newRow][newCol]->hasMine = true;
			board[row][col]->hasMine = false;
			board[row][col]->isRevealed = true;
			std::cout << "A mine has been redirected to another position on first move" << std::endl;
		}
		else {
			board[row][col]->isRevealed = true;
			setGameState(GameState::FINISHED_LOSS);
		}
	}
}

GameState MinesweeperBoard::getGameState() const {
	bool hasRevealedMine = false;
	int unrevealedNonMines = 0;
	int flaggedMines = 0;
	int minecount = getMineCount();
	std::vector<std::pair<int, int>> unrevealedNonMineIndices;


	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			if (!board[i][j]->isRevealed) {
				if (!board[i][j]->hasMine) {
					unrevealedNonMines++;
					unrevealedNonMineIndices.push_back({ j, i });

				}
			}
			else if (board[i][j]->hasMine) {
				hasRevealedMine = true;
			}
			else if (board[i][j]->hasFlag) {
				flaggedMines++;
			}
		}
	}

	int remainingMineCount = minecount - flaggedMines;

	if (hasRevealedMine) {
		std::cout << "Game state: FINISHED_LOSS" << std::endl;
		std::cout << "Remaining mines: " << remainingMineCount << std::endl;
		return GameState::FINISHED_LOSS;
	}
	else if (unrevealedNonMines == 0 || (flaggedMines == minecount)) {
		std::cout << "Game state: FINISHED_WIN" << std::endl;
		std::cout << "Remaining mines: 0" << std::endl;
		return GameState::FINISHED_WIN;
	}
	else {
		std::cout << "Game state: RUNNING" << std::endl;
		std::cout << "Remaining mines: " << remainingMineCount << std::endl;
		std::cout << "Remaining mines: " << minecount << std::endl;
		std::cout << "Unrevealed mines: " << unrevealedNonMines << std::endl;
		std::cout << "Unrevealed mines: ";

		for (const auto& index : unrevealedNonMineIndices) {
			std::cout << "(" << index.first << ", " << index.second << ") ";
		}
		std::cout << std::endl;
		std::cout << "Flagged mines: " << flaggedMines << std::endl << std::endl;

		return GameState::RUNNING;
	}
}


void MinesweeperBoard::testRevealFieldAndGetGameState() {
	std::cout << "Testing revealField() and getGameState():\n";

	// Test the initial game state
	std::cout << "Game state: " << (getGameState() == GameState::RUNNING ? "Running" : "Finished") << std::endl;

	// Reveal a non-mine field
	std::cout << "Revealing a non-mine field (0, 1):\n";
	revealField(4, 9);
	std::cout << "Game state: " << (getGameState() == GameState::RUNNING ? "Running" : "Finished") << std::endl;

	// Reveal a mine field
	std::cout << "Revealing a mine field (0, 0):\n";
	revealField(0, 0);
	std::cout << "Game state: " << (getGameState() == GameState::RUNNING ? "Running" : "Finished") << std::endl;

	// Reveal another mine field
	std::cout << "Revealing another mine field (1, 0):\n";
	revealField(1, 0);
	std::cout << "Game state: " << (getGameState() == GameState::RUNNING ? "Running" : "Finished") << std::endl;

	std::cout << std::endl;
}
char MinesweeperBoard::getFieldInfo(int row, int col) const {
	if (row < 0 || row >= height || col < 0 || col >= width) {
		return '#';
	}

	if (!isRevealed(row, col)) {
		if (hasFlag(row, col)) {
			return 'F';
		}
		else {
			return '_';
		}
	}

	if (board[row][col]->hasMine) {
		return 'x';
	}

	int mineCount = countMines(row, col);
	if (mineCount == 0) {
		return ' ';
	}
	else {
		return static_cast<char>('0' + mineCount);
	}
}

void MinesweeperBoard::setGameState(GameState state) {
	this->gameState = state;
}

bool MinesweeperBoard::hasAtLeastOneCellRevealed() {
	for (int row = 0; row < board.size(); ++row) {
		for (int col = 0; col < board.size(); ++col) {
			if (board[row][col]->isRevealed) {
				return true; // At least one cell is revealed
			}
		}
	}
	return false; // No cell is revealed
}


MinesweeperBoard::~MinesweeperBoard() {
	// Destroy the board
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			board[i][j].reset();
		}
		board[i].clear();
	}
	board.clear();

	std::cout << "Board has been destroyed\n";

};
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
