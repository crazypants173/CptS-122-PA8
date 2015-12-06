/*
	game.h 
		Main location for calling functions to play game
		Manages main game window, game status
*/

#pragma once

#include "Map.h"
#include "menu.h"

enum gameStatus {Starting, Menuing, Playing, Scoreboarding, Exiting}; // Names for game status

// Class used to play the game - Contains static functions and variables - Only one instance of the game may be run per computer
class Game
{
	public:
		
		static void StartGame(); // Initalizes main window, then calls menu - Menu handles from there;
		
		static sf::RenderWindow & getMainWin() // return main game window; 
		{
			return _mainGameWindow; 
		}

		static void GameLoop(); // Run based upon current game state

	private:
		static bool _isExit; // Bool for an exit status of the game
		static gameStatus _gStatus; // Current status of the game
		static sf::RenderWindow _mainGameWindow; // Main game window
}; 