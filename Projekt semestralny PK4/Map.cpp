#include "Map.h"




Map::Map()
{
	map.setSize(sf::Vector2f(1920.0f*scale, 1080.0f*scale));
	map.setPosition(0, 0);
}


Map::~Map()
{

}

void Map::drawMap(sf::RenderWindow & window)
{
	window.draw(map);
	for (auto p : placesForTowers)
	{
		window.draw(p->returnSquare());
	}
}

void Map::generatePlaces()
{
	//tworze miejsca pod wiezyczki
	std::shared_ptr<PlaceForTower> p1 = std::make_shared<PlaceForTower>(385 * scale, 235 * scale);
	placesForTowers.push_back(p1);
	std::shared_ptr<PlaceForTower> p2 = std::make_shared<PlaceForTower>(580 * scale, 250 * scale);
	placesForTowers.push_back(p2);
	std::shared_ptr<PlaceForTower> p3 = std::make_shared<PlaceForTower>(685 * scale, 250 * scale);
	placesForTowers.push_back(p3);
	std::shared_ptr<PlaceForTower> p4 = std::make_shared<PlaceForTower>(885 * scale, 240 * scale);
	placesForTowers.push_back(p4);
	std::shared_ptr<PlaceForTower> p5 = std::make_shared<PlaceForTower>(1021 * scale, 242 * scale);
	placesForTowers.push_back(p5);
	std::shared_ptr<PlaceForTower> p6 = std::make_shared<PlaceForTower>(1023 * scale, 453 * scale);
	placesForTowers.push_back(p6);
	std::shared_ptr<PlaceForTower> p7 = std::make_shared<PlaceForTower>(902 * scale, 627 * scale);
	placesForTowers.push_back(p7);
	std::shared_ptr<PlaceForTower> p8 = std::make_shared<PlaceForTower>(906 * scale, 835 * scale);
	placesForTowers.push_back(p8);
	std::shared_ptr<PlaceForTower> p9 = std::make_shared<PlaceForTower>(1040 * scale, 835 * scale);
	placesForTowers.push_back(p9);
	std::shared_ptr<PlaceForTower> p10 = std::make_shared<PlaceForTower>(1236 * scale, 820 * scale);
	placesForTowers.push_back(p10);
	std::shared_ptr<PlaceForTower> p11 = std::make_shared<PlaceForTower>(1346 * scale, 820 * scale);
	placesForTowers.push_back(p11);
	std::shared_ptr<PlaceForTower> p12 = std::make_shared<PlaceForTower>(1540 * scale, 840 * scale);
	placesForTowers.push_back(p12);
	std::shared_ptr<PlaceForTower> p13 = std::make_shared<PlaceForTower>(1072 * scale, 626 * scale);
	placesForTowers.push_back(p13);
	std::shared_ptr<PlaceForTower> p14 = std::make_shared<PlaceForTower>(1222 * scale, 296 * scale);
	placesForTowers.push_back(p14);
	std::shared_ptr<PlaceForTower> p15 = std::make_shared<PlaceForTower>(714 * scale, 726 * scale);
	placesForTowers.push_back(p15);
	std::shared_ptr<PlaceForTower> p16= std::make_shared<PlaceForTower>(822 * scale, 445 * scale);
	placesForTowers.push_back(p16);
	std::shared_ptr<PlaceForTower> p17= std::make_shared<PlaceForTower>(693 * scale, 417 * scale);
	placesForTowers.push_back(p17);
	std::shared_ptr<PlaceForTower> p18= std::make_shared<PlaceForTower>(471 * scale, 68 * scale);
	placesForTowers.push_back(p18);
}

void Map::setMapTexture()
{
	try
	{
		bool a = mapTexture.loadFromFile("Textures/Grass1.png");
		if (a == false)
		{
			std::string wyjatek = "Please check for that texture!";
			throw wyjatek;
		}
		mapTexture.setSmooth(true);
		map.setTexture(&mapTexture);
		generatePlaces();
	}
	catch (std::string wyjatek)
	{
		std::cout << wyjatek << std::endl;
		system("pause");
		exit(0);
	}
}

std::vector<std::shared_ptr<PlaceForTower>> * Map::returnPlaces()
{
	return &placesForTowers;
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