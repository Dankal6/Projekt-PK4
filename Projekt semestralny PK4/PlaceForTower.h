#pragma once
#include "Scale.h"

class PlaceForTower
{
	sf::RectangleShape placeForTower;
	sf::Texture placeForTowerTexture;
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

