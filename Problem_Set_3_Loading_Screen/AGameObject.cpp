#include "AGameObject.h"

AGameObject::AGameObject(String name) : m_name(name) {}

AGameObject::~AGameObject() {}

void AGameObject::draw(sf::RenderWindow* target_window)
{
	if (this->m_sprite != NULL) 
	{
		this->m_sprite->setPosition(this->m_position);
		this->m_sprite->setScale(this->m_scale);
		target_window->draw(*this->m_sprite);
	}
}

String AGameObject::getName()
{
	return this->m_name;
}

void AGameObject::setPosition(sf::Vector2f position)
{
	this->m_position = position;

	if (this->m_sprite != nullptr)
	{
		this->m_sprite->setPosition(position);
	}
}

sf::Vector2f AGameObject::getPosition()
{
	return this->m_position;
}

void AGameObject::setScale(sf::Vector2f scale)
{
	this->m_scale = scale;

	if(this->m_sprite != nullptr)
	{
		this->m_sprite->setScale(scale);
	}
}
