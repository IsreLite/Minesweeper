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




class Minesweeper3D
{
public:
	Minesweeper3D();

	// Constructor with parameters
	Minesweeper3D(std::shared_ptr<sf::RenderWindow> app, int BOARD_SIZE, GameMode gameMode);



	void run() {
		while (app->isOpen()) {
			handleEvents();
			updateWindowSize();
			render();
		}
	}



private:
	MinesweeperBoard minesweeperBoard;
	GameMode gameMode;
	friend class SplashScreen;

	int BOARD_SIZE; // Assuming a square board
	float startX, startY, mousePosX, mousePosY, windowWidth, windowHeight;
	bool isGamePaused, isGameWin, isGameLost, isMuted;
	float CELL_SIZE = 50.0f; // Size of each cell in pixels

	std::vector<std::vector<int>> board; // Represents the state of the Minesweeper board

	std::shared_ptr<sf::RenderWindow> app;

	sf::Font font;


	sf::Vector2u currentWindowSize;
	sf::Vector2u windowSize;
	sf::Vector2i mousePos;

	sf::Event event;

	sf::Texture flaggedTexture;
	sf::Texture revealedTexture;
	sf::Texture unrevealedTexture;
	sf::Texture bombTexture;
	sf::Texture muteButtonTexture;
	sf::Texture unmuteButtonTexture;

	sf::RectangleShape cellShape; // Shape for each cell on the board
	sf::RectangleShape exitButton;
	sf::RectangleShape pauseButton;
	sf::RectangleShape muteButton;
	sf::RectangleShape backToHomeButton;

	sf::Text exitText;
	sf::Text pauseText;
	sf::Text backToHomeText;

	sf::Clock gameClock; // Timer for tracking elapsed time
	sf::Clock pauseClock; // Clock to track the time when the game is paused
	sf::Time elapsedTime; // Elapsed time since the game started
	sf::Time pauseTime;   // Total time elapsed during pause

	sf::SoundBuffer explosionBuffer;
	sf::SoundBuffer gameOverBuffer;
	sf::SoundBuffer levelUpBuffer;
	sf::SoundBuffer buttonBuffer;
	sf::Sound explosionSound;
	sf::Sound gameOverSound;
	sf::Sound levelUpSound;
	sf::Sound buttonSound;


	void handleEvents();
	void initInGameUtils();
	void handleGameButtons();
	void update();
	void updateTimer();
	void displayOverlay(int scenario);
	void drawBoard();
	void render();
	void resetGame();
	void updateMousePos();
	void updateWindowSize();

	std::pair<float, float> getGridStartPosition();

	sf::Vector2i getMousePos() const;
	sf::Vector2f getMousePosFloat() const;
	void initializeButton(sf::Text& text, sf::RectangleShape& button, const sf::String& label,
		const sf::Color& fillColor, const sf::Vector2f& buttonPosition, const sf::Vector2f& textOffset);
	void initialize(int boardSize, GameMode gameMode) {
		// Initialize the game with the provided parameters
		this->BOARD_SIZE = boardSize;
		this->gameMode = gameMode;
		// Other initialization tasks...
		// Start the game loop
		run();
	}
};

