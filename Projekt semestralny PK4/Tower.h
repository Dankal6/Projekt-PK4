#pragma once
#include "Enemy.h"
#include "Bullet.h"
#include "Scale.h"
#include "PlaceForTower.h"

class Enemy;	//potrzebny aby  nie bylo bledu wzajemnego include, do poprawy

class Tower
{
private:
	sf::RectangleShape tower;
	sf::CircleShape range;
	sf::Vector2f position;
	sf::RenderWindow *window;
	std::vector<std::shared_ptr<Bullet>> Bullets;
	std::thread the_thread;
	sf::Texture towerTexture;
	sf::Texture tower2Texture;
	std::shared_ptr<PlaceForTower> place;
	int type;
	int size = 130 * scale;
	int range_rad = 200 * scale;
	bool is_builded = false;
	int showRange = false;
	int damage;
	int upgradeLevel;
	int frame;	//czestotliwosc strzelania dla kazdej z wiezyczek
public:
	Tower(sf::RenderWindow*,sf::Vector2f,int);
	~Tower();
	void drawTower();
	void drawRange(bool);
	void shoot();
	void aim(std::shared_ptr<Enemy>);
	std::vector<std::shared_ptr<Bullet>> *returnBullets();
	void bullets_out_of_range();
	std::shared_ptr<Enemy> check_if_in_range(std::vector<std::shared_ptr<Enemy>>*);
	bool isClicked(sf::Vector2f);
	sf::Vector2f returnPosition();
	void setPlace(std::shared_ptr<PlaceForTower>);
	std::shared_ptr<PlaceForTower> getPlace();

	int returnDamage();
	void setDamage(int);
	int returnLevel();
	void setLevel(int);
	int returnRange();
	void setRange(int);
	int returnType();

	void incrementFrame();
	int returnFrames();
	void resetFrames();
	sf::RectangleShape* returnTower();

	void actionWithTower();
	void calcaimDirNorm(sf::Vector2f, sf::Vector2f, sf::Vector2f, sf::Vector2f&);
};


