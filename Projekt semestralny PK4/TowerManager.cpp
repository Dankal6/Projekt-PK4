#include "TowerManager.h"



TowerManager::TowerManager(Map *map, std::vector<Tower*> *_Towers, sf::RenderWindow *_window)
{
	placesForTowers = map->returnPlaces();
	Towers = _Towers;
	window = _window;
	buttonX.setRadius(20 * scale);
	buttonXTexture.loadFromFile("Textures/X.png");
	buttonXTexture.setSmooth(true);
	buttonX.setTexture(&buttonXTexture);
	buttonX.setOrigin(20 * scale, 20 * scale);

}


TowerManager::~TowerManager()
{
}

bool TowerManager::isPlaceClicked(sf::Vector2f mousePosition)
{
	for (auto p : *placesForTowers)
	{
		if (p->returnSquare().getGlobalBounds().contains(mousePosition))
		{
			if (p->isOccupied() == false)
			{
				p->returnSquare().setFillColor(sf::Color::Red);
				Tower *tower = new Tower(window, p->returnSquare().getPosition());
				tower->setPlace(p);
				Towers->push_back(tower);
				p->setOccupied(true);
				return true;
			}
		}
	}
	return false;
}

bool TowerManager::isTowerClicked(sf::Vector2f mousePosition)
{
	if (buttonX.getGlobalBounds().contains(mousePosition))
	{
		sellTower(managedTower);
	}
	for (auto t : *Towers)
	{
		if (t->returnTower()->getGlobalBounds().contains(mousePosition))
		{
			//t->returnTower()->setFillColor(sf::Color::Red);
			managedTower = t;
			t->drawRange(true);
			buttonX.setPosition(t->returnPosition().x + (60 * scale), t->returnPosition().y - (40*scale));
			return true;
		}
	}
	return false;
}

void TowerManager::nothingClicked()
{
	for (auto t : *Towers)
	{
		t->drawRange(false);
		buttonX.setPosition(-100, -100);	//aby przycisk zniknal, wyrzucam go tymczasowo poza ekran
	}

}

void TowerManager::drawMenu()
{
	window->draw(buttonX);
}

void TowerManager::sellTower(Tower* toSell)
{
	int i = 0;
	for (auto t : *Towers)
	{
		if (t->returnPosition() == toSell->returnPosition())
		{
			t->getPlace()->setOccupied(false);
			Towers->erase(Towers->begin() + i);
		}
		i++;
	}
}
