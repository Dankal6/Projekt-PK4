#pragma once
#include <SFML/Graphics.hpp>
#include "Enemy.h"

class EnemyBase
{
private:
	sf::Vector2f position;
	int toSpawn;
	int frame;	//prowizoryczna czestotliwosc tworzenia przeciwnikow
	std::vector<Enemy*> Enemies;

public:
	EnemyBase(sf::Vector2f);
	~EnemyBase();
	void spawnEnemy(std::vector<Enemy*>*);
	void setToSpawn(int);

	void incrementFrame();
	int returnFrames();
	void resetFrames();
};

