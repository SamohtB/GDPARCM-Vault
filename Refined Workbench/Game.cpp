#include "Game.h"

#include "GameObjectManager.h"
#include "TextureManager.h"

#include "IconDisplay.h"
#include "Background.h"
#include "FPSCounter.h"

const float FRAME_RATE = 60.0f;
const sf::Time Game::TIME_PER_FRAME = sf::seconds(1.0f / FRAME_RATE);
Game* Game::sharedInstance = nullptr;

Game::Game() : m_window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "PS2 Batch Asset Loader", sf::Style::Close)
{
	sharedInstance = this;
	this->m_window.setFramerateLimit(static_cast<int>(FRAME_RATE));

	GameObjectManager::initialize();
	TextureManager::initialize();

	TextureManager::getInstance()->loadFromAssetList();

	auto background = new Background("BGObject");
	GameObjectManager::getInstance()->addGameObject(background);

	auto display = new IconDisplay();
	GameObjectManager::getInstance()->addGameObject(display);

	auto counter = new FPSCounter();
	GameObjectManager::getInstance()->addGameObject(counter);
}

Game::~Game() {}

void Game::run()
{
	sf::Clock clock;
	sf::Time previousTime = clock.getElapsedTime();
	sf::Time currentTime;

	while (this->m_window.isOpen())
	{
		currentTime = clock.getElapsedTime();
		float deltaTime = currentTime.asSeconds() - previousTime.asSeconds();
		this->fps = floor(1.0f / deltaTime);

		processEvents();
		update(sf::seconds(1.0f / this->fps));
		render();

		previousTime = currentTime;
	}
}

Game* Game::getInstance()
{
	return sharedInstance;
}

float Game::getFPS() const
{
	return this->fps;
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
	GameObjectManager::destroy();
	TextureManager::destroy();
	m_window.close();
}







