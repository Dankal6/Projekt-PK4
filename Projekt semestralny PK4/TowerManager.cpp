#include "TowerManager.h"



TowerManager::TowerManager(Map *map, std::vector<std::shared_ptr<Tower>> *_Towers, sf::RenderWindow *_window, PlayerBase *_player, std::vector<std::shared_ptr<Enemy>> *_Enemies)
{
	placesForTowers = map->returnPlaces();
	Towers = _Towers;
	window = _window;
	player = _player;
	Enemies = _Enemies;


	std::thread the_thread(&TowerManager::loadTexturesAndFont, this);
	the_thread.join();
	std::cout << "Przechodze dalej" <<std::endl;
	towerLevel.setCharacterSize(35 * scale);
	towerDmg.setCharacterSize(35 * scale);
	towerRange.setCharacterSize(35 * scale);
	arrowCost.setCharacterSize(15 * scale);
	fireballCost.setCharacterSize(15 * scale);
	arrowUpgradeCost.setCharacterSize(15 * scale);
	fireballUpgradeCost.setCharacterSize(15 * scale);

	towerLevel.setOrigin(25 * scale, 25 * scale);
	towerDmg.setOrigin(25 * scale, 25 * scale);
	towerRange.setOrigin(25 * scale, 25 * scale);

	towerLevel.setFillColor(sf::Color::Black);
	towerDmg.setFillColor(sf::Color::Black);
	towerRange.setFillColor(sf::Color::Black);
	arrowCost.setFillColor(sf::Color::Black);
	fireballCost.setFillColor(sf::Color::Black);
	arrowUpgradeCost.setFillColor(sf::Color::Black);
	fireballUpgradeCost.setFillColor(sf::Color::Black);

	towerLevel.setPosition(-100, -100);
	towerDmg.setPosition(-100, -100);
	towerRange.setPosition(-100, -100);
	arrowCost.setPosition(-100, -100);
	fireballCost.setPosition(-100, -100);
	arrowUpgradeCost.setPosition(-100, -100);
	fireballUpgradeCost.setPosition(-100, -100);

	fireballCost.setString("40$");
	arrowCost.setString("25$");
	fireballUpgradeCost.setString("20$");
	arrowUpgradeCost.setString("12$");
	arrowSell = arrowUpgradeCost;
	fireballSell = fireballUpgradeCost;

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
				arrowCost.setPosition(p->returnPosition().x + (40 * scale), p->returnPosition().y - (20 * scale));
				fireballCost.setPosition(p->returnPosition().x - (75 * scale), p->returnPosition().y - (20 * scale));
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
		if (player->returnCash() >= 25)
		{
			std::shared_ptr<Tower> tower = std::make_shared<Tower>(window, managedPlace->returnSquare().getPosition(), 1);
			tower->setPlace(managedPlace);
			Towers->push_back(tower);
			buttonArrow.setPosition(-100, -100);
			buttonFireball.setPosition(-100, -100);
			fireballCost.setPosition(-100, -100);
			arrowCost.setPosition(-100, -100);
			managedPlace->setOccupied(true);
			managedPlace = NULL;
			player->spendCash(25);
		}
	}
	if (buttonFireball.getGlobalBounds().contains(mousePosition))
	{
		if (player->returnCash() >= 40)
		{
			std::shared_ptr<Tower> tower = std::make_shared<Tower>(window, managedPlace->returnSquare().getPosition(), 2);
			tower->setPlace(managedPlace);
			Towers->push_back(tower);
			buttonArrow.setPosition(-100, -100);
			buttonFireball.setPosition(-100, -100);
			fireballCost.setPosition(-100, -100);
			arrowCost.setPosition(-100, -100);
			managedPlace->setOccupied(true);
			managedPlace = NULL;
			player->spendCash(40);
		}
	}


}

