#pragma once

#include <SFML/Graphics.hpp>

class SplashScreen {
public:
	SplashScreen();

	void run(sf::RenderWindow& window);

private:
	sf::Texture logoTexture;
	sf::Font font;
	sf::Texture aboveLoadingBarTexture;
	sf::Sprite aboveLoadingBarSprite;
	float scaleFactor = 1.0f;
	int boardSize = 4; // Default board size
	const int MAX_BOARD_SIZE = 20; // Maximum allowed board size

	void displayLogo(sf::RenderWindow& window);
	sf::Sprite loadAboveLoadingBarImage(sf::RenderWindow& window);
	void loadAndDisplayAboveLoadingBarImage(sf::RenderWindow& window);
	void displayMainMenu(sf::RenderWindow& window);
	void displayUI(sf::RenderWindow& window);
};
