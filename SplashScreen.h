#pragma once
#include "MinesweeperBoard.h"
#include "WindowManager.h"
#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>

constexpr unsigned int MIN_WINDOW_WIDTH = 800; // Minimum window width
constexpr unsigned int MIN_WINDOW_HEIGHT = 600; // Minimum window height

class SplashScreen {
public:
	SplashScreen(std::shared_ptr<sf::RenderWindow> window);
	void run();
	void displayMainMenu();
	void displayUI();

private:
	std::shared_ptr<sf::RenderWindow> window;
	sf::Texture logoTexture;
	sf::Font font;
	sf::Texture aboveLoadingBarTexture;
	sf::Sprite aboveLoadingBarSprite;
	//float scaleFactor = 1.0f;
	sf::View view;  // Add this line
	sf::Vector2u windowSize;
	float scaleFactor, windowWidth, windowHeight;


	int boardSize = 4; // Default board size
	const int MAX_BOARD_SIZE = 20; // Maximum allowed board size
	friend class WindowManager;
	friend class Minesweeper3D;
	void displayLogo();
	void setupUIElements();
	void updateUIElements();
	std::pair<float, float> getGridStartPosition();
	sf::Sprite loadAboveLoadingBarImage();
	void loadAndDisplayAboveLoadingBarImage();
	void startGame(std::shared_ptr<sf::RenderWindow> window, int boardSize, GameMode selectedGameMode);


	void updateWindowSize() {
		windowSize = window->getSize();
		windowWidth = static_cast<float>(windowSize.x);
		windowHeight = static_cast<float>(windowSize.y);
	}

};
