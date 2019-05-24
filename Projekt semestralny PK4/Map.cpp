#include "Map.h"



Map::Map()
{
	placeSize = sf::Vector2f(60, 60);

	map.setSize(sf::Vector2f(1920.0f, 1080.0f));
	map.setPosition(0, 0);
	mapTexture.loadFromFile("Textures/Grass1.png");
	mapTexture.setSmooth(true);
	map.setTexture(&mapTexture);

	//tworze sciezke jako prostokaty 
	sf::RectangleShape* p1;
	p1->setPosition(355, 195);
	placesForTowers.push_back(p1);

	sf::RectangleShape *p2;
	p2->setPosition(550, 210);
	placesForTowers.push_back(p2);

	sf::RectangleShape *p3;
	p3->setPosition(655, 210);
	placesForTowers.push_back(p3);

	sf::RectangleShape *p4;
	p4->setPosition(855, 200);
	placesForTowers.push_back(p4);

	sf::RectangleShape *p5;
	p5->setPosition(991, 202);
	placesForTowers.push_back(p5);

	sf::RectangleShape *p6;
	p6->setPosition(993, 423);
	placesForTowers.push_back(p6);

	sf::RectangleShape* p7;
	p7->setPosition(862, 587);
	placesForTowers.push_back(p7);

	sf::RectangleShape* p8;
	p8->setPosition(866,805);
	placesForTowers.push_back(p8);

	sf::RectangleShape *p9;
	p9->setPosition(1009, 809);
	placesForTowers.push_back(p9);

	sf::RectangleShape *p10;
	p10->setPosition(1196, 791);
	placesForTowers.push_back(p10);

	sf::RectangleShape *p11;
	p11->setPosition(1316, 791);
	placesForTowers.push_back(p11);

	sf::RectangleShape *p12;
	p12->setPosition(1507, 807);
	placesForTowers.push_back(p12);

	sf::RectangleShape *p13;
	p13->setPosition(1032, 586);
	placesForTowers.push_back(p13);

	sf::RectangleShape* p14;
	p14->setPosition(1182, 256);
	placesForTowers.push_back(p14);

	sf::RectangleShape *p15;
	p15->setPosition(674, 686);
	placesForTowers.push_back(p15);

	sf::RectangleShape *p16;
	p16->setPosition(782, 395);
	placesForTowers.push_back(p16);

	sf::RectangleShape *p17;
	p17->setPosition(653, 377);
	placesForTowers.push_back(p17);

	sf::RectangleShape *p18;
	p18->setPosition(431, 28);
	placesForTowers.push_back(p18);

	sf::RectangleShape *p19;
	p19->setPosition(356, 194);
	placesForTowers.push_back(p19);

	for (auto p : placesForTowers)
	{
		p->setSize(placeSize);
		p->setFillColor(sf::Color::Black);
	}
}


Map::~Map()
{

}

void Map::drawMap(sf::RenderWindow & window)
{
	window.draw(map);
	for (auto p : placesForTowers)
	{
		window.draw(*p);
	}
}
/*
void Map::initMapAsSquares()
{
	for (int i = 0; i < 48; i++)
	{
		for (int j = 0; j < 27; j++)
		{
			sf::RectangleShape square;
			square.setPosition((i * 40),(j * 40));
			square.setSize(sf::Vector2f(40, 40));
			square.setFillColor(sf::Color(i*5,j*8,i+j*4));
			squares.push_back(square);
		}
	}
}

void Map::drawMapAsSquares(sf::RenderWindow& window)
{
	for (auto s : squares)
	{
		window.draw(s);
	}
}
*/