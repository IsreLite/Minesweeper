// Minesweeper.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Minesweeperboard.h"
#include <array>
#include <iomanip>
#include <iostream>
#include <memory> // Include for shared_ptr
#include <random>
#include <stdexcept>
#include <vector>

MinesweeperBoard::MinesweeperBoard() : width(7), height(5), gameMode(GameMode::EASY) {
	std::cout << "I am nonparametric constructor" << std::endl;
	initializeBoard();
}

MinesweeperBoard::MinesweeperBoard(int width, int height, GameMode gameMode) :
	width(width), height(height), gameMode(gameMode) {
	std::cout << "I am parametric constructor" << std::endl;

}

void MinesweeperBoard::initializeBoard() {
	// Initialize the board
	board.resize(height, std::vector<std::shared_ptr<Field>>(width));


	// Lambda function to set a field
	auto setField = [&](int row, int col, bool hasMine, bool hasFlag, bool isRevealed) {
		board[row][col] = std::make_shared<Field>(hasMine, hasFlag, isRevealed);
		};

	// Set specific fields
	setField(0, 0, true, false, false);
	setField(1, 1, false, false, true);
	setField(0, 2, true, true, false);
}

MinesweeperBoard::~MinesweeperBoard() {};

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
