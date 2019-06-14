#pragma once
#include "Scale.h"


class Bullet
{
private:
	sf::RectangleShape bullet;
	sf::Vector2f speed;
	sf::Texture bulletTexture;
	sf::Texture bullet2Texture;
	int damage;
public:
	Bullet(sf::Vector2f,int);
	~Bullet();
	void setSpeed(float, float);
	void setRotation(float);
	void move();
	void drawBullet(sf::RenderWindow*);
	sf::Vector2f returnPosition();

};

