#include "game.h"
#include <iostream>

using std::cout;

void Game::StartGame()
{
	if (_gStatus != Starting) // An instance is running
		return; 

	_mainGameWindow.create(sf::VideoMode(800,600,32), "Mario Clone");
	_gStatus = Menuing;

	while(!_isExit)
	{
		GameLoop();
	}

	_mainGameWindow.close(); 
}

void Game::GameLoop()
{
	sf::Event curEvnt;

	_mainGameWindow.clear(sf::Color(255,255,255));
	_mainGameWindow.display();

	while(_mainGameWindow.pollEvent(curEvnt))
	{
		switch(_gStatus)
		{
			case Menuing:
				Menu runGame; // create a menu
				Menu::menuOptions option = runGame.displayMenuOptions(_mainGameWindow); // display the menu

				switch (option)
				{
					case Menu::None: 
						break;
					case Menu::ExitGame: 
						_isExit = true; 
						break; 
					case Menu::PlayGame: // Implement the starting of the game
						break; 
					case Menu::Scoreboard: // Implement the scoreboard
						break; 
				}
				break;
		}

		if (curEvnt.type == sf::Event::Closed)
		{
			_gStatus = Exiting;
			_isExit = true;

			break;
		}
	}
}

gameStatus Game::_gStatus = Starting;
bool Game::_isExit = false; 
sf::RenderWindow Game::_mainGameWindow;