#include "menu.h"
#include <iostream>

using std::exception;
using std::cout;

Menu::menuOptions Menu::displayMenuOptions(sf::RenderWindow &window)
{
	this->img.loadFromFile("img/Menu.png");
	sprite.setTexture(img);

	// Play Game Button
	_menuItems[0].rect.top = 225; 
	_menuItems[0].rect.height = 45;
	_menuItems[0].rect.left = 285; 
	_menuItems[0].rect.width = 230;
	_menuItems[0].action = PlayGame; 
	
	// Scoreboard Button
	_menuItems[1].rect.top = 275; 
	_menuItems[1].rect.height = 45;
	_menuItems[1].rect.left = 285; 
	_menuItems[1].rect.width = 230;
	_menuItems[1].action = Scoreboard; 

	// Exit Game Button
	_menuItems[2].rect.top = 320;
	_menuItems[2].rect.height = 45; 
	_menuItems[2].rect.left = 285; 
	_menuItems[2].rect.width = 230; 
	_menuItems[2].action = ExitGame;

	window.draw(sprite); 
	window.display();

	menuOptions retVal = _GetMouseClick(window);// Return None to continue menuing


	return retVal;
}

Menu::menuOptions Menu::_HandleClick(int x, int y)
{
	int index = 0; 

	for (index = 0; index < 3; index++)
	{
		sf::Rect<int> menuItemRect = _menuItems[index].rect; // Take the size of the rectangle for the current item
		if (menuItemRect.top < y && (menuItemRect.top + menuItemRect.height) > y // Check if at the right height
			&& menuItemRect.left < x && (menuItemRect.width + menuItemRect.left) > x) // check if at right width
		{
			return _menuItems[index].action;
		}
	}
	
	return None; // Not in range
}

Menu::menuOptions Menu::_GetMouseClick(sf::RenderWindow & window)
{
	sf::Event curEvnt;

	while(true)
	{
		while(window.pollEvent(curEvnt))
		{
			if (curEvnt.type == sf::Event::MouseButtonPressed)
				return this->_HandleClick(curEvnt.mouseButton.x, curEvnt.mouseButton.y);
			if (curEvnt.type == sf::Event::Closed)
				return ExitGame;
		}
	}
}
