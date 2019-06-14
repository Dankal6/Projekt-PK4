#include "PlayerBase.h"



PlayerBase::PlayerBase(sf::Vector2f pos)
{
	base.setSize(sf::Vector2f(60.0f*scale, 60.0f*scale));
	base.setFillColor(sf::Color::Blue);
	base.setPosition(pos);
	base.setOrigin(30 * scale, 30 * scale);
	lifes = 20;

	playerInfo.setSize(sf::Vector2f(430 * scale, 350 * scale));
	playerInfoTexture.loadFromFile("Textures/infoPlayer.png");
	playerInfoTexture.setSmooth(true);
	playerInfo.setTexture(&playerInfoTexture);
	playerInfo.setPosition(1480*scale, 0);

	ttf.loadFromFile("fonts/towerInfo.ttf");

	_points.setFont(ttf);
	_points.setCharacterSize(35 * scale);
	_points.setFillColor(sf::Color::Black);
	_points.setPosition(1510 * scale, 160 * scale);

	_cash.setFont(ttf);
	_cash.setCharacterSize(35 * scale);
	_cash.setFillColor(sf::Color::Black);
	_cash.setPosition(1510 * scale, 120 * scale);

	_lifes.setFont(ttf);
	_lifes.setCharacterSize(35 * scale);
	_lifes.setFillColor(sf::Color::Black);
	_lifes.setPosition(1510 * scale, 80 * scale);

	this->cash = 50;

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
			return;
		}
		i++;
	}

}

void PlayerBase::gameOver(sf::RenderWindow* window)
{
	sf::Font ttf;
	ttf.loadFromFile("fonts/towerInfo.ttf");
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

	std::string slifes = "Lifes: " + std::to_string(this->lifes);
	_lifes.setString(slifes);
	std::string scash = "Cash: " + std::to_string(this->cash);
	_cash.setString(scash);
	std::string spoints = "Points: " + std::to_string(this->points);
	_points.setString(spoints);

	window->draw(playerInfo);
	window->draw(_lifes);
	window->draw(_points);
	window->draw(_cash);
}

void PlayerBase::addPoints(int x)
{
	points += x;
}

void PlayerBase::setPoints(int x)
{
	points = x;
}

int PlayerBase::returnPoints()
{
	return this->points;
}

void PlayerBase::addCash(int x)
{
	this->cash += x;
}

void PlayerBase::setLifes(int x)
{
	this->lifes = x;
}

void PlayerBase::setCash(int x)
{
	this->cash = x;
}

int PlayerBase::returnCash()
{
	return this->cash;
}

void PlayerBase::spendCash(int x)
{
	this->cash -= x;
}
