#include "PressAnyKeyPrompt.h"
#include "GameObjectManager.h"
#include "LoadingSprite.h"
#include "config.h"

PressAnyKeyPrompt::PressAnyKeyPrompt(LoadingSprite* loadingScreen) : AGameObject("PressAnyKeyPrompt"), loadingSprite(loadingScreen)
{
    this->m_font = new sf::Font("Media/Sansation.ttf");

    if (m_font == nullptr)
    {
        std::cerr << "Failed to load font" << std::endl;
    }

    this->m_text = new sf::Text(*this->m_font);

    if (m_text == nullptr)
    {
        std::cerr << "Failed to load text" << std::endl;
    }

    this->m_text->setString("Press Any Key To Continue");
    this->m_text->setCharacterSize(60);
    this->m_text->setOutlineColor(sf::Color::Black);
    this->m_text->setOutlineThickness(2.0f);
    this->m_text->setFillColor(sf::Color::White);

    sf::FloatRect textBounds = this->m_text->getLocalBounds();

    // Set origin to the center of the text
    this->m_text->setOrigin(textBounds.getCenter());

    // Position the text in the center of the window
    this->m_text->setPosition({ WINDOW_WIDTH * 0.5f, WINDOW_HEIGHT * 0.75f });
}

void PressAnyKeyPrompt::processInput(const std::optional<sf::Event> event)
{
    if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
    {
        startFadeOut();
        GameObjectManager::getInstance()->deleteObject(this);
    }
}

void PressAnyKeyPrompt::update(sf::Time delta_time) {}

void PressAnyKeyPrompt::draw(sf::RenderWindow* target_window)
{
    target_window->draw(*m_text);
}

void PressAnyKeyPrompt::startFadeOut()
{
    if (loadingSprite)
    {
        loadingSprite->startFadeOut();
    }
}
