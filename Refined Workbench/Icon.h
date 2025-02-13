#pragma once
#include "AGameObject.h"
class Icon : public AGameObject
{
public:
	Icon(String name, int texture_index);
	~Icon();

	// Inherited via AGameObject
	void processInput(const std::optional<sf::Event> event) override;
	void update(sf::Time delta_time) override;

private:
	int m_texture_index = 0;
};

