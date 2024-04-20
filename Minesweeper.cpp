// Minesweeper.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Minesweeperboard.h"
#include <iostream>

int main()
{
	// Test the default constructor
	std::cout << "Testing default constructor:\n";
	MinesweeperBoard mine;
	mine.debug_display();
	std::cout << std::endl;

	//Test the parametric constructor with different game modes
	std::cout << "Testing easy game mode:\n";
	MinesweeperBoard mineEasy(10, 10, GameMode::EASY);
	mineEasy.debug_display();
	std::cout << std::endl;

	std::cout << "Testing normal game mode:\n";
	MinesweeperBoard mineNormal(10, 10, GameMode::NORMAL);
	mineNormal.debug_display();
	std::cout << std::endl;

	std::cout << "Testing hard game mode:\n";
	MinesweeperBoard mineHard(10, 10, GameMode::HARD);
	mineHard.debug_display();
	std::cout << std::endl;

	std::cout << "Testing debug game mode:\n";
	MinesweeperBoard mineDebug(10, 10, GameMode::DEBUG);
	mineDebug.debug_display();
	std::cout << std::endl;

	return 0;

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
