#include "WindowManager.h"

WindowManager::WindowManager(int width, int height, const std::string& title) {
	std::cout << "Created the window: " << title << std::endl;
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	window = std::make_shared<sf::RenderWindow>(sf::VideoMode(width, height), title, sf::Style::Default, settings);
}

std::shared_ptr<sf::RenderWindow> WindowManager::getWindow() {
	return window;
}