bool TowerManager::isTowerClicked(sf::Vector2f mousePosition)
{
	if (buttonX.getGlobalBounds().contains(mousePosition))
	{
		if (managedTower->returnType() == 1)
		{
			player->addCash(12);
		}
		else
		{
			player->addCash(20);
		}
		sellTower(managedTower);
	}
	if (buttonY.getGlobalBounds().contains(mousePosition))
	{
		if (managedTower->returnType() == 1 && player->returnCash() >= 12)
		{
			player->spendCash(12);
			upgradeTower(managedTower);
		}
		else if (managedTower->returnType() == 2 && player->returnCash() >= 20)
		{
			player->spendCash(20);
			fireballUpgradeCost.setPosition(-100, -100);
			arrowUpgradeCost.setPosition(-100, -100);
			upgradeTower(managedTower);
		}
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
			managedTower = t;
			managedTower->drawRange(true);

			buttonX.setPosition(t->returnPosition().x + (60 * scale), t->returnPosition().y - (40 * scale));
			if (managedTower->returnType() == 1)
				arrowSell.setPosition(t->returnPosition().x + (40 * scale), t->returnPosition().y - (20 * scale));
			else if (managedTower->returnType() == 2)
				fireballSell.setPosition(t->returnPosition().x + (40 * scale), t->returnPosition().y - (20 * scale));

			buttonUpgrade.setPosition(t->returnPosition().x - (60 * scale), t->returnPosition().y - (40 * scale));
			if (managedTower->returnType() == 1)
				arrowUpgradeCost.setPosition(t->returnPosition().x - (75 * scale), t->returnPosition().y - (20 * scale));
			else if (managedTower->returnType() == 2)
				fireballUpgradeCost.setPosition(t->returnPosition().x - (75 * scale), t->returnPosition().y - (20 * scale));

			showTowerInfo(managedTower);
			towerInfo.setPosition(0, 720 * scale);
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
	}
	buttonX.setPosition(-100, -100);	//aby przycisk zniknal, wyrzucam go tymczasowo poza ekran
	buttonUpgrade.setPosition(-100, -100);	//aby przycisk zniknal, wyrzucam go tymczasowo poza ekran
	towerLevel.setPosition(-100, -100);
	towerDmg.setPosition(-100, -100);
	towerRange.setPosition(-100, -100);
	buttonArrow.setPosition(-100, -100);
	buttonFireball.setPosition(-100, -100);
	fireballCost.setPosition(-100, -100);
	arrowCost.setPosition(-100, -100);
	fireballUpgradeCost.setPosition(-100, -100);
	arrowUpgradeCost.setPosition(-100, -100);
	fireballSell.setPosition(-100, -100);
	arrowSell.setPosition(-100, -100);
	towerInfo.setPosition(-1000, -1000);
}


void TowerManager::drawMenu()
{
	window->draw(buttonX);
	window->draw(buttonUpgrade);
	window->draw(buttonY);
	window->draw(buttonArrow);
	window->draw(buttonFireball);
	window->draw(towerInfo);
	window->draw(towerLevel);
	window->draw(towerDmg);
	window->draw(towerRange);
	window->draw(fireballCost);
	window->draw(arrowCost);
	window->draw(fireballUpgradeCost);
	window->draw(arrowUpgradeCost);
	window->draw(fireballSell);
	window->draw(arrowSell);
}

