#pragma once

#include <SFML/graphics.hpp>

#include "component.h"

class Transform : public Component
{
private:
	sf::Vector2f position;
	bool isStatic;

public:
	Transform(GameObject* owner);

	sf::Vector2f getPosition() { return this->position; };
	void setStatic(bool isStatic) { this->isStatic = isStatic; }
	bool getStatic() { return this->isStatic; }
	void setPosition(sf::Vector2f newPosition) { this->position = newPosition; }
	void move(sf::Vector2f deltaMove);

};