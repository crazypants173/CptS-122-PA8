#include "Player.h"

Player::Player(string filename)
{

	if(!playerTexture.loadFromFile(filename))
	{
		std::cout << "Error loading player texture" << std::endl;
	}
	playerSprite.setTexture(playerTexture);
	width = playerTexture.getSize().x;
	height = playerTexture.getSize().y;
	jumping = false;
	falling = false;
	x = 0;
	y = 0;
	last_x = 0;
	last_y = 0;
}

void Player::setPos(float nx, float ny, CORNER c = TOP_LEFT)
{
	last_x = x;
	last_y = y;
	switch(c)
	{
	case TOP_LEFT:
		x = nx;
		y = ny;
		break;
	case TOP_RIGHT:
		x = nx - width;
		y = ny;
		break;
	case BOTTOM_LEFT:
		x = nx;
		y = ny - height;
		break;
	case BOTTOM_RIGHT:
		x = nx - width;
		y = ny - height;
		break;
	}
	playerSprite.setPosition(x, y);
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states = RenderStates::Default) const
{
	target.draw(playerSprite, states);
}

void Player::update(Map &m)
{
	if(true)
	{
		doGravity(m);
	}
}

void Player::move(float offset_x, float offset_y)
{
	last_x = x;
	last_y = y;
	x+=offset_x;
	y+=offset_y;
	playerSprite.move(offset_x, offset_y);
	
}

void Player::jump(float force)
{
	if(jumping) //do nothing if already jumping
	{
		return;
	}
	jumpForce = force;
	jumping = true;
	falling = true;
	gravityTimer.restart();
	jumpTimer.restart();
}

void Player::getPos(float &px, float &py, CORNER c)
{
	switch(c)
	{
	case TOP_LEFT:
		px = x;
		py = y;
		break;
	case TOP_RIGHT:
		px = x+width;
		py = y;
		break;
	case BOTTOM_LEFT:
		px = x;
		py = y+height;
		break;
	case BOTTOM_RIGHT:
		px = x+width;
		py = y+height;
		break;
	}
}

void Player::getLastPos(float &px, float &py, CORNER c)
{
	switch(c)
	{
	case TOP_LEFT:
		px = last_x;
		py = last_y;
		break;
	case TOP_RIGHT:
		px = last_x+width;
		py = last_y;
		break;
	case BOTTOM_LEFT:
		px = last_x;
		py = last_y+height;
		break;
	case BOTTOM_RIGHT:
		px = last_x+width;
		py = last_y+height;
		break;
	}
}

void Player::checkHits(Map &m)
{
	CORNER corners[2] = {BOTTOM_RIGHT, BOTTOM_LEFT};
	bool onground[2] = {false, false};

	for(int i = 0; i < 2; i++)
	{
		float lx, ly, nx, ny;
		getLastPos(lx, ly, corners[i]);
		getPos(nx, ny, corners[i]);
		if(m.collides(lx, ly, nx, ny, &onground[i]))
		{
			setPos(nx, ny, corners[i]);
			break;
		}
	}

	if(onground[0] == false && onground[1] == false) //neither corner on the ground
	{
		if(!jumping)
		{
			//std::cout << "hey" << std::endl;
			jump(0);
		}
	}
	else
	{
		falling = false;
	}
}

void Player::doGravity(Map &m)
{
	if(jumping)
	{
		float time = jumpTimer.getElapsedTime().asSeconds();
		jumpTimer.restart();
		float h = (-jumpForce + gravityTimer.getElapsedTime().asSeconds()*gravityTimer.getElapsedTime().asSeconds()*1000) * time * 10 ;
		last_y = y;
		y+=h;
		playerSprite.move(0,h);
		checkHits(m);
		if(y != last_y+h)
		{
			jumping = false;
		}
		else
		{
			std::cout << last_y << " " << y << std::endl;
		}
	}
}
