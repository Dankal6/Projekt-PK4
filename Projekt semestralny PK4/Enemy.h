#pragma once
#include <SFML/Graphics.hpp>

class Enemy
{
private:
	sf::Vector2f speed;
	sf::RectangleShape enemy;
public:
	Enemy();
	~Enemy();
	void drawEnemy(sf::RenderWindow*);
	void move();
	void setSpeed(float, float);
	sf::Vector2f getPosition();
};

