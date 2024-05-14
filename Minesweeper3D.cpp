#include "Minesweeper3D.h"


Minesweeper3D::Minesweeper3D(std::shared_ptr<sf::RenderWindow> app, int boardsize, GameMode gamemode) {

	this->BOARD_SIZE = boardsize;
	this->gameMode = gamemode;
	this->app = app;
	minesweeperBoard = MinesweeperBoard(BOARD_SIZE, BOARD_SIZE, gameMode);

	// Initialize the window
	app->create(sf::VideoMode(800, 600), "Minesweeper 3D");

	// Set the initial view of the window
	sf::FloatRect initialView(0, 0, 800, 600);
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
	if (!revealedTexture.loadFromFile("src/img/flag.gif")) {
		std::cerr << "Failed to load revealed texture" << std::endl;
	}
	if (!unrevealedTexture.loadFromFile("src/img/flag.gif")) {
		std::cerr << "Failed to load unrevealed texture" << std::endl;
	}
	if (!bombTexture.loadFromFile("src/img/flag.gif")) {
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

	//initialize(BOARD_SIZE, gameMode); // Default parameters
}

//Minesweeper3D::Minesweeper3D(int boardsize, GameMode gamemode) {
//	// copy the data from the provided instance
//	this->BOARD_SIZE = boardsize;
//	this->gameMode = gamemode;
//
//	// start the game loop
//	//initialize(boardsize, gamemode); // custom parameters
//	run();
//}

void Minesweeper3D::handleEvents() {

	while (app->pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			app->close();
		}
		else if (event.type == sf::Event::Resized)
		{
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

					// Update the game state after toggling a flag
					//		if (minesweeperBoard.board[x][y]->hasMine) {
			//			// Play  sound
			///*			explosionSound.setBuffer(explosionBuffer);
			//			explosionSound.play();*/
			//			gameOverSound.play();

			//			// If a bomb is clicked, reveal all cells
			//			for (int i = 0; i < BOARD_SIZE; ++i) {
			//				for (int j = 0; j < BOARD_SIZE; ++j) {
			//					minesweeperBoard.board[i][j]->isRevealed = true;
			//				}
			//			}
			//			update(); // Update the game state after toggling a flag

			//		}
			//		else {
			//			minesweeperBoard.revealField(x, y);
			//			update(); // Update the game state after toggling a flag
			//		}
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

			//updateTimer();
		}
	}

}
void Minesweeper3D::initInGameUtils() {
	// Initialize the exit button
	exitButton.setSize(sf::Vector2f(100, 50));
	exitButton.setPosition(static_cast<float>(currentWindowSize.x) - 120.0f, 10.0f);
	exitButton.setFillColor(sf::Color::Red);
	exitButton.setOutlineColor(sf::Color::Black);
	exitButton.setOutlineThickness(2.0f);

	// Initialize the exit text
	exitText.setFont(font);
	exitText.setString("Exit");
	exitText.setCharacterSize(24);
	exitText.setFillColor(sf::Color::White);
	exitText.setPosition(exitButton.getPosition().x + 20, exitButton.getPosition().y + 10);

	pauseButton.setSize(sf::Vector2f(100, 50));
	pauseButton.setPosition(20, 10);
	pauseButton.setFillColor(sf::Color::Yellow);
	pauseButton.setOutlineColor(sf::Color::Black);
	pauseButton.setOutlineThickness(2.0f);
	pauseText.setFont(font);
	isGamePaused ?
		(pauseText.setString("Resume"), pauseButton.setSize(sf::Vector2f(130, 50))) :
		(pauseText.setString("Pause"), pauseButton.setSize(sf::Vector2f(110, 50)));

	pauseText.setCharacterSize(24);
	pauseText.setFillColor(sf::Color::Black);
	pauseText.setPosition(pauseButton.getPosition().x + 15, pauseButton.getPosition().y + 10);

	//muteButton.setPosition(static_cast<float>(currentWindowSize.x) - 570.0f, static_cast<float>(currentWindowSize.y) - 500.0f);
	muteButton.setPosition(static_cast<float>(currentWindowSize.x) - 120, static_cast<float>(currentWindowSize.y) - 120.0f);
	muteButton.setSize(sf::Vector2f(100, 100));
	//muteButton.setFillColor(sf::Color::Transparent);
	muteText.setFont(font);
	muteText.setFillColor(sf::Color::White);
	muteText.setCharacterSize(24);

	/*	isMuted ?
			(muteText.setString("Unmute"), muteButton.setSize(sf::Vector2f(140, 50))) :
			(muteText.setString("Mute"), muteButton.setSize(sf::Vector2f(110, 50)));*/
	isMuted ?
		// Set the texture of the mute button
		(muteButton.setTexture(&unmuteButtonTexture)) :
		(muteButton.setTexture(&muteButtonTexture));
	muteText.setPosition(muteButton.getPosition().x + 15, muteButton.getPosition().y + 10);

	// In the render function
	sf::Text timerText;
	timerText.setFont(font);
	timerText.setCharacterSize(24);
	timerText.setFillColor(sf::Color::White);
	timerText.setPosition(static_cast<float>(currentWindowSize.x / 2.2f) - timerText.getGlobalBounds().width, 10);


	int minutes = static_cast<int>(elapsedTime.asSeconds()) / 60;
	int seconds = static_cast<int>(elapsedTime.asSeconds()) % 60;
	timerText.setString("Time: " + std::to_string(minutes) + ":" + std::to_string(seconds));

	this->app->draw(timerText);
	//Display pause button when game is running
	if (!isGameWin && !isGameLoss) {
		app->draw(pauseButton);
		app->draw(pauseText);
	}
	app->draw(muteButton);
	app->draw(muteText);
	app->draw(exitButton);
	app->draw(exitText);

	//Start clock countdown 
	updateTimer();

}

