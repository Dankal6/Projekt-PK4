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
	sf::Font ttf;
	sf::Text towerLevel;

	sf::CircleShape buttonX;
	sf::Texture buttonXTexture;
	sf::CircleShape buttonUpgrade;
	sf::Texture buttonUpgradeTexture;
	sf::CircleShape buttonY;
	sf::Texture buttonYTexture;
	Tower* managedTower;
public:
	TowerManager(Map*,std::vector<Tower*>*, sf::RenderWindow*);
	~TowerManager();

	bool isPlaceClicked(sf::Vector2f);
	bool isTowerClicked(sf::Vector2f);
	void nothingClicked();
	void drawMenu();
	void sellTower(Tower*);
	void upgradeTower(Tower*);
	void showTowerLevel(Tower*);
};

