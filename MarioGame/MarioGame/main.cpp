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
#include "gameNetworking.h"

/*
	To access main game window, type Game::getMainWin(); - returns a reference to the main window
	It is a sf::RenderWindow type

	You can also have func(sf::RenderWindow & window) as a parameter to a function and it will work
*/

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

	sf::View v(sf::FloatRect(0,0,800, 600));
	window.setView(v);
	
	Map m(800,600);
	m.load("test.map");
	float x = 0, y = 400;
	Collision_Detection cd; 
	cd.Load("img/Hero_duck2.png");
	cd.SetPosition(x,y);
	cd.Draw(window);
	

	sf::Clock c;
	float prevx, prevy;
    while (window.isOpen())
    {
		prevx = x;
		prevy = y;
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
			if(event.type == sf::Event::KeyPressed)
			{
				if(event.key.code == sf::Keyboard::D)
				{
					cd.SetPosition(x+=5, y);
				}
				if(event.key.code == sf::Keyboard::S)
				{
					cd.SetPosition(x, y+=5);
				}
			}
        }

		m.collides(prevx, prevy, x, y);
		window.clear(sf::Color::Blue);
		window.setView(v);
		float time = c.getElapsedTime().asSeconds();
		c.restart();
		float move = 200.0 * time;
		if(1/time < 60)
		{
			cout << "Under 120!" << endl;
		}
		v.move(move, 0);
		m.moveBackground(move*.5, 0);
		window.draw(m);
		//cd.Draw(window);
        window.display();
		
    }

	Game::StartGame();

    return 0;
}