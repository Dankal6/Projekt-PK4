#pragma once
#include "Scale.h"
#include "Map.h"

class Menu
{
private:
	sf::RenderWindow *window;
	sf::RectangleShape menu;
	sf::RectangleShape startButton;
	sf::Texture startButtonTexture;
	sf::RectangleShape quitButton;
	sf::Texture quitButtonTexture;
public:
	Menu(sf::RenderWindow*);
	~Menu();
	void drawMenu();
	void action(Map&);
	bool isPlayClicked(sf::Vector2f);
	bool isQuitClicked(sf::Vector2f);
};

