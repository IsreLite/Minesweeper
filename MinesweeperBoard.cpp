// Minesweeper.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Minesweeperboard.h"
#include <array>
#include <iomanip>
#include <iostream>
#include <memory> // Include for shared_ptr
#include <stdexcept>
#include <vector>
#include <random>

MinesweeperBoard::MinesweeperBoard() {

	//Debug
	std::cout << "I am default constructor" << std::endl;

	// Set the size of the board
	width = 7;
	height = 5;

	// Initialize the board
	board.resize(height, std::vector<Field>(width));

	// Set the initial values of the fields using lambda functions
	auto setField = [&](int row, int col, bool hasMine, bool hasFlag, bool isRevealed) {
		board[row][col] = { hasMine, hasFlag, isRevealed };
		};

	// Set specific fields
	setField(0, 0, true, false, false);
	setField(1, 1, false, false, true);
	setField(0, 2, true, true, false);

};

MinesweeperBoard::MinesweeperBoard(int width, int height, GameMode mode)
	: width(width), height(height), gameMode(mode) {

	// Initialize the board
	board.resize(height, std::vector<Field>(width));

	// Place mines on the board based on the game mode
	placeMines();
}


MinesweeperBoard::~MinesweeperBoard() {
	// Deallocate memory for the 2D array

}


bool MinesweeperBoard::isValidIndex(int row, int col) const {
	return (row >= 0 && row < height) && (col >= 0 && col < width);
}


// Methods
void MinesweeperBoard::debug_display() const {
	// Display the column numbers
	std::cout << "    ";
	for (int col = 0; col < width; ++col) {
		std::cout << std::setw(4) << col;
	}
	std::cout << std::endl;

	// Display the board
	for (int row = 0; row < height; ++row) {
		//std::cout << std::setw(2) << row << " ";
		for (int col = 0; col < width; ++col) {
			std::cout << "[" << (board[row][col].hasMine ? "M" : ".") << (board[row][col].isRevealed ? "r" : ".") << (board[row][col].hasFlag ? "f" : ".") << "]";
		}
		std::cout << std::endl;
	}
}


void MinesweeperBoard::placeMines() {
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

void MinesweeperBoard::placeRandomMines(double mineRatio) {
	// Place mines randomly on the board
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(0, 1);

	int numMines = static_cast<int>(width * height * mineRatio);
	for (int k = 0; k < numMines; ++k) {
		int row, col;
		do {
			row = rand() % height;
			col = rand() % width;
		} while (board[row][col]->hasMine);
		board[row][col]->hasMine = true;
	}
}

void MinesweeperBoard::placeDebugMines() {
	// Place mines in a specific pattern for debug mode
	for (int row = 0; row < height; ++row) {
		for (int col = 0; col < width; ++col) {
			if (row == col || row == 0 || (col == 0 && row % 2 == 0)) {
				board[row][col].hasMine = true;
			}
		}
	}
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
