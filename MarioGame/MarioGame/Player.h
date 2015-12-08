#pragma once

#include <SFML\Graphics.hpp>
#include <string>
#include <iostream>
#include "Map.h"

using namespace sf;
using std::string;

typedef enum CORNER
{
	TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT
};

class Player:public Drawable
{
public:
	Player(string filename);
	void setPos(float x, float y, CORNER c);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void move(float offset_x, float offset_y);
	void jump(float force);
	void getLastPos(float &x, float &y, CORNER c);
	void getPos(float &x, float &y, CORNER c);
	void checkHits(Map &m);
	void update(Map &m);
	
	
private:
	Texture playerTexture;
	Sprite playerSprite;
	Clock gravityTimer;

	bool jumping, falling;
	int width, height;
	float x, y, last_x, last_y, jumpForce;

	void doGravity(Map &m);
};