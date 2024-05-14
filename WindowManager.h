#pragma once
#include "SplashScreen.h"
#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>

//
//class WindowManager {
//public:
//	WindowManager(int width, int height, const std::string& title) {
//		std::cout << "Created the window: " << title << std::endl;
//
//		sf::ContextSettings settings;
//		settings.antialiasingLevel = 8;
//		window.create(sf::VideoMode(width, height), title, sf::Style::Default, settings);
//
//		// Create and use the SplashScreen instance
//		SplashScreen splashScreen;
//		splashScreen.run(window);
//	}
//
//	sf::RenderWindow& getWindow() {
//		return window;
//	}
//
//private:
//	sf::RenderWindow window;
//
//
//	WindowManager() { // Private constructor to prevent direct object creation
//		window.create(sf::VideoMode(800, 600), "Minesweeper 3D", sf::Style::Default);
//	}
//
//};

class WindowManager {
public:
	WindowManager(int width, int height, const std::string& title) {
		std::cout << "Created the window: " << title << std::endl;
		sf::ContextSettings settings;
		settings.antialiasingLevel = 8;
		window = std::make_shared<sf::RenderWindow>(sf::VideoMode(width, height), title, sf::Style::Default, settings);
	}

	std::shared_ptr<sf::RenderWindow> getWindow() {
		return window;
	}

private:
	std::shared_ptr<sf::RenderWindow> window;
};

