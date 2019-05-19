#pragma once
#include <SFML/Graphics.hpp>
#include "Bullet.h"
#include "PlayerBase.h"
#include <iostream>

class PlayerBase;	//potrzebny aby  nie bylo bledu wzajemnego include, do poprawy

class Enemy
{
private:
	sf::Vector2f speed;
	sf::RectangleShape enemy;
	double healthPoint;
public:
	Enemy(sf::Vector2f);
	~Enemy();
	void drawEnemy(sf::RenderWindow*);
	void move();
	void setSpeed(float, float);
	sf::Vector2f returnSpeed();
	sf::Vector2f getPosition();
	bool gotHitted(std::vector<Enemy*> *, std::vector<Bullet*>*,PlayerBase*);
};

