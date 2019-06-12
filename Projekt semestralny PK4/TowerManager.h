#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Tower.h"
#include "PlaceForTower.h"

class TowerManager
{
	std::vector<std::shared_ptr<PlaceForTower>> *placesForTowers;
	std::vector<std::shared_ptr<Tower>> *Towers;
	sf::RenderWindow *window;
	sf::Font ttf;
	sf::Text towerLevel;

	sf::CircleShape buttonX;
	sf::Texture buttonXTexture;
	sf::CircleShape buttonUpgrade;
	sf::Texture buttonUpgradeTexture;
	sf::CircleShape buttonY;
	sf::Texture buttonYTexture;
	sf::CircleShape buttonArrow;
	sf::Texture buttonArrowTexture;
	sf::CircleShape buttonFireball;
	sf::Texture buttonFireballTexture;

	std::shared_ptr<Tower> managedTower;
	std::shared_ptr<PlaceForTower> managedPlace;
public:
	TowerManager(Map*,std::vector<std::shared_ptr<Tower>>*,sf::RenderWindow*);
	~TowerManager();

	bool isPlaceClicked(sf::Vector2f);
	bool isTowerClicked(sf::Vector2f);
	void isNewTowerClicked(sf::Vector2f);
	void nothingClicked();
	void drawMenu();
	void sellTower(std::shared_ptr<Tower>);
	void upgradeTower(std::shared_ptr<Tower>);
	void showTowerLevel(std::shared_ptr<Tower>);
};

