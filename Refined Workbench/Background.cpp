#include "Background.h"
#include "TextureManager.h"
#include "Game.h"

Background::Background(String name) : AGameObject(name)
{
	std::cout << "Declared as " << this->getName() << std::endl;

	TexturePtr texture = TextureManager::getInstance()->getFromTextureMap("Desert", 0);
	texture->setRepeated(true);
	sf::Vector2u textureSize = texture->getSize();

	this->m_sprite = std::make_unique<sf::Sprite>(*texture);
	this->m_sprite->setTextureRect(sf::IntRect({ 0, 0 }, { Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT * 8 } ));
	this->setPosition({ 0, -Game::WINDOW_HEIGHT * 7 });
}

void Background::processInput(const std::optional<sf::Event> event) {}

void Background::update(sf::Time delta_time)
{
	sf::Vector2f position = this->getPosition();
	position.y += this->SPEED_MULTIPLIER * delta_time.asSeconds();
	this->setPosition(position);

	sf::Vector2f localPos = this->m_sprite->getPosition();
	if (localPos.y * delta_time.asSeconds() > 0) 
	{
		this->setPosition({ 0, -Game::WINDOW_HEIGHT * 7 });
	}
}
