#include "include/SnakeBodyNode.h"
#include <cmath>

using namespace sfSnake;

SnakeBodyNode::SnakeBodyNode(sf::Vector2f position, float angle) : SnakeNode(position) {
    circle_shape_.setRadius(SnakeNode::Radius);
    circle_shape_.setOrigin(SnakeNode::Radius, SnakeNode::Radius);
    circle_shape_.setPosition(position_);
    circle_shape_.setFillColor(sf::Color::Yellow);
    circle_shape_.setRotation(angle);

    rectangle_shape_.setSize(sf::Vector2f(2 * SnakeNode::Radius, SnakeNode::Radius / 3));
    rectangle_shape_.setOrigin(sf::Vector2f(SnakeNode::Radius, SnakeNode::Radius / 6));
    rectangle_shape_.setPosition(position_);
    rectangle_shape_.setFillColor(sf::Color::Black);
    rectangle_shape_.setRotation(angle);
}

void SnakeBodyNode::setPosition(sf::Vector2f position) {
    position_ = position;
    rectangle_shape_.setPosition(position_);
    circle_shape_.setPosition(position_);
}

void SnakeBodyNode::setPosition(float x, float y) {
    position_.x = x;
    position_.y = y;
    rectangle_shape_.setPosition(position_);
    circle_shape_.setPosition(position_);
}

void SnakeBodyNode::move(float xOffset, float yOffset) {
    if (xOffset != 0 || yOffset != 0) {
        float angle = std::atan2(yOffset, xOffset) * 180.f / M_PI + 90.f;
        rectangle_shape_.setRotation(angle);
        circle_shape_.setRotation(angle);  
    }
    position_.x += xOffset;
    position_.y += yOffset;
    rectangle_shape_.setPosition(position_);
    circle_shape_.setPosition(position_);
}

void SnakeBodyNode::render(sf::RenderWindow& window) {
    window.draw(circle_shape_);
    window.draw(rectangle_shape_);
}

sf::Vector2f SnakeBodyNode::getPosition() const {
    return position_;
}

sf::FloatRect SnakeBodyNode::getBounds() const {
    return circle_shape_.getGlobalBounds();
}

float SnakeBodyNode::getRotation() const {
    return rectangle_shape_.getRotation();
}

