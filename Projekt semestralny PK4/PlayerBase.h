#pragma once
#include <SFML/Graphics.hpp>
#include "EnemyBase.h"

class Enemy;	//potrzebny aby  nie bylo bledu wzajemnego include, do poprawy
class EnemyBase;

class PlayerBase
{
private:
	sf::Vector2f position;
	sf::RectangleShape base;
	std::vector<std::shared_ptr<Enemy>> *Enemies;
	EnemyBase *enemybase;
	sf::RectangleShape playerInfo;
	sf::Texture playerInfoTexture;
	sf::Font ttf;
	sf::Text _points;
	sf::Text _cash;
	sf::Text _lifes;
	sf::Text _speed;
	sf::Text _wave;

	int lifes;
	int speed;
	int wave;
	int points = 0;
	int cash = 0;
	bool start = false;
public:
	PlayerBase(EnemyBase*);
	~PlayerBase();
	void check_if_enemy_in();
	void gameOver(sf::RenderWindow*);
	void drawBase(sf::RenderWindow*);

	void addPoints(int);
	int returnPoints();
	void setPoints(int);

	void addCash(int);
	int returnCash();
	void setCash(int);
	void spendCash(int);

	void setLifes(int);
	void setSpeed(int);
	void setWave();
	void resetWaves();

	void setStart(bool);
	bool getStart();
};

