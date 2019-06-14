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
	//kwadrat ma miec wymiary 40x40, co daje nam tablice kwadratow przy fullhd 48x27
	std::vector<sf::RectangleShape> squares;

public:
	Map();
	~Map();
	void drawMap(sf::RenderWindow&);
	void generatePlaces();
	bool setMapTexture();
	std::vector<std::shared_ptr<PlaceForTower>> *returnPlaces();
	//do wykorzystania przy algorytmie wyszukiwania drogi
	//void initMapAsSquares();
	//void drawMapAsSquares(sf::RenderWindow&);
};

