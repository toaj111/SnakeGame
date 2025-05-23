#include <SFML/Graphics.hpp>

#include <random>
#include <memory>
#include <iostream>

#include "include/GameScreen.h"
#include "include/GameOverScreen.h"
#include "include/Game.h"

using namespace sfSnake;

GameScreen::GameScreen() : snake_()
{

}

void GameScreen::handleInput(sf::RenderWindow& window)
{
	snake_.handleInput(window);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		Game::GameContext.change_screen = true;
		Game::GameContext.prev_screen = ScreenId::GAME_SCREEN;
		Game::GameContext.current_screen = ScreenId::SETTING_SCREEN;
	}
}

void GameScreen::update(sf::Time delta)
{
	if (fruit_.size() == 0)
		generateFruit();

	snake_.update(delta);
	snake_.checkFruitCollisions(fruit_);

	if (snake_.hitSelf()) {
		Game::GameContext.change_screen = true;
		Game::GameContext.prev_screen = ScreenId::GAME_SCREEN;
		Game::GameContext.current_screen = ScreenId::GAME_OVER_SCREEN;
	}
}

void GameScreen::render(sf::RenderWindow& window)
{
	snake_.render(window);

	for (auto fruit : fruit_)
		fruit.render(window);
}

void GameScreen::generateFruit()
{
	static std::default_random_engine engine;
	engine.seed(time(NULL));
	static std::uniform_int_distribution<int> xDistribution(0, Game::Width - 2 * SnakeNode::Radius);
	static std::uniform_int_distribution<int> yDistribution(0, Game::Height - 2 * SnakeNode::Radius);

	fruit_.push_back(Fruit(sf::Vector2f(xDistribution(engine), yDistribution(engine))));
}

