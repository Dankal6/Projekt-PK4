#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

#include <thread>
#include <iostream>
#include "Enemy.h"
#include "Tower.h"
#include "EnemyBase.h"
#include "PlayerBase.h"

using namespace std;

void placeTower(sf::RenderWindow *window, vector<Tower*> *Towers, vector<Enemy*> *Enemies)
{
	bool clicked = false;
	sf::Event e;
	while (clicked == false)
	{
		window->clear();
		window->pollEvent(e);

		//sprawdzam co sie zmienilo


		float x = sf::Mouse::getPosition(*window).x;
		float y = sf::Mouse::getPosition(*window).y;
		sf::Vector2f pos = { x,y };
		Tower temp(window, pos);
		temp.drawTower();

		//Odtwarzanie dotychczasowych przeciwnikow na mapie
		for (auto e : *Enemies)
		{
			e->drawEnemy(window);
		}
		//Odtwarzanie dotychczasowych wiez na mapie
		for (auto e : *Towers)
		{
			e->drawTower();
		}
		window->display();
		if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left)
		{
			clicked = true;
		}
		if (e.type == sf::Event::Closed || (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)))
		{
			window->close();
		}
	}
	float x = sf::Mouse::getPosition(*window).x;
	float y = sf::Mouse::getPosition(*window).y;
	sf::Vector2f pos = { x,y };
	Tower *tower = new Tower(window, pos);
	Towers->push_back(tower);
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!");
	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(false);

	int frame = 0;
	bool start = false;
	bool placing_tower = false;

	vector<Tower*> Towers;
	vector<Enemy*> Enemies;
	EnemyBase enemybase(sf::Vector2f(560.0f, -10.0f));
	PlayerBase playerbase(sf::Vector2f(560.0f, 500.0f));


	while (window.isOpen())
	{
		window.clear();
		frame++;

		//czesc odpowiedzialna za czestotliwosc pojawiania sie przeciwnika, oraz pociskow
		for (auto t : Towers)
		{
			t->incrementFrame();
		}
		enemybase.incrementFrame();

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)))
			{
				window.close();
			}
			//Wyrazam chec stworzenia nowej wiezy
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				placing_tower = true;
			}
			//Tworze nowego przeciwnika
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				start = true;
				enemybase.setToSpawn(5);
			}
		}
		//modul tworzenia wiezy
		if (placing_tower)
		{
			placeTower(&window, &Towers, &Enemies);
			placing_tower = false;
		}
		//rysowanie bazy gracza
		playerbase.drawBase(&window);
		playerbase.check_if_enemy_in(&Enemies);
		//rysowanie wiez
		for (auto t : Towers)
		{
			t->drawTower();
			//sprawdzanie, czy jakis przecinik jest w zasiegu
			Enemy *enemy_to_shoot = t->check_if_in_range(&Enemies);
			if (enemy_to_shoot != NULL)
			{
				if (t->returnFrames() >= 10)
				{
					//wystrzal
					t->shoot(enemy_to_shoot);
					t->resetFrames();
				}
			}
			//sprawdzanie, czy przeciwnik zostal trafiony
			for (auto e : Enemies)
			{
				e->gotHitted(&Enemies, t->returnBullets(),&playerbase);
			}
		}
		//rysowanie pociskow, w osobnej petli, aby byly narysowane "na" wiezach
		for (auto t : Towers)
		{
			t->drawBullets();
		}

		//start gry, przeciwnik rusza
		if (start)
		{
			if (enemybase.returnFrames() >= 30)
			{
				enemybase.spawnEnemy(&Enemies);
				enemybase.resetFrames();
			}

			for (auto e : Enemies)
			{
				e->move();
				e->drawEnemy(&window);
			}
			//zmiana kierunku ruchu przeciwnika
			for (auto e : Enemies)
			{
				sf::Vector2f enemy_pos = e->getPosition();
				if (enemy_pos.y == 850)
				{
					e->setSpeed(2, 0);
				}
				if (enemy_pos.x == 1800)
				{
					e->setSpeed(0, -2);
				}
			}
		}

		window.display();
	}

	return 0;
}