#pragma once
#include "MinesweeperBoard.h"
#include "SplashScreen.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include<time.h>
#include <vector>

const int BOARD_SIZE = 8; // Assuming a square board
const float CELL_SIZE = 50.0f; // Size of each cell in pixels

class Minesweeper3D
{
public:
	Minesweeper3D();

	std::pair<float, float> getGridStartPosition()
	{
		// Get the size of the window
		sf::Vector2u windowSize = app.getSize();

		// Check if the window size has changed
		if (windowSize != currentWindowSize)
		{
			// Window size has changed, recalculate the grid parameters
			currentWindowSize = windowSize;

			// Calculate the starting position of the grid
			float gridWidth = BOARD_SIZE * CELL_SIZE;
			float gridHeight = BOARD_SIZE * CELL_SIZE;
			startX = (currentWindowSize.x - gridWidth) / 2;
			startY = (currentWindowSize.y - gridHeight) / 2;

		}

		return std::make_pair(startX, startY);
	}

	void run() {
		while (app.isOpen()) {
			handleEvents();
			//update();
			render();
		}
	}

private:
	sf::RenderWindow app;
	std::vector<std::vector<int>> board; // Represents the state of the Minesweeper board
	sf::RectangleShape cellShape; // Shape for each cell on the board
	sf::Font font;
	MinesweeperBoard minesweeperBoard = MinesweeperBoard(BOARD_SIZE, BOARD_SIZE, GameMode::NORMAL);
	sf::Vector2u currentWindowSize;
	float startX, startY;
	sf::Event event;

	void handleEvents();

	void update();

	void drawBoard();

	void render();

};

