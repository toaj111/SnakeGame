#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>
#include <memory>
#include <unordered_map>

#include "Screen.h"

namespace sfSnake
{
enum class ScreenId {
	MENU_SCREEN, GAME_SCREEN, SETTING_SCREEN, GAME_OVER_SCREEN
};

enum class GameState {
	ON, OFF, PAUSE
};

struct Context {
	GameState game_state;
	bool change_screen;
	bool grid_on;
	sf::Color bg_color;
	sf::Color grid_color;
	ScreenId prev_screen;
	ScreenId current_screen;
	unsigned score;
};

class Game
{
public:
	Game();

	void run();

	void handleInput();
	void update(sf::Time delta);
	void render();

	static const int Width = 1600;
	static const int Height = 1200;
	static const int cell_size = Width / 20;

	static std::shared_ptr<Screen> CurrentScreen;
	static Context GameContext;

	static std::shared_ptr<Screen> GameScreenBuffer;
private:
	sf::RenderWindow window_;
	sf::Music bgMusic_;
	sf::VertexArray grid_lines_;
	static const sf::Time TimePerFrame;
};
}

