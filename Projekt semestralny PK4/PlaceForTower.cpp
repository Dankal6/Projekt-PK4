#include "PlaceForTower.h"

int how_many_places = 0;

PlaceForTower::PlaceForTower(int x, int y)
{
	position = sf::Vector2f(x, y);
	placeSize = sf::Vector2f(80 * scale, 80 * scale);
	placeForTowerTexture.loadFromFile("Textures/placeTowerGrass.png");
	placeForTowerTexture.setSmooth(true);
	placeForTower.setSize(placeSize);
	placeForTower.setTexture(&placeForTowerTexture);
	placeForTower.setOrigin(40 * scale, 40 * scale);
	placeForTower.setPosition(x, y);
	occupied = false;

	how_many_places++;
}

PlaceForTower::~PlaceForTower()
{
	how_many_places--;
	std::cout << "Destroy place, remain: " << how_many_places << std::endl;
}

sf::RectangleShape PlaceForTower::returnSquare()
{
	return placeForTower;
}

sf::Vector2f PlaceForTower::returnPosition()
{
	return position;
}

void PlaceForTower::setOccupied(bool x)
{
	this->occupied = x;
}

bool PlaceForTower::isOccupied()
{
	return this->occupied;
}


