#include "Enemy.h"

Enemy::Enemy(sf::Vector2f pos, int _type, int wave)
{
	enemy.setSize(sf::Vector2f(25.0f*scale, 50.0f*scale));
	std::thread the_thread(&Enemy::loadTextures, this, _type, wave);

	enemy.setPosition(pos);
	enemy.setOrigin(10 * scale, 20 * scale);
	type = _type;
	healthBar.setSize(sf::Vector2f(26.0f*scale, 2.0f*scale));
	healthBar.setFillColor(sf::Color::Green);
	healthBar.setOrigin(13 * scale, 25 * scale);
	healthBar.setPosition(pos);
	this->setSpeed(2, 0);

	the_thread.join();
	enemyTexture.setSmooth(true);
	enemy.setTexture(&enemyTexture);
	animation = new Animation(&enemyTexture, sf::Vector2u(3, 4), 0.3);

}


Enemy::~Enemy()
{
}

void Enemy::drawEnemy(sf::RenderWindow& window)
{
	window.draw(enemy);
	window.draw(healthBar);
}

void Enemy::move(float deltaTime)
{
	//czesc odpowiedzialna za animacje
	if (speed.x == 0 && speed.y > 0)
		animation->Update(0, deltaTime);
	else if (speed.x == 0 && speed.y < 0)
		animation->Update(3, deltaTime);
	else if (speed.x > 0)
		animation->Update(2, deltaTime);
	else if (speed.x < 0)
		animation->Update(1, deltaTime);
	enemy.setTextureRect(animation->uvRect);

	this->checkToTurn();

	enemy.move(speed);
	healthBar.move(speed);
}

void Enemy::checkToTurn()
{
	//zakrety na trasie
	if (enemy.getPosition().x > 478 * scale && enemy.getPosition().x < 482 * scale && enemy.getPosition().y >= 144 * scale && enemy.getPosition().y < 302 * scale)
	{
		this->setSpeed(0 * scale, 2 * scale);
	}
	else if (enemy.getPosition().x > 478 * scale && enemy.getPosition().x < 482 && enemy.getPosition().y > 302 * scale)
	{
		this->setSpeed(2 * scale, 0 * scale);
	}
	else if (enemy.getPosition().x > 780 * scale && enemy.getPosition().x < 784 * scale && enemy.getPosition().y > 302 * scale)
	{
		this->setSpeed(0 * scale, -2 * scale);
	}
	else if (enemy.getPosition().x > 780 * scale && enemy.getPosition().x < 784 * scale && enemy.getPosition().y < 146 * scale)
	{
		this->setSpeed(2 * scale, 0 * scale);
	}
	else if (enemy.getPosition().x > 1110 * scale && enemy.getPosition().y < 146 * scale)
	{
		this->setSpeed(0 * scale, 2 * scale);
	}
	else if (enemy.getPosition().x > 1110 * scale && enemy.getPosition().y > 514 * scale && enemy.getPosition().y < 520 * scale)
	{
		this->setSpeed(-2 * scale, 0 * scale);
	}
	else if (enemy.getPosition().x > 804 * scale && enemy.getPosition().x < 810 * scale && enemy.getPosition().y > 504 * scale && enemy.getPosition().y < 530 * scale)
	{
		this->setSpeed(0 * scale, 2 * scale);
	}
	else if (enemy.getPosition().x > 804 * scale && enemy.getPosition().x < 810 * scale && enemy.getPosition().y > 900 * scale)
	{
		this->setSpeed(2 * scale, 0 * scale);
	}
	else if (enemy.getPosition().x > 1120 * scale && enemy.getPosition().x < 1124 * scale && enemy.getPosition().y > 900 * scale)
	{
		this->setSpeed(0 * scale, -2 * scale);
	}
	else if (enemy.getPosition().x > 1120 * scale && enemy.getPosition().x < 1124 * scale && enemy.getPosition().y < 730 * scale)
	{
		this->setSpeed(2 * scale, 0 * scale);
	}
	else if (enemy.getPosition().x > 1434 * scale && enemy.getPosition().x < 1438 * scale && enemy.getPosition().y < 730 * scale)
	{
		this->setSpeed(0 * scale, 2 * scale);
	}
	else if (enemy.getPosition().x > 1434 * scale && enemy.getPosition().x < 1438 * scale && enemy.getPosition().y > 900 * scale)
	{
		this->setSpeed(2 * scale, 0 * scale);
	}
}

