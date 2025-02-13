#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

using String = std::string;
using SpritePtr = std::unique_ptr<sf::Sprite>;

class AGameObject
{
public:
	AGameObject(String name);
	~AGameObject();

	virtual void processInput(const std::optional<sf::Event> event) = 0;
	virtual void update(sf::Time delta_time) = 0;
	virtual void draw(sf::RenderWindow* target_window);

	String getName() const;

	virtual void setPosition(sf::Vector2f position);
	virtual sf::Vector2f getPosition();

	virtual void setScale(sf::Vector2f scale);
	virtual sf::Vector2f getScale();

	virtual sf::FloatRect getLocalBounds();

protected:
	std::string m_name;
	SpritePtr m_sprite = nullptr;

	sf::Vector2f m_position = {0.0f, 0.0f};
	sf::Vector2f m_scale = {1.0f, 1.0f};
};

