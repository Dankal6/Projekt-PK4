#pragma once
#include "Enemy.h"

class Enemy;

class EnemyBase
{
private:
	sf::Vector2f position;
	sf::RectangleShape base;
	int toSpawn;
	int wave;
	int frame;	//prowizoryczna czestotliwosc tworzenia przeciwnikow
	std::vector<std::shared_ptr<Enemy>> Enemies;
	int which_type = 1; //na tej podstawie jest wybierany typ przeciwnika

public:
	EnemyBase(sf::Vector2f);
	~EnemyBase();
	void spawnEnemy(std::vector<std::shared_ptr<Enemy>>*);
	void setToSpawn(int);
	void drawBase(sf::RenderWindow&);

	void incrementFrame();
	int returnFrames();
	void resetFrames();

	int returnWave();
};

