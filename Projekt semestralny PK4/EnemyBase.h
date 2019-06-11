#pragma once
#include <SFML/Graphics.hpp>
#include "Enemy.h"

class EnemyBase
{
private:
	sf::Vector2f position;
	sf::RectangleShape base;
	int toSpawn;
	int frame;	//prowizoryczna czestotliwosc tworzenia przeciwnikow
	std::vector<std::shared_ptr<Enemy>> Enemies;

public:
	EnemyBase(sf::Vector2f);
	~EnemyBase();
	void spawnEnemy(std::vector<std::shared_ptr<Enemy>>*);
	void setToSpawn(int);
	void drawBase(sf::RenderWindow&);

	void incrementFrame();
	int returnFrames();
	void resetFrames();
};

