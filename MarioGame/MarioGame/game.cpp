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

	switch(_gStatus)
	{
		case Menuing: 
			showMenu();
			break;
		case Playing:
			// Implement me
			break;
		case Scoreboarding:
			break;
		case Exiting:
			_isExit = true;
			break;
	}
}

void Game::showMenu()
{
	Menu menu;
	Menu::menuOptions selected = menu.displayMenuOptions(_mainGameWindow);

	switch (selected)
	{
		case Menu::PlayGame:
			_gStatus = Playing;
			break;
		case Menu::Scoreboard:
			_gStatus = Scoreboarding;
			break;
		case Menu::ExitGame:
			_gStatus = Exiting;
			break;
		case Menu::None:
			break;
	}
}

gameStatus Game::_gStatus = Starting;
bool Game::_isExit = false; 
sf::RenderWindow Game::_mainGameWindow;