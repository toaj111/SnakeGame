#include "include/SettingScreen.h"
#include "include/Game.h"
#include "include/MenuScreen.h"
#include "include/GameScreen.h"
#include "include/GameOverScreen.h"
#include <iostream>

using namespace sfSnake;

const float SettingScreen::BgButtonHeight = 150.f;
const float SettingScreen::BgButtonWidth = 300.f;
const float SettingScreen::EscButtonSize = 50.f;

SettingScreen::SettingScreen() {
    std::cout << "setting screen created" << std::endl;
    font_.loadFromFile("assets/fonts/setting_screen_font.ttf");
    esc_button_texture_.loadFromFile("assets/image/go_back_ui.png");

    bg_buttons_.resize(3);
    grid_on_buttons_.resize(2);
    grid_color_buttons_.resize(3);
    description_texts_.resize(3);

    for (uint32_t i = 0; i < 3; i++) {
        bg_buttons_[i].setFont(font_);
        bg_buttons_[i].setCharacterSize(64);
        bg_buttons_[i].setStyle(sf::Text::Bold);

        switch (i) {
            case 0:
                bg_buttons_[i].setString(L"白色");
                bg_buttons_[i].setColor(sf::Color(128, 128, 128));
                break;  
            case 1:
                bg_buttons_[i].setString(L"黑色");
                bg_buttons_[i].setColor(sf::Color(128, 128, 128));
                break;
            case 2:
                bg_buttons_[i].setString(L"棕色");
                bg_buttons_[i].setColor(sf::Color(128, 128, 128));
                break;
        }
        sf::FloatRect button_bounds = bg_buttons_[i].getLocalBounds();
        bg_buttons_[i].setOrigin(button_bounds.left + button_bounds.width / 2,
        button_bounds.top + button_bounds.height / 2);
        
        bg_buttons_[i].setPosition(Game::Width / 5 + 3 * i * Game::Width / 10, Game::Height / 5);
    }

        

    for (uint32_t i = 0; i < 2; i++) {
        grid_on_buttons_[i].setFont(font_);
        grid_on_buttons_[i].setCharacterSize(64);
        grid_on_buttons_[i].setStyle(sf::Text::Bold);

        switch (i) {
            case 0:
                grid_on_buttons_[i].setString(L"关");
                grid_on_buttons_[i].setColor(sf::Color(128, 128, 128));
                break;
            case 1:
                grid_on_buttons_[i].setString(L"开");
                grid_on_buttons_[i].setColor(sf::Color(128, 128, 128));
                break;
        }
        sf::FloatRect button_bounds = grid_on_buttons_[i].getLocalBounds();
        grid_on_buttons_[i].setOrigin(button_bounds.left + button_bounds.width / 2,
        button_bounds.top + button_bounds.height / 2);

        grid_on_buttons_[i].setPosition(2 * Game::Width / 5 + i * Game::Width / 5, Game::Height / 2);
    }


    for (uint32_t i = 0; i < 3; i++) {
        grid_color_buttons_[i].setFont(font_);
        grid_color_buttons_[i].setCharacterSize(64);
        grid_color_buttons_[i].setStyle(sf::Text::Bold);

        switch (i) {
            case 0:
                grid_color_buttons_[i].setString(L"白色");
                grid_color_buttons_[i].setColor(sf::Color(128, 128, 128));
                break;  
            case 1:
                grid_color_buttons_[i].setString(L"黑色");
                grid_color_buttons_[i].setColor(sf::Color(128,128, 128));
                break;
            case 2:
                grid_color_buttons_[i].setString(L"棕色");
                grid_color_buttons_[i].setColor(sf::Color(128, 128, 128));
                break;
        }
        sf::FloatRect button_bounds = grid_color_buttons_[i].getLocalBounds();
        grid_color_buttons_[i].setOrigin(button_bounds.left + button_bounds.width / 2,
        button_bounds.top + button_bounds.height / 2);

        grid_color_buttons_[i].setPosition(Game::Width / 5 + 3 * i * Game::Width / 10, 4 * Game::Height / 5);
    }

    for (uint32_t i = 0; i < 3; i++) {
        description_texts_[i].setFont(font_);
        description_texts_[i].setCharacterSize(64);
        description_texts_[i].setStyle(sf::Text::Bold);
        description_texts_[i].setColor(sf::Color::Black);

        switch (i) {
            case 0:
                description_texts_[i].setString(L"背景颜色");
                break;
            case 1:
                description_texts_[i].setString(L"网格开关");
                break;
            case 2:
                description_texts_[i].setString(L"网格颜色");
                break;
        }
        sf::FloatRect descript_bounds = description_texts_[i].getLocalBounds();
        description_texts_[i].setOrigin(descript_bounds.left + descript_bounds.width / 2,
        descript_bounds.top + descript_bounds.height / 2);

        description_texts_[i].setPosition(Game::Width / 2, Game::Height / 10 + 3 * i * Game::Height / 10);
    }

    esc_button_button_.setRadius(EscButtonSize);
    esc_button_button_.setOrigin(EscButtonSize, EscButtonSize);
    esc_button_button_.setTexture(&esc_button_texture_);
    esc_button_button_.setPosition(sf::Vector2f(13 * Game::Width / 14, Game::Height / 12));

    if (Game::GameContext.grid_on) {
        grid_on_ = 1;
    } else {
        grid_on_ = 0;
    }

    if (Game::GameContext.bg_color == sf::Color::White) {
        bg_color_ = 0;
    } else if (Game::GameContext.bg_color == sf::Color::Black) {
        bg_color_ = 1;
    } else {
        bg_color_ = 2;
    }
    if (Game::GameContext.grid_color == sf::Color::White) {
        grid_color_ = 0;
    } else if (Game::GameContext.grid_color == sf::Color::Black) {
        grid_color_ = 1;
    } else {
        grid_color_ = 2;
    }

    bg_buttons_[bg_color_].setColor(sf::Color::Green);
    grid_on_buttons_[grid_on_].setColor(sf::Color::Green);
    grid_color_buttons_[grid_color_].setColor(sf::Color::Green);

}

