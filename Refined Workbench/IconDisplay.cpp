#include "IconDisplay.h"
#include "GameObjectManager.h"
#include "TextureManager.h"
#include "Icon.h"

IconDisplay::IconDisplay() : AGameObject("IconDisplay") {}

IconDisplay::~IconDisplay()
{
	this->m_icon_list.clear();
}

void IconDisplay::processInput(const std::optional<sf::Event> event) {}

void IconDisplay::update(sf::Time delta_time)
{
	this->m_ticks += delta_time.asSeconds();

	if (this->m_streaming_type == SINGLE_STREAM && this->m_ticks > this->STREAMING_LOAD_DELAY)
	{
		this->m_ticks = 0.f;
		TextureManager::getInstance()->loadSingleAsset(this->m_num_displayed, this);
		this->m_num_displayed++;
	}
	else if (this->m_streaming_type == BATCH_LOAD && this->m_ticks > this->STREAMING_LOAD_DELAY && !this->m_started_streaming)
	{
		this->m_started_streaming = true;
		this->m_ticks = 0.f;
		TextureManager::getInstance()->loadStreamingAssets();
	}
}

void IconDisplay::onFinishedExecution()
{
	this->spawnObject();
}

void IconDisplay::spawnObject()
{
	this->guard.lock();	

	String objectName = "Icon_" + std::to_string(this->m_icon_list.size());
	auto icon = std::make_shared<Icon>(objectName, this->m_icon_list.size());
	this->m_icon_list.push_back(icon);

	int IMG_WIDTH = 68; int IMG_HEIGHT = 68;
	float x = static_cast<float>(this->m_column_grid * IMG_WIDTH);
	float y = static_cast<float>(this->m_row_grid * IMG_HEIGHT);
	icon->setPosition({x, y});

	std::cout << "Set position: " << x << " " << y << std::endl;

	this->m_column_grid++;

	if (this->m_column_grid == this->MAX_COLUMN)
	{
		this->m_column_grid = 0;
		this->m_row_grid++;
	}

	GameObjectManager::getInstance()->addGameObject(icon);
	this->guard.unlock();
}
