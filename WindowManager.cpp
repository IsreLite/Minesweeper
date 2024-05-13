#include "WindowManager.h"


//WindowManager::WindowManager(sf::RenderWindow& window)
//	: window(window), isRunning(true) {
//}


//WindowManager::WindowManager(int width, int height, const std::string& title)
//	: window(sf::VideoMode(width, height), title), isRunning(true) {
//}
//
//WindowManager::~WindowManager() {
//	// Clean up resources if needed
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
//sf::RenderWindow& WindowManager::getWindow() {
//	return window;
//}
//
//
////const sf::RenderWindow& WindowManager::getWindow() const {
////	return window;
////}
////
////const sf::RenderWindow& WindowManager::createWindow(int width, int height, const std::string& title) {
////	window.create(sf::VideoMode(width, height), title);
////	return window;
////}
////const sf::RenderWindow& WindowManager::createWindow() {
////	//window.create(sf::VideoMode(width, height), title);
////	window.create(sf::VideoMode(600, 600), "title");
////	return window;
////}