void Minesweeper3D::handleGameButtons() {
	if (event.type == sf::Event::MouseButtonPressed) {
		sf::Vector2i mousePos = sf::Mouse::getPosition(*app);
		if (exitButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
			app->close();
		}

		if (pauseButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
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

		if (muteButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
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

	}
}
void Minesweeper3D::updateTimer() {
	if (!isGamePaused && !isGameWin && !isGameLoss) {
		// Update the elapsed time if the game is not paused or finished
		elapsedTime = gameClock.getElapsedTime() - pauseTime;;
	}
}
void Minesweeper3D::update() {
	// Update game state here if needed
// Call the getGameState function to update the game state
	GameState gameState = minesweeperBoard.getGameState();

	if (!isGamePaused && !isGameLoss || !isGamePaused && !isGameWin) {
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
			isGameLoss = true;
			gameOverSound.play();
		}
	}
	// Check if the game has finished
	if (gameState != GameState::RUNNING) {
		// If the game has finished, render the scene immediately
		render();
	}
}

void Minesweeper3D::displayWinOverlay() {
	// Draw a semi-transparent overlay or message
	sf::RectangleShape winOverlay(sf::Vector2f(static_cast<float>(app->getSize().x), static_cast<float>(app->getSize().y)));
	winOverlay.setFillColor(sf::Color(0, 0, 0, 128)); // Semi-transparent black
	app->draw(winOverlay);

	sf::Text winText("You've Won!", font, 48);
	winText.setFillColor(sf::Color::White);
	winText.setPosition(static_cast<float>(app->getSize().x) / 2.0f - winText.getGlobalBounds().width / 2.0f,
		static_cast<float>(app->getSize().y) / 2.0f - winText.getGlobalBounds().height / 2.0f);
	app->draw(winText);
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

			// Set cell position
			cellShape.setPosition(xPos, yPos);
			cellShape.move(0, zPos); // Adjust for the z position

			// Determine which texture to use based on cell state
			sf::Texture* textureToUse = nullptr;

			if (minesweeperBoard.board[x][y]->hasMine && minesweeperBoard.board[x][y]->isRevealed) {
				//textureToUse = &bombTexture;
				//this->cellShape.setTexture(textureToUse);
				this->cellShape.setFillColor(sf::Color::Magenta);
				app->draw(cellShape);
			}
			if (minesweeperBoard.board[x][y]->hasMine) {
				// Draw the cell shape

				this->cellShape.setFillColor(sf::Color::Red); // Revealed cell with number of adjacent mines
				textureToUse = &bombTexture;
				//this->cellShape.setTexture(textureToUse);
				app->draw(cellShape);
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

				//if (mineCount >= 0)

				//	// Display the number of adjacent mines
				//	//textureToUse = &revealedTexture;
				sf::Color customColor(255, 128, 0); // Orange

				this->cellShape.setFillColor(customColor); // Revealed cell with number of adjacent mines
				//app->draw(this->cellShape);
				if (mineCount > 0)  // Only display the count if it's greater than 0
					mineCountText.setString(std::to_string(mineCount));

				mineCountText.setFont(font);
				mineCountText.setCharacterSize(30);
				mineCountText.setFillColor(textColor);
				mineCountText.setPosition((xPos + x - 1) + CELL_SIZE / 4, (yPos - y + 2) + CELL_SIZE / 4); // Position the text
				// Draw the cell shape

				//cellShape.setTexture(textureToUse);

				app->draw(cellShape);
				app->draw(mineCountText);


			}
			else if (minesweeperBoard.board[x][y]->hasFlag) {
				//textureToUse = &flaggedTexture;
				// Draw the cell shape
				this->cellShape.setFillColor(sf::Color::Yellow); // Flag
				app->draw(cellShape);
			}
			else {
				//textureToUse = &unrevealedTexture;
				this->cellShape.setFillColor(sf::Color::White); // Unrevealed cell
				// Draw the cell shape
				app->draw(cellShape);
			}

			//Apply the texture to the cell shape
			//cellShape.setTexture(textureToUse);


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
		this->currentWindowSize = windowSize;
		this->drawBoard();
	}
	else if (isGamePaused) {
		// Draw a semi-transparent overlay or message
		sf::RectangleShape pauseOverlay(sf::Vector2f(static_cast<float>(app->getSize().x), static_cast<float>(app->getSize().y)));
		pauseOverlay.setFillColor(sf::Color(0, 0, 0, 128)); // Semi-transparent black
		app->draw(pauseOverlay);

		sf::Text pausedText("Game Paused", font, 48);
		pausedText.setFillColor(sf::Color::White);
		pausedText.setPosition(static_cast<float>(app->getSize().x) / 2.0f - pausedText.getGlobalBounds().width / 2.0f,
			static_cast<float>(app->getSize().y) / 2.0f - pausedText.getGlobalBounds().height / 2.0f);
		app->draw(pausedText);

	}
	else if (isGameWin) {
		displayWinOverlay();

	}

	else {
		// Draw the 3D board
		this->drawBoard();

	}

	// Display the updated window
	initInGameUtils();
	app->display();


}

