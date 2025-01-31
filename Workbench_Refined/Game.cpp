#include "Game.h"

#include "GameObjectManager.h"
#include "TextureManager.h"

#include "IconDisplay.h"
#include "Background.h"
#include "FPSCounter.h"

Game::Game() : m_window(sf::VideoMode({1920, 1080}), "Basic Workbench", sf::Style::Close)
{
	GameObjectManager::initialize();
	TextureManager::initialize();

	Background* background = new Background("BGObject");
	GameObjectManager::getInstance()->addGameObject(background);

	IconDisplay* display = new IconDisplay();
	GameObjectManager::getInstance()->addGameObject(display);

	FPSCounter* counter = new FPSCounter();
	GameObjectManager::getInstance()->addGameObject(counter);
}

Game::~Game() 
{
	GameObjectManager::destroy();
	TextureManager::destroy();
}

void Game::run()
{
	sf::Clock clock = sf::Clock();
	sf::Time time_since_last_update = sf::Time::Zero;

	while (this->m_window.isOpen())
	{
		sf::Time elapsed_time = clock.restart();
		time_since_last_update += elapsed_time;

		while (time_since_last_update > TIME_PER_FRAME)
		{
			time_since_last_update -= TIME_PER_FRAME;

			processEvents();
			//update(TIME_PER_FRAME);
			update(elapsed_time);
		}

		render();
	}
}

void Game::update(sf::Time elapsed_time)
{
	GameObjectManager::getInstance()->update(elapsed_time);
}

void Game::render()
{
	this->m_window.clear();
	GameObjectManager::getInstance()->draw(&this->m_window);
	this->m_window.display();
}

void Game::processEvents()
{
	while (const std::optional event = m_window.pollEvent())
	{
		if (event->is<sf::Event::Closed>())
		{
			m_window.close();
		}

		GameObjectManager::getInstance()->processInput(event);
	}
}

void Game::onClose(const sf::Event::Closed&)
{
	m_window.close();
}







