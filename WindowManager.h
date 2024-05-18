#pragma once
#include "SplashScreen.h"
#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>

class WindowManager {
public:
	WindowManager(int width, int height, const std::string& title);

	std::shared_ptr<sf::RenderWindow> getWindow();


private:
	std::shared_ptr<sf::RenderWindow> window;
	sf::Vector2u currentWindowSize;
	float startX, startY;

};

