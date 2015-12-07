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
#include "menu.h"
#include "Map.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

	sf::View v(sf::FloatRect(0,0,800, 600));
	window.setView(v);
	
	Map m(800,600);
	m.load("test.map");

	sf::Clock c;

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

	/*
	To access main game window, type Menu::_mainGameWindow
	It is a sf::RenderWindow type
	*/

	Menu::StartGame(); 

    return 0;
}