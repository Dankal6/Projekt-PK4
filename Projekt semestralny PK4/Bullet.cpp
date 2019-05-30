#include "Bullet.h"



Bullet::Bullet(sf::Vector2f pos)
{
	bullet.setRadius(5);
	bullet.setFillColor(sf::Color::Yellow);
	bullet.setPosition(pos);
}


Bullet::~Bullet()
{
}

void Bullet::setSpeed(float x, float y)
{
	this->speed = { x,y };
}

void Bullet::move()
{
	bullet.move(speed);
}

void Bullet::drawBullet(sf::RenderWindow* window)
{
	window->draw(bullet);
}

sf::Vector2f Bullet::returnPosition()
{
	return this->bullet.getPosition();
}
