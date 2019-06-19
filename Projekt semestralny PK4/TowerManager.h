#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Tower.h"
#include "PlaceForTower.h"
#include "PlayerBase.h"

class TowerManager
{
	std::vector<std::shared_ptr<PlaceForTower>> *placesForTowers;
	std::vector<std::shared_ptr<Tower>> *Towers;
	std::vector<std::shared_ptr<Enemy>> *Enemies;
	PlayerBase *player;
	sf::RenderWindow *window;
	std::thread the_thread;
	std::thread the_thread2;
	std::thread the_thread3;
	std::thread the_thread4;
	std::thread the_thread5;
	std::thread the_thread6;
	std::thread the_thread7;
	sf::Font ttf;
	sf::Text towerLevel;
	sf::Text towerDmg;
	sf::Text towerRange;
	sf::Text arrowCost;
	sf::Text fireballCost;
	sf::Text arrowUpgradeCost;
	sf::Text fireballUpgradeCost;
	sf::Text arrowSell;
	sf::Text fireballSell;


	sf::CircleShape buttonX;
	sf::Texture buttonXTexture;
	sf::CircleShape buttonUpgrade;
	sf::Texture buttonUpgradeTexture;
	sf::CircleShape buttonY;
	sf::Texture buttonYTexture;
	sf::RectangleShape buttonArrow;
	sf::Texture buttonArrowTexture;
	sf::RectangleShape buttonFireball;
	sf::Texture buttonFireballTexture;

	sf::RectangleShape towerInfo;
	sf::Texture towerInfoTexture;

	std::shared_ptr<Tower> managedTower;
	std::shared_ptr<PlaceForTower> managedPlace;
public:
	TowerManager(Map*,std::vector<std::shared_ptr<Tower>>*,sf::RenderWindow*,PlayerBase*, std::vector<std::shared_ptr<Enemy>>*);
	~TowerManager();

	bool isPlaceClicked(sf::Vector2f);
	bool isTowerClicked(sf::Vector2f);
	void isNewTowerClicked(sf::Vector2f);
	void nothingClicked();
	void drawMenu();
	void sellTower(std::shared_ptr<Tower>);
	void upgradeTower(std::shared_ptr<Tower>);
	void showTowerInfo(std::shared_ptr<Tower>);
	void shooting();
	void drawTowers();
	void incrementFrames();
	void loadTexturesAndFont();
	void loadXTexture();
	void loadUpgradeTexture();
	void loadYTexture();
	void loadBowTexture();
	void loadFireballTexture();
	void loadInfoTowerTexture();
	void loadFont();
};

