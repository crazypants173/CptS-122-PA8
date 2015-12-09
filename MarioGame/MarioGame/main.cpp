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

	Player p("img/duck_small.png");
	p.setJumpSprite("img/duck_jump_small.png");
	p.setPos(0,350, TOP_LEFT);
	//p.setScale(.5);

	cd.SetPosition(x,y);
	cd.Draw(window);
	

	sf::Clock c;
	float prevx, prevy;
	bool moveRight = false, moveLeft = false, flipped = false;;

    while (window.isOpen())
    {
		p.getPos(prevx, prevy, BOTTOM_LEFT);
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
					if(flipped)
					{
						p.unflip();
						flipped = false;
					}
				}
				else if(event.key.code == sf::Keyboard::A)
				{
					moveLeft = true;
					moveRight = false;
					if(!flipped)
					{
						p.flip();
						flipped = true;
					}
				}
								else if(event.key.code == sf::Keyboard::W) //delete after testing
				{
					p.move(0,-5);
				}
								else if(event.key.code == sf::Keyboard::S) //delete after testing
				{
					p.flip();
				}
				if(event.key.code == sf::Keyboard::Space)
				{
					p.jump(100);
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
		float time; //= c.getElapsedTime().asMilliseconds()/1000;
		if(moveLeft)
		{
			time = c.getElapsedTime().asSeconds();
			c.restart();
			p.move(-500 * time, 0);
		}
		else if(moveRight)
		{
			time = c.getElapsedTime().asSeconds();
			c.restart();
			p.move(500 * time, 0);
		}
		else
		{
			c.restart();
		}

		p.update(m);
		window.clear();
		window.setView(v);
		/*if(1/time < 60)
		{
			cout << "Under 60!" << endl;
		}*/
		float cx, cy, lx, ly;
		p.getPos(cx, cy, BOTTOM_CENTER);
		v.setCenter(sf::Vector2f(cx, 300)); //window height/2
		p.getPos(lx, ly, BOTTOM_LEFT);
		m.moveBackground((lx-prevx)/2, 0);

		window.draw(m);
		window.draw(p);
        window.display();
		
    }

	Game::StartGame();

    return 0;
}