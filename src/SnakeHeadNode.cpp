#include <SFML/Graphics.hpp>
#include "include/SnakeHeadNode.h"
#include <cmath>

using namespace sfSnake;

SnakeHeadNode::SnakeHeadNode(sf::Vector2f position) : SnakeNode(position) {
    texture_.loadFromFile("assets/image/snake_head_image.png");
    sprite_.setTexture(texture_);
    sprite_.setOrigin(texture_.getSize().x / 2, texture_.getSize().y / 2);
    sprite_.setScale(2 * SnakeNode::Radius / texture_.getSize().x, 2 * SnakeNode::Radius / texture_.getSize().y);
    sprite_.setPosition(position_);
}

void SnakeHeadNode::setPosition(sf::Vector2f position) {
    position_ = position;
    sprite_.setPosition(position_);
}

void SnakeHeadNode::setPosition(float x, float y) {
    position_.x = x;
    position_.y = y;
    sprite_.setPosition(position_);
}

void SnakeHeadNode::move(float xOffset, float yOffset) {
    if (xOffset != 0 || yOffset != 0) {
        float angle = std::atan2(yOffset, xOffset) * 180.f / M_PI + 90.f;
        sprite_.setRotation(angle);
    }
    position_.x += xOffset;
	position_.y += yOffset;
	sprite_.setPosition(position_);
}

sf::FloatRect SnakeHeadNode::getBounds() const {
    return sprite_.getGlobalBounds();
}

sf::Vector2f SnakeHeadNode::getPosition() const {
    return position_;
}

void SnakeHeadNode::render(sf::RenderWindow& window) {
    window.draw(sprite_);
}

float SnakeHeadNode::getRotation() const {
    return sprite_.getRotation();
}
