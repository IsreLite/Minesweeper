#include "Minesweeper3D.h"


Minesweeper3D::Minesweeper3D() {
	// Initialize the window
	app.create(sf::VideoMode(800, 600), "Minesweeper 3D");

	// Set the initial view of the window
	sf::FloatRect initialView(0, 0, 800, 600);
	app.setView(sf::View(initialView));

	// Initialize the board
	board.resize(BOARD_SIZE, std::vector<int>(BOARD_SIZE, 0)); // Assuming no mines initially

	// Initialize 3D cell shapes
	cellShape.setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));
	cellShape.setFillColor(sf::Color::White);
	cellShape.setOutlineThickness(1.0f);
	cellShape.setOutlineColor(sf::Color::Black);

	// Calculate the initial grid starting position
	std::tie(startX, startY) = getGridStartPosition();
}

void Minesweeper3D::handleEvents() {

	while (app.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			app.close();
		}
		else if (event.type == sf::Event::Resized)
		{
			// Window has been resized, recalculate the grid parameters
			float startX, startY;
			std::tie(startX, startY) = getGridStartPosition();
			// update the view to the new size of the window
			sf::FloatRect visibleArea(0, 0, static_cast<float>(event.size.width), static_cast<float>(event.size.height));
			app.setView(sf::View(visibleArea));
		}
		else if (event.type == sf::Event::MouseButtonPressed) {
			sf::Vector2i pos = sf::Mouse::getPosition(app);

			// Calculate the cell coordinates based on the mouse position
			int x = static_cast<int>((pos.x - startX) / CELL_SIZE);
			int y = static_cast<int>((pos.y - startY) / CELL_SIZE);

			if (event.mouseButton.button == sf::Mouse::Left) {
				minesweeperBoard.revealField(x, y);
				//update(); // Update the game state after toggling a flag
			}
			else if (event.mouseButton.button == sf::Mouse::Right) {
				minesweeperBoard.toggleFlag(x, y);
				//update(); // Update the game state after toggling a flag
			}
			update(); // Update the game state after toggling a flag
		}
	}

}

void Minesweeper3D::update() {
	// Update game state here if needed
// Call the getGameState function to update the game state
	GameState gameState = minesweeperBoard.getGameState();

	// Check if the game has finished
	if (gameState != GameState::RUNNING) {
		// If the game has finished, render the scene immediately
		render();
	}
}

void Minesweeper3D::drawBoard()
{
	// Get the grid starting position
	std::tie(startX, startY) = getGridStartPosition();
	// Draw the 3D board
	for (int x = 0; x < BOARD_SIZE; ++x)
	{
		for (int y = 0; y < BOARD_SIZE; ++y)
		{
			float xPos = startX + x * CELL_SIZE;
			float yPos = startY + y * CELL_SIZE;
			float zPos = 0.0f; // Assuming all cells are on the same plane
			sf::Text mineCountText;

			this->cellShape.setPosition(xPos, yPos);
			this->cellShape.move(0, zPos); // Adjust for the z position

			if (this->minesweeperBoard.board[x][y]->hasMine)
			{
				this->cellShape.setFillColor(sf::Color::Red); // Mine
				app.draw(this->cellShape);
			}
			else if (this->minesweeperBoard.board[x][y]->isRevealed)
			{
				//this->cellShape.setFillColor(sf::Color::Magenta); // Revealed mine
				int mineCount = minesweeperBoard.countMines(x, y);
				//std::cout << "Counted: " + mineCount << std::endl;

				if (mineCount == -1)
				{
					// The cell is not revealed or the coordinates are not valid
					cellShape.setFillColor(sf::Color::White); // Unrevealed cell
					app.draw(this->cellShape);
				}
				else if (mineCount == 0)
				{
					cellShape.setFillColor(sf::Color::Green); // Revealed cell with no adjacent mines
					app.draw(this->cellShape);
				}
				else
				{
					// Display the number of adjacent mines
					cellShape.setFillColor(sf::Color::Green); // Revealed cell with number of adjacent mines
					app.draw(this->cellShape);
					mineCountText.setString(std::to_string(mineCount));
					mineCountText.setFont(font);
					mineCountText.setCharacterSize(30);
					mineCountText.setFillColor(sf::Color::Blue);
					mineCountText.setPosition((xPos + x - 1) + CELL_SIZE / 4, (yPos - y + 2) + CELL_SIZE / 4); // Position the text
					//mineCountText.setPosition(xPos + CELL_SIZE / 2, yPos - (CELL_SIZE));
					app.draw(mineCountText);

				}
			}
			else if (this->minesweeperBoard.board[x][y]->hasFlag)
			{
				this->cellShape.setFillColor(sf::Color::Yellow); // Flag
				app.draw(this->cellShape);
			}
			else
			{
				this->cellShape.setFillColor(sf::Color::White); // Unrevealed cell
				app.draw(this->cellShape);
			}
		}
	}
	// Display the total number of mines
	int totalMines = minesweeperBoard.getMineCount();
	sf::Text mineCountText("Mines: " + std::to_string(totalMines), font, 20);
	mineCountText.setFillColor(sf::Color::Blue); // Set the font color to blue
	mineCountText.setPosition(10, 10); // Position the text relative to the grid starting position
	app.draw(mineCountText);
}

void Minesweeper3D::render() {
	this->app.clear(sf::Color::Black);

	if (!font.loadFromFile("src/fonts/Minecrafter.Reg.ttf")) {
		std::cerr << "Failed to load font" << std::endl;
		return;
	}
	// Get the current window size
	sf::Vector2u windowSize = this->app.getSize();

	if (windowSize != currentWindowSize) {
		// Window size has changed, recalculate the grid parameters
		this->currentWindowSize = windowSize;
		this->drawBoard();
	}
	else {
		// Draw the 3D board
		this->drawBoard();
	}

	// Display the updated window
	this->app.display();


}