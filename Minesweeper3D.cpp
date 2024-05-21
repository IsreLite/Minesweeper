/*
 * Copyright 2024 Israel Owolabi
 *
 * Licensed under the MIT License.
 * See LICENSE file in the project root for full license information.
 */


#include "Minesweeper3D.h"
#include <iostream>

Minesweeper3D::Minesweeper3D(std::shared_ptr<sf::RenderWindow> app, int boardsize, GameMode gamemode)
{

	this->BOARD_SIZE = boardsize;
	this->gameMode = gamemode;
	this->app = app;

	updateMousePos(); // Update mouse position on initialization
	updateWindowSize();

	minesweeperBoard = MinesweeperBoard(BOARD_SIZE, BOARD_SIZE, gameMode);

	// Set the initial view of the window
	sf::FloatRect initialView(0, 0, windowWidth, windowHeight);
	app->setView(sf::View(initialView));

	// Initialize the board
	board.resize(BOARD_SIZE, std::vector<int>(BOARD_SIZE, 0)); // Assuming no mines initially

	// Initialize 3D cell shapes
	cellShape.setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));
	cellShape.setFillColor(sf::Color::White);
	cellShape.setOutlineThickness(1.0f);
	cellShape.setOutlineColor(sf::Color::Black);



	// Load textures
	if (!flaggedTexture.loadFromFile("src/img/flag.gif")) {
		std::cerr << "Failed to load flagged texture" << std::endl;
	}
	if (!revealedTexture.loadFromFile("src/img/rev.jpg")) {
		std::cerr << "Failed to load revealed texture" << std::endl;
	}
	if (!unrevealedTexture.loadFromFile("src/img/unrev.jpeg")) {
		std::cerr << "Failed to load unrevealed texture" << std::endl;
	}
	if (!bombTexture.loadFromFile("src/img/bmb.jpg")) {
		std::cerr << "Failed to load unrevealed texture" << std::endl;
	}
	// Load sound effects
	if (!explosionBuffer.loadFromFile("src/wav/explosion.wav")) {
		std::cerr << "Failed to load explosion sound" << std::endl;
	}
	if (!levelUpBuffer.loadFromFile("src/wav/levelUp.wav")) {
		std::cerr << "Failed to load levelUp sound" << std::endl;
	}
	if (!gameOverBuffer.loadFromFile("src/wav/gameover.wav")) {
		std::cerr << "Failed to load gameover sound" << std::endl;
	}
	if (!buttonBuffer.loadFromFile("src/wav/click.wav")) {
		std::cerr << "Failed to load click sound" << std::endl;
	}
	// Load the mute button image texture
	if (!muteButtonTexture.loadFromFile("src/img/unmute.png")) {
		std::cerr << "Failed to load mute button texture" << std::endl;
	}
	if (!unmuteButtonTexture.loadFromFile("src/img/mute.png")) {
		std::cerr << "Failed to load mute button texture" << std::endl;
	}

	gameOverSound.setBuffer(gameOverBuffer);
	levelUpSound.setBuffer(levelUpBuffer);
	explosionSound.setBuffer(explosionBuffer);
	buttonSound.setBuffer(buttonBuffer);

	// Calculate the initial grid starting position
	std::tie(startX, startY) = getGridStartPosition();
	gameClock.restart();
}

// Function to update the mouse position internally
void Minesweeper3D::updateMousePos() {
	mousePos = sf::Mouse::getPosition(*app);
	mousePosX = static_cast<float>(mousePos.x);
	mousePosY = static_cast<float>(mousePos.y);
}
sf::Vector2i Minesweeper3D::getMousePos() const {
	return mousePos;
}
void Minesweeper3D::updateWindowSize() {
	windowSize = app->getSize();
	windowWidth = static_cast<float>(windowSize.x);
	windowHeight = static_cast<float>(windowSize.y);
}

