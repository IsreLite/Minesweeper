#include "SplashScreen.h"
#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

SplashScreen::SplashScreen() {
	// Load resources and initialize variables here
	if (!logoTexture.loadFromFile("src/img/logo.png")) {
		std::cerr << "Failed to load logo.png" << std::endl;
		return;
	}

	if (!font.loadFromFile("src/fonts/Minecrafter.Reg.ttf")) {
		std::cerr << "Failed to load font" << std::endl;
		return;
	}

	if (!aboveLoadingBarTexture.loadFromFile("src/img/minesweeper_image.jpeg")) {
		std::cerr << "Failed to load splash_screen.png" << std::endl;
		std::cerr << "Loading a placeholder image instead." << std::endl;
		sf::Image placeholderImage;
		placeholderImage.create(400, 300, sf::Color::Red); // Placeholder image size
		aboveLoadingBarTexture.loadFromImage(placeholderImage);
	}

	sf::Vector2u windowSize = sf::Vector2u(800, 600); // Default window size, adjust as needed
	sf::Vector2u imageSize = aboveLoadingBarTexture.getSize();
	float scaleX = static_cast<float>(windowSize.x) / imageSize.x;
	float scaleY = static_cast<float>(windowSize.y) / imageSize.y;
	scaleFactor = std::min(scaleX * 1.5f, scaleY * 1.5f);

	aboveLoadingBarSprite.setScale(scaleFactor, scaleFactor);
	aboveLoadingBarSprite.setPosition((windowSize.x - aboveLoadingBarSprite.getLocalBounds().width) / 2 + 20, (windowSize.y - aboveLoadingBarSprite.getLocalBounds().height) / 2);
}

void SplashScreen::run(sf::RenderWindow& window) {
	// Display the logo
	//displayLogo(window);

	// Display UI elements
	displayUI(window);
}
void SplashScreen::displayLogo(sf::RenderWindow& window) {
	sf::Sprite logoSprite(logoTexture);
	logoSprite.setPosition(window.getSize().x / 2 - logoTexture.getSize().x / 2, window.getSize().y / 2 - logoTexture.getSize().y / 2);
	window.draw(logoSprite);
	window.display();
	sf::sleep(sf::seconds(2)); // Wait for 2 seconds (adjust as needed)
}

sf::Sprite SplashScreen::loadAboveLoadingBarImage(sf::RenderWindow& window) {
	// Load the image to display above the loading bar
	sf::Texture aboveLoadingBarTexture;
	if (!aboveLoadingBarTexture.loadFromFile("src/img/minesweeper_image.jpeg")) {
		// If loading fails, display a placeholder message
		std::cerr << "Failed to load minesweeper_image.jpeg" << std::endl;
		std::cerr << "Loading a placeholder image instead." << std::endl;
		sf::Image placeholderImage;
		placeholderImage.create(400, 300, sf::Color::Red); // Placeholder image size
		aboveLoadingBarTexture.loadFromImage(placeholderImage);
	}

	sf::Sprite aboveLoadingBarSprite(aboveLoadingBarTexture);

	// Get the size of the window
	sf::Vector2u windowSize = window.getSize();

	// Get the size of the loaded image
	sf::Vector2u imageSize = aboveLoadingBarTexture.getSize();

	// Calculate the scale factor to fit the image into the window
	float scaleX = static_cast<float>(windowSize.x) / imageSize.x;
	float scaleY = static_cast<float>(windowSize.y) / imageSize.y;
	float scaleFactor = std::min(scaleX * 1.5f, scaleY * 1.5f);

	// Set the scale of the sprite
	aboveLoadingBarSprite.setScale(scaleFactor, scaleFactor);

	// Center the sprite in the window
	aboveLoadingBarSprite.setPosition((windowSize.x - aboveLoadingBarSprite.getLocalBounds().width) / 2 + 20, (windowSize.y - aboveLoadingBarSprite.getLocalBounds().height) / 2);

	return aboveLoadingBarSprite;
}

