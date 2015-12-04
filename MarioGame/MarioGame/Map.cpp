#include "Map.h"

Map::Map(RenderWindow &window)
{
	rw = &window;
	windowWidth = window.getSize().x;
	windowHeight = window.getSize().y;

	loadTiles();
	for(int i = 0; i < MAP_HEIGHT; i++)
	{
		for(int j = 0; j < MAP_WIDTH; j++)
		{
			mapSprite[i][j] = nullptr;
		}
	}
}

void Map::loadTiles()
{
	string key[] = {"Brown Block", "Dirt Block", "Grass Block", "Plain Block", "Stone Block", "Wall Block", "Water Block", "Wood Block"};
	for(int i = 0; i < TILES; i++)
	{
		string path = "img/" + key[i] + ".png";
		if(!tileTexture[i].loadFromFile(path))
		{
			std::cout << "Error loading texture" << std::endl;
		}
	}
}

void Map::load(string filename)
{
	ifstream input;

	input.open(filename, std::ios::in);

	for(int i = 0; i < MAP_HEIGHT; i++)
	{
		for(int j = 0; j < MAP_WIDTH; j++)
		{
			int code;
			input >> code;
			if(code != 0)
			{
				mapSprite[i][j] =  new Sprite();
				mapSprite[i][j]->setTexture(tileTexture[0]);
				mapSprite[i][j]->setPosition(TILE_WIDTH * j, windowHeight - TILE_LENGTH - TILE_HEIGHT * (MAP_HEIGHT - i - 1));
			}
		}
	}
}

void Map::draw()
{
	for(int i = MAP_HEIGHT - 1; i >= 0; i--)
	{
		for(int j = 0; j < MAP_WIDTH; j++)
		{
			if(mapSprite[i][j] != nullptr)
			{
				rw->draw(*mapSprite[i][j]);
			}
		}
	}
}

