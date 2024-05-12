#pragma once
#include "Minesweeper3D.h"
#include "MinesweeperBoard.h"
#include "SplashScreen.h"
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include<time.h>
#include <vector>



const float CELL_SIZE = 50.0f; // Size of each cell in pixels

class Minesweeper3D
{
public:
	Minesweeper3D();

	// Constructor with parameters
	Minesweeper3D(int BOARD_SIZE, GameMode gameMode);


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
	MinesweeperBoard minesweeperBoard;
	GameMode gameMode;
	int BOARD_SIZE; // Assuming a square board
	sf::RenderWindow app;
	std::vector<std::vector<int>> board; // Represents the state of the Minesweeper board
	sf::RectangleShape cellShape; // Shape for each cell on the board
	sf::Font font;
	sf::Vector2u currentWindowSize;
	sf::Event event;
	sf::Texture flaggedTexture;
	sf::Texture revealedTexture;
	sf::Texture unrevealedTexture;
	sf::Texture bombTexture;
	sf::Texture muteButtonTexture;
	sf::Texture unmuteButtonTexture;
	sf::RectangleShape exitButton;
	sf::RectangleShape pauseButton;
	sf::RectangleShape muteButton;
	sf::Text exitText;
	sf::Text muteText;
	sf::Text pauseText;
	sf::Clock gameClock; // Timer for tracking elapsed time
	sf::Time elapsedTime; // Elapsed time since the game started
	sf::Clock pauseClock; // Clock to track the time when the game is paused
	sf::Time pauseTime;   // Total time elapsed during pause
	sf::SoundBuffer explosionBuffer;
	sf::SoundBuffer gameOverBuffer;
	sf::SoundBuffer levelUpBuffer;
	sf::SoundBuffer buttonBuffer;
	sf::Sound explosionSound;
	sf::Sound gameOverSound;
	sf::Sound levelUpSound;
	sf::Sound buttonSound;


	float startX, startY, isGamePaused, isGameWin, isGameLoss, isMuted;
	void handleEvents();

	void initInGameUtils();

	void handleGameButtons();

	void update();
	void updateTimer();
	void displayWinOverlay();

	void drawBoard();

	void render();

	void initialize(int boardSize, GameMode gameMode) {
		// Initialize the game with the provided parameters
		this->BOARD_SIZE = boardSize;
		this->gameMode = gameMode;
		// Other initialization tasks...
		// Start the game loop
		run();
	}
};

