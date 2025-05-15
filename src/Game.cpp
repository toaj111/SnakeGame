#include <SFML/Graphics.hpp>

#include <memory>
#include <iostream>

#include "MenuScreen.h"
#include "GameScreen.h"
#include "GameOverScreen.h"
#include "SettingScreen.h"
#include "include/Game.h"

using namespace sfSnake;

const sf::Time Game::TimePerFrame = sf::seconds(1.f / 10.f);

std::shared_ptr<Screen> Game::CurrentScreen = std::make_shared<MenuScreen>();
std::shared_ptr<Screen> Game::GameScreenBuffer = nullptr;

Context	Game::GameContext{GameState::OFF, false, false, sf::Color::White, sf::Color::Black, ScreenId::MENU_SCREEN, ScreenId::MENU_SCREEN, 0};

Game::Game()
: window_(sf::VideoMode(Game::Width, Game::Height), "sfSnake")
{
	// 打开背景音乐文件
	bgMusic_.openFromFile("assets/music/bg_music.wav");
	bgMusic_.setLoop(true);
	bgMusic_.play();
}

void Game::handleInput()
{
	sf::Event event;

	// 处理用户对主窗口的操作
	while (window_.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window_.close();
	}

	Game::CurrentScreen->handleInput(window_);
}

void Game::update(sf::Time delta)
{
	Game::CurrentScreen->update(delta);

	if (GameContext.change_screen) {
		switch (GameContext.current_screen) {
			case ScreenId::GAME_SCREEN:
				if (GameContext.game_state == GameState::PAUSE) {
					Game::CurrentScreen = std::move(GameScreenBuffer);
				} else {
					Game::CurrentScreen = std::make_shared<GameScreen>();
				}
				GameContext.game_state = GameState::ON;
				break;
			case ScreenId::MENU_SCREEN:
				Game::CurrentScreen = std::make_shared<MenuScreen>();
				GameContext.game_state = GameState::OFF;
				break;
			case ScreenId::SETTING_SCREEN:
				if (GameContext.prev_screen == ScreenId::GAME_SCREEN) {
					GameScreenBuffer = std::move(Game::CurrentScreen);
					Game::CurrentScreen = std::make_shared<SettingScreen>();
					GameContext.game_state = GameState::PAUSE;
				} else {
					Game::CurrentScreen = std::make_shared<SettingScreen>();
					GameContext.game_state = GameState::OFF;
				}
				break;
			case ScreenId::GAME_OVER_SCREEN:
				GameScreenBuffer.reset();
				Game::CurrentScreen = std::make_shared<GameOverScreen>(GameContext.score);
				GameContext.game_state = GameState::OFF;
				break;
		}


		GameContext.change_screen = false;
	}
}

void Game::render()
{
	// TODO:设置界面，菜单界面
	if (GameContext.game_state == GameState::ON) {
		window_.clear(GameContext.bg_color);
	} else {
		window_.clear(sf::Color::White);
	}
	Game::CurrentScreen->render(window_);
	window_.display();
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	// 当窗口保持打开时进入游戏循环
	while (window_.isOpen())
	{
		// 距离上一次循环隔了多久
		sf::Time delta = clock.restart();

		// 距离上一次更新隔了多久
		timeSinceLastUpdate += delta;

		// 当大于每一帧的时间后，更新相应次数的帧
		while (timeSinceLastUpdate > Game::TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			handleInput();
			update(TimePerFrame);
		}

		render();
	}
}