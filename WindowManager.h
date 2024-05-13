#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>


//class WindowManager {
//public:
//	//WindowManager(int width, int height, const std::string& title);
//	WindowManager() : window(sf::VideoMode(800, 600), "Default Window"), isRunning(true) {
//		std::cout << "Created the window" << std::endl;
//	}
//
//	WindowManager(sf::RenderWindow& window);
//
//	WindowManager(int width, int height, const std::string& title);
//
//	~WindowManager();
//
//	void run();
//	sf::RenderWindow& createWindow(int width, int height, const std::string& title);
//
//	sf::RenderWindow& createWindow();
//
//	sf::RenderWindow& getWindow();
//
//private:
//	sf::RenderWindow window;
//	bool isRunning;
//
//
//};
//
//WindowManager::~WindowManager() {
//	// Clean up resources if needed
//}
//
//WindowManager::WindowManager(int width, int height, const std::string& title)
//{
//	std::cout << " Created the window " << std::endl;
//	//window.create(sf::VideoMode(width, height), title);
//}
//
//// //WindowManager::WindowManager(int width, int height, const std::string& title)
////	: window(sf::VideoMode(width, height), title), isRunning(true) {
////	std::cout << " Created the window " << std::endl;
////	//window.create(sf::VideoMode(width, height), title);
////}
//
////WindowManager::WindowManager(sf::RenderWindow& window)
////	: isRunning(true) {
////}
//
//sf::RenderWindow& WindowManager::getWindow() {
//	return window;
//}
//
//void WindowManager::run() {
//	while (isRunning) {
//		sf::Event event;
//		while (window.pollEvent(event)) {
//			if (event.type == sf::Event::Closed) {
//				isRunning = false;
//			}
//			// Handle other events if needed
//		}
//
//		// Update and render the window
//		// ...
//
//		window.display();
//	}
//}
//
//
//
//sf::RenderWindow& WindowManager::createWindow(int width, int height, const std::string& title) {
//	window.create(sf::VideoMode(width, height), title);
//	return window;
//}
//
//sf::RenderWindow& WindowManager::createWindow() {
//	//window.create(sf::VideoMode(width, height), title);
//	window.create(sf::VideoMode(600, 600), "title");
//	return window;
//}


class WindowManager {
public:
	WindowManager(int width, int height, const std::string& title) {
		window.create(sf::VideoMode(width, height), title);
		std::cout << "Created the window: " << title << std::endl;
	}

	sf::RenderWindow& getWindow() {
		return window;
	}

private:
	WindowManager(); // Private constructor to prevent direct object creation
	sf::RenderWindow window;
	static WindowManager& getInstance(); // Static method to get the instance
	friend class Minesweeper3D;
};

WindowManager::WindowManager() {
	window.create(sf::VideoMode(800, 600), "Minesweeper 3D");

}

WindowManager& WindowManager::getInstance() {
	static WindowManager instance; // Create the single instance
	return instance;
}