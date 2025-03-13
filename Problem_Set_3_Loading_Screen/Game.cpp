#include "Game.h"

#include "GameObjectManager.h"
#include "TextureManager.h"
#include "LevelLoader.h"

#include "Icon.h"
#include "LoadingSprite.h"

Game::Game() : m_window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), WINDOW_TITLE, sf::Style::Close, sf::State::Fullscreen)
{
	GameObjectManager::initialize();
	TextureManager::initialize();

	LevelLoader* levelLoader = new LevelLoader(this);

	/* add interactive loader assets here */
	LoadingSprite* loader = new LoadingSprite(levelLoader);
	GameObjectManager::getInstance()->addGameObject(loader);

	levelLoader->start();
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
			update(TIME_PER_FRAME);
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

void Game::onFinishedExecution()
{
	std::cout << "Level Loaded" << std::endl;

	Icon* icon = new Icon("Test", 0);
	GameObjectManager::getInstance()->addGameObject(icon);

	icon = new Icon("Test_1", 1);
	icon->setPosition({0.0f, WINDOW_HEIGHT / 2});
	GameObjectManager::getInstance()->addGameObject(icon);
}