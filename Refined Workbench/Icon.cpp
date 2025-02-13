#include "Icon.h"

#include "TextureManager.h"

Icon::Icon(String name, int texture_index) : AGameObject(name), m_texture_index(texture_index)
{
	TexturePtr texture = TextureManager::getInstance()->getStreamTextureFromList(texture_index);
	this->m_sprite = std::make_unique<sf::Sprite>(*texture);
}

Icon::~Icon() {}

void Icon::processInput(const std::optional<sf::Event> event) {}

void Icon::update(sf::Time delta_time) {}
