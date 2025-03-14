#pragma once
#include "AGameObject.h"
class LoadingOrb :  public AGameObject
{
public:
	LoadingOrb();
	~LoadingOrb();

	void processInput(const std::optional<sf::Event> event) override;
	void update(sf::Time deltaTime) override;
	void draw(sf::RenderWindow* targetWindow) override;

	void setOuterRadius(float radius);
	void setProgress(float progress);
private:
	sf::Vector2f velocity = {0.f,0.f};
	float radius = 0;
	float progress = 0;
	float threshold = 0;
};