void TowerManager::sellTower(std::shared_ptr<Tower> toSell)
{
	int i = 0;
	for (auto t : *Towers)
	{
		if (t->returnPosition() == toSell->returnPosition())
		{
			nothingClicked();
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
	if (tower->returnType() == 1)
	{
		tower->setDamage(tower->returnDamage() + 10);
		tower->setLevel(tower->returnLevel() + 1);
		tower->setRange(20);
	}
	else if (tower->returnType() == 2)
	{
		tower->setDamage(tower->returnDamage() + 20);
		tower->setLevel(tower->returnLevel() + 1);
		tower->setRange(10);
	}
}

void TowerManager::showTowerInfo(std::shared_ptr<Tower> managedTower)
{
	std::string towerLvl = "Tower level: " + std::to_string(managedTower->returnLevel());
	towerLevel.setString(towerLvl);
	towerLevel.setPosition(60 * scale, 820 * scale);
	std::string towerDamage = "Damage: " + std::to_string(managedTower->returnDamage());
	towerDmg.setString(towerDamage);
	towerDmg.setPosition(60 * scale, 860 * scale);
	std::string towerRan = "Range: " + std::to_string(managedTower->returnRange());
	towerRange.setString(towerRan);
	towerRange.setPosition(60 * scale, 900 * scale);
}

void TowerManager::shooting()
{

	//rysowanie wiez
	for (std::vector<std::shared_ptr<Tower>>::iterator t = Towers->begin(); t != Towers->end(); t++)
	{
		(*t)->shoot();
		//sprawdzanie, czy jakis przecinik jest w zasiegu
		std::shared_ptr<Enemy> enemy_to_shoot = (*t)->check_if_in_range(Enemies);
		if (enemy_to_shoot != NULL)
		{
			if ((*t)->returnFrames() >= 20)
			{
				//wycelowanie
				(*t)->aim(enemy_to_shoot);
				(*t)->resetFrames();
			}
		}
		//sprawdzanie, czy przeciwnik zostal trafiony
		for (std::vector<std::shared_ptr<Enemy>>::iterator e = Enemies->begin(); e != Enemies->end(); e++)
		{
			bool hitted = (*e)->gotHitted(Enemies, *t, player);
			//gotHitted zwraca true gry przecniwnik zginie i zostanie usuniety z wektora, dlatego po usunieciu wychodze z petli
			if (hitted == true)
				break;
		}
	}
}

void TowerManager::drawTowers()
{
	//rysowanie pociskow i wiez
	for (auto t : *Towers)
	{
		t->drawTower();
	}
}

void TowerManager::incrementFrames()
{
	for (std::vector<std::shared_ptr<Tower>>::iterator t = Towers->begin(); t != Towers->end(); t++)
	{
		(*t)->incrementFrame();
	}
}

void TowerManager::loadTexturesAndFont()
{
	std::thread the_thread2(&TowerManager::loadXTexture, this);
	std::thread the_thread3(&TowerManager::loadUpgradeTexture, this);
	std::thread the_thread4(&TowerManager::loadYTexture, this);
	std::thread the_thread5(&TowerManager::loadBowTexture, this);
	std::thread the_thread6(&TowerManager::loadFireballTexture, this);
	std::thread the_thread7(&TowerManager::loadInfoTowerTexture, this);
	loadFont();
	the_thread2.join();
	the_thread3.join();
	the_thread4.join();
	the_thread5.join();
	the_thread6.join();
	the_thread7.join();
}

void TowerManager::loadXTexture()
{
	try
	{
		bool a = buttonXTexture.loadFromFile("Textures/X.png");
		if (a == false)
		{
			std::string wyjatek = "Please check for that texture!";
			throw wyjatek;
		}
		buttonX.setRadius(20 * scale);
		buttonXTexture.setSmooth(true);
		buttonX.setTexture(&buttonXTexture);
		buttonX.setOrigin(20 * scale, 20 * scale);
	}
	catch (std::string wyjatek)
	{
		std::cout << wyjatek << std::endl;
		system("pause");
		exit(0);
	}
}

void TowerManager::loadUpgradeTexture()
{
	try
	{
		bool a = buttonUpgradeTexture.loadFromFile("Textures/upgrade.png");
		if (a == false)
		{
			std::string wyjatek = "Please check for that texture!";
			throw wyjatek;
		}
		buttonUpgrade.setRadius(20 * scale);
		buttonUpgradeTexture.setSmooth(true);
		buttonUpgrade.setTexture(&buttonUpgradeTexture);
		buttonUpgrade.setOrigin(20 * scale, 20 * scale);
	}
	catch (std::string wyjatek)
	{
		std::cout << wyjatek << std::endl;
		system("pause");
		exit(0);
	}
}

void TowerManager::loadYTexture()
{
	try
	{
		bool a = buttonYTexture.loadFromFile("Textures/Y.png");
		if (a == false)
		{
			std::string wyjatek = "Please check for that texture!";
			throw wyjatek;
		}
		buttonY.setRadius(20 * scale);
		buttonYTexture.setSmooth(true);
		buttonY.setTexture(&buttonYTexture);
		buttonY.setOrigin(20 * scale, 20 * scale);
	}
	catch (std::string wyjatek)
	{
		std::cout << wyjatek << std::endl;
		system("pause");
		exit(0);
	}
}

void TowerManager::loadBowTexture()
{
	try
	{
		bool a = buttonArrowTexture.loadFromFile("Textures/bow.png");
		if (a == false)
		{
			std::string wyjatek = "Please check for that texture!";
			throw wyjatek;
		}
		buttonArrow.setSize(sf::Vector2f(40 * scale, 40 * scale));
		buttonArrowTexture.setSmooth(true);
		buttonArrow.setTexture(&buttonArrowTexture);
		buttonArrow.setOrigin(20 * scale, 20 * scale);
	}
	catch (std::string wyjatek)
	{
		std::cout << wyjatek << std::endl;
		system("pause");
		exit(0);
	}
}

void TowerManager::loadFireballTexture()
{
	try
	{
		bool a = buttonFireballTexture.loadFromFile("Textures/fireball.png");
		if (a == false)
		{
			std::string wyjatek = "Please check for that texture!";
			throw wyjatek;
		}
		buttonFireball.setSize(sf::Vector2f(40 * scale, 40 * scale));
		buttonFireballTexture.setSmooth(true);
		buttonFireball.setTexture(&buttonFireballTexture);
		buttonFireball.setOrigin(20 * scale, 20 * scale);
	}
	catch (std::string wyjatek)
	{
		std::cout << wyjatek << std::endl;
		system("pause");
		exit(0);
	}
}

void TowerManager::loadInfoTowerTexture()
{
	try
	{
		bool a = towerInfoTexture.loadFromFile("Textures/infoTower.png");
		if (a == false)
		{
			std::string wyjatek = "Please check for that texture!";
			throw wyjatek;
		}
		towerInfo.setSize(sf::Vector2f(430 * scale, 350 * scale));
		towerInfoTexture.setSmooth(true);
		towerInfo.setTexture(&towerInfoTexture);
		towerInfo.setPosition(-500, 0);
	}
	catch (std::string wyjatek)
	{
		std::cout << wyjatek << std::endl;
		system("pause");
		exit(0);
	}
}

void TowerManager::loadFont()
{
	try
	{
		bool a = ttf.loadFromFile("fonts/towerInfo.ttf");
		if (a == false)
		{
			std::string wyjatek = "Please check for that Font!";
			throw wyjatek;
		}
		towerLevel.setFont(ttf);
		towerDmg.setFont(ttf);
		towerRange.setFont(ttf);
		arrowCost.setFont(ttf);
		fireballCost.setFont(ttf);
		arrowUpgradeCost.setFont(ttf);
		fireballUpgradeCost.setFont(ttf);
	}
	catch (std::string wyjatek)
	{
		std::cout << wyjatek << std::endl;
		system("pause");
		exit(0);
	}
}
