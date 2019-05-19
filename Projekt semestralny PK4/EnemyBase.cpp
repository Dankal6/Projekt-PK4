#include "EnemyBase.h"



EnemyBase::EnemyBase(sf::Vector2f pos)
{
	position = pos;
	frame = 0;
}


EnemyBase::~EnemyBase()
{
}

void EnemyBase::spawnEnemy(std::vector<Enemy*>*Enemies)
{
	if(this->toSpawn>0)
	{
		Enemy *enemy = new Enemy(position);
		enemy->setSpeed(0, 2);
		Enemies->push_back(enemy);
		this->toSpawn--;
	}
	
}

void EnemyBase::setToSpawn(int x)
{
	this->toSpawn = x;
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