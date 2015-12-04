#include "menu.h"

void Menu::StartGame()
{
	if (_gStatus != Starting)
		return; 

	_isExit = false; 
	_mainGameWindow.create(sf::VideoMode(800,600,32), "Testing Mario Game"); 

	_gStatus = Starting;

	while (!_isExit)
	{
		_menu(); 
	}

	_mainGameWindow.close(); 
}

void Menu::_menu()
{
	_gStatus = Menuing;  

	menuOptions optionChoice = None; 

	sf::Event currentEvent;

	while(_mainGameWindow.pollEvent(currentEvent))
	{
		switch (_gStatus)
		{
			case Menuing:
				optionChoice = _displayMenuOptions();
				switch (optionChoice)
				{
				case None: break;
				case PlayGame: _gStatus = Playing;
					break;
				case Scoreboard: _gStatus = Scoreboarding;
					break;
				case ExitGame: _isExit = true; 
					break; 
				}
				break; 
		}
	}
}
/*
____________________________________________________________________________________
____________________________________________________________________________________
_______________________________IMPLEMENT ME!!!!_____________________________________
____________________________________________________________________________________
____________________________________________________________________________________
*/
menuOptions Menu::_displayMenuOptions()
{
	_mainGameWindow.clear(sf::Color(255,0,0));
    _mainGameWindow.display();

	return None; // Return None to continue menuing
}

gameStatus Menu::_gStatus = Starting;
bool Menu::_isExit = false; 
sf::RenderWindow Menu::_mainGameWindow;