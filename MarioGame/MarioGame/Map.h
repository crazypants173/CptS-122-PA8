#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>

#define MAP_WIDTH 30
#define MAP_HEIGHT 5
#define TILE_WIDTH 100
#define TILE_HEIGHT 43
#define TILE_LENGTH 170
#define TILES 8

using std::string;
using std::ifstream;
using sf::Texture;
using sf::Sprite;
using sf::RenderWindow;
using sf::RenderTexture;
using sf::Drawable;
using sf::FloatRect;

class Map:public Drawable
{
public:
	Map(int width, int height);
	~Map();
	void load(string filename);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	Texture getTexture();
	bool collides(float prevx, float prevy, float &x, float &y, bool *onGround = nullptr);
	void moveBackground(float x, float y);
	void setDrawColumnRange(float x);

private:
	void drawToTexture(RenderTexture& rt);
	void loadTiles();
	void generateShadows();
	void findDimensions(string filename);

	Sprite *mapSprite[MAP_HEIGHT][MAP_WIDTH];
	Sprite *shadowSprite[MAP_HEIGHT][MAP_WIDTH];
	Sprite backgroundSprite;
	Texture tileTexture[TILES];
	Texture shadowTextureEast, shadowTextureWest, backgroundTexture;
	int maxColumn, minColumn;
	int windowHeight, windowWidth;
};