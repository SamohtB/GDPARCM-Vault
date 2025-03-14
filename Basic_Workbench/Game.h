#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Game
{
public:
	static const int WINDOW_WIDTH = 1920;
	static const int WINDOW_HEIGHT = 1080;

	Game();
	~Game();

	void run();

private:
	sf::RenderWindow m_window;
	sf::Time TIME_PER_FRAME = sf::seconds(1.f / 60.f);

	void update(sf::Time elapsed_time);
	void render();
	void processEvents();

	void onClose(const sf::Event::Closed&);
};

