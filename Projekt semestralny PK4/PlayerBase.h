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
	int lifes;
	int speed;
	int wave;
	std::vector<Enemy*> *Enemies;
	EnemyBase *enemybase;
	int points = 0;
	int cash = 0;
	bool start = false;
	sf::RectangleShape playerInfo;
	sf::Texture playerInfoTexture;
	sf::Font ttf;
	sf::Text _points;
	sf::Text _cash;
	sf::Text _lifes;
	sf::Text _speed;
	sf::Text _wave;
public:
	PlayerBase(EnemyBase*);
	~PlayerBase();
	void check_if_enemy_in();
	void gameOver(sf::RenderWindow*);
	void drawBase(sf::RenderWindow*);

	void setSpeed(int);

	void addPoints(int);
	int returnPoints();
	void setPoints(int);

	void addCash(int);
	int returnCash();
	void setCash(int);
	void spendCash(int);

	void setLifes(int);
	void setWave();

	void setStart(bool);
	bool getStart();
};

