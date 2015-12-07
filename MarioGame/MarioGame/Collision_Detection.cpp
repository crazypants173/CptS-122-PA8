#include "Collision_Detection.h"

using std::cin;
using std::cout;
using std::endl;

Collision_Detection::Collision_Detection()
{
  _isLoaded = false;
}


Collision_Detection::~Collision_Detection()
{
}

void Collision_Detection::Load(std::string filename)
{
	if(_image.loadFromFile(filename) == false)
  {
    _filename = "";
    _isLoaded = false;
	cout << "fail" << endl;
  }
  else
  {
    _filename = filename;
	_sprite.setTexture(_image);
    _isLoaded = true;
	cout << "success" << endl;
  }
}

void Collision_Detection::Draw(sf::RenderWindow & renderWindow)
{
  if(_isLoaded == true)
  {
    renderWindow.draw(_sprite);
  }
}

void Collision_Detection::SetPosition(float x, float y)
{
  if(_isLoaded)
  {
	  _sprite.setPosition(x,y);
  }
}