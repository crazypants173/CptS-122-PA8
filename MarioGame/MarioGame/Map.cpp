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
		std::cout << "Error loading shadow textures" << std::endl;
	}

	if(!backgroundTexture.loadFromFile("img/b.png"))
	{
		std::cout << "Error loading background texture" << std::endl;
	}
	backgroundTexture.setSmooth(true);
	backgroundTexture.setRepeated(true);
	
	backgroundSprite.setTexture(backgroundTexture);

	float scale;
	scale = (float)height/(float)backgroundTexture.getSize().y;
	backgroundSprite.setScale(scale, scale);

	backgroundSprite.setTextureRect(sf::IntRect(0,0,MAP_WIDTH*TILE_WIDTH/scale + 2*windowWidth,height/scale)); //don't judge me
	backgroundSprite.setPosition(-windowWidth,0);

	maxColumn = MAP_WIDTH - 1;
	minColumn = 0;
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
	string key[] = {"Brown Block", "Dirt Block", "Grass Block", "Plain Block", "Stone Block", "Wall Block", "Water Block", "Wood Block", "Rock", "Tree Short", "Lava Block"};
	for(int i = 0; i < TILES; i++)
	{
		string path = "img/" + key[i] + ".png";
		if(!tileTexture[i].loadFromFile(path))
		{
			std::cout << "Error loading " << key[i] << " texture" << std::endl;
		}
	}
}

void Map::load(string filename)
{
	ifstream input;
	findDimensions(filename);

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
	target.draw(backgroundSprite);
	for(int i = MAP_HEIGHT - 1; i >= 0; i--) 
	{
		for(int j = minColumn; j <= maxColumn; j++)
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

bool Map::collides(float prevx, float prevy ,float &x, float &y, bool *onGround)
{
	int column = x/(float)TILE_WIDTH;
	int row = (y - (float)MAP_HEIGHT*TILE_HEIGHT - TILE_LENGTH)/(float)TILE_HEIGHT;

	int prevcolumn = prevx/(float)TILE_WIDTH;
	int prevrow = (prevy - (float)MAP_HEIGHT*TILE_HEIGHT - TILE_LENGTH)/(float)TILE_HEIGHT;

	bool collided = false;

	if(column > MAP_WIDTH-1 || column < 0 || row > MAP_HEIGHT-1 || row < 0) //if the point is outside of the map
	{
		collided = false;
	}

	else if(mapSprite[row][column] != nullptr) //if it collided
	{
		if(column < prevcolumn) //moving left
		{
			x = prevcolumn * (float)TILE_WIDTH;
		}
		if(column > prevcolumn) //moving right
		{
			x = (prevcolumn+1) * (float)TILE_WIDTH - .001;
		}
		if(row > prevrow) // moving down
		{
			y = windowHeight - TILE_HEIGHT * (MAP_HEIGHT - prevrow) + TILE_HEIGHT - .001;
		}
		if(row < prevrow)
		{
			//std::cout << "yup";
		}
		if(mapSprite[row][column]->getTexture() == &tileTexture[10])
		{
			y = windowHeight*2;
			return true;
		}
		collided = true;
	}

	int temprow = (y + .002 - (float)MAP_HEIGHT*TILE_HEIGHT - TILE_LENGTH)/(float)TILE_HEIGHT;
	if(onGround != nullptr && temprow > row && mapSprite[temprow][column] != nullptr)
	{
		*onGround = true;
	}
	return collided;
}

void Map::moveBackground(float x, float y)
{
	backgroundSprite.move(x, y);
}

void Map::setDrawColumnRange(float x)
{
	int column = x/(float)TILE_WIDTH;
	int onScreen = windowWidth/MAP_WIDTH;
	minColumn = column - onScreen/2;
	maxColumn = column + onScreen/2;
	if(minColumn < 0)
		minColumn = 0;
	if(maxColumn > MAP_WIDTH-1)
		maxColumn = MAP_WIDTH-1;
}

void Map::findDimensions(string filename)
{
	ifstream input;

	input.open(filename);

	string term;
	int count = 0, lines = 0, width = 0;
	while(!input.eof())
	{
		term = "";
	while(term.find("\n") == string::npos && !input.eof())
	{
		char buffer[10];
		input.getline(buffer, 1000, '\t');
		term = buffer;
		count++;
	}
	if(lines == 0)
	{
		width = count;
	}
	lines++;
	}
	input.close();
	std::cout << lines << "," << width << std::endl;
}