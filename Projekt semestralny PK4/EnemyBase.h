#pragma once
#include "Enemy.h"

class Enemy;

class EnemyBase
{
private:
	sf::Vector2f position;
	sf::RectangleShape base;
	sf::RenderWindow *window;
	std::vector<std::shared_ptr<Enemy>> *Enemies;
	int toSpawn;
	int wave;
	int frame;	//czestotliwosc tworzenia przeciwnikow
	int which_type = 1; //na tej podstawie jest wybierany typ przeciwnika
public:
	EnemyBase(sf::RenderWindow *, std::vector<std::shared_ptr<Enemy>>*);
	~EnemyBase();
	void spawnEnemy();
	void drawBase();
	void incrementFrame();
	int returnFrames();
	void resetFrames();
	void resetWaves();
	int returnWave();
	void moveEnemies(float);
	void drawEnemies();
	std::vector<std::shared_ptr<Enemy>>* getEnemies();
};

