#include "Tower.h"



Tower::Tower(sf::RenderWindow *main_window, sf::Vector2f pos)
{
	window = main_window;
	position = pos;
	tower.setSize(sf::Vector2f(size, size));
	tower.setOrigin((size/2), (size-(40*scale)));
	tower.setPosition(position);
	damage = 5;
	upgradeLevel = 0;

	range.setRadius(range_rad);
	range.setOrigin(range_rad, range_rad);
	range.setPosition(position);
	range.setFillColor(sf::Color(50, 50, 50, 128));

	towerTexture.loadFromFile("Textures/tower1.png");
	tower.setTexture(&towerTexture);

	this->frame = 0;
}


Tower::~Tower()
{
}


void Tower::drawTower()
{
	if (this->showRange == true)
	{
		window->draw(range);
	}
	window->draw(tower);
	for (auto b : Bullets)
	{
		b->drawBullet(window);
	}
}

void Tower::drawRange(bool x)
{
	this->showRange = x;
}

void Tower::shoot()
{
	for (auto b : Bullets)
	{
		b->move();
	}
}

void Tower::aim(Enemy *to_shoot)
{

	sf::Vector2f enemy_pos = to_shoot->getPosition();
	sf::Vector2f enemy_speed = to_shoot->returnSpeed();
	Bullet *bullet = new Bullet(this->position);
	bullet->setSpeed((enemy_pos.x - this->position.x) / 30 + enemy_speed.x, (enemy_pos.y - this->position.y) / 30 + enemy_speed.y);
	//std::cout << "Predkosc pocisku x: " << (enemy_pos.x - this->position.x) / 50 <<
	//	" y : " << (enemy_pos.y - this->position.y) / 50 << std::endl;
	Bullets.push_back(bullet);
}

Enemy* Tower::check_if_in_range(std::vector<Enemy*> *Enemies)
{
	float d;


	for (auto e : *Enemies)
	{
		sf::Vector2f enemy_pos = e->getPosition();
		if (sqrt(pow(enemy_pos.x - this->position.x, 2) + pow(enemy_pos.y - this->position.y, 2)) < this->range_rad)
			return e;
	}
	return NULL;
}

bool Tower::isClicked(sf::Vector2f mousePosition)
{
	if (this->tower.getGlobalBounds().contains(mousePosition))
	{
		return true;
	}
	else
	{
		return false;
	}
}

sf::Vector2f Tower::returnPosition()
{
	return position;
}

void Tower::setPlace(PlaceForTower * new_place)
{
	place = new_place;
}

PlaceForTower * Tower::getPlace()
{
	return place;
}

void Tower::incrementFrame()
{
	this->frame++;
}

int Tower::returnFrames()
{
	return this->frame;
}

void Tower::resetFrames()
{
	this->frame = 0;
}

sf::RectangleShape * Tower::returnTower()
{
	return &this->tower;
}

void Tower::actionWithTower()
{
	this->tower.setFillColor(sf::Color::Red);
}

int Tower::returnDamage()
{
	return damage;
}

void Tower::setDamage(int x)
{
	damage = x;
}

int Tower::returnLevel()
{
	return upgradeLevel;
}

void Tower::setLevel(int x)
{
	upgradeLevel = x;
}

std::vector<Bullet*> *Tower::returnBullets()
{
	return &this->Bullets;
}