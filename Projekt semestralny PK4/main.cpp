#include "Enemy.h"
#include "Tower.h"
#include "EnemyBase.h"
#include "PlayerBase.h"
#include "Map.h"
#include "TowerManager.h"
#include "Scale.h"
#include "Menu.h"

using namespace std;


int main()
{
	sf::RenderWindow window(sf::VideoMode(1920*scale, 1080*scale), "Projekt PK4 Daniel Kaleta");
	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(false);

	sf::Clock clock;
	float deltaTime;
	bool game_paused = false;

	vector<std::shared_ptr<Tower>> Towers;
	vector<std::shared_ptr<Enemy>> Enemies;
	Map map;
	EnemyBase enemybase(&window, &Enemies);
	PlayerBase playerbase(&enemybase);
	TowerManager towermanager(&map, &Towers, &window, &playerbase, &Enemies);
	Menu menu(&window, &map, &playerbase, &Towers, &Enemies);

	map.setMapTexture();

	menu.action();

	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		window.clear();
		map.drawMap(window);

		//czesc odpowiedzialna za czestotliwosc pojawiania sie przeciwnika, oraz pociskow
		towermanager.incrementFrames();
		enemybase.incrementFrame();

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				menu.action();
			}
			//operacje zwiazane z myszka
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
			{
				sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition(window);
				if (!towermanager.isPlaceClicked(mousePos) && !towermanager.isTowerClicked(mousePos))
				{
					towermanager.nothingClicked();
				}
			}
			//Zmiany predkosci gry
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1))
			{
				game_paused = false;
				playerbase.setSpeed(1);
				window.setFramerateLimit(60);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2))
			{
				game_paused = false;
				playerbase.setSpeed(2);
				window.setFramerateLimit(120);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3))
			{
				game_paused = false;
				playerbase.setSpeed(3);
				window.setFramerateLimit(240);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad0))
			{
				playerbase.setSpeed(0);
				game_paused = true;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				playerbase.setStart(true);
			}
		}
		if (game_paused == false)
		{
			//start gry, przeciwnik rusza
			if (playerbase.getStart())
			{
				towermanager.shooting();
				if (enemybase.returnFrames() >= 30)
				{
					enemybase.spawnEnemy();
					enemybase.resetFrames();
				}
				enemybase.moveEnemies(deltaTime);
				playerbase.check_if_enemy_in();
			}
		}
		//rysowanie
		playerbase.drawBase(&window);
		enemybase.drawBase();
		enemybase.drawEnemies();
		towermanager.drawTowers();
		towermanager.drawMenu();
		window.display();
	}

	return 0;
}