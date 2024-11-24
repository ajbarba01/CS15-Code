#include "transform.h"
#include <iostream>

Transform::Transform(GameObject* owner) : Component(owner, ComponentType::T_Transform)
{
	this->isStatic = false;
}

void Transform::move(sf::Vector2f deltaMove)
{
	this->position += deltaMove;
}