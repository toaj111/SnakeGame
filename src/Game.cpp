#include <SFML/Graphics.hpp>

#include <memory>

#include "MenuScreen.h"
#include "include/Game.h"

using namespace sfSnake;

const sf::Time Game::TimePerFrame = sf::seconds(1.f / 10.f);

std::shared_ptr<Screen> Game::CurrentScreen = std::make_shared<MenuScreen>();

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
}

void Game::render()
{
	// 清理游戏窗口，并渲染下一帧
	window_.clear();
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