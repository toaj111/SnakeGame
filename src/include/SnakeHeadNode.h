#pragma once

#include "SnakeNode.h"

namespace sfSnake {
class SnakeHeadNode : public SnakeNode {
public:
    SnakeHeadNode(sf::Vector2f position = sf::Vector2f(0, 0));

	void setPosition(sf::Vector2f position) override;
	void setPosition(float x, float y) override;

	void move(float xOffset, float yOffset) override;

	void render(sf::RenderWindow& window) override;

	sf::Vector2f getPosition() const override;
	sf::FloatRect getBounds() const override;

	float getRotation() const override;

private:
    sf::Sprite sprite_;
    sf::Texture texture_;
};
}