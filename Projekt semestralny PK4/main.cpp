#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

#include <thread>
#include <iostream>
#include "Enemy.h"
#include "Tower.h"

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

	int frame = 0;
	bool fire = false;
	bool start = false;
	bool placing_tower = false;
	sf::Clock clock;


	vector<Tower*> Towers;
	vector<Enemy*> Enemies;



	while (window.isOpen())
	{
		frame++;
		window.clear();
		window.setKeyRepeatEnabled(false);

		for (auto t : Towers)
		{
			t->incrementFrame();
		}


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
				Enemy *enemy = new Enemy;
				enemy->setSpeed(0, 2);
				Enemies.push_back(enemy);
			}
		}
		//modul tworzenia wiezy
		if (placing_tower)
		{
			placeTower(&window, &Towers, &Enemies);
			placing_tower = false;
		}
		//rysowanie wiez
		for (auto t : Towers)
		{
			t->drawTower();
			Enemy *enemy_to_shoot=t->check_if_in_range(&Enemies);
			if (enemy_to_shoot != NULL)
			{
				if (t->returnFrames() >= 10)
				{
					t->shoot(enemy_to_shoot);
					t->resetFrames();
				}
			}
			for (auto e : Enemies)
			{
				e->gotHitted(&Enemies, t->returnBullets());
			}
			//rysowanie pociskow
			t->drawBullets();
		}

		//start gry, przeciwnik rusza
		if (start)
		{
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
				if (enemy_pos.x == 1900)
				{
					e->setSpeed(0, -2);
				}
			}
		}

		window.display();



		//zabawa z czasem
		{
			sf::Time time = clock.getElapsedTime();
			float t = time.asSeconds();
			if (t > 4)
			{
				cout << frame << endl;
				clock.restart();
				//frame = 0;
			}
		}

	}

	return 0;
}