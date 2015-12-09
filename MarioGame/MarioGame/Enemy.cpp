#include "Enemy.h"

Enemy::Enemy(float placex, float placey, float minx, float maxx)
{
	enemyTexture.loadFromFile("img/Enemy Bug.png");
	enemySprite.setTexture(enemyTexture);
	x = placex;
	y = placey;
	min_x = minx;
	max_x = maxx;
	speed = 100;
	dead = false;
	enemySprite.setPosition(x,y);
}

void Enemy::move(float multiplier)
{
	if(dead)
		return;
	x+=(speed*multiplier);

	if(x < min_x)
	{
		x = min_x;
		speed *=-1;
		enemySprite.setTextureRect(sf::IntRect(0, 0, enemyTexture.getSize().x, enemyTexture.getSize().y));
	}
	if(x > max_x)
	{
		x = max_x;
		speed*=-1;
		enemySprite.setTextureRect(sf::IntRect(enemyTexture.getSize().x, 0, 1-enemyTexture.getSize().x, enemyTexture.getSize().y));
	}
	enemySprite.setPosition(x,y);
}
void Enemy::collides(Player &p)
{
	if(dead == true){ return;}
	float px, py;
	bool left = false, right = false;
	int hits = 0;
	FloatRect pos(x, y+90, enemyTexture.getSize().x, enemyTexture.getSize().y-90);
	p.getPos(px, py, BOTTOM_LEFT);
	if(pos.contains(px, py)) //if it is in the same x region
	{
		left = true;
		hits++;
	}
	p.getPos(px, py, BOTTOM_RIGHT);
	if(pos.contains(px, py)) //if it is in the same x region
	{
		right = true;
		hits++;
	}
	p.getLastPos(px, py, BOTTOM_LEFT);

	if(hits > 0 && py < (y+90)) // if both corners are on top of the enemy
	{
		dead = true;
	}
	else if(hits > 0) //he loses
	{
		p.setPos(0,1000,TOP_LEFT);
	}
}

void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states = RenderStates::Default) const
{
	if(dead)
		return;
	target.draw(enemySprite, states);
}