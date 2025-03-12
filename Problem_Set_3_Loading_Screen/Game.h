#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "config.h"
#include "IFinishedTask.h"

class Game : public IFinishedTask 
{
public:
	Game();
	~Game();

	void run();
	void onFinishedTask(int threadId) override;

private:
	sf::RenderWindow m_window;
	sf::Time TIME_PER_FRAME = sf::seconds(1.f / FRAME_LIMIT);

	void update(sf::Time elapsed_time);
	void render();
	void processEvents();

	void onClose(const sf::Event::Closed&);
};

