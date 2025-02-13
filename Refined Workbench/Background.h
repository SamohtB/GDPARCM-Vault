#pragma once
#include "AGameObject.h"
class Background : public AGameObject
{
public:
	Background(String name);

	void processInput(const std::optional<sf::Event> event);
	void update(sf::Time delta_time);
private:
	const float SPEED_MULTIPLIER = 100.0f;

};

