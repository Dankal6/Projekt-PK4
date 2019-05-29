#pragma once
#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include "Bullet.h"
#include <math.h>
#include "Scale.h"

#include <iostream>

class Tower
{
private:
	sf::RectangleShape tower;
	sf::CircleShape range;
	sf::Vector2f position;
	sf::RenderWindow *window;
	std::vector<Bullet*> Bullets;
	sf::Texture towerTexture;
	int size = 140 * scale;
	int range_rad = 200 * scale;
	bool is_builded = false;
	int frame;	//prowizoryczna czestotliwosc strzelania dla kazdej z wiezyczek
public:
	Tower(sf::RenderWindow*,sf::Vector2f);
	~Tower();
	void drawTower();
	void drawBullets();
	void shoot(Enemy*);
	Enemy* check_if_in_range(std::vector<Enemy*>*);
	bool isClicked(sf::Vector2f);

	std::vector<Bullet*> *returnBullets();
	void incrementFrame();
	int returnFrames();
	void resetFrames();
	sf::RectangleShape* returnTower();

	void actionWithTower();
};


