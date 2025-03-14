#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "config.h"
#include "IExecutionEvent.h"

class LevelLoader;

class Game : public IExecutionEvent
{
public:
	Game();
	~Game();

	void run();
	void onFinishedExecution() override;

private:
	sf::RenderWindow m_window;
	sf::Time TIME_PER_FRAME = sf::seconds(1.f / FRAME_LIMIT);

	void update(sf::Time elapsed_time);
	void render();
	void processEvents();

	void onClose(const sf::Event::Closed&);

	LevelLoader* levelLoader = nullptr;
};

