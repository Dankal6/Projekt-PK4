#include "EnemyBase.h"



EnemyBase::EnemyBase(sf::RenderWindow *_window,std::vector<std::shared_ptr<Enemy>>*_Enemies)
{
	position = sf::Vector2f(-20.0f*scale, 145.0f*scale);
	frame = 0;
	Enemies = _Enemies;
	window = _window;

	base.setSize(sf::Vector2f(60.0f*scale, 60.0f*scale));
	base.setFillColor(sf::Color::Red);
	base.setPosition(position);
	base.setOrigin(30 * scale, 30 * scale);
}


EnemyBase::~EnemyBase()
{
}

void EnemyBase::spawnEnemy()
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

void EnemyBase::drawBase()
{
	window->draw(base);
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

void EnemyBase::moveEnemies(float deltaTime)
{
	for (auto e : *Enemies)
	{
		e->move(deltaTime);
	}
}

void EnemyBase::drawEnemies()
{
	//rysowanie przeciwnikow
	for (auto e : *Enemies)
	{
		e->drawEnemy(*window);
	}
}
