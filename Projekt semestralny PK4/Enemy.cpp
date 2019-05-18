#include "Enemy.h"



Enemy::Enemy()
{
	enemy.setSize(sf::Vector2f(40.0f, 40.0f));
	enemy.setFillColor(sf::Color::Red);
	enemy.setPosition(sf::Vector2f(60.0f, -10.0f));
	enemy.setOrigin(20, 20);
	this->healthPoint = 60;
}


Enemy::~Enemy()
{
}

void Enemy::drawEnemy(sf::RenderWindow *window)
{
	window->draw(enemy);
}

void Enemy::move()
{
	enemy.move(speed);
}

void Enemy::setSpeed(float x, float y)
{
	this->speed = { x, y };
}

sf::Vector2f Enemy::getPosition()
{
	return enemy.getPosition();
}

sf::Vector2f Enemy::returnSpeed()
{
	return this->speed;
}

bool Enemy::gotHitted(std::vector<Enemy*> *Enemies, std::vector<Bullet*> *Bullets)
{
	int i = 0;
	for (auto e : *Enemies)
	{
	if (e->getPosition() == this->getPosition())
		{
			break;
		}
		i++;
	}

	for (auto b : *Bullets)
	{
		//if (enemy.getGlobalBounds().contains(b->returnPosition))
		sf::Vector2f bullet_pos = b->returnPosition();
		float x = bullet_pos.x;
		float y = bullet_pos.y;
		if (enemy.getGlobalBounds().contains(x, y))
		{
 			this->healthPoint -= 20;
			Bullets->erase(Bullets->begin());
			if (this->healthPoint <= 0)
			{
				Enemies->erase(Enemies->begin() + i);  
				std::cout << "Padl przeciwnik: " << i << ", pozostalo przeciwnikow: " << Enemies->size() << std::endl;
			}
			return true;
		}

	}
} 