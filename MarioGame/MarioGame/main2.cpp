

	
	/*
	Programming Assignment 8 - Mario Game
	A Mario Emulator

	Authors
		Benjamin Herrmann
		___
		___
		___
*/

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>


int framesPassed = 0;


int main2()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(2.f);
	sf::CircleShape enemyShape(2.f);
    shape.setFillColor(sf::Color::Green);
	enemyShape.setFillColor(sf::Color::Red);
	window.setFramerateLimit(60);
	shape.setPosition(10,175);
	enemyShape.setPosition(175,175);

    while (window.isOpen())
    {
        sf::Event event;


    while (window.pollEvent(event))
        {
            
			if (event.type == sf::Event::EventType::KeyPressed && event.key.code == (sf::Keyboard::Key::Space))
			{
			for (framesPassed = 0; framesPassed < 41; framesPassed++) //jump

				{    
					 shape.move(0,-2+(.1*framesPassed));
					 enemyShape.move(-.2,0);

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
				{
					shape.move(.5, 0);
				}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
				{
					shape.move(-.5, 0);
				}
					
					 window.clear();
					 window.draw(shape);
					 window.draw(enemyShape);
					 window.display();
				}
			//COLLISION DETECTION 
			}
			


        }
	
//below this point the player is not jumping

if (event.type == sf::Event::Closed)
                window.close();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
			{
				shape.move(.5, 0);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
			{
				shape.move(-.5, 0);
			}

			
			
		enemyShape.move(-.2,0);
		//collision detection
        window.clear();
        window.draw(shape);
		window.draw(enemyShape);
        window.display();


    }

    return 0;
}



