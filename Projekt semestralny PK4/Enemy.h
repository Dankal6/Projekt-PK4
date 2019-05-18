#pragma once
#include <SFML/Graphics.hpp>
#include "Bullet.h"
#include <iostream>

class Enemy
{
private:
	sf::Vector2f speed;
	sf::RectangleShape enemy;
	double healthPoint;
public:
	Enemy();
	~Enemy();
	void drawEnemy(sf::RenderWindow*);
	void move();
	void setSpeed(float, float);
	sf::Vector2f returnSpeed();
	sf::Vector2f getPosition();
	bool gotHitted(std::vector<Enemy*> *, std::vector<Bullet*>*);
};

