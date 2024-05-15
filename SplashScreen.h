#pragma once
#include "WindowManager.h"
#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>


class SplashScreen {
public:
	SplashScreen(std::shared_ptr<sf::RenderWindow> window);
	void run();

private:
	std::shared_ptr<sf::RenderWindow> window;

	sf::Texture logoTexture;
	sf::Font font;
	sf::Texture aboveLoadingBarTexture;
	sf::Sprite aboveLoadingBarSprite;


	float scaleFactor = 1.0f;
	int boardSize = 4; // Default board size
	const int MAX_BOARD_SIZE = 20; // Maximum allowed board size
	friend class WindowManager;
	friend class Minesweeper3D;
	void displayLogo();
	sf::Sprite loadAboveLoadingBarImage();
	void loadAndDisplayAboveLoadingBarImage();
	void displayMainMenu();
	void displayUI();


};
