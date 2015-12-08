/*
	Programming Assignment 8 - Mario Game
	A Mario Emulator

	Authors
		Benjamin Herrmann
		Michael Duncan
		Patrick Stewart
		Jake Bogen
*/

#include <SFML/Graphics.hpp>
#include "game.h"
#include "Map.h"
#include "gameNetworking.h"
#include "Player.h"

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

	Player p("img/Hero_duck2.png");
	p.setPos(0,350, TOP_LEFT);

	cd.SetPosition(x,y);
	cd.Draw(window);
	

	sf::Clock c;
	float prevx, prevy;
	bool moveRight = false, moveLeft = false;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
			if(event.type == sf::Event::KeyPressed)
			{
				if(event.key.code == sf::Keyboard::D)
				{
					moveRight = true;
					moveLeft = false;
				}
				else if(event.key.code == sf::Keyboard::A)
				{
					moveLeft = true;
					moveRight = false;
				}
								else if(event.key.code == sf::Keyboard::W) //delete after testing
				{
					p.move(0,-5);
				}
								else if(event.key.code == sf::Keyboard::S) //delete after testing
				{
					p.move(0,5);
				}
				if(event.key.code == sf::Keyboard::Space)
				{
					p.jump(4);
				}
			}
			if(event.type == sf::Event::KeyReleased)
			{
				if(event.key.code == sf::Keyboard::D && moveRight)
				{
					moveRight = false;
				}
				else if(event.key.code == sf::Keyboard::A && moveLeft)
				{
					moveLeft = false;
				}
			}
        }
		float time = c.getElapsedTime().asSeconds();
		c.restart();
		if(moveLeft)
		{
			p.move(-400 * time, 0);
		}
		else if(moveRight)
		{
			p.move(400 * time, 0);
		}

		p.checkHits(m);
		p.update(m);
		p.checkHits(m);
		//m.collides(prevx, prevy, x, y);
		window.clear(sf::Color::Blue);
		window.setView(v);
		float move = 200.0 * time;
		if(1/time < 60)
		{
			cout << "Under 120!" << endl;
		}
		//v.move(move, 0);
		//m.moveBackground(move*.5, 0);
		window.draw(m);
		window.draw(p);
		//cd.Draw(window);
        window.display();
		
    }

	Game::StartGame();

    return 0;
}