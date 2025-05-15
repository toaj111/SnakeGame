#include <SFML/Graphics.hpp>

#include <iostream>
#include <memory>

#include "Game.h"
#include "GameScreen.h"
#include "include/GameOverScreen.h"

using namespace sfSnake;

GameOverScreen::GameOverScreen(std::size_t score) : score_(score)
{
	font_.loadFromFile("assets/fonts/game_over.ttf");
	text_.setFont(font_);
	text_.setString("Your score: " + std::to_string(score) + "!"
		"\n\nPress [SPACE] to retry"
		"\n\nPress [ESC] to quit");
	text_.setColor(sf::Color::Red);

	sf::FloatRect textBounds = text_.getLocalBounds();
	text_.setOrigin(textBounds.left + textBounds.width / 2,
		textBounds.top + textBounds.height / 2);
	text_.setPosition(Game::Width / 2, Game::Height / 2);

	setting_button_.setSize(sf::Vector2f(100.f, 50.f));
	setting_button_.setOrigin(sf::Vector2f(50.f, 25.f));
	setting_button_.setPosition(Game::Width / 2, 3 * Game::Height / 4);
	setting_button_.setFillColor(sf::Color::Blue);
}

void GameOverScreen::handleInput(sf::RenderWindow& window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		Game::GameContext.prev_screen = ScreenId::MENU_SCREEN;
		Game::GameContext.current_screen = ScreenId::GAME_SCREEN;
		Game::GameContext.change_screen = true;
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		window.close();

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		auto mouse_pos = sf::Vector2f(sf::Mouse::getPosition(window));
		if (setting_button_.getGlobalBounds().contains(mouse_pos)) {
			Game::GameContext.current_screen = ScreenId::SETTING_SCREEN;
			Game::GameContext.prev_screen = ScreenId::GAME_OVER_SCREEN;
			Game::GameContext.change_screen = true;
		}
	}
}

void GameOverScreen::update(sf::Time delta)
{

}

void GameOverScreen::render(sf::RenderWindow& window)
{
	window.draw(text_);
	window.draw(setting_button_);
}