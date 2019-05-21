#include "Enemy.h"



Enemy::Enemy(sf::Vector2f pos)
{
	enemy.setSize(sf::Vector2f(20.0f, 40.0f));
	//enemy.setFillColor(sf::Color::Red);
	enemy.setPosition(pos);
	enemy.setOrigin(10, 20);
	this->healthPoint = 60;
	this->healthPointLeft = 60;
	healthBar.setSize(sf::Vector2f(26.0f, 2.0f));
	healthBar.setFillColor(sf::Color::Green);
	healthBar.setOrigin(13, 25);
	healthBar.setPosition(pos);

	//inicjacja ruchu
	this->setSpeed(0, 2);

	enemyTexture.loadFromFile("Textures/orc-green-SWEN.png");
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
	if(speed.x==0 && speed.y > 0)
		animation->Update(0, deltaTime);
	else if(speed.x == 0 && speed.y <0)
		animation->Update(3, deltaTime);
	else if(speed.x>0)
		animation->Update(2, deltaTime);
	else if(speed.x < 0)
		animation->Update(1, deltaTime);


	enemy.setTextureRect(animation->uvRect);


	enemy.move(speed);
	this->position = enemy.getPosition();
	healthBar.move(speed);
}

void Enemy::setSpeed(float x, float y)
{
	this->speed = { x, y };
}

sf::Vector2f Enemy::getPosition()
{
	return this->position;
}

sf::Vector2f Enemy::returnSpeed()
{
	return this->speed;
}

bool Enemy::gotHitted(std::vector<Enemy*> *Enemies, std::vector<Bullet*> *Bullets, PlayerBase *player)
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
	for (auto b : *Bullets)
	{
		//if (enemy.getGlobalBounds().contains(b->returnPosition))
		sf::Vector2f bullet_pos = b->returnPosition();
		float x = bullet_pos.x;
		float y = bullet_pos.y;
		if (enemy.getGlobalBounds().contains(x, y))
		{
  			this->healthPointLeft -= 15;
			this->healthBar.setSize(sf::Vector2f(this->returnHealthAsPercent()*this->enemy.getSize().x, 5.0f));
			Bullets->erase(Bullets->begin()+j);
			if (this->healthPointLeft <= 0)
			{
				Enemies->erase(Enemies->begin() + i);  
				std::cout << "Padl przeciwnik: " << i << ", pozostalo przeciwnikow: " << Enemies->size() << std::endl;
				player->addPoints(1);
			}
			return true;
		}
		j++;
	}
} 

double Enemy::returnHealthAsPercent()
{
	return (this->healthPointLeft / this->healthPoint);
}