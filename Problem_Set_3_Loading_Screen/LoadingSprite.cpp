#include "LoadingSprite.h"
#include "TextureManager.h"
#include "GameObjectManager.h"
#include "LevelLoader.h"
#include "LoadingOrb.h"
#include "config.h"

LoadingSprite::LoadingSprite(LevelLoader* tracker) : AGameObject("Loading Sprite"), progressTracker(tracker)
{
    sf::Texture* texture = TextureManager::getInstance()->getFromTextureMap("Stage1", 0);
    this->m_sprite = new sf::Sprite(*texture);

    this->fillShader = new sf::Shader(L"Media/Shaders/FragmentShader.frag", sf::Shader::Type::Fragment);

    if (this->fillShader == nullptr)
    {
        std::cerr << "Error Loading Shader!" << std::endl;
    }

	this->fillShader->setUniform("resolution", sf::Vector2f({ WINDOW_WIDTH, WINDOW_HEIGHT }));

	this->orb = new LoadingOrb();
	GameObjectManager::getInstance()->addGameObject(this->orb);

	this->maxRadius = sqrt(WINDOW_WIDTH * WINDOW_WIDTH + WINDOW_HEIGHT * WINDOW_HEIGHT) / 2.0f;
	this->maxRadius /= WINDOW_WIDTH;
}


LoadingSprite::~LoadingSprite()
{
}

void LoadingSprite::processInput(const std::optional<sf::Event> event)
{
}

void LoadingSprite::update(sf::Time deltaTime)
{
	float progress = this->progressTracker->getProgress();

	sf::Vector2f orbPosition = this->orb->getPosition();
	this->fillShader->setUniform("center", sf::Vector2f(orbPosition.x / WINDOW_WIDTH, orbPosition.y / WINDOW_HEIGHT));

	float innerRadius = 0.05f + progress * maxRadius;
	float outerRadius = 0.1f + progress * maxRadius * 1.1f;

	this->fillShader->setUniform("innerRadius", innerRadius);
	this->fillShader->setUniform("outerRadius", outerRadius);

	this->orb->setOuterRadius(outerRadius);
	this->orb->setProgress(progress);

	/*std::cout << "Progress: " << progress * 100 << "% | Inner Radius: " << innerRadius
		<< " | Outer Radius: " << outerRadius << std::endl;*/
}


void LoadingSprite::draw(sf::RenderWindow* targetWindow)
{
	if (this->m_sprite != nullptr && this->fillShader != nullptr)
	{
		targetWindow->draw(*this->m_sprite, this->fillShader);
		//targetWindow->draw(*this->m_sprite);
	}
}
