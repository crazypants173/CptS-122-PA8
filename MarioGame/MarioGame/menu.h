#pragma once


#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>

class Menu
{
	public:
		enum menuOptions {None, PlayGame, Scoreboard, ExitGame}; // Names of menu options

		struct menuItem 
		{
			sf::Rect<int> rect;
			menuOptions action; 
		}; 

		menuOptions displayMenuOptions(sf::RenderWindow & window); // Display options to the window 

	private:	
		sf::Texture img; // Attempting to fix code
		sf::Sprite sprite;

		menuOptions _HandleClick(int x, int y); // Handle mouse clicks
		menuOptions _GetMouseClick(sf::RenderWindow & window); // Get the mouse click from the window
		menuItem _menuItems[3]; // List of buttons
};