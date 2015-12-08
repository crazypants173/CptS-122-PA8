#pragma once

#include <SFML\Graphics.hpp>
#include <string>

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
	
private:
	Texture playerTexture;
	Sprite playerSprite;
	Clock c;

	bool jumping;
	int width, height;
	float x, y, jumpForce;
};