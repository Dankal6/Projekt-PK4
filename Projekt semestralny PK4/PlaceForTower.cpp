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

	/*
	sf::RectangleShape* p1 = new sf::RectangleShape;
	p1->setPosition(385, 235);
	placesForTowers.push_back(p1);

	sf::RectangleShape *p2 = new sf::RectangleShape;
	p2->setPosition(580, 250);
	placesForTowers.push_back(p2);

	sf::RectangleShape *p3 = new sf::RectangleShape;
	p3->setPosition(685, 250);
	placesForTowers.push_back(p3);

	sf::RectangleShape *p4 = new sf::RectangleShape;
	p4->setPosition(885, 240);
	placesForTowers.push_back(p4);

	sf::RectangleShape *p5 = new sf::RectangleShape;
	p5->setPosition(1021, 242);
	placesForTowers.push_back(p5);

	sf::RectangleShape *p6 = new sf::RectangleShape;
	p6->setPosition(1023, 453);
	placesForTowers.push_back(p6);

	sf::RectangleShape* p7 = new sf::RectangleShape;
	p7->setPosition(902, 627);
	placesForTowers.push_back(p7);

	sf::RectangleShape* p8 = new sf::RectangleShape;
	p8->setPosition(906, 835);
	placesForTowers.push_back(p8);

	sf::RectangleShape *p9 = new sf::RectangleShape;
	p9->setPosition(1040, 835);
	placesForTowers.push_back(p9);

	sf::RectangleShape *p10 = new sf::RectangleShape;
	p10->setPosition(1236, 820);
	placesForTowers.push_back(p10);

	sf::RectangleShape *p11 = new sf::RectangleShape;
	p11->setPosition(1346, 820);
	placesForTowers.push_back(p11);

	sf::RectangleShape *p12 = new sf::RectangleShape;
	p12->setPosition(1540, 840);
	placesForTowers.push_back(p12);

	sf::RectangleShape *p13 = new sf::RectangleShape;
	p13->setPosition(1072, 626);
	placesForTowers.push_back(p13);

	sf::RectangleShape* p14 = new sf::RectangleShape;
	p14->setPosition(1222, 296);
	placesForTowers.push_back(p14);

	sf::RectangleShape *p15 = new sf::RectangleShape;
	p15->setPosition(714, 726);
	placesForTowers.push_back(p15);

	sf::RectangleShape *p16 = new sf::RectangleShape;
	p16->setPosition(822, 445);
	placesForTowers.push_back(p16);

	sf::RectangleShape *p17 = new sf::RectangleShape;
	p17->setPosition(693, 417);
	placesForTowers.push_back(p17);

	sf::RectangleShape *p18 = new sf::RectangleShape;
	p18->setPosition(471, 68);
	placesForTowers.push_back(p18);
	*/

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


