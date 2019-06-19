#pragma once
#include "Tower.h"
#include "PlayerBase.h"
#include "Animation.h"
#include "Scale.h"

class PlayerBase;	//potrzebny aby  nie bylo bledu wzajemnego include, do poprawy
class Tower;

class Enemy
{
private:
	sf::Vector2f speed;
	sf::RectangleShape enemy;
	sf::RectangleShape healthBar;
	sf::Texture enemyTexture;
	Animation *animation;
	static std::thread the_thread;
	double healthPoint;
	double healthPointLeft;
	int type;
public:
	Enemy(sf::Vector2f,int,int);
	~Enemy();
	void drawEnemy(sf::RenderWindow&);
	void move(float);
	void checkToTurn();
	void setSpeed(float, float);
	sf::Vector2f returnSpeed();
	sf::Vector2f getPosition();
	bool gotHitted(std::vector<std::shared_ptr<Enemy>> *, std::shared_ptr<Tower>,PlayerBase*);
	double returnHealthAsPercent();
	int returnType();
	void loadTextures(int,int);
};

