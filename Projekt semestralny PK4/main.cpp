#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

#include <thread>
#include <iostream>
#include "Enemy.h"
#include "Tower.h"
#include "EnemyBase.h"
#include "PlayerBase.h"
#include "Map.h"
#include "TowerManager.h"

using namespace std;

int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "TD");
	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(false);

	sf::Clock clock;
	float deltaTime;

	int frame = 0;
	bool start = false;
	bool placing_tower = false;

	vector<Tower*> Towers;
	vector<Enemy*> Enemies;
	Map map;
	EnemyBase enemybase(sf::Vector2f(-20.0f, 145.0f));
	PlayerBase playerbase(sf::Vector2f(1940.0f, 920.0f));
	TowerManager towermanager(&map, &Towers,&window);



	while (window.isOpen())
	{
		std::cout << sf::Mouse::getPosition(window).x << ";" << sf::Mouse::getPosition(window).y << endl;
		deltaTime = clock.restart().asSeconds();
		window.clear();
		frame++;
		map.drawMap(window);

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
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
			{
				sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition(window);
				towermanager.isPlaceClicked(mousePos);
 				towermanager.isTowerClicked(mousePos);
			}
			//Tworze nowego przeciwnika
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1))
			{
				window.setFramerateLimit(60);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2))
			{
				window.setFramerateLimit(120);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3))
			{
				window.setFramerateLimit(240);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad0))
			{
				window.setFramerateLimit(0);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				start = true;
				enemybase.setToSpawn(5);
				//prowizoryczne poki co wyswietlanie Start
				sf::Font ttf;
				ttf.loadFromFile("fonts/font.ttf");
				std::string s("Start");
				sf::Text txt(s, ttf);
				txt.setCharacterSize(150);
				txt.setFillColor(sf::Color::Red);
				txt.setPosition(1000, 40);
				window.draw(txt);
			}
		}
		//rysowanie bazy gracza
		playerbase.drawBase(&window);
		enemybase.drawBase(window);
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
				e->move(deltaTime);
				e->drawEnemy(window);
			}
		}
		window.display();
	}

	return 0;
}