#pragma once
#include "AGameObject.h"

class LevelLoader;
class LoadingOrb;

class LoadingSprite : public AGameObject
{
public:
	LoadingSprite(LevelLoader* loader);
	~LoadingSprite();

	void processInput(const std::optional<sf::Event> event) override;
	void update(sf::Time deltaTime) override;
	void draw(sf::RenderWindow* targetWindow) override;

private:
	sf::Shader* fillShader = nullptr;
	LevelLoader* progressTracker = nullptr;
	LoadingOrb* orb = nullptr;

	float maxRadius = 0.0f;
};

