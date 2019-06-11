#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Bullet
{
private:
	sf::CircleShape bullet;
	sf::Vector2f speed;
	int damage;
public:
	Bullet(sf::Vector2f);
	~Bullet();
	void setSpeed(float, float);
	void move();
	void drawBullet(sf::RenderWindow*);
	sf::Vector2f returnPosition();

};

