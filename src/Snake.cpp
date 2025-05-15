#include <SFML/Graphics.hpp>

#include <memory>
#include <iostream>
#include <cmath>

#include "include/Snake.h"
#include "include/Game.h"
#include "include/Fruit.h"
#include "include/SnakeNode.h"
#include "include/GameOverScreen.h"
#include "include/SnakeHeadNode.h"
#include "include/SnakeBodyNode.h"

using namespace sfSnake;

const int Snake::InitialSize = 5;
const float Snake::UnitDistance = sqrt(8 * SnakeNode::Radius * SnakeNode::Radius);

float getDistance(const sf::Vector2f& a, const sf::Vector2f& b) {
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
};

Snake::Snake() : hitSelf_(false), offset_x_(0), offset_y_(-UnitDistance)
{
	initNodes();

	pickupBuffer_.loadFromFile("assets/sounds/pickup.aiff");
	pickupSound_.setBuffer(pickupBuffer_);
	pickupSound_.setVolume(30);

	dieBuffer_.loadFromFile("assets/sounds/die.wav");
	dieSound_.setBuffer(dieBuffer_);
	dieSound_.setVolume(50);
}

void Snake::initNodes()
{
	nodes_.push_back(std::make_unique<SnakeHeadNode>(sf::Vector2f(
		Game::Width / 2 - SnakeNode::Radius,
		Game::Height / 2 - SnakeNode::Radius)));
	
	for (int i = 1; i < Snake::InitialSize; ++i)
	{
		nodes_.push_back(std::make_unique<SnakeBodyNode>(sf::Vector2f(
			Game::Width / 2 - SnakeNode::Radius,
			Game::Height / 2 - SnakeNode::Radius + (2 * SnakeNode::Radius * i))));
	}
}

void Snake::handleInput(sf::RenderWindow& window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		offset_x_ = 0;
		offset_y_ = -UnitDistance;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		offset_x_ = 0;
		offset_y_ = UnitDistance;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		offset_x_ = -UnitDistance;
		offset_y_ = 0;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		offset_x_ = UnitDistance;
		offset_y_ = 0;
	}
	
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		auto mouse_pos = sf::Mouse::getPosition(window);
		float dx = mouse_pos.x - nodes_[0]->getPosition().x;
		float dy = mouse_pos.y - nodes_[0]->getPosition().y;

		float dist = sqrt(dx * dx + dy * dy);

		offset_x_ = dx * UnitDistance / dist;
		offset_y_ = dy * UnitDistance / dist;
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
		if (it->getBounds().intersects(nodes_[0]->getBounds()))
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
	auto prev_last_node_pos = nodes_[nodes_.size() - 1]->getPosition();
	if (nodes_.size() == 1) {
		auto last_node_pos = sf::Vector2f(prev_last_node_pos.x - offset_x_, prev_last_node_pos.y - offset_y_);
		nodes_.push_back(std::make_unique<SnakeBodyNode>(last_node_pos, nodes_[0]->getRotation()));
		return;
	}
	auto prev_second_last_node_pos = nodes_[nodes_.size() - 1]->getPosition();
	float offset_x = prev_second_last_node_pos.x - prev_last_node_pos.x;
	float offset_y = prev_second_last_node_pos.y - prev_last_node_pos.y;
	auto last_node_pos = sf::Vector2f(prev_last_node_pos.x - offset_x, prev_last_node_pos.y - offset_y_);
	
	nodes_.push_back(std::make_unique<SnakeBodyNode>(last_node_pos, nodes_[nodes_.size() - 1]->getRotation()));
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
	auto& headNode = nodes_[0];
	for (decltype(nodes_.size()) i = 1; i < nodes_.size(); ++i)
	{
		
		if (getDistance(headNode->getPosition(), nodes_[i]->getPosition()) < 0.5 * SnakeNode::Radius)
		{
			dieSound_.play();
			sf::sleep(sf::seconds(dieBuffer_.getDuration().asSeconds()));
			hitSelf_ = true;
		}
	}
}

void Snake::checkEdgeCollisions()
{	
	auto& headNode = nodes_[0];
	if (headNode->getPosition().x <= 0)
		headNode->setPosition(Game::Width, headNode->getPosition().y);
	else if (headNode->getPosition().x >= Game::Width)
		nodes_[0]->setPosition(0, nodes_[0]->getPosition().y);
	else if (headNode->getPosition().y <= 0)
		headNode->setPosition(headNode->getPosition().x, Game::Height);
	else if (headNode->getPosition().y >= Game::Height)
		headNode->setPosition(headNode->getPosition().x, 0);
}

void Snake::move()
{
	for (decltype(nodes_.size()) i = nodes_.size() - 1; i > 0; --i)
	{
		auto offset_x = nodes_[i - 1]->getPosition().x - nodes_[i]->getPosition().x;
		auto offset_y = nodes_[i - 1]->getPosition().y - nodes_[i]->getPosition().y;
		nodes_[i]->move(offset_x, offset_y);
	}

	nodes_[0]->move(offset_x_, offset_y_);
}

void Snake::render(sf::RenderWindow& window)
{
	for (auto& node : nodes_)
		node->render(window);
}