void Enemy::setSpeed(float x, float y)
{
	this->speed = { x, y };
}

sf::Vector2f Enemy::getPosition()
{
	return enemy.getPosition();
}

sf::Vector2f Enemy::returnSpeed()
{
	return this->speed;
}

bool Enemy::gotHitted(std::vector<std::shared_ptr<Enemy>> *Enemies, std::shared_ptr<Tower> tower, PlayerBase *player)
{
	int i = 0;
	for (auto e : *Enemies)
	{
		if (e->getPosition() == this->getPosition())
		{
			break;
		}
		i++;
	}
	int j = 0;
	for (auto b : *tower->returnBullets())
	{
		sf::Vector2f bullet_pos = b->returnPosition();
		float x = bullet_pos.x;
		float y = bullet_pos.y;
		if (enemy.getGlobalBounds().contains(x, y))
		{
			this->healthPointLeft -= tower->returnDamage();
			this->healthBar.setSize(sf::Vector2f(this->returnHealthAsPercent()*this->enemy.getSize().x, 2.0f*scale));
			tower->returnBullets()->erase(tower->returnBullets()->begin() + j);
			if (this->healthPointLeft <= 0)
			{
				if (this->type == 2 || this->type == 4)
				{
					player->addPoints(2);
					player->addCash(2);
				}
				else
				{
					player->addPoints(1);
					player->addCash(1);
				}
				Enemies->erase(Enemies->begin() + i);
				return true;
			}
			return false;
		}
		j++;
	}
}

double Enemy::returnHealthAsPercent()
{
	return (this->healthPointLeft / this->healthPoint);
}

int Enemy::returnType()
{
	return this->type;
}

void Enemy::loadTextures(int type, int wave)
{
	if (type == 1)
	{
		try
		{
			bool a = enemyTexture.loadFromFile("Textures/orc_warrior-green-SWEN.png");
			if (a == false)
			{
				std::string wyjatek = "Please check for that texture!";
				throw wyjatek;
			}
			this->healthPoint = 20 + ((type * 5 * wave) / 2);
			this->healthPointLeft = this->healthPoint;
		}
		catch (std::string wyjatek)
		{
			std::cout << wyjatek << std::endl;
			system("pause");
			exit(0);
		}

	}
	else if (type == 2)
	{
		try
		{
			bool a = enemyTexture.loadFromFile("Textures/orc_chief-brown-SWEN.png");
			if (a == false)
			{
				std::string wyjatek = "Please check for that texture!";
				throw wyjatek;
			}
			this->healthPoint = 40 + ((type * 5 * wave) / 2);
			this->healthPointLeft = this->healthPoint;
		}
		catch (std::string wyjatek)
		{
			std::cout << wyjatek << std::endl;
			system("pause");
			exit(0);
		}
	}
	else if (type == 3)
	{
		try
		{
			bool a = enemyTexture.loadFromFile("Textures/orc_spearman-green-SWEN.png");
			if (a == false)
			{
				std::string wyjatek = "Please check for that texture!";
				throw wyjatek;
			}
			this->healthPoint = 30 + ((type * 5 * wave) / 2);
			this->healthPointLeft = this->healthPoint;
		}
		catch (std::string wyjatek)
		{
			std::cout << wyjatek << std::endl;
			system("pause");
			exit(0);
		}
	}
	else if (type == 4)
	{
		try
		{
			bool a = enemyTexture.loadFromFile("Textures/orc_shaman-brown-SWEN.png");
			if (a == false)
			{
				std::string wyjatek = "Please check for that texture!";
				throw wyjatek;
			}
			this->healthPoint = 60 + ((type * 5 * wave) / 2);
			this->healthPointLeft = this->healthPoint;
		}
		catch (std::string wyjatek)
		{
			std::cout << wyjatek << std::endl;
			system("pause");
			exit(0);
		}
	}
}
