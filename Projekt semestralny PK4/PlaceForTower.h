#pragma once
#include <SFML/Graphics.hpp>
#include "Scale.h"
#include <iostream>

class PlaceForTower
{
	sf::Texture placeForTowerTexture;
	sf::RectangleShape placeForTower;
	sf::Vector2f placeSize;
	bool occupied;
public:
	PlaceForTower(int,int);
	~PlaceForTower();
	sf::RectangleShape returnSquare();
	void setOccupied(bool);
	bool isOccupied();
};

