#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Tower.h"
#include "PlaceForTower.h"

class TowerManager
{
	std::vector<PlaceForTower*> *placesForTowers;
	std::vector<Tower*> *Towers;
	sf::RenderWindow *window;
public:
	TowerManager(Map*,std::vector<Tower*>*, sf::RenderWindow*);
	~TowerManager();

	void isPlaceClicked(sf::Vector2f);
	void isTowerClicked(sf::Vector2f);
};

