#pragma once
#include <SFML/Graphics.hpp>
#include "Scale.h"
#include <iostream>

class PlaceForTower
{
	sf::Texture placeForTowerTexture;
	sf::RectangleShape placeForTower;
	sf::Vector2f placeSize;
	sf::Vector2f position;
	bool occupied;
public:
	PlaceForTower(int,int);
	~PlaceForTower();
	sf::RectangleShape returnSquare();
	sf::Vector2f returnPosition();
	void setOccupied(bool);
	bool isOccupied();
};

