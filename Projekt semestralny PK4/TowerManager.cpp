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

	buttonArrow.setSize(sf::Vector2f(40, 40));
	buttonArrowTexture.loadFromFile("Textures/bow.png");
	buttonArrowTexture.setSmooth(true);
	buttonArrow.setTexture(&buttonArrowTexture);
	buttonArrow.setOrigin(20 * scale, 20 * scale);

	buttonFireball.setSize(sf::Vector2f(40, 40));
	buttonFireballTexture.loadFromFile("Textures/fireball.png");
	buttonFireballTexture.setSmooth(true);
	buttonFireball.setTexture(&buttonFireballTexture);
	buttonFireball.setOrigin(20 * scale, 20 * scale);

	ttf.loadFromFile("fonts/font.otf");
	towerLevel.setFont(ttf);
	towerLevel.setString("0");
	towerLevel.setCharacterSize(100);
	towerLevel.setOrigin(25, 25);
	towerLevel.setFillColor(sf::Color::Black);
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
				managedPlace = p;
				buttonArrow.setPosition(p->returnPosition().x + (60 * scale), p->returnPosition().y - (40 * scale));
				buttonFireball.setPosition(p->returnPosition().x - (60 * scale), p->returnPosition().y - (40 * scale));
				return true;
			}
		}
	}
	isNewTowerClicked(mousePosition);
	return false;
}

void TowerManager::isNewTowerClicked(sf::Vector2f mousePosition)
{

	if (buttonArrow.getGlobalBounds().contains(mousePosition))
	{
		std::shared_ptr<Tower> tower = std::make_shared<Tower>(window, managedPlace->returnSquare().getPosition(), 1);
		tower->setPlace(managedPlace);
		Towers->push_back(tower);
		buttonArrow.setPosition(-100, -100);
		buttonFireball.setPosition(-100, -100);
		managedPlace->setOccupied(true);
		managedPlace = NULL;
	}
	if (buttonFireball.getGlobalBounds().contains(mousePosition))
	{
		std::shared_ptr<Tower> tower = std::make_shared<Tower>(window, managedPlace->returnSquare().getPosition(),2);
		tower->setPlace(managedPlace);
		Towers->push_back(tower);
		buttonArrow.setPosition(-100, -100);
		buttonFireball.setPosition(-100, -100);
		managedPlace->setOccupied(true);
		managedPlace = NULL;
	}


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
		towerLevel.setPosition(-100, -100);
		buttonArrow.setPosition(-100, -100);
		buttonFireball.setPosition(-100, -100);
	}

}


void TowerManager::drawMenu()
{
	window->draw(buttonX);
	window->draw(buttonUpgrade);
	window->draw(buttonY);
	window->draw(towerLevel);
	window->draw(buttonArrow);
	window->draw(buttonFireball);
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
