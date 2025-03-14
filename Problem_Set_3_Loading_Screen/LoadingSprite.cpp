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

	sf::FloatRect spriteBounds = this->m_sprite->getLocalBounds();
	this->m_sprite->setOrigin(spriteBounds.getCenter());
	this->m_sprite->setPosition({ WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f });

    this->fillShader = new sf::Shader(L"Media/Shaders/FragmentShader.frag", sf::Shader::Type::Fragment);

    if (this->fillShader == nullptr)
    {
        std::cerr << "Error Loading Shader!" << std::endl;
    }

	this->fillShader->setUniform("resolution", sf::Vector2f({ WINDOW_WIDTH, WINDOW_HEIGHT }));

	this->orb = new LoadingOrb();
	GameObjectManager::getInstance()->addGameObject(this->orb);

	this->maxRadius = static_cast<float>(sqrt(WINDOW_WIDTH * WINDOW_WIDTH + WINDOW_HEIGHT * WINDOW_HEIGHT)) / 2.0f;
	this->maxRadius /= WINDOW_WIDTH;
	this->maxRadius += this->maxRadius * 0.5f;
}


LoadingSprite::~LoadingSprite()
{
}

void LoadingSprite::processInput(const std::optional<sf::Event> event)
{
}

void LoadingSprite::update(sf::Time deltaTime)
{
	this->ticks += deltaTime.asSeconds();

	/* fade out */
	if (fadingOut)
	{
		fadeAlpha -= fadeSpeed * deltaTime.asSeconds();

		if (fadeAlpha <= 0)
		{
			fadeAlpha = 0;
			GameObjectManager::getInstance()->deleteObject(this);
			return;
		}
	}

	/* loading process */
	float progress = this->progressTracker->getProgress();

	sf::Vector2f orbPosition = this->orb->getPosition();
	this->fillShader->setUniform("center", sf::Vector2f(orbPosition.x / WINDOW_WIDTH, orbPosition.y / WINDOW_HEIGHT));

	float innerRadius = 0.05f + progress * maxRadius;
	float outerRadius = 0.1f + progress * maxRadius * 1.1f;

	this->fillShader->setUniform("innerRadius", innerRadius);
	this->fillShader->setUniform("outerRadius", outerRadius);

	this->orb->setOuterRadius(outerRadius);
	this->orb->setProgress(progress);

	this->fillShader->setUniform("alpha", fadeAlpha / 255.0f);

	/*std::cout << "Progress: " << progress * 100 << "% | Inner Radius: " << innerRadius
		<< " | Outer Radius: " << outerRadius << std::endl;*/

	if (ticks >= 30.0f)
	{
		ticks = 0.0f;

		currentStage = (currentStage % 3) + 1;

		std::string nextTextureKey = "Stage" + std::to_string(currentStage);
		sf::Texture* nextTexture = TextureManager::getInstance()->getFromTextureMap(nextTextureKey, 0);

		if (nextTexture)
		{
			this->m_sprite->setTexture(*nextTexture);
		}
	}
}


void LoadingSprite::draw(sf::RenderWindow* targetWindow)
{
	if (this->m_sprite != nullptr && this->fillShader != nullptr)
	{
		targetWindow->draw(*this->m_sprite, this->fillShader);
		//targetWindow->draw(*this->m_sprite);
	}
}

void LoadingSprite::startFadeOut()
{
	this->fadingOut = true;
}