void SplashScreen::loadAndDisplayAboveLoadingBarImage(sf::RenderWindow& window) {
	// Load the image to display above the loading bar
	sf::Texture aboveLoadingBarTexture;
	if (!aboveLoadingBarTexture.loadFromFile("src/img/minesweeper_image.jpeg")) {
		// If loading fails, display a placeholder message
		std::cerr << "Failed to load minesweeper_image.jpeg" << std::endl;
		std::cerr << "Loading a placeholder image instead." << std::endl;
		sf::Image placeholderImage;
		placeholderImage.create(400, 300, sf::Color::Red); // Placeholder image size
		aboveLoadingBarTexture.loadFromImage(placeholderImage);
	}

	sf::Sprite aboveLoadingBarSprite(aboveLoadingBarTexture);

	// Get the size of the window
	sf::Vector2u windowSize = window.getSize();

	// Get the size of the loaded image
	sf::Vector2u imageSize = aboveLoadingBarTexture.getSize();

	// Calculate the scale factor to fit the image into the window
	float scaleX = static_cast<float>(windowSize.x) / imageSize.x;
	float scaleY = static_cast<float>(windowSize.y) / imageSize.y;
	float scaleFactor = std::min(scaleX * 1.5f, scaleY * 1.5f);

	// Set the scale of the sprite
	aboveLoadingBarSprite.setScale(scaleFactor, scaleFactor);

	// Center the sprite in the window
	aboveLoadingBarSprite.setPosition((windowSize.x - aboveLoadingBarSprite.getLocalBounds().width) / 2 + 20, (windowSize.y - aboveLoadingBarSprite.getLocalBounds().height) / 2);

	// Define loading bar properties
	sf::RectangleShape loadingBar(sf::Vector2f(400, 30));
	loadingBar.setPosition(window.getSize().x / 2 - loadingBar.getSize().x / 2, window.getSize().y / 2 + logoTexture.getSize().y / 2 + 60); // Position the loading bar below the loading text
	float cornerRadius = 35.0f;
	loadingBar.setOutlineThickness(2);
	loadingBar.setOutlineColor(sf::Color::Black);
	loadingBar.setFillColor(sf::Color::Transparent);

	// Create a gradient for rainbow colors
	sf::VertexArray gradient(sf::Quads, 4);
	gradient[0].color = sf::Color::Red;
	gradient[1].color = sf::Color::Yellow;
	gradient[2].color = sf::Color::Green;
	gradient[3].color = sf::Color::Blue;

	// Animation variables
	sf::Clock clock; // Declare the clock outside the loop to keep track of time continuously
	float elapsedTime = 0.0f;
	float animationDuration = 3.0f; // Duration of the animation in seconds
	float loadingProgress = 0.0f;

	// Define loading text properties
	sf::Text loadingText("Loading...", font, 30);
	loadingText.setFillColor(sf::Color::White);
	loadingText.setOutlineColor(sf::Color::Black);
	loadingText.setOutlineThickness(2);
	loadingText.setPosition(window.getSize().x / 2 - loadingText.getGlobalBounds().width / 2, window.getSize().y / 2 + logoTexture.getSize().y / 2 + 20); // Position the loading text below the logo

	// Define game text properties
	sf::Text gameText("Minesweeper 3D", font, 70);
	gameText.setFillColor(sf::Color::White);
	gameText.setOutlineColor(sf::Color::Black);
	gameText.setOutlineThickness(2);
	gameText.setPosition(window.getSize().x / 2 - gameText.getGlobalBounds().width / 2, window.getSize().y / 2 + logoTexture.getSize().y / 2 - 350); // Position the game text below the logo


	// Display the sprite, loading bar, and loading text together
	while (clock.getElapsedTime().asSeconds() < animationDuration) {
		// Clear the window
		window.clear();

		// Update the loading progress
		elapsedTime = clock.getElapsedTime().asSeconds();
		loadingProgress = elapsedTime / animationDuration;

		// Draw the sprite, loading bar, and loading text
		window.draw(aboveLoadingBarSprite);

		loadingBar.setSize(sf::Vector2f(400 * loadingProgress, 30));

		gradient[0].position = loadingBar.getPosition();
		gradient[1].position = sf::Vector2f(loadingBar.getPosition().x + loadingBar.getSize().x, loadingBar.getPosition().y);
		gradient[2].position = loadingBar.getPosition() + loadingBar.getSize();
		gradient[3].position = sf::Vector2f(loadingBar.getPosition().x, loadingBar.getPosition().y + loadingBar.getSize().y);

		window.draw(gradient);
		window.draw(loadingBar);
		window.draw(gameText);
		window.draw(loadingText);

		// Display the window
		window.display();
	}

	// Wait for a few seconds before closing
	sf::sleep(sf::seconds(2));
}
void SplashScreen::displayMainMenu(sf::RenderWindow& window) {
	bool exitClicked = false;

	// Define UI elements
	sf::Text newText("New Game", font, 30);
	newText.setFillColor(sf::Color::White);
	newText.setOutlineColor(sf::Color::Black);
	newText.setOutlineThickness(2);
	newText.setPosition(window.getSize().x / 2 - newText.getGlobalBounds().width / 2, window.getSize().y / 2 - 50); // Adjust position as needed

	sf::Text settingsText("Settings", font, 30);
	settingsText.setFillColor(sf::Color::White);
	settingsText.setOutlineColor(sf::Color::Black);
	settingsText.setOutlineThickness(2);
	settingsText.setPosition(window.getSize().x / 2 - settingsText.getGlobalBounds().width / 2, window.getSize().y / 2); // Adjust position as needed

	sf::Text exitText("Exit", font, 30);
	exitText.setFillColor(sf::Color::White);
	exitText.setOutlineColor(sf::Color::Black);
	exitText.setOutlineThickness(2);
	exitText.setPosition(window.getSize().x / 2 - exitText.getGlobalBounds().width / 2, window.getSize().y / 2 + 50); // Adjust position as needed

	while (window.isOpen() && !exitClicked) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
				return; // Exit the method if the window is closed
			}
			else if (event.type == sf::Event::MouseButtonPressed) {
				// Check if the mouse click is within the bounds of the "Exit" text
				sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
				if (exitText.getGlobalBounds().contains(mousePos)) {
					window.close(); // Close the window if "Exit" is clicked
					exitClicked = true; // Set the flag to exit the loop
				}
			}
		}

		// Draw UI elements
		window.clear();
		window.draw(newText);
		window.draw(settingsText);
		window.draw(exitText);
		window.display();
	}
}





void SplashScreen::displayUI(sf::RenderWindow& window) {


	// Load and display the image above the loading bar
	loadAndDisplayAboveLoadingBarImage(window);

	// Display the main menu
	displayMainMenu(window);

}
