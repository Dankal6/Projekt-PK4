#include "Tower.h"

int how_many_towers = 0;

Tower::Tower(sf::RenderWindow *main_window, sf::Vector2f pos, int _type)
{
	window = main_window;
	position = pos;
	type = _type;
	tower.setSize(sf::Vector2f(size - (50 * scale), size));
	tower.setOrigin(((size - (50 * scale)) / 2), (size - (40 * scale)));
	tower.setPosition(position);
	upgradeLevel = 0;

	if (type == 1)
	{
		range.setRadius(range_rad);
		range.setOrigin(range_rad, range_rad);
		towerTexture.loadFromFile("Textures/tower1.png");
		damage = 10;
	}
	else if (type == 2)
	{
		range.setRadius(range_rad - (50 * scale));
		range.setOrigin(range_rad - (50 * scale), range_rad - (50 * scale));
		towerTexture.loadFromFile("Textures/tower2.png");
		damage = 20;
	}

	range.setPosition(position);
	range.setFillColor(sf::Color(50, 50, 50, 128));
	towerTexture.setSmooth(true);
	tower.setTexture(&towerTexture);

	this->frame = 0;
	how_many_towers++;
}


Tower::~Tower()
{
	how_many_towers--;
	std::cout << "Destroy tower, remain: " << how_many_towers << std::endl;
}


void Tower::drawTower()
{
	if (this->showRange == true)
	{
		window->draw(range);
	}
	window->draw(tower);
	this->bullets_out_of_range();	//usuwanie pociskow poza zasiegiem wiezy
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

void Tower::aim(std::shared_ptr<Enemy> to_shoot)
{

	sf::Vector2f enemy_pos = to_shoot->getPosition();
	sf::Vector2f enemy_speed = to_shoot->returnSpeed();
	sf::Vector2f aimDirNorm;
	std::thread the_thread(&Tower::calcaimDirNorm, this, enemy_pos, enemy_speed, this->position, std::ref(aimDirNorm));
	std::shared_ptr<Bullet> bullet;
	if (this->type == 1)
	{
		bullet = std::make_shared<Bullet>(this->position, type);
	}
	else if (this->type == 2)
	{
		bullet = std::make_shared<Bullet>(this->position, type);
	}
	the_thread.join();
	float deg = atan2(aimDirNorm.y, aimDirNorm.x) * 180 / 3.14f;
	bullet->setSpeed(6 * aimDirNorm.x, 6 * aimDirNorm.y);
	bullet->setRotation(deg + 90);
	Bullets.push_back(bullet);
}

std::shared_ptr<Enemy> Tower::check_if_in_range(std::vector<std::shared_ptr<Enemy>> *Enemies)
{
	float d;
	for (auto e : *Enemies)
	{
		sf::Vector2f enemy_pos = e->getPosition();
		if (sqrt(pow(enemy_pos.x - this->position.x, 2) + pow(enemy_pos.y - this->position.y, 2)) < this->range.getRadius())
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

void Tower::setPlace(std::shared_ptr<PlaceForTower> new_place)
{
	place = new_place;
}

std::shared_ptr<PlaceForTower> Tower::getPlace()
{
	return place;
}

void Tower::incrementFrame()
{
	if (type == 2)
		this->frame++;
	else if (type == 1)
		this->frame += 2;
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

void Tower::calcaimDirNorm(sf::Vector2f enemy_pos, sf::Vector2f enemy_speed, sf::Vector2f position, sf::Vector2f &aimDirNorm)
{
	float x = 8;
	sf::Vector2f aimDir = enemy_pos - position + x * enemy_speed;
	float aimVectorMod = sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));
	aimDirNorm = aimDir / aimVectorMod;

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

int Tower::returnRange()
{
	return this->range.getRadius();
}

void Tower::setRange(int x)
{
	this->range.setRadius(range.getRadius() + x);
	this->range.setOrigin(range.getRadius(), range.getRadius());
	this->range.setPosition(this->position);
}

int Tower::returnType()
{
	return this->type;
}

std::vector<std::shared_ptr<Bullet>> *Tower::returnBullets()
{
	return &this->Bullets;
}

void Tower::bullets_out_of_range()
{
	int j = 0;
	for (auto b : Bullets)
	{
		sf::Vector2f bullet_pos = b->returnPosition();
		float x = bullet_pos.x;
		float y = bullet_pos.y;
		if (range.getGlobalBounds().contains(x, y))
		{
			j++;
			continue;
		}
		else
		{
			Bullets.erase(Bullets.begin() + j);
			return;
		}

	}
}
