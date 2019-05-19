#pragma once
#include <SFML/Graphics.hpp>
#include "Enemy.h"

class Enemy;	//potrzebny aby  nie bylo bledu wzajemnego include, do poprawy

class PlayerBase
{
private:
	sf::Vector2f position;
	sf::RectangleShape base;
	int lifes;
	std::vector<Enemy*> *Enemies;
	int points = 0;
public:
	PlayerBase(sf::Vector2f);
	~PlayerBase();
	void check_if_enemy_in(std::vector<Enemy*> *);
	void gameOver(sf::RenderWindow*);
	void drawBase(sf::RenderWindow*);
	void addPoints(int);
	int returnPoints();
};

