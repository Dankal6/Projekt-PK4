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
	int cash = 0;
	sf::RectangleShape playerInfo;
	sf::Texture playerInfoTexture;
	sf::Font ttf;
	sf::Text _points;
	sf::Text _cash;
	sf::Text _lifes;
public:
	PlayerBase(sf::Vector2f);
	~PlayerBase();
	void check_if_enemy_in(std::vector<std::shared_ptr<Enemy>> *);
	void gameOver(sf::RenderWindow*);
	void drawBase(sf::RenderWindow*);

	void addPoints(int);
	int returnPoints();
	void setPoints(int);

	void addCash(int);
	int returnCash();
	void setCash(int);
	void spendCash(int);

	void setLifes(int);
};

