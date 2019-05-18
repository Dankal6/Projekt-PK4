#pragma once
#include <SFML/Graphics.hpp>
class Bullet
{
private:
	sf::CircleShape bullet;
	sf::Vector2f speed;
public:
	Bullet(sf::Vector2f);
	~Bullet();
	void setSpeed(float, float);
	void move();
	void drawBullet(sf::RenderWindow*);
};

