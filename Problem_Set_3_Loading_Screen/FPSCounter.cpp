#include "FPSCounter.h"
#include "Game.h"

FPSCounter::FPSCounter() : AGameObject("FPSCounter") 
{
	sf::Font* font = new sf::Font("Media/Sansation.ttf");

	this->m_stats_text = new sf::Text(*font);
	this->m_stats_text->setPosition({ WINDOW_WIDTH - 150, WINDOW_HEIGHT - 70 });
	this->m_stats_text->setOutlineColor(sf::Color(1.0f, 1.0f, 1.0f));
	this->m_stats_text->setOutlineThickness(2.5f);
	this->m_stats_text->setCharacterSize(35);
}

FPSCounter::~FPSCounter() {}

void FPSCounter::processInput(const std::optional<sf::Event> event) {}

void FPSCounter::update(sf::Time delta_time)
{
}

void FPSCounter::draw(sf::RenderWindow* target_window)
{
	target_window->draw(*m_stats_text);
}

void FPSCounter::updateFPS(float averageFPS)
{
	this->m_stats_text->setString("FPS: " + std::to_string(static_cast<int>(averageFPS)));
}

