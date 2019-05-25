#include "TowerManager.h"



TowerManager::TowerManager(Map *map, std::vector<Tower*> *_Towers, sf::RenderWindow *_window)
{
	placesForTowers = map->returnPlaces();
	Towers = _Towers;
	window = _window;
}


TowerManager::~TowerManager()
{
}

void TowerManager::isPlaceClicked(sf::Vector2f mousePosition)
{
	for (auto p : *placesForTowers)
	{
		if(p->returnSquare().getGlobalBounds().contains(mousePosition))
		{
			if (p->isOccupied()==false)
			{
				p->returnSquare().setFillColor(sf::Color::Red);
				Tower *tower = new Tower(window, p->returnSquare().getPosition());
				Towers->push_back(tower);
				p->setOccupied(true);
			}
		}

	}
}

void TowerManager::isTowerClicked(sf::Vector2f mousePosition)
{
	for (auto t : *Towers)
	{
		if (t->returnTower()->getGlobalBounds().contains(mousePosition))
		{
			//t->returnTower()->setFillColor(sf::Color::Red);

		}
	}
}