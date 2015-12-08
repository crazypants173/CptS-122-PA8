#include "game.h"


void Game::StartGame()
{
	if (_gStatus != Starting) // An instance is running
		return; 

	_mainGameWindow.create(sf::VideoMode(800,600,32), "Mario Clone");
	_networking.setDefaultUsernameScore();
	

	_gStatus = Menuing;

	while(!_isExit)
	{
		GameLoop();
	}

	_mainGameWindow.close(); 
}

void Game::GameLoop()
{
	hero.Load("img/Hero_duck2.png");
	hero.SetPosition(3,3);

	sf::Event curEvnt; // Remove after testing - will screw up event stack

	_mainGameWindow.clear(sf::Color(255,255,255));

	/*hero.Draw(_mainGameWindow);*/

	_mainGameWindow.display();

	_networking.network();

	switch(_gStatus)
	{
		case Menuing: 
			showMenu();
			break;
		case Playing:
			// Implement me - If Play game is pressed - ADD THE FUNCTION THAT STARTS THE GAME
			//_mainGameWindow.pollEvent(curEvnt); // remove
			 
			//if (curEvnt.type == sf::Event::Closed) // remove 
			//{
			//	_gStatus = Exiting;
			//	_isExit = true;
			//}
			break;
		case Scoreboarding:
			// Implement me - If scoreboard is pressed - ADD THE FUNCTION THAT SHOWS THE SCOREBOARD
			_mainGameWindow.pollEvent(curEvnt); //remove

			if (curEvnt.type == sf::Event::Closed) //remove
			{
				_gStatus = Exiting;
				_isExit = true;
			}
			break;
		case Exiting:
			_isExit = true;
			break;
	};
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
gNetwork Game::_networking; 
Collision_Detection Game:: hero;