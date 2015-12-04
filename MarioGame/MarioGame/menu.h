#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>

enum gameStatus {Starting, Menuing, Playing, Scoreboarding, Exiting};
enum menuOptions {None, PlayGame, Scoreboard, ExitGame};

class Menu
{
	public:
		static void StartGame(); // Start the game
		
	private:
		static void _menu(); // 
		static menuOptions _displayMenuOptions(); 

		static bool _isExit; 
		static gameStatus _gStatus; 
		static sf::RenderWindow _mainGameWindow; 
};