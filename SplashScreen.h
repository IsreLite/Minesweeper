#pragma once

#include <SFML/Graphics.hpp>

class SplashScreen {
public:
	SplashScreen();
	//SplashScreen(int width, int height, const std::string& title);

	//void run(sf::RenderWindow& window);
	//void run(sf::RenderWindow& window);
	//void run() {
	//	// Access the window through the window manager
	//	const sf::RenderWindow& window = windowManager.getWindow();
	//	// Use the window as needed
	//	// ...
	//}

	void run(sf::RenderWindow& window);



private:
	//WindowManager& windowManager; // Reference to the window manager
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
