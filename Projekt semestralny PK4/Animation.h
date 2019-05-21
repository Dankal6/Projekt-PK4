#pragma once
#include "SFML/Graphics.hpp"
class Animation
{
public:
	Animation(sf::Texture*,sf::Vector2u,float);
	~Animation();

	void Update(int row, float deltaTime);

	sf::IntRect uvRect;

private:
	sf::Vector2u imageCount;
	sf::Vector2u currentImage;

	float totalTime;
	float switchTime;
};

