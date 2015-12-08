#include "Player.h"

Player::Player(string filename)
{
	playerTexture.loadFromFile(filename);
	playerSprite.setTexture(playerTexture);
	jump = false;
}
void Player::setPos(float nx, float ny, CORNER c = TOP_LEFT)
{
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

void Player::move(float offset_x, float offset_y)
{
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
}
