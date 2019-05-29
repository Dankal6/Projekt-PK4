#include "Map.h"



Map::Map()
{
	map.setSize(sf::Vector2f(1920.0f*scale, 1080.0f*scale));
	map.setPosition(0, 0);
	mapTexture.loadFromFile("Textures/Grass1.png");
	mapTexture.setSmooth(true);
	map.setTexture(&mapTexture);
	generatePlaces();
}


Map::~Map()
{

}

void Map::drawMap(sf::RenderWindow & window)
{
	window.draw(map);
	for (auto p : placesForTowers)
	{
		window.draw(p->returnSquare());
	}
}

void Map::generatePlaces()
{
	//tworze miejsca pod wiezyczki
	PlaceForTower *p1 = new PlaceForTower(385 * scale, 235 * scale);
	placesForTowers.push_back(p1);
	PlaceForTower *p2 = new PlaceForTower(580 * scale,250 * scale);
	placesForTowers.push_back(p2);
	PlaceForTower *p3 = new PlaceForTower(685 * scale, 250 * scale);
	placesForTowers.push_back(p3);
	PlaceForTower *p4 = new PlaceForTower(885 * scale, 240 * scale);
	placesForTowers.push_back(p4);
	PlaceForTower *p5 = new PlaceForTower(1021 * scale, 242 * scale);
	placesForTowers.push_back(p5);
	PlaceForTower *p6 = new PlaceForTower(1023 * scale, 453 * scale);
	placesForTowers.push_back(p6);
	PlaceForTower* p7 = new PlaceForTower(902 * scale, 627 * scale);
	placesForTowers.push_back(p7);
	PlaceForTower* p8 = new PlaceForTower(906 * scale, 835 * scale);
	placesForTowers.push_back(p8);
	PlaceForTower *p9 = new PlaceForTower(1040 * scale, 835 * scale);
	placesForTowers.push_back(p9);
	PlaceForTower *p10 = new PlaceForTower(1236 * scale, 820 * scale);
	placesForTowers.push_back(p10);
	PlaceForTower *p11 = new PlaceForTower(1346 * scale, 820 * scale);
	placesForTowers.push_back(p11);
	PlaceForTower *p12 = new PlaceForTower(1540 * scale, 840 * scale);
	placesForTowers.push_back(p12);
	PlaceForTower *p13 = new PlaceForTower(1072 * scale, 626 * scale);
	placesForTowers.push_back(p13);
	PlaceForTower* p14 = new PlaceForTower(1222 * scale, 296 * scale);
	placesForTowers.push_back(p14);
	PlaceForTower *p15 = new PlaceForTower(714 * scale, 726 * scale);
	placesForTowers.push_back(p15);
	PlaceForTower *p16 = new PlaceForTower(822 * scale, 445 * scale);
	placesForTowers.push_back(p16);
	PlaceForTower *p17 = new PlaceForTower(693 * scale, 417 * scale);
	placesForTowers.push_back(p17);
	PlaceForTower *p18 = new PlaceForTower(471 * scale, 68 * scale);
	placesForTowers.push_back(p18);
}

std::vector<PlaceForTower*> * Map::returnPlaces()
{
	return &placesForTowers;
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