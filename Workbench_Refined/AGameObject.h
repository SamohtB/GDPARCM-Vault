#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

typedef std::string String;

class AGameObject
{
public:
	AGameObject(String name);
	~AGameObject();

	virtual void processInput(const std::optional<sf::Event> event) = 0;
	virtual void update(sf::Time delta_time) = 0;
	virtual void draw(sf::RenderWindow* target_window);

	String getName();

	virtual void setPosition(sf::Vector2f position);
	virtual sf::Vector2f getPosition();

protected:
	std::string m_name;
	sf::Sprite* m_sprite = nullptr;

	sf::Vector2f m_position = {0.0f, 0.0f};
	sf::Vector2f m_scale = {1.0f, 1.0f};
};

