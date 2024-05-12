// Minesweeper.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Minesweeper3D.h"
#include "Minesweeperboard.h"
#include "MSTextController.h"
#include "SplashScreen.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>



int main()
{

	//MinesweeperBoard mineEasy(10, 10, GameMode::EASY);
	//mineEasy.debug_display();
	//std::cout << std::endl;

	//// Test the revealField() and getGameState() functions
	//std::cout << "Testing revealField() and getGameState():\n";
	//std::cout << std::endl;
	//std::cout << "Game state: " << (mineEasy.getGameState() == GameState::RUNNING ? "Running" : "Finished") << std::endl;

	//mineEasy.revealField(4, 7);
	//std::cout << "Game state: " << (mineEasy.getGameState() == GameState::RUNNING ? "Running" : "Finished") << std::endl;

	//mineEasy.revealField(0, 0);
	//std::cout << "Game state: " << (mineEasy.getGameState() == GameState::RUNNING ? "Running" : "Finished") << std::endl;
	//std::cout << std::endl;

	//// Test the normal game mode
	//std::cout << "Testing normal game mode:\n";
	//MinesweeperBoard mineNormal(10, 10, GameMode::NORMAL);
	//mineNormal.debug_display();
	//std::cout << std::endl;

	//// Test the revealField() and getGameState() functions
	//std::cout << "Testing revealField() and getGameState():\n";
	//std::cout << "Game state: " << (mineNormal.getGameState() == GameState::RUNNING ? "Running" : "Finished") << std::endl;
	//mineNormal.revealField(0, 0);
	//std::cout << "Game state: " << (mineNormal.getGameState() == GameState::RUNNING ? "Running" : "Finished") << std::endl;
	//std::cout << std::endl;

	//// Test the hard game mode
	//std::cout << "Testing hard game mode:\n";
	//MinesweeperBoard mineHard(10, 10, GameMode::HARD);
	//mineHard.debug_display();
	//std::cout << std::endl;

	//// Test the revealField() and getGameState() functions
	//std::cout << "Testing revealField() and getGameState():\n";
	//std::cout << "Game state: " << (mineHard.getGameState() == GameState::RUNNING ? "Running" : "Finished") << std::endl;
	//mineHard.revealField(0, 0);
	//std::cout << "Game state: " << (mineHard.getGameState() == GameState::RUNNING ? "Running" : "Finished") << std::endl;
	//std::cout << std::endl;


	//std::cout << "Testing debug game mode:\n";
	//MinesweeperBoard mineDebug(10, 10, GameMode::DEBUG);
	//mineDebug.debug_display();
	//std::cout << std::endl;

	//// Test the countMines() function
	//std::cout << "Testing countMines():\n";
	//std::cout << "Mines around (0, 0): " << mineDebug.countMines(0, 0) << std::endl;
	//std::cout << "Mines around (1, 0): " << mineDebug.countMines(1, 0) << std::endl;
	//std::cout << "Mines around (2, 9): " << mineDebug.countMines(2, 9) << std::endl;
	//std::cout << "Mines around (2, 1): " << mineDebug.countMines(2, 1) << std::endl;
	//std::cout << "Mines around (6, 7): " << mineDebug.countMines(6, 7) << std::endl;
	//std::cout << std::endl;

	//// Test the hasFlag() and toggleFlag() functions
	//std::cout << "Testing hasFlag() and toggleFlag():\n";
	//std::cout << "Has flag at (0, 2)? " << (mineDebug.hasFlag(0, 2) ? "Yes" : "No") << std::endl;
	//mineDebug.toggleFlag(0, 0);
	//std::cout << "Has flag at toggled (0, 0)? " << (mineDebug.hasFlag(0, 0) ? "Yes" : "No") << std::endl;
	//std::cout << std::endl;

	//// Test the revealField() and getGameState() functions
	//std::cout <me state: ";
	//mineDebug.getGameS< "Testing revealField() and getGameState():\n";
	//std::cout << "GameState();
	//mineDebug.revealField(2, 1);
	//std::cout << "Game state: " << (mineDebug.getGameState()) << std::endl;
	//std::cout << "Game state: " << (mineDebug.getGameState() == GameState::RUNNING ? "Running" : "Finished") << std::endl;
	//std::cout << std::endl;



	//// Test the getFieldInfo() function
	//mineDebug.revealField(4, 9);
	//std::cout << "Testing getFieldInfo():\n";
	//std::cout << "Field info at (0, 0): " << mineDebug.getFieldInfo(0, 0) << std::endl;
	//std::cout << "Field info at (1, 1): " << mineDebug.getFieldInfo(1, 1) << std::endl;
	//std::cout << "Field info at (0, 2): " << mineDebug.getFieldInfo(0, 2) << std::endl;
	//std::cout << "Field info at (6, 7): " << mineDebug.getFieldInfo(20, 7) << std::endl;
	//std::cout << "Field info at (4, 9): " << mineDebug.getFieldInfo(4, 9) << std::endl;
	//std::cout << "Field info at (4, 9): " << mineDebug.getFieldInfo(7, 0) << std::endl;
	//std::cout << std::endl;




	//MinesweeperBoard board(20, 10, GameMode::NORMAL);
	//MSBoardTextView view(board);
	////view.display();
	////board.revealField(0, 5);
	////view.display();

	//MSTextController ctrl(board, view);
	//ctrl.play();


	//MinesweeperBoard board(20, 10, GameMode::NORMAL);
	//MSBoardTextView view(board);
	////view.display();
	////board.revealField(0, 5);
	////view.display();

	//MSTextController ctrl(board, view);
	//ctrl.play();


	//Minesweeper3D game;
	// 
	Minesweeper3D game(4, GameMode::NORMAL);

	game.run();


	//sf::ContextSettings settings;
	//settings.antialiasingLevel = 8;
	//sf::RenderWindow window(sf::VideoMode(800, 600), "Minesweeper Splash Screen", sf::Style::Default, settings);

	//SplashScreen splashScreen;
	//splashScreen.run(window);



	//return EXIT_SUCCESS;

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
