#pragma once
#include "AGameObject.h"

class FPSCounter : public AGameObject
{
public:
	FPSCounter();
	~FPSCounter();

	void processInput(const std::optional<sf::Event> event) override;
	void update(sf::Time delta_time) override;
	void draw(sf::RenderWindow* targetWindow) override;

private:
	sf::Time m_update_time;
	sf::Text* m_stats_text;
	int m_frames_passed = 0;

	void updateFPS(sf::Time elapsed_time);
};

