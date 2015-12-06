/*
	Programming Assignment 8 - Mario Game
	A Mario Emulator

	Authors
		Benjamin Herrmann
		Michael Duncan
		___
		___
*/

#include <SFML/Graphics.hpp>
#include "game.h"
#include "Map.h"

/*
	To access main game window, type Game::getMainWin(); - returns a reference to the main window
	It is a sf::RenderWindow type

	You can also have func(sf::RenderWindow & window) as a parameter to a function and it will work
*/

int main()
{
    /*sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

	sf::View v(sf::FloatRect(0,0,800, 600));
	window.setView(v);
	
	Map m(800,600);
	m.load("test.map");

	sf::Clock c;
	c.getElapsedTime();
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

		window.clear(sf::Color::Blue);
		window.setView(v);
		v.move(200.0 * c.getElapsedTime().asSeconds(), 0);
		c.restart();
		window.draw(m);
        window.display();
    }
*/

	Game::StartGame();

    return 0;
}