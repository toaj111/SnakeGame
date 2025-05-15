#include <SFML/Graphics.hpp>

#include "include/SnakeNode.h"

using namespace sfSnake;

const float SnakeNode::Radius = 15.f;

SnakeNode::SnakeNode(sf::Vector2f position) : position_(position) {}