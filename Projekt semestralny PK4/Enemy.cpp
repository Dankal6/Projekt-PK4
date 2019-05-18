#include "Enemy.h"



Enemy::Enemy()
{
	enemy.setSize(sf::Vector2f(40.0f, 40.0f));
	enemy.setFillColor(sf::Color::Red);
	enemy.setPosition(sf::Vector2f(60.0f, -10.0f));
	enemy.setOrigin(20, 20);
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