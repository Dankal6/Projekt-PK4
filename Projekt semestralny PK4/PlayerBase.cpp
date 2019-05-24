#include "PlayerBase.h"



PlayerBase::PlayerBase(sf::Vector2f pos)
{
	base.setSize(sf::Vector2f(60.0f, 60.0f));
	base.setFillColor(sf::Color::Blue);
	base.setPosition(pos);
	base.setOrigin(30, 30);
	lifes = 1;
}


PlayerBase::~PlayerBase()
{
}

void PlayerBase::check_if_enemy_in(std::vector<Enemy*> *Enemies)
{
	int i = 0;
	for (auto e : *Enemies)
	{
		sf::Vector2f enemy_pos = e->getPosition();
		if (base.getGlobalBounds().contains(enemy_pos))
		{
			lifes--;
			Enemies->erase(Enemies->begin() + i);
		}
		i++;
	}

}

void PlayerBase::gameOver(sf::RenderWindow* window)
{
	sf::Font ttf;
	ttf.loadFromFile("fonts/font.ttf");
	std::string s("GAME OVER");
	sf::Text txt(s, ttf);
	txt.setCharacterSize(150);
	txt.setFillColor(sf::Color(69, 120, 189));
	txt.setPosition(100, 40);
	window->draw(txt);
}

void PlayerBase::drawBase(sf::RenderWindow* window)
{
	window->draw(base);
	if (lifes <= 0)
	{
		gameOver(window);
	}
	//Wyswietlanie punktow gracza
	sf::Font ttf;
	ttf.loadFromFile("fonts/font.ttf");
	std::string s(std::to_string(returnPoints()));
	sf::Text txt(s, ttf);
	txt.setCharacterSize(150);
	txt.setFillColor(sf::Color(69, 120, 189));
	txt.setPosition(1600, 40);
	window->draw(txt);
}

void PlayerBase::addPoints(int x)
{
	points += x;
}

int PlayerBase::returnPoints()
{
	return this->points;
}