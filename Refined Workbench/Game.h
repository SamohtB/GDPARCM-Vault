#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Game
{
public:
	static const sf::Time	TIME_PER_FRAME;
	static const int WINDOW_WIDTH = 1920;
	static const int WINDOW_HEIGHT = 1080;

	Game();
	~Game();

	void run();

	static Game* getInstance();
	static Game* sharedInstance;
	float getFPS() const;

private:
	sf::RenderWindow m_window;
	float fps = 0.0f;

	void update(sf::Time elapsed_time);
	void render();
	void processEvents();

	void onClose(const sf::Event::Closed&);
};

