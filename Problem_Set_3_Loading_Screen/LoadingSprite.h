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

	void startFadeOut();

private:
	sf::Shader* fillShader = nullptr;
	LevelLoader* progressTracker = nullptr;
	LoadingOrb* orb = nullptr;

	float ticks = 0.0f;
	int currentStage = 0;
	float transitionAlpha = 0.0f;
	const float transitionSpeed = 2.0f;
	float maxRadius = 0.0f;

	bool fadingOut = false;
	float fadeAlpha = 255.0f;
	float fadeSpeed = 150.0f;
};
