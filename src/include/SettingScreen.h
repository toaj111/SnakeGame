#pragma once

#include "Screen.h"

namespace sfSnake {

class SettingScreen : public Screen {
public:
	SettingScreen();
	void handleInput(sf::RenderWindow& window) override;
	void update(sf::Time delta) override;
	void render(sf::RenderWindow& window) override;


private:
	sf::Font font_;

	// 0: white 1: black 2: brown
	std::vector<sf::Text> bg_buttons_;
	// 0: off 1: on
	std::vector<sf::Text> grid_on_buttons_;
	// 0: white 1: black 2: brown
	std::vector<sf::Text> grid_color_buttons_;

	std::vector<sf::Text> description_texts_;
	
	sf::CircleShape esc_button_button_;

	sf::Texture esc_button_texture_;

	// 0: white 1: black 2: brown
	int bg_color_;

	// 0: off 1: on
	int grid_on_;

	// 0: white 1: black 2: brown
	int grid_color_;

	static const float BgButtonWidth;
	static const float BgButtonHeight;

	static const float EscButtonSize;
};
};