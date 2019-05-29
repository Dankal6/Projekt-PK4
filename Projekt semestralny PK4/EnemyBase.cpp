#include "EnemyBase.h"



EnemyBase::EnemyBase(sf::Vector2f pos)
{
	position = pos;
	frame = 0;

	base.setSize(sf::Vector2f(60.0f*scale, 60.0f*scale));
	base.setFillColor(sf::Color::Red);
	base.setPosition(pos);
	base.setOrigin(30 * scale, 30 * scale);
}


EnemyBase::~EnemyBase()
{
}

void EnemyBase::spawnEnemy(std::vector<Enemy*>*Enemies)
{
	if(this->toSpawn>0)
	{
		Enemy *enemy = new Enemy(position);
		Enemies->push_back(enemy);
		this->toSpawn--;
	}
	
}

void EnemyBase::setToSpawn(int x)
{
	this->toSpawn = x;
}

void EnemyBase::drawBase(sf::RenderWindow & window)
{
	window.draw(base);
}

void EnemyBase::incrementFrame()
{
	this->frame++;
}

int EnemyBase::returnFrames()
{
	return this->frame;
}

void EnemyBase::resetFrames()
{
	this->frame = 0;
}