#include "IconDisplay.h"
#include "GameObjectManager.h"
#include "TextureManager.h"

IconDisplay::IconDisplay() : AGameObject("Icon Display") {}

void IconDisplay::processInput(const std::optional<sf::Event> event) {}

void IconDisplay::update(sf::Time delta_time)
{
	this->m_ticks += delta_time.asSeconds();

	if (this->m_ticks >= SPAWN_TIME)
	{
		spawnObject();
		this->m_ticks = 0.f;
	}
}

void IconDisplay::spawnObject()
{
	int current_icon_count = static_cast<int>(this->m_icon_list.size());

	TextureManager::getInstance()->loadSingleAsset(current_icon_count);

	String objectName = "Icon_" + std::to_string(current_icon_count);
	Icon* icon = new Icon(objectName, current_icon_count);
	this->m_icon_list.push_back(icon);

	int IMG_WIDTH = 68; int IMG_HEIGHT = 68;
	float x = this->m_column_grid * IMG_WIDTH;
	float y = this->m_row_grid * IMG_HEIGHT;
	icon->setPosition({ x, y });

	std::cout << "Set position: " << x << " " << y << std::endl;

	this->m_column_grid++;

	if (this->m_column_grid == this->MAX_COLUMN)
	{
		this->m_column_grid = 0;
		this->m_row_grid++;
	}

	GameObjectManager::getInstance()->addGameObject(icon);
}
