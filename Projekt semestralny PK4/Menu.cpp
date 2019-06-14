#include "Menu.h"



Menu::Menu(sf::RenderWindow* _window)
{
	window = _window;
	menu.setSize(sf::Vector2f(1920 * scale, 1080 * scale));
	menu.setFillColor(sf::Color(200, 255, 200, 180));

	startButton.setSize(sf::Vector2f(400 * scale, 120 * scale));
	startButton.setOrigin((400 * scale) / 2, (120 * scale) / 2);
	startButton.setPosition((1920 * scale) / 2, 200 * scale);
	menuButtonTexture.loadFromFile(("Textures/menu button.png"));
	menuButtonTexture.setSmooth(true);
	startButton.setTexture(&menuButtonTexture);

	restartButton.setSize(sf::Vector2f(400 * scale, 120 * scale));
	restartButton.setOrigin((400 * scale) / 2, (120 * scale) / 2);
	restartButton.setPosition((1920 * scale) / 2, 350 * scale);
	restartButton.setTexture(&menuButtonTexture);

	quitButton.setSize(sf::Vector2f(400 * scale, 120 * scale));
	quitButton.setOrigin((400 * scale) / 2, (120 * scale) / 2);
	quitButton.setPosition((1920 * scale) / 2, 500 * scale);
	quitButton.setTexture(&menuButtonTexture);

	ttf.loadFromFile("fonts/towerInfo.ttf");
	start.setFont(ttf);
	restart.setFont(ttf);
	quit.setFont(ttf);

	start.setCharacterSize(50 * scale);
	restart.setCharacterSize(50 * scale);
	quit.setCharacterSize(50 * scale);

	start.setFillColor(sf::Color::Black);
	restart.setFillColor(sf::Color::Black);
	quit.setFillColor(sf::Color::Black);

	start.setPosition(-100, -100);
	restart.setPosition(-100, -100);
	quit.setPosition(-100, -100);

	start.setString("Play");
	start.setPosition((1830 * scale) / 2, 175 * scale);
	restart.setString("Restart");
	restart.setPosition((1760 * scale) / 2, 325 * scale);
	quit.setString("Quit");
	quit.setPosition((1830 * scale) / 2, 475 * scale);
}


Menu::~Menu()
{
}

void Menu::drawMenu()
{
	window->draw(menu);
	window->draw(startButton);
	window->draw(restartButton);
	window->draw(quitButton);
	window->draw(start);
	window->draw(restart);
	window->draw(quit);
}

void Menu::action(Map &map, PlayerBase&player, std::vector<std::shared_ptr<Tower>>& towers, std::vector<std::shared_ptr<Enemy>>& enemies)
{
	while (window->isOpen())
	{
		map.drawMap(*window);
		drawMenu();
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window->close();
			}
			//operacje zwiazane z myszka
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
			{
				sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition(*window);
				if (isPlayClicked(mousePos))
					return;
				else if (isReplayClicked(mousePos))
				{
					for (auto t : towers)
					{
						t->getPlace()->setOccupied(false);
					}
					towers.clear();
					enemies.clear();
					player.setCash(50);
					player.setPoints(0);
					player.setLifes(20);
					return;
				}
				else if (isQuitClicked(mousePos))
					window->close();
			}
		}
		window->display();
	}
}

bool Menu::isPlayClicked(sf::Vector2f mousePosition)
{
	if (startButton.getGlobalBounds().contains(mousePosition))
		return true;
}

bool Menu::isQuitClicked(sf::Vector2f mousePosition)
{
	if (quitButton.getGlobalBounds().contains(mousePosition))
		return true;
}

bool Menu::isReplayClicked(sf::Vector2f mousePosition)
{
	if (restartButton.getGlobalBounds().contains(mousePosition))
		return true;
}
