#include "PlayerBase.h"



PlayerBase::PlayerBase(sf::Vector2f pos)
{
	base.setSize(sf::Vector2f(60.0f*scale, 60.0f*scale));
	base.setFillColor(sf::Color::Blue);
	base.setPosition(pos);
	base.setOrigin(30 * scale, 30 * scale);
	lifes = 1;
}


PlayerBase::~PlayerBase()
{
}

void PlayerBase::check_if_enemy_in(std::vector<std::shared_ptr<Enemy>> *Enemies)
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
	ttf.loadFromFile("fonts/font.otf");
	std::string s("GAME OVER");
	sf::Text txt(s, ttf);
	txt.setCharacterSize(150 * scale);
	txt.setFillColor(sf::Color(69, 120, 189));
	txt.setPosition(100 * scale, 40 * scale);
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
	ttf.loadFromFile("fonts/font.otf");
	std::string s(std::to_string(returnPoints()));
	sf::Text txt(s, ttf);
	txt.setCharacterSize(150 * scale);
	txt.setFillColor(sf::Color(69, 120, 189));
	txt.setPosition(1600*scale, 40 * scale);
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