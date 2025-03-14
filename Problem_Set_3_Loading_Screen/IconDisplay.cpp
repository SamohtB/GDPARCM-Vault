#include "IconDisplay.h"
#include "GameObjectManager.h"
#include "TextureManager.h"
#include "config.h"
#include <corecrt_math_defines.h>

IconDisplay::IconDisplay() : AGameObject("Icon Display") 
{
    m_card_scale = static_cast<float>(WINDOW_HEIGHT) / (MAX_ROW * 1017);
    m_scaled_width = 727.0f * m_card_scale;
    m_scaled_height = 1017.0f * m_card_scale;

    MAX_COLUMN = static_cast<int>(275 / MAX_ROW);

	spawnAllIcons();

    m_max_scroll = std::max(0.0f, (m_icon_list.size() / MAX_ROW) * m_scaled_width - WINDOW_WIDTH);
}

void IconDisplay::processInput(const std::optional<sf::Event> event) 
{
    if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
    {
        this->m_is_moving = true;
    }
}

void IconDisplay::update(sf::Time delta_time)
{
    this->m_ticks += delta_time.asSeconds();

    if (m_is_moving)
    {
        float period = 60.0f;
        float t = std::fmod(this->m_ticks / period, 1.0f);

        offsetX = m_max_scroll * (0.5f * (1 - static_cast<float>(std::cos(t * M_PI))));

        for (int i = 0; i < m_icon_list.size(); ++i) {
            int row = i / MAX_COLUMN;
            int col = i % MAX_COLUMN;

            float x = (col * m_scaled_width) - offsetX;
            float y = row * m_scaled_height;

            m_icon_list[i]->setPosition({ x, y });
        }
    }
}

void IconDisplay::spawnObject(int id)
{
    String objectName = "Icon_" + std::to_string(id);
    Icon* icon = new Icon(objectName, id);
    this->m_icon_list.push_back(icon);

    icon->setScale({ m_card_scale , m_card_scale });

    float x = this->m_column_grid * m_scaled_width;
    float y = this->m_row_grid * m_scaled_height;
    icon->setPosition({ x, y });

    this->m_column_grid++;

    if (m_column_grid == WINDOW_WIDTH)
    {
        this->m_column_grid = 0;
        this->m_row_grid++;
    }

    GameObjectManager::getInstance()->addGameObjectBehind(icon);
}

void IconDisplay::spawnAllIcons()
{
    this->m_column_grid = 0;
    this->m_row_grid = 0;

    int count = TextureManager::getInstance()->getNumLoadedStreamTextures();

    for (int i = 0; i < count; i++) 
    {
        spawnObject(i);
    }
}
