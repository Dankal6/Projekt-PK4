#pragma once
#include "PlaceForTower.h"
#include "Scale.h"

class Map
{
private:
	int level;
	sf::RectangleShape map;
	std::vector<std::shared_ptr<PlaceForTower>> placesForTowers;
	sf::Texture mapTexture;
	std::vector<sf::RectangleShape> squares;

public:
	Map();
	~Map();
	void drawMap(sf::RenderWindow&);
	void generatePlaces();
	void setMapTexture();
	std::vector<std::shared_ptr<PlaceForTower>> *returnPlaces();
};

