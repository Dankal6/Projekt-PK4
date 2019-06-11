#include "TowerManager.h"



TowerManager::TowerManager(Map *map, std::vector<std::shared_ptr<Tower>> *_Towers, sf::RenderWindow *_window)
{
	placesForTowers = map->returnPlaces();
	Towers = _Towers;
	window = _window;

	buttonX.setRadius(20 * scale);
	buttonXTexture.loadFromFile("Textures/X.png");
	buttonXTexture.setSmooth(true);
	buttonX.setTexture(&buttonXTexture);
	buttonX.setOrigin(20 * scale, 20 * scale);

	buttonUpgrade.setRadius(20 * scale);
	buttonUpgradeTexture.loadFromFile("Textures/upgrade.png");
	buttonUpgradeTexture.setSmooth(true);
	buttonUpgrade.setTexture(&buttonUpgradeTexture);
	buttonUpgrade.setOrigin(20 * scale, 20 * scale);

	buttonY.setRadius(20 * scale);
	buttonYTexture.loadFromFile("Textures/Y.png");
	buttonYTexture.setSmooth(true);
	buttonY.setTexture(&buttonYTexture);
	buttonY.setOrigin(20 * scale, 20 * scale);

	ttf.loadFromFile("fonts/font.ttf");
	towerLevel.setFont(ttf);
	towerLevel.setString("0");
	towerLevel.setCharacterSize(200);
	towerLevel.setFillColor(sf::Color::Red);
	towerLevel.setPosition(-100,-100);

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
				std::shared_ptr<Tower> tower = std::make_shared<Tower>(window, p->returnSquare().getPosition());
				//Tower *tower = new Tower(window, p->returnSquare().getPosition());
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
	if (buttonY.getGlobalBounds().contains(mousePosition))
	{
		upgradeTower(managedTower);
		buttonY.setPosition(-100, -100);	//aby przycisk zniknal, wyrzucam go tymczasowo poza ekran
	}
	else if (buttonUpgrade.getGlobalBounds().contains(mousePosition))
	{
		buttonY.setPosition(managedTower->returnPosition().x - (60 * scale), managedTower->returnPosition().y - (40 * scale));
	}

	for (auto t : *Towers)
	{
		if (t->returnTower()->getGlobalBounds().contains(mousePosition))
		{
			//t->returnTower()->setFillColor(sf::Color::Red);
			managedTower = t;
			t->drawRange(true);
			showTowerLevel(managedTower);	//t to samo
			buttonX.setPosition(t->returnPosition().x + (60 * scale), t->returnPosition().y - (40*scale));
			buttonUpgrade.setPosition(t->returnPosition().x - (60 * scale), t->returnPosition().y - (40 * scale));
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
		buttonUpgrade.setPosition(-100, -100);	//aby przycisk zniknal, wyrzucam go tymczasowo poza ekran
	}

}


void TowerManager::drawMenu()
{
	window->draw(buttonX);
	window->draw(buttonUpgrade);
	window->draw(buttonY);
	window->draw(towerLevel);
}

void TowerManager::sellTower(std::shared_ptr<Tower> toSell)
{
	int i = 0;
	for (auto t : *Towers)
	{
		if (t->returnPosition() == toSell->returnPosition())
		{
			t->getPlace()->setOccupied(false);
			Towers->erase(Towers->begin() + i);
			buttonX.setPosition(-100, -100);	//aby przycisk zniknal, wyrzucam go tymczasowo poza ekran
			buttonUpgrade.setPosition(-100, -100);	//aby przycisk zniknal, wyrzucam go tymczasowo poza ekran
			managedTower = NULL;
			return;
		}
		i++;
	}
}

void TowerManager::upgradeTower(std::shared_ptr<Tower> tower)
{
	tower->setDamage(tower->returnDamage() + 5);
	tower->setLevel(tower->returnLevel()+1);
}

void TowerManager::showTowerLevel(std::shared_ptr<Tower> managedTower)
{
	std::string s = std::to_string(managedTower->returnLevel());
	towerLevel.setString(s);
	towerLevel.setPosition(managedTower->returnPosition().x, managedTower->returnPosition().y + (20 * scale));
}
