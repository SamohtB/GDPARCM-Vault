#pragma once
#include "AGameObject.h"

class LoadingSprite;

class PressAnyKeyPrompt : public AGameObject
{
public:
    PressAnyKeyPrompt(LoadingSprite* loadingScreen);

    void processInput(const std::optional<sf::Event> event) override;
    void update(sf::Time delta_time) override;
    void draw(sf::RenderWindow* target_window) override;

private:
    sf::Font* m_font = nullptr;
    sf::Text* m_text = nullptr;
    LoadingSprite* loadingSprite = nullptr;

    bool m_fading = false;
    float m_alpha = 255.0f;
    float fadeSpeed = 150.0f; // Controls how fast the fade happens

    void startFadeOut();
};
