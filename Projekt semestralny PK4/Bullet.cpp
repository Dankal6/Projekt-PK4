#include "Bullet.h"

//sprawdzanie wyciekow pamieci
int how_many_bullets = 0;

Bullet::Bullet(sf::Vector2f pos,int type)
{

	bullet.setPosition(pos);

	if (type == 1)
	{
		bulletTexture.loadFromFile("Textures/arrow.png");
		bullet.setSize(sf::Vector2f(10.0f*scale, 35.0f*scale));
	}
	else if (type == 2)

	{
		bulletTexture.loadFromFile("Textures/fireball.png");
		bullet.setSize(sf::Vector2f(20.0f*scale, 20.0f*scale));
	}

	bulletTexture.setSmooth(true);
	bullet.setTexture(&bulletTexture);
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

void Bullet::setRotation(float x)
{
	bullet.setRotation(x);
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
