#include "Map.h"

Map::Map(int width, int height)
{
	windowWidth = width;
	windowHeight = height;


	loadTiles();
	for(int i = 0; i < MAP_HEIGHT; i++)
	{
		for(int j = 0; j < MAP_WIDTH; j++)
		{
			mapSprite[i][j] = nullptr;
			shadowSprite[i][j] = nullptr;
		}
	}

	if(!shadowTextureEast.loadFromFile("img/Shadow East.png") || !shadowTextureWest.loadFromFile("img/Shadow West.png")) //Load shadows
	{
		std::cout << "Error loading texture" << std::endl;
	}
}

Map::~Map()
{
	for(int i = 0; i < MAP_HEIGHT; i++)
	{
		for(int j = 0; j < MAP_WIDTH; j++)
		{
			if(mapSprite[i][j] != nullptr)
			{
				delete mapSprite[i][j];
				std::cout << "Delete block(" << j << "," << i << ")" << std::endl;
			}
			if(shadowSprite[i][j] != nullptr)
			{
				delete shadowSprite[i][j];
				std::cout << "Delete shadow(" << j << "," << i << ")" << std::endl;
			}
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
				mapSprite[i][j]->setTexture(tileTexture[code-1]);
				mapSprite[i][j]->setPosition(TILE_WIDTH * j, windowHeight - TILE_LENGTH - TILE_HEIGHT * (MAP_HEIGHT - i - 1));
			}
		}
	}
	generateShadows();
}

void Map::generateShadows()
{
	for(int i = 1; i < MAP_HEIGHT; i++) //start on the second highest row because the highest won't have shadows
	{
		for(int j = 1; j < MAP_WIDTH; j++) //west shadows
		{
			if( mapSprite[i-1][j-1] != nullptr && mapSprite[i-1][j] == nullptr && mapSprite[i][j] != nullptr) // if there is a block one to left and one up AND no block above
			{
				shadowSprite[i][j] = new Sprite();
				shadowSprite[i][j]->setTexture(shadowTextureWest);
				shadowSprite[i][j]->setPosition(TILE_WIDTH * j, windowHeight - TILE_LENGTH - TILE_HEIGHT * (MAP_HEIGHT - i - 1));
			}
		}
		for(int j = 0; j < MAP_WIDTH - 1; j++)
		{
			if( mapSprite[i-1][j+1] != nullptr && mapSprite[i-1][j] == nullptr && mapSprite[i][j] != nullptr) //if there is a block one to right an one up AND no block above
			{
				shadowSprite[i][j] = new Sprite();
				shadowSprite[i][j]->setTexture(shadowTextureEast);
				shadowSprite[i][j]->setPosition(TILE_WIDTH * j, windowHeight - TILE_LENGTH - TILE_HEIGHT * (MAP_HEIGHT - i - 1));
			}
		}
	}
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const
{
	for(int i = MAP_HEIGHT - 1; i >= 0; i--) 
	{
		for(int j = 0; j < MAP_WIDTH; j++)
		{
			if(mapSprite[i][j] != nullptr)
			{
				target.draw(*mapSprite[i][j], states); //draw blocks
			}
			if(shadowSprite[i][j] != nullptr)
			{
				target.draw(*shadowSprite[i][j], states); //draw shadows
			}
		}
	}
}

void Map::drawToTexture(RenderTexture& rt)
{
	for(int i = MAP_HEIGHT - 1; i >= 0; i--) 
	{
		for(int j = 0; j < MAP_WIDTH; j++)
		{
			if(mapSprite[i][j] != nullptr)
			{
				rt.draw(*mapSprite[i][j]); //draw blocks
			}
			if(shadowSprite[i][j] != nullptr)
			{
				rt.draw(*shadowSprite[i][j]); //draw shadows
			}
		}
	}
}

Texture Map::getTexture()
{
	RenderTexture rt;

	rt.create(MAP_WIDTH * TILE_WIDTH, MAP_HEIGHT * TILE_LENGTH);
	rt.clear();
	drawToTexture(rt);
	rt.display();

	return rt.getTexture();
}


