#pragma once
#include "AGameObject.h"
#include "Icon.h"

class IconDisplay : public AGameObject
{
public:
	IconDisplay();
	void processInput(const std::optional<sf::Event> event) override;
	void update(sf::Time delta_time) override;

private:
	typedef std::vector<Icon*> IconList;
	IconList m_icon_list;

	float m_ticks = 0.0f;
	const float SPAWN_TIME = 1.f;

	int m_column_grid = 0; int m_row_grid = 0;

	const int MAX_COLUMN = 28;
	const int MAX_ROW = 22;

	void spawnObject();
};


