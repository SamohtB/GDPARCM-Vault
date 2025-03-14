#include "LoadingOrb.h"
#include "config.h"

LoadingOrb::LoadingOrb() : AGameObject("Spotlight")
{
	this->setPosition({ WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f });
	this->velocity = sf::Vector2f(static_cast<float>((rand() % 400 - 200)), static_cast<float>((rand() % 400 - 200)));
}

LoadingOrb::~LoadingOrb()
{
}

void LoadingOrb::processInput(const std::optional<sf::Event> event)
{
}

void LoadingOrb::update(sf::Time deltaTime)
{   
	sf::Vector2f newPosition = this->getPosition() + this->velocity * deltaTime.asSeconds();
	float radiusX = this->radius * WINDOW_WIDTH;
	float radiusY = this->radius * WINDOW_HEIGHT;

	if (this->progress >= 1.0f)
	{
		this->setPosition({ WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f });
		this->velocity = { 0.0f, 0.0f };
	}

	else if (radiusY * 2.0f >= WINDOW_HEIGHT - 50.0f)
	{
		sf::Vector2f center(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f);
		sf::Vector2f currentPosition = this->getPosition();
		sf::Vector2f direction = center - currentPosition;

		this->setPosition(currentPosition + direction * (deltaTime.asSeconds() * (1.0f - this->progress) * 5.0f));
	}

	else
	{
		if (newPosition.x - radiusX <= 0)
		{
			this->velocity.x = std::abs(this->velocity.x);
			newPosition.x = radiusX;
		}
		else if (newPosition.x + radiusX >= WINDOW_WIDTH)
		{
			this->velocity.x = -std::abs(this->velocity.x);
			newPosition.x = WINDOW_WIDTH - radiusX;
		}

		if (newPosition.y - radiusY <= 0)
		{
			this->velocity.y = std::abs(this->velocity.y);
			newPosition.y = radiusY;
		}
		else if (newPosition.y + radiusY >= WINDOW_HEIGHT)
		{
			this->velocity.y = -std::abs(this->velocity.y);
			newPosition.y = WINDOW_HEIGHT - radiusY;
		}

		this->setPosition(newPosition);
	}    
}

void LoadingOrb::draw(sf::RenderWindow* targetWindow)
{
}

void LoadingOrb::setOuterRadius(float radius)
{
    this->radius = radius;
}

void LoadingOrb::setProgress(float progress)
{
    this->progress = progress;
}
