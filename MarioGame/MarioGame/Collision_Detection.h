#pragma once
#include "Map.h" 
//taken straight from gamesfromscratch.com so that i could go directly into collision detection
class Collision_Detection
{
 public:
	Collision_Detection();
	virtual ~Collision_Detection();   
	virtual void Load(std::string filename);
	virtual void Draw(sf::RenderWindow & window);
	virtual void SetPosition(float x, float y);

	private:
	sf::Sprite  _sprite;
	sf::Texture _image;
	std::string _filename;
	bool _isLoaded;
};

