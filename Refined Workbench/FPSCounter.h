#pragma once
#include "AGameObject.h"
#include "SFML/Graphics.hpp"

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
	std::unique_ptr<sf::Text> m_stats_text;

	void updateFPS(sf::Time elapsed_time);
};

