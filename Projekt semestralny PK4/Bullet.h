#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Scale.h"


class Bullet
{
private:
	sf::RectangleShape bullet;
	sf::Vector2f speed;
	sf::Texture bulletTexture;
	int damage;
public:
	Bullet(sf::Vector2f);
	~Bullet();
	void setSpeed(float, float);
	void setRotation(float);
	void move();
	void drawBullet(sf::RenderWindow*);
	sf::Vector2f returnPosition();

};

