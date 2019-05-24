#pragma once
#include <SFML/Graphics.hpp>

class Map
{
private:
	int level;
	sf::RectangleShape map;
	std::vector<sf::RectangleShape*> placesForTowers;
	sf::Texture mapTexture;
	sf::Vector2f placeSize;
	//kwadrat ma miec wymiary 40x40, co daje nam tablice kwadratow przy fullhd 48x27
	std::vector<sf::RectangleShape> squares;

public:
	Map();
	~Map();
	void drawMap(sf::RenderWindow&);
	//do wykorzystania przy algorytmie wyszukiwania drogi
	//void initMapAsSquares();
	//void drawMapAsSquares(sf::RenderWindow&);
};

