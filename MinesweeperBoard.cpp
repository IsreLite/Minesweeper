// Minesweeper.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Minesweeperboard.h"
#include <array>
#include <iomanip>
#include <iostream>
#include <memory> // Include for shared_ptr
#include <random>
#include <set>
#include <stdexcept>
#include <vector>

MinesweeperBoard::MinesweeperBoard() : width(7), height(5), gameMode(GameMode::EASY) {
	std::cout << "I am nonparametric constructor" << std::endl;
	initializeBoard();
}

MinesweeperBoard::MinesweeperBoard(int w, int h, GameMode mode) : width(w), height(h), gameMode(mode) {
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
		}
	}
	else {
		// Calculate number of mines based on game mode
		int numMines = 0;
		switch (mode) {
		case GameMode::EASY:
			numMines = static_cast<int>(width * height * 0.1); // 10% of board area
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
	auto initializeField = [&](int row, int col, bool hasMine = false, bool hasFlag = false, bool isRevealed = false) {
		board[row][col] = std::make_shared<Field>(hasMine, hasFlag, isRevealed);
		};

	// Initialize all fields with default values
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			initializeField(i, j);
		}
	}

	// Set specific fields if provided
	for (const auto& fieldData : defaultSpecificFields) {
		int row, col;
		bool hasMine, hasFlag, isRevealed;
		std::tie(row, col, hasMine, hasFlag, isRevealed) = fieldData;
		initializeField(row, col, hasMine, hasFlag, isRevealed);
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
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> widthDist(0, width - 1);
	std::uniform_int_distribution<> heightDist(0, height - 1);
	std::set<std::pair<int, int>> minePositions;

	int minesPlaced = 0;
	while (minesPlaced < numMines) {
		int row = heightDist(gen);
		int col = widthDist(gen);
		if (minePositions.insert(std::make_pair(row, col)).second) {
			board[row][col]->hasMine = true;
			minesPlaced++;
		}
	}
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
