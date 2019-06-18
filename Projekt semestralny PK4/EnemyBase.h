#pragma once
#include "Enemy.h"

class Enemy;

class EnemyBase
{
private:
	sf::Vector2f position;
	sf::RectangleShape base;
	sf::RenderWindow *window;
	int toSpawn;
	int wave;
	int frame;	//prowizoryczna czestotliwosc tworzenia przeciwnikow
	std::vector<std::shared_ptr<Enemy>> *Enemies;
	int which_type = 1; //na tej podstawie jest wybierany typ przeciwnika

public:
	EnemyBase(sf::RenderWindow *, std::vector<std::shared_ptr<Enemy>>*);
	~EnemyBase();
	void spawnEnemy();
	void setToSpawn(int);
	void drawBase();

	void incrementFrame();
	int returnFrames();
	void resetFrames();

	int returnWave();
	void moveEnemies(float);
	void drawEnemies();
};

