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

	int m_column_grid = 0; int m_row_grid = 0;
	int MAX_COLUMN = 0;
	const int MAX_ROW = 5;
	const float SCROLL_SPEED = 500.0f;

	float offsetX = 0.0f;
	float m_card_scale = 0;
	float m_scaled_width = 0;
	float m_scaled_height = 0;
	float m_max_scroll = 0;
	bool m_is_moving = false;

	void spawnObject(int id);
	void spawnAllIcons();
};