void SettingScreen::handleInput(sf::RenderWindow& window) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        auto mouse_pos = sf::Mouse::getPosition(window);

        for (uint32_t i = 0; i < 3; i++) {
            if (bg_buttons_[i].getGlobalBounds().contains(sf::Vector2f(mouse_pos))) {
                switch (i) {
                    case 0:
                        Game::GameContext.bg_color = sf::Color::White;
                        break;
                    case 1:
                        Game::GameContext.bg_color = sf::Color::Black;
                        break;
                    case 2:
                        Game::GameContext.bg_color = sf::Color(128, 128, 128);
                        break;
                }
                bg_buttons_[bg_color_].setColor(sf::Color(128, 128, 128));
                bg_color_ = i;
                bg_buttons_[bg_color_].setColor(sf::Color::Green);
            }
        }

        for (uint32_t i = 0; i < 2; i++) {
            if (grid_on_buttons_[i].getGlobalBounds().contains(sf::Vector2f(mouse_pos))) {
                switch (i) {
                    case 0:
                        Game::GameContext.grid_on = false;
                        break;
                    case 1:
                        Game::GameContext.grid_on = true;
                        break;
                }
                grid_on_buttons_[grid_on_].setColor(sf::Color(128, 128, 128));
                grid_on_ = i;
                grid_on_buttons_[grid_on_].setColor(sf::Color::Green);
            }
        }

        for (uint32_t i = 0; i < 3; i++) {
            if (grid_color_buttons_[i].getGlobalBounds().contains(sf::Vector2f(mouse_pos))) {
                switch (i) {
                    case 0:
                        Game::GameContext.grid_color = sf::Color::White;
                        break;
                    case 1:
                        Game::GameContext.grid_color = sf::Color::Black;
                        break;
                    case 2:
                        Game::GameContext.grid_color = sf::Color(128, 128, 128);
                        break;
                }
                grid_color_buttons_[grid_color_].setColor(sf::Color(128, 128, 128));
                grid_color_ = i;
                grid_color_buttons_[grid_color_].setColor(sf::Color::Green);
            }
        }


        // TODO:从设置界面返回
        if (esc_button_button_.getGlobalBounds().contains(sf::Vector2f(mouse_pos)) || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            Game::GameContext.change_screen = true;
            std::swap(Game::GameContext.current_screen, Game::GameContext.prev_screen);
        }
    }
}

void SettingScreen::update(sf::Time delta) {

}

void SettingScreen::render(sf::RenderWindow& window) {
    for (const auto& bg_button : bg_buttons_) {
        window.draw(bg_button);
    }

    for (const auto& grid_on_button : grid_on_buttons_) {
        window.draw(grid_on_button);
    }

    for (const auto& grid_color_button : grid_color_buttons_) {
        window.draw(grid_color_button);
    }

    for (const auto& descript : description_texts_) {
        window.draw(descript);
    }

    window.draw(esc_button_button_);
}