std::pair<float, float> Minesweeper3D::getGridStartPosition()
{
	updateWindowSize();
	// Get the size of the window
	sf::Vector2u wSize = app->getSize();

	// Check if the window size has changed
	if (wSize != currentWindowSize)
	{
		const int MIN_BOARD_SIZE = 3;
		const int MAX_BOARD_SIZE = 20;


		// Window size has changed, recalculate the grid parameters
		currentWindowSize = wSize;

		// Calculate the maximum number of cells that can fit in the window
		int maxCellsHorizontal = static_cast<float>(windowSize.x / CELL_SIZE);
		int maxCellsVertical = static_cast<float>(windowSize.y / CELL_SIZE);


		// Adjust BOARD_SIZE based on window size (example: increase by 1 cell for every 100 pixels over 800)
		//CELL_SIZE = std::min(windowWidth, windowHeight) / 8;
		CELL_SIZE = std::max(MIN_BOARD_SIZE, std::min(MAX_BOARD_SIZE, std::min(maxCellsHorizontal, maxCellsVertical)));


		// Recalculate the CELL_SIZE based on the new BOARD_SIZE and window size
		if (BOARD_SIZE <= 8)
		{
			// For BOARD_SIZE <= 8, use a constant cell size
			CELL_SIZE = 70.0f;
		}
		else
		{
			// For BOARD_SIZE > 8, adjust the cell size based on the window size
			CELL_SIZE = std::min(windowSize.x, windowSize.y) / BOARD_SIZE;
		}

		// Calculate the starting position of the grid
		float gridWidth = BOARD_SIZE * CELL_SIZE;
		float gridHeight = BOARD_SIZE * CELL_SIZE;
		startX = (currentWindowSize.x - gridWidth) / 2;
		startY = (currentWindowSize.y - gridHeight) / 2;

	}

	return std::make_pair(startX, startY);
}
void Minesweeper3D::handleEvents() {

	while (app->pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			app->close();

		}
		else if (event.type == sf::Event::Resized)
		{
			sf::Vector2u newSize(event.size.width, event.size.height);
			if (newSize.x < MIN_WINDOW_WIDTH || newSize.y < MIN_WINDOW_HEIGHT) {
				newSize.x = std::max(newSize.x, MIN_WINDOW_WIDTH);
				newSize.y = std::max(newSize.y, MIN_WINDOW_HEIGHT);
				app->setSize(newSize);
			}
			windowWidth = static_cast<float>(newSize.x);
			windowHeight = static_cast<float>(newSize.y);
			drawBoard();
			updateWindowSize();
			// Window has been resized, recalculate the grid parameters
			float startX, startY;
			std::tie(startX, startY) = getGridStartPosition();
			// update the view to the new size of the window
			sf::FloatRect visibleArea(0, 0, static_cast<float>(event.size.width), static_cast<float>(event.size.height));
			app->setView(sf::View(visibleArea));
		}
		else if (event.type == sf::Event::MouseButtonPressed) {
			sf::Vector2i pos = sf::Mouse::getPosition(*app);

			// Calculate the cell coordinates based on the mouse position
			int x = static_cast<int>((pos.x - startX) / CELL_SIZE);
			int y = static_cast<int>((pos.y - startY) / CELL_SIZE);

			// Check if click is within grid bounds
			if (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE) {
				// Play click sound
				buttonSound.play();

				if (event.mouseButton.button == sf::Mouse::Left) {
					minesweeperBoard.revealField(x, y);
					update();
				}
				else if (event.mouseButton.button == sf::Mouse::Right) {
					minesweeperBoard.toggleFlag(x, y);
					//update(); // Update the game state after toggling a flag
				}
			}


			else
			{
				handleGameButtons();
			}
		}
	}

}
const void Minesweeper3D::initializeButton(sf::Text& text, sf::RectangleShape& button, const sf::String& label,
	const sf::Color& fillColor, const sf::Vector2f& buttonPosition, const sf::Vector2f& textOffset) const {

	// Initialize the exit button
	button.setSize(sf::Vector2f(100, 50));
	button.setPosition(buttonPosition); // Set position as per your requirement
	button.setOutlineColor(sf::Color::Black);
	button.setOutlineThickness(2.0f);

	// Initialize the exit text
	text.setFont(font);
	text.setString(label);
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::White);
	text.setPosition(button.getPosition() + textOffset);

	// Set the button's fill color
	button.setFillColor(fillColor);
}
void Minesweeper3D::initInGameUtils() {
	updateWindowSize();
	// Initialize the exit button
	sf::Color buttonColor = sf::Color::Red;
	sf::Vector2f buttonPosition(windowWidth - 120.0f, 10.0f);
	sf::Vector2f textOffset(20, 10);
	initializeButton(exitText, exitButton, "Exit", buttonColor, buttonPosition, textOffset);

	// Initialize the pause button
	buttonColor = sf::Color::Yellow;
	buttonPosition = { 20, 10 };
	initializeButton(pauseText, pauseButton, "Pause", buttonColor, buttonPosition, textOffset);
	pauseText.setPosition(pauseButton.getPosition().x + 15, pauseButton.getPosition().y + 10);
	pauseText.setFillColor(sf::Color::Black);
	isGamePaused ?
		(pauseText.setString("Resume"), pauseButton.setSize(sf::Vector2f(130, 50))) :
		(pauseText.setString("Pause"), pauseButton.setSize(sf::Vector2f(110, 50)));

	// Initialize the home button
	buttonColor = sf::Color::Blue;
	buttonPosition = { 20, windowHeight - 70.0f };
	initializeButton(backToHomeText, backToHomeButton, "Home", buttonColor, buttonPosition, textOffset);
	backToHomeText.setPosition(backToHomeButton.getPosition().x + 15, backToHomeButton.getPosition().y + 10);

	// Initialize the mute button
	muteButton.setPosition(windowWidth - 120.0f, windowHeight - 110.0f);
	muteButton.setSize(sf::Vector2f(100, 100));
	isMuted ?
		// Set the texture of the mute button
		(muteButton.setTexture(&unmuteButtonTexture)) :
		(muteButton.setTexture(&muteButtonTexture));

	// Initialize the timer
	sf::Text timerText;
	int minutes = static_cast<int>(elapsedTime.asSeconds()) / 60;
	int seconds = static_cast<int>(elapsedTime.asSeconds()) % 60;
	timerText.setFont(font);
	timerText.setCharacterSize(24);
	timerText.setFillColor(sf::Color::White);
	timerText.setPosition((windowWidth / 2.2f) - timerText.getGlobalBounds().width, 10);
	timerText.setString("Time: " + std::to_string(minutes) + ":" + std::to_string(seconds));

	//Display buttons and pause button when game is running
	this->app->draw(timerText);
	if (!isGameWin && !isGameLost) {
		app->draw(pauseButton);
		app->draw(pauseText);
	}
	app->draw(muteButton);
	app->draw(exitButton);
	app->draw(exitText);
	app->draw(backToHomeButton);
	app->draw(backToHomeText);

	//Start clock countdown 
	updateTimer();

}
void Minesweeper3D::handleGameButtons() {
	updateMousePos();
	if (event.type == sf::Event::MouseButtonPressed) {
		if (exitButton.getGlobalBounds().contains(mousePosX, mousePosY)) {
			app->close();
		}
		else if (pauseButton.getGlobalBounds().contains(mousePosX, mousePosY)) {
			isGamePaused = !isGamePaused;

			if (isGamePaused) {
				// Game is paused, record the pause time
				pauseClock.restart();
			}
			else {
				// Game is resumed, subtract pause time from elapsed time
				pauseTime += pauseClock.getElapsedTime();
			}

		}
		else if (muteButton.getGlobalBounds().contains(mousePosX, mousePosY)) {
			// Toggle mute state
			isMuted = !isMuted;

			// Optionally, you can mute/unmute the sound here
			// For example:
			buttonSound.setVolume(isMuted ? 0.0f : 100.0f);
			explosionSound.setVolume(isMuted ? 0.0f : 100.0f);
			levelUpSound.setVolume(isMuted ? 0.0f : 100.0f);
			gameOverSound.setVolume(isMuted ? 0.0f : 100.0f);

			// Update the mute button text
		}
		else if (backToHomeText.getGlobalBounds().contains(mousePosX, mousePosY)) {
			// Reset the game state and any necessary variables
			// Create a new instance of the SplashScreen class and pass the window shared pointer
			SplashScreen splashScreen(app);
			splashScreen.displayMainMenu();
			resetGame();

		}
	}
}
void Minesweeper3D::updateTimer() {
	if (!isGamePaused && !isGameWin && !isGameLost) {
		// Update the elapsed time if the game is not paused or finished
		elapsedTime = gameClock.getElapsedTime() - pauseTime;;
	}
}
void Minesweeper3D::update() {
	// Update game state here if needed
	// Call the getGameState function to update the game state
	GameState gameState = minesweeperBoard.getGameState();

	if (!isGamePaused && !isGameLost || !isGamePaused && !isGameWin) {
		// Update the elapsed time if the game is not paused or finished
		elapsedTime = gameClock.getElapsedTime();
	}
	// Check if the game has finished
	if (gameState != GameState::RUNNING) {
		if (gameState == GameState::FINISHED_WIN) {
			// Play victory sound
			levelUpSound.play();
			isGameWin = true;
			// Stop the game clock
			gameClock.restart();
		}
		else if (gameState == GameState::FINISHED_LOSS) {
			// Play victory sound
			// If a bomb is clicked, reveal all cells
			for (int i = 0; i < BOARD_SIZE; ++i) {
				for (int j = 0; j < BOARD_SIZE; ++j) {
					minesweeperBoard.board[i][j]->isRevealed = true;
				}
			}
			render();

			isGameLost = true;
			explosionSound.play();
			sf::sleep(sf::milliseconds(300));
			gameOverSound.play();
		}
	}
	// Check if the game has finished
	if (gameState != GameState::RUNNING) {
		// If the game has finished, render the scene immediately
		render();
	}
}
void Minesweeper3D::displayOverlay(int scenario) {
	// Draw a semi-transparent overlay or message
	sf::RectangleShape overlay(sf::Vector2f(windowWidth, windowHeight));
	overlay.setFillColor(sf::Color(0, 0, 0, 128)); // Semi-transparent black

	sf::Text overlayText("", font, 48);
	overlayText.setFillColor(sf::Color::White);

	// Set the overlay text and position based on the scenario
	switch (scenario) {
	case 1:
		overlayText.setString("Game Paused");
		break;
	case 2:
		overlayText.setString("Game Over");
		break;
	case 3:
		overlayText.setString("You've Won!");
		break;
	default:
		// Invalid scenario, do nothing
		return;
	}

	// Position the text in the center of the window
	overlayText.setPosition(windowWidth / 2.0f - overlayText.getGlobalBounds().width / 2.0f,
		windowHeight / 2.0f - overlayText.getGlobalBounds().height / 2.0f);

	// Draw the overlay and text
	app->draw(overlay);
	app->draw(overlayText);
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
			float xPos = startX + x * this->CELL_SIZE;
			float yPos = startY + y * this->CELL_SIZE;
			float zPos = 0.0f; // Assuming all cells are on the same plane
			sf::Text mineCountText;

			this->cellShape.setPosition(xPos, yPos);
			this->cellShape.move(0, zPos); // Adjust for the z position

			// Set cell position
			this->cellShape.setSize(sf::Vector2f(this->CELL_SIZE, this->CELL_SIZE)); // Update cell size
			this->cellShape.setPosition(xPos, yPos);
			this->cellShape.move(0, zPos); // Adjust for the z position

			// Determine which texture to use based on cell state
			sf::Texture* textureToUse = nullptr;

			if (minesweeperBoard.board[x][y]->isRevealed && minesweeperBoard.board[x][y]->hasMine) {
				textureToUse = &bombTexture;
				this->cellShape.setTexture(textureToUse);

				sf::sleep(sf::milliseconds(50));
				resetGame();
			}
			else if (minesweeperBoard.board[x][y]->isRevealed) {
				int mineCount = minesweeperBoard.countMines(x, y);
				// Determine color based on mineCount
				sf::Color textColor;
				if (mineCount == 1) {
					textColor = sf::Color::Blue;
				}
				else if (mineCount == 2) {
					textColor = sf::Color::Green;
				}
				else if (mineCount == 3) {
					textColor = sf::Color::Red;
				}

				if (mineCount > 0) { // Only display the count if it's greater than 0
					mineCountText.setString(std::to_string(mineCount));
					mineCountText.setFont(font);
					mineCountText.setCharacterSize(30);
					mineCountText.setFillColor(textColor);
					// Center the text within the cell
					float yOffset = -0.09f * this->CELL_SIZE; // 5% upward shift
					mineCountText.setPosition(xPos + (this->CELL_SIZE / 2) - (mineCountText.getGlobalBounds().width / 2),
						yPos + (this->CELL_SIZE / 2) - (mineCountText.getGlobalBounds().height / 2) + yOffset);
				}


				// Draw the cell shape
				textureToUse = &revealedTexture;
				this->cellShape.setTexture(textureToUse);
			}
			else if (minesweeperBoard.board[x][y]->hasFlag) {
				textureToUse = &flaggedTexture;
				this->cellShape.setTexture(textureToUse);
			}
			else {
				textureToUse = &unrevealedTexture;
				this->cellShape.setTexture(textureToUse);
			}

			//Apply the texture to the cell shape
			app->draw(cellShape);
			app->draw(mineCountText);
		}
	}
	//}
	//// Display the total number of mines
	//int totalMines = minesweeperBoard.getMineCount();
	//sf::Text mineCountText("Mines: " + std::to_string(totalMines), font, 20);
	//mineCountText.setFillColor(sf::Color::Blue); // Set the font color to blue
	//mineCountText.setPosition(10, 10); // Position the text relative to the grid starting position
	//app->draw(mineCountText);
}
void Minesweeper3D::render() {
	app->clear(sf::Color::Black);

	if (!font.loadFromFile("src/fonts/Minecrafter.Reg.ttf")) {
		std::cerr << "Failed to load font" << std::endl;
		return;
	}
	// Get the current window size
	sf::Vector2u windowSize = app->getSize();

	if (windowSize != currentWindowSize) {
		// Window size has changed, recalculate the grid parameters
		updateWindowSize();
		this->currentWindowSize = windowSize;
		this->drawBoard();
	}
	else if (isGamePaused) {
		// Draw a semi-transparent overlay or message
		sf::sleep(sf::milliseconds(300));
		displayOverlay(1);
	}
	else if (isGameLost) {
		sf::sleep(sf::milliseconds(2000));
		displayOverlay(2);
	}
	else if (isGameWin) {
		displayOverlay(3);
	}

	else {
		// Draw the 3D board
		this->drawBoard();
	}

	// Display the updated window
	initInGameUtils();
	app->display();


}
void Minesweeper3D::resetGame() {
	// Reset the game board
	this->board.clear();
	//delete& board;
	// Reset player score
	//playerScore = 0;

	// Reset game timer
	pauseClock.restart();

	// Reset any other game-related variables
	// ...
}
