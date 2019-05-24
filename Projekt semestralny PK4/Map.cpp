#include "Map.h"



Map::Map()
{
	map.setSize(sf::Vector2f(1920.0f, 1080.0f));
	map.setPosition(0, 0);
	mapTexture.loadFromFile("Textures/Grass1.png");
	mapTexture.setSmooth(true);
	map.setTexture(&mapTexture);
}


Map::~Map()
{

}

void Map::drawMap(sf::RenderWindow & window)
{
	window.draw(map);
}
/*
void Map::initMapAsSquares()
{
	for (int i = 0; i < 48; i++)
	{
		for (int j = 0; j < 27; j++)
		{
			sf::RectangleShape square;
			square.setPosition((i * 40),(j * 40));
			square.setSize(sf::Vector2f(40, 40));
			square.setFillColor(sf::Color(i*5,j*8,i+j*4));
			squares.push_back(square);
		}
	}
}

void Map::drawMapAsSquares(sf::RenderWindow& window)
{
	for (auto s : squares)
	{
		window.draw(s);
	}
}
*/