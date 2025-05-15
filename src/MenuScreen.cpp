#include <SFML/Graphics.hpp>

#include <memory>
#include <iostream>

#include "include/GameScreen.h"
#include "include/MenuScreen.h"
#include "include/Game.h"

using namespace sfSnake;

// const float MenuScreen::SettingButtonWidth = 100.f;
// const float MenuScreen::SettingButtonHeight = 50.f;

MenuScreen::MenuScreen()
{
	font_.loadFromFile("assets/fonts/game_over.ttf");
	text_.setFont(font_);
	text_.setString(
		"\n\n\n\n\n\n\n\n\nPress [SPACE] to play"
		"\n\nPress [ESC] to quit");

	snakeText_.setFont(font_);
	snakeText_.setString("Snake!");
	snakeText_.setColor(sf::Color::Green);
	snakeText_.setCharacterSize(64);
	snakeText_.setStyle(sf::Text::Bold);

	sf::FloatRect textBounds = text_.getLocalBounds();
	text_.setOrigin(textBounds.left + textBounds.width / 2,
		textBounds.top + textBounds.height / 2);
	text_.setPosition(Game::Width / 2, Game::Height / 2);

	sf::FloatRect snakeTextBounds = snakeText_.getLocalBounds();
	snakeText_.setOrigin(snakeTextBounds.left + snakeTextBounds.width / 2,
		snakeTextBounds.top + snakeTextBounds.height / 2);
	snakeText_.setPosition(Game::Width / 2, Game::Height / 4);

	setting_button_.setSize(sf::Vector2f(100.f, 50.f));
	setting_button_.setOrigin(50.f, 25.f);
	setting_button_.setPosition(Game::Width / 2, 3 * Game::Height / 4);
	setting_button_.setFillColor(sf::Color::Blue);
	
}

void MenuScreen::handleInput(sf::RenderWindow& window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		Game::GameContext.change_screen = true;
		Game::GameContext.game_state = GameState::ON;
		Game::GameContext.prev_screen = ScreenId::MENU_SCREEN;
		Game::GameContext.current_screen = ScreenId::GAME_SCREEN;
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		window.close();
	
	// TODO:与上面的逻辑合并
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		auto mouse_pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
		if (setting_button_.getGlobalBounds().contains(mouse_pos)) {
			Game::GameContext.change_screen = true;
			Game::GameContext.prev_screen = ScreenId::MENU_SCREEN;
			Game::GameContext.current_screen = ScreenId::SETTING_SCREEN;
		}
	}
	
	
}

void MenuScreen::update(sf::Time delta)
{
	static bool movingLeft = false;
	static bool movingRight = true;

	if (movingRight)
	{
		snakeText_.rotate(delta.asSeconds());

		if (static_cast<int>(snakeText_.getRotation()) == 10)
		{
			movingRight = false;
			movingLeft = true;
		}
	}

	if (movingLeft)
	{
		snakeText_.rotate(-delta.asSeconds());

		if (static_cast<int>(snakeText_.getRotation()) == (360 - 10))
		{
			movingLeft = false;
			movingRight = true;
		}
	}
}

void MenuScreen::render(sf::RenderWindow& window)
{
	window.draw(text_);
	window.draw(snakeText_);
	window.draw(setting_button_);
}
