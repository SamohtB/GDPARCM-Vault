#pragma once
#include "AGameObject.h"

class LevelLoader;

class LoadingSprite : public AGameObject
{
public:
	LoadingSprite(LevelLoader* loader);
	~LoadingSprite();

	void processInput(const std::optional<sf::Event> event) override;
	void update(sf::Time deltaTime) override;
	void draw(sf::RenderWindow* targetWindow) override;

	void setProgressMonitor(LevelLoader* tracker);

private:
	sf::Shader* fillShader = nullptr;
	LevelLoader* progressTracker = nullptr;

};

