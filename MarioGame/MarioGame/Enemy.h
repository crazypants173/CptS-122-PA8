#pragma once

#include <SFML\Graphics.hpp>
#include "Player.h"
using namespace sf;

class Enemy:public Drawable
{
public:
	Enemy(float placex, float placey, float minx, float maxx);

	void move(float multiplier);
	void setSpeed(float nSpeed)
	{
		speed = nSpeed;
	}
	void setDead(bool isDead)
	{
		dead = isDead;
	}
	void collides(Player &p);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	float x, y, min_x, max_x, speed;
	bool dead;
	Texture enemyTexture;
	Sprite enemySprite;
};