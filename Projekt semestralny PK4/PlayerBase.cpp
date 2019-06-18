#include "PlayerBase.h"



PlayerBase::PlayerBase(EnemyBase *_enemybase)
{
	base.setSize(sf::Vector2f(60.0f*scale, 60.0f*scale));
	base.setFillColor(sf::Color::Blue);
	base.setPosition(sf::Vector2f(1940.0f*scale, 920.0f*scale));
	base.setOrigin(30 * scale, 30 * scale);
	lifes = 20;
	enemybase = _enemybase;

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

	_speed.setFont(ttf);
	_speed.setCharacterSize(35 * scale);
	_speed.setFillColor(sf::Color::Black);
	_speed.setPosition(1510 * scale, 200 * scale);
	_speed.setString("Speed: 1");

	_wave.setFont(ttf);
	_wave.setCharacterSize(35 * scale);
	_wave.setFillColor(sf::Color::Black);
	_wave.setPosition(1510 * scale, 240 * scale);
	_wave.setString("Wave: 0");

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

	setWave();

	window->draw(playerInfo);
	window->draw(_lifes);
	window->draw(_points);
	window->draw(_cash);
	window->draw(_speed);
	window->draw(_wave);
}

void PlayerBase::setSpeed(int x)
{
	this->speed = x;
	_speed.setString("Speed: " + std::to_string(x));
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

void PlayerBase::setWave()
{
	_wave.setString("Wave: " + std::to_string(enemybase->returnWave()));
}

void PlayerBase::setStart(bool _start)
{
	this->start = _start;
}

bool PlayerBase::getStart()
{
	return start;
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
