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
		damage = 5;
	}
	else if (type == 2)
	{
		range.setRadius(range_rad - (50 * scale));
		range.setOrigin(range_rad - (50 * scale), range_rad - (50 * scale));
		towerTexture.loadFromFile("Textures/tower2.png");
		damage = 10;
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
	std::shared_ptr<Bullet> bullet;
	if (this->type == 1)
	{
		bullet = std::make_shared<Bullet>(this->position, type);
	}
	else if (this->type == 2)
	{
		bullet = std::make_shared<Bullet>(this->position, type);
	}
	bullet->setSpeed((enemy_pos.x - this->position.x) / 20 + enemy_speed.x, (enemy_pos.y - this->position.y) / 20 + enemy_speed.y);
	double a = sqrt(pow(enemy_pos.x - this->position.x + enemy_speed.x, 2) + pow(enemy_pos.y - this->position.y, 2));
	double b = sqrt(pow(enemy_pos.x - this->position.x + enemy_speed.x, 2));
	double sin = b / a;
	double rad = asin(sin);
	double degrees = rad * (180.0 / 3.141592653589793238463);
	//przeciwnik po lewej, wyzej
	if ((enemy_pos.x - this->position.x) < 0 && (enemy_pos.y - this->position.y) < 0)
		bullet->setRotation(360 - degrees);
	//przeciwnik po prawej, wyzej
	else if ((enemy_pos.y - this->position.y) < 0 && (enemy_pos.x - this->position.x) > 0)
		bullet->setRotation(degrees);
	//przeciwnik po lewej, nizej
	else if ((enemy_pos.y - this->position.y) > 0 && (enemy_pos.x - this->position.x) < 0)
		bullet->setRotation(180 + degrees);
	//przeciwnik po prawej, nizej
	else
		bullet->setRotation(180 - degrees);
	Bullets.push_back(bullet);
}

std::shared_ptr<Enemy> Tower::check_if_in_range(std::vector<std::shared_ptr<Enemy>> *Enemies)
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
