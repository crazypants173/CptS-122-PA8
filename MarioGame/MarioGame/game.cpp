#include "game.h"

/*
	To access main game window, type Game::getMainWin(); - returns a reference to the main window
	It is a sf::RenderWindow type

	In game.cpp (this file), you can also use _mainGameWindow as the window parameter

	You can also use func(sf::RenderWindow &window) as a parameter to a function and it will work
*/

void Game::StartGame()
{
	if (_gStatus != Starting) // An instance is running
		return; 

	_mainGameWindow.create(sf::VideoMode(800,600,32), "Mario Clone");
	_networking.setDefaultUsernameScore();
	

	sf::Thread netSendThread(Game::runNetworkSend);
	sf::Thread netRecvThread(Game::runNetworkRecv);

	netRecvThread.launch();
	netSendThread.launch();

	_gStatus = Menuing;	

	while(!_isExit)
	{
		GameLoop();
	}

	netRecvThread.terminate();
	netSendThread.terminate();

	_mainGameWindow.close(); 
}
/*
	if you want to exit the game, set _gStatus = Exiting
*/
void Game::GameLoop()
{
	hero.Load("img/Hero_duck2.png");
	hero.SetPosition(3,3);

	sf::Event curEvnt; // Remove after testing - will screw up event stack

	_mainGameWindow.clear(sf::Color(255,255,255));

	/*hero.Draw(_mainGameWindow);*/

	_mainGameWindow.display();

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

void Game::runNetworkSend()
{
	bool ifSent = false; // Boolean to see if a packet was sent

	while(true)
	{
		time_t curTime = time(NULL); 
	
		if(curTime % 60 == 0 && !ifSent) // Broadcast every minute
		{
			_networking.broadcastToNetwork();
			ifSent = true;
		}
		else if (curTime % 60 != 0)
			ifSent = false;
	}
}

void Game::runNetworkRecv()
{
	while(true)
		_networking.listenToNetwork();
}

gameStatus Game::_gStatus = Starting;
bool Game::_isExit = false; 
sf::RenderWindow Game::_mainGameWindow;
gNetwork Game::_networking; 
Collision_Detection Game:: hero;
