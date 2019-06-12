#include "Menu.h"



Menu::Menu(sf::RenderWindow* _window)
{
	window = _window;
	menu.setSize(sf::Vector2f(1920 * scale, 1080 * scale));
	menu.setFillColor(sf::Color(200, 255, 200, 180));

	startButton.setSize(sf::Vector2f(200 * scale, 60 * scale));
	startButton.setOrigin((200 * scale) / 2, (60 * scale) / 2);
	startButton.setPosition((1920 * scale) / 2, 200 * scale);
	startButtonTexture.loadFromFile(("Textures/play button.png"));
	startButtonTexture.setSmooth(true);
	startButton.setTexture(&startButtonTexture);

	quitButton.setSize(sf::Vector2f(200 * scale, 60 * scale));
	quitButton.setOrigin((200 * scale) / 2, (60 * scale) / 2);
	quitButton.setPosition((1920 * scale) / 2, 400 * scale);
	quitButtonTexture.loadFromFile(("Textures/quit button.png"));
	quitButtonTexture.setSmooth(true);
	quitButton.setTexture(&quitButtonTexture);
}


Menu::~Menu()
{
}

void Menu::drawMenu()
{
	window->draw(menu);
	window->draw(startButton);
	window->draw(quitButton);
}

void Menu::action(Map &map)
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

