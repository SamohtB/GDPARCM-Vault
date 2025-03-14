#include "Game.h"

#include "GameObjectManager.h"
#include "TextureManager.h"
#include "LevelLoader.h"

#include "Icon.h"
#include "IconDisplay.h"
#include "LoadingSprite.h"
#include "PressAnyKeyPrompt.h"

Game::Game() : m_window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), WINDOW_TITLE, sf::Style::Close, sf::State::Fullscreen)
{
	GameObjectManager::initialize();
	TextureManager::initialize();

	/* Create Level Loader Thread*/
	this->levelLoader = new LevelLoader(this);

	/* interactive Loading Screen here */
	this->loader = new LoadingSprite(levelLoader);
	GameObjectManager::getInstance()->addGameObject(loader);

	/* Start Level Loader Thread*/
	levelLoader->start();
}

Game::~Game() 
{
	delete this->levelLoader;
	delete this->loader;

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
	//sf::Color(173, 216, 230)
	this->m_window.clear(sf::Color(204, 179, 255));
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
		else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
		{
			if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
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

	IconDisplay* display = new IconDisplay();
	GameObjectManager::getInstance()->addGameObject(display);

	if (this->loader != nullptr)
	{
		PressAnyKeyPrompt* prompt = new PressAnyKeyPrompt(this->loader);
		GameObjectManager::getInstance()->addUIObject(prompt);
	}
	
}