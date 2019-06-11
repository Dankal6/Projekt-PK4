#include "Bullet.h"

//sprawdzanie wyciekow pamieci
int how_many_bullets = 0;

Bullet::Bullet(sf::Vector2f pos)
{
	bullet.setRadius(5);
	bullet.setFillColor(sf::Color::Yellow);
	bullet.setPosition(pos);
	how_many_bullets++;
}


Bullet::~Bullet()
{
	how_many_bullets--;
	std::cout << "Destroy bullet, remain: " << how_many_bullets << std::endl;
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
