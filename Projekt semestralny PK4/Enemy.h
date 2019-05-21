#pragma once
#include <SFML/Graphics.hpp>
#include "Bullet.h"
#include "PlayerBase.h"
#include <iostream>
#include "Animation.h"

class PlayerBase;	//potrzebny aby  nie bylo bledu wzajemnego include, do poprawy

class Enemy
{
private:
	sf::Vector2f speed;
	sf::RectangleShape enemy;
	sf::Vector2f position;
	sf::RectangleShape healthBar;
	double healthPoint;
	double healthPointLeft;
	sf::Texture enemyTexture;
	Animation *animation;
public:
	Enemy(sf::Vector2f);
	~Enemy();
	void drawEnemy(sf::RenderWindow&);
	void move(float);
	void setSpeed(float, float);
	sf::Vector2f returnSpeed();
	sf::Vector2f getPosition();
	bool gotHitted(std::vector<Enemy*> *, std::vector<Bullet*>*,PlayerBase*);
	double returnHealthAsPercent();
};

