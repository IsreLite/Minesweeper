#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

const int BOARD_SIZE = 10; // Assuming a square board
const float CELL_SIZE = 50.0f; // Size of each cell in pixels

class Minesweeper3D
{
public:
	Minesweeper3D() {
		// Initialize the window
		window.create(sf::VideoMode(800, 600), "Minesweeper 3D");

		// Initialize the board
		board.resize(BOARD_SIZE, std::vector<int>(BOARD_SIZE, 0)); // Assuming no mines initially

		// Initialize 3D cell shapes
		cellShape.setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));
		cellShape.setFillColor(sf::Color::White);
		cellShape.setOutlineThickness(1.0f);
		cellShape.setOutlineColor(sf::Color::Black);
	}

	void run() {
		while (window.isOpen()) {
			handleEvents();
			update();
			render();
		}
	}

private:
	sf::RenderWindow window;
	std::vector<std::vector<int>> board; // Represents the state of the Minesweeper board
	sf::RectangleShape cellShape; // Shape for each cell on the board

	void handleEvents() {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
	}

	void update() {
		// Update game state here if needed
	}

	void render() {
		window.clear(sf::Color::Black);

		// Draw the 3D board
		for (int x = 0; x < BOARD_SIZE; ++x) {
			for (int y = 0; y < BOARD_SIZE; ++y) {
				float xPos = x * CELL_SIZE;
				float yPos = y * CELL_SIZE;
				float zPos = 0.0f; // Assuming all cells are on the same plane

				cellShape.setPosition(xPos, yPos);
				cellShape.move(0, zPos); // Adjust for the z position
				window.draw(cellShape);
			}
		}

		window.display();
	}
};

