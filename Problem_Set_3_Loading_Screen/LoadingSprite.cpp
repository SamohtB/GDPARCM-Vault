#include "LoadingSprite.h"
#include "TextureManager.h"
#include "LevelLoader.h"
#include "config.h"

LoadingSprite::LoadingSprite(LevelLoader* tracker) : AGameObject("Loading Sprite"), progressTracker(tracker)
{
	sf::Texture* texture = TextureManager::getInstance()->getFromTextureMap("Card", 0);
	this->m_sprite = new sf::Sprite(*texture);
	this->m_sprite->setOrigin({ texture->getSize().x / 2.0f, texture->getSize().y / 2.0f });
	this->m_position = { WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 };

	this->fillShader = new sf::Shader(L"Media/Shaders/FillShader.frag", sf::Shader::Type::Fragment);

	if (this->fillShader == nullptr)
	{
		std::cerr << "Error Loading Shader!" << std::endl;
	}

	this->fillShader->setUniform("resolution", sf::Vector2f({ WINDOW_WIDTH, WINDOW_HEIGHT }));
	this->fillShader->setUniform("angle", 0.0f);
	this->fillShader->setUniform("offset", 0.0f);
}

LoadingSprite::~LoadingSprite()
{
	delete this->fillShader;
	delete this->m_sprite;
}

void LoadingSprite::processInput(const std::optional<sf::Event> event)
{
}

void LoadingSprite::update(sf::Time deltaTime)
{
	float progress = this->progressTracker ? this->progressTracker->getProgress() : 0.0f;

	float thickness = 0.05f + (2.0f - 0.05f) * progress;

	if (progress >= 1.0f)
	{
		thickness = 2.0f;
	}

	this->fillShader->setUniform("thickness", thickness);
}


void LoadingSprite::draw(sf::RenderWindow* targetWindow)
{
	if (this->m_sprite != nullptr && this->fillShader != nullptr)
	{
		this->m_sprite->setPosition(this->m_position);
		this->m_sprite->setScale(this->m_scale);
		targetWindow->draw(*this->m_sprite, this->fillShader);
	}
}
