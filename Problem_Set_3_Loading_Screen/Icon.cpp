#include "Icon.h"

#include "TextureManager.h"

Icon::Icon(String name, int texture_index) : AGameObject(name), m_texture_index(texture_index)
{
	sf::Texture* texture = TextureManager::getInstance()->getStreamTextureFromList(texture_index);
	this->m_sprite = new sf::Sprite(*texture);
}

Icon::~Icon() 
{
	delete this->m_sprite;
}

void Icon::processInput(const std::optional<sf::Event> event) {}

void Icon::update(sf::Time delta_time) {}
