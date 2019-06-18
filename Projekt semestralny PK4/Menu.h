#pragma once
#include "Scale.h"
#include "Map.h"
#include "Enemy.h"
#include "Tower.h"
#include "PlayerBase.h"


class Menu
{
private:
	sf::RenderWindow *window;
	Map* map;
	PlayerBase* player;
	std::vector<std::shared_ptr<Tower>>* Towers;
	std::vector<std::shared_ptr<Enemy>>* Enemies;

	sf::RectangleShape menu;
	sf::RectangleShape startButton;
	sf::RectangleShape restartButton;
	sf::RectangleShape quitButton;

	sf::Texture menuButtonTexture;

	sf::Font ttf;
	sf::Text start;
	sf::Text restart;
	sf::Text quit;
public:
	Menu(sf::RenderWindow*, Map* ,PlayerBase* ,std::vector<std::shared_ptr<Tower>>* ,std::vector<std::shared_ptr<Enemy>>*);
	~Menu();
	void drawMenu();
	void action();
	bool isPlayClicked(sf::Vector2f);
	bool isQuitClicked(sf::Vector2f);
	bool isReplayClicked(sf::Vector2f);
};

