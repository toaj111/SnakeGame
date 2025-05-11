#include <SFML/Graphics.hpp>

#include <memory>
#include <iostream>
#include <cmath>

#include "include/Snake.h"
#include "include/Game.h"
#include "include/Fruit.h"
#include "include/SnakeNode.h"
#include "include/GameOverScreen.h"

using namespace sfSnake;

const int Snake::InitialSize = 5;

Snake::Snake() : direction_(Direction::Up), hitSelf_(false)
{
	initNodes();

	unit_distance_ = sqrt(SnakeNode::Width * SnakeNode::Width + SnakeNode::Height * SnakeNode::Height);
	offset_x_ = 0;
	offset_y_ = unit_distance_;

	pickupBuffer_.loadFromFile("assets/sounds/pickup.aiff");
	pickupSound_.setBuffer(pickupBuffer_);
	pickupSound_.setVolume(30);

	dieBuffer_.loadFromFile("assets/sounds/die.wav");
	dieSound_.setBuffer(dieBuffer_);
	dieSound_.setVolume(50);
}

void Snake::initNodes()
{
	for (int i = 0; i < Snake::InitialSize; ++i)
	{
		nodes_.push_back(SnakeNode(sf::Vector2f(
			Game::Width / 2 - SnakeNode::Width / 2,
			Game::Height / 2 - (SnakeNode::Height / 2) + (SnakeNode::Height * i))));
	}
}

void Snake::handleInput(sf::RenderWindow& window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		offset_x_ = 0;
		offset_y_ = unit_distance_;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		offset_x_ = 0;
		offset_y_ = -unit_distance_;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		offset_x_ = -unit_distance_;
		offset_y_ = 0;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		offset_x_ = unit_distance_;
		offset_y_ = 0;
	}
	
	// TODO:处理鼠标输入
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		auto mouse_pos = sf::Mouse::getPosition(window);
		float dx = mouse_pos.x - position_.x;
		float dy = mouse_pos.y - position_.y;

		float dist = sqrt(dx * dx + dy * dy);

		offset_x_ = dx * unit_distance_ / dist;
		offset_y_ = dy * unit_distance_ / dist;
	}
	
}

void Snake::update(sf::Time delta)
{
	move();
	checkEdgeCollisions();
	checkSelfCollisions();
}

void Snake::checkFruitCollisions(std::vector<Fruit>& fruits)
{
	decltype(fruits.begin()) toRemove = fruits.end();

	for (auto it = fruits.begin(); it != fruits.end(); ++it)
	{
		if (it->getBounds().intersects(nodes_[0].getBounds()))
			toRemove = it;
	}

	if (toRemove != fruits.end())
	{
		pickupSound_.play();
		grow();
		fruits.erase(toRemove);
	}
}

void Snake::grow()
{
	// switch (direction_)
	// {
	// case Direction::Up:
	// 	nodes_.push_back(SnakeNode(sf::Vector2f(nodes_[nodes_.size() - 1].getPosition().x,
	// 		nodes_[nodes_.size() - 1].getPosition().y + SnakeNode::Height)));
	// 	break;
	// case Direction::Down:
	// 	nodes_.push_back(SnakeNode(sf::Vector2f(nodes_[nodes_.size() - 1].getPosition().x,
	// 		nodes_[nodes_.size() - 1].getPosition().y - SnakeNode::Height)));
	// 	break;
	// case Direction::Left:
	// 	nodes_.push_back(SnakeNode(sf::Vector2f(nodes_[nodes_.size() - 1].getPosition().x + SnakeNode::Width,
	// 		nodes_[nodes_.size() - 1].getPosition().y)));
	// 	break;
	// case Direction::Right:
	// 	nodes_.push_back(SnakeNode(sf::Vector2f(nodes_[nodes_.size() - 1].getPosition().x - SnakeNode::Width,
	// 		nodes_[nodes_.size() - 1].getPosition().y)));
	// 	break;
	// }

	// TODO:在snakeNode中存储每一块的方向
	nodes_.push_back(SnakeNode(sf::Vector2f(nodes_[nodes_.size() - 1].getPosition().x - offset_x_, nodes_[nodes_.size() - 1].getPosition().y - offset_y_)));
}

unsigned Snake::getSize() const
{
	return nodes_.size();
}

bool Snake::hitSelf() const
{
	return hitSelf_;
}

void Snake::checkSelfCollisions()
{
	SnakeNode& headNode = nodes_[0];

	for (decltype(nodes_.size()) i = 1; i < nodes_.size(); ++i)
	{
		if (headNode.getBounds().intersects(nodes_[i].getBounds()))
		{
			dieSound_.play();
			sf::sleep(sf::seconds(dieBuffer_.getDuration().asSeconds()));
			hitSelf_ = true;
		}
	}
}

void Snake::checkEdgeCollisions()
{
	SnakeNode& headNode = nodes_[0];

	if (headNode.getPosition().x <= 0)
		headNode.setPosition(Game::Width, headNode.getPosition().y);
	else if (headNode.getPosition().x >= Game::Width)
		headNode.setPosition(0, headNode.getPosition().y);
	else if (headNode.getPosition().y <= 0)
		headNode.setPosition(headNode.getPosition().x, Game::Height);
	else if (headNode.getPosition().y >= Game::Height)
		headNode.setPosition(headNode.getPosition().x, 0);
}

void Snake::move()
{
	for (decltype(nodes_.size()) i = nodes_.size() - 1; i > 0; --i)
	{
		nodes_[i].setPosition(nodes_.at(i - 1).getPosition());
	}

	// switch (direction_)
	// {
	// case Direction::Up:
	// 	nodes_[0].move(offset_x_, offset_y_);
	// 	break;
	// case Direction::Down:
	// 	nodes_[0].move(0, unit_;
	// 	break;
	// case Direction::Left:
	// 	nodes_[0].move(-unit_distance_, 0);
	// 	break;
	// case Direction::Right:
	// 	nodes_[0].move(unit_distance_, 0);
	// 	break;
	// }

	nodes_[0].move(offset_x_, offset_y_);
}

void Snake::render(sf::RenderWindow& window)
{
	for (auto& node : nodes_)
		node.render(window);
}

