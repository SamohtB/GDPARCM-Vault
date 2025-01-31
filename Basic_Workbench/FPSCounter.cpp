#include "FPSCounter.h"
#include "Game.h"

FPSCounter::FPSCounter() : AGameObject("FPSCounter") 
{
	sf::Font* font = new sf::Font("Media/Sansation.ttf");

	this->m_stats_text = new sf::Text(*font);
	this->m_stats_text->setPosition({ Game::WINDOW_WIDTH - 150, Game::WINDOW_HEIGHT - 70 });
	this->m_stats_text->setOutlineColor(sf::Color(1.0f, 1.0f, 1.0f));
	this->m_stats_text->setOutlineThickness(2.5f);
	this->m_stats_text->setCharacterSize(35);
}

FPSCounter::~FPSCounter() {}

void FPSCounter::processInput(const std::optional<sf::Event> event) {}

void FPSCounter::update(sf::Time delta_time)
{
	this->updateFPS(delta_time);
}

void FPSCounter::draw(sf::RenderWindow* target_window)
{
	target_window->draw(*m_stats_text);
}

void FPSCounter::updateFPS(sf::Time time_elapsed)
{
	this->m_update_time += time_elapsed;

	if (this->m_update_time >= sf::seconds(0.25f))
	{
		float fps = static_cast<float>(m_frames_passed) / m_update_time.asSeconds();
		this->m_stats_text->setString("FPS: " + std::to_string(static_cast<int>(fps)));

		this->m_update_time = sf::seconds(0.0f);
	}
}

