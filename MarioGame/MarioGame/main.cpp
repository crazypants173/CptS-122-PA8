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
#include "Map.h"
int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 700), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
	Map m = Map(window);
	m.load("test.map");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        //window.draw(shape);
		m.draw();
        window.display();
    }

    return 0;
}