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

void EnemyBase::spawnEnemy(std::vector<std::shared_ptr<Enemy>> *Enemies)
{


	if (this->which_type == 3 || this->which_type == 4 || this->which_type == 6)
	{
		std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>(position, 3, this->wave);
		Enemies->push_back(enemy);
	}
	else if (this->which_type == 5)
	{
		std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>(position, 2, this->wave);
		Enemies->push_back(enemy);
	}
	else if (this->which_type == 7)
	{
		std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>(position, 4, this->wave);
		Enemies->push_back(enemy);
		this->which_type=0;
		this->wave++;
		return;
	}
	else
	{
		std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>(position, 1, this->wave);
		Enemies->push_back(enemy);
	}
	this->which_type++;
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

int EnemyBase::returnWave()
{
	return this->wave;
}
