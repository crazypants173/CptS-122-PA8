#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>

#define MAP_WIDTH 10
#define MAP_HEIGHT 5
#define TILE_WIDTH 100
#define TILE_HEIGHT 47
#define TILE_LENGTH 170
#define TILES 8

using std::string;
using std::ifstream;
using sf::Texture;
using sf::Sprite;
using sf::RenderWindow;

class Map
{
public:
	Map(RenderWindow &window);
	//~Map();
	void load(string filename);
	void draw();
private:
	string numToName(int num);
	void loadTiles();
private:
	RenderWindow *rw;
	Sprite *mapSprite[MAP_HEIGHT][MAP_WIDTH];
	Texture tileTexture[TILES];
	int windowHeight, windowWidth;
};