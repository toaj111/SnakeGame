#pragma once

#include <SFML/Graphics.hpp>

namespace sfSnake
{
class SnakeNode
{
public:
	SnakeNode(sf::Vector2f position = sf::Vector2f(0, 0));

	virtual void setPosition(sf::Vector2f position) = 0;
	virtual void setPosition(float x, float y) = 0;

	virtual void move(float xOffset, float yOffset) = 0;

	virtual void render(sf::RenderWindow& window) = 0;

	virtual sf::Vector2f getPosition() const = 0;
	virtual sf::FloatRect getBounds() const = 0;

	virtual float getRotation() const = 0;

	static const float Radius;

protected:
	sf::Vector2f position_;
};
}

