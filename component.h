#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "enum.h"

class GameObject;

class Component
{
public:
	GameObject* owner;
	ComponentType componentType;

public:
	Component(GameObject* owner, ComponentType componentType);
	virtual ~Component() { };
	
	virtual void awake() { }
	virtual void start() { }
	virtual void earlyUpdate() { }
	virtual void update() { }
	virtual void lateUpdate() { }
	virtual void render(sf::RenderWindow* window) { }

	void setOwner(GameObject* owner) { this->owner = owner; }
};