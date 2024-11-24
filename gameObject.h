#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>

#include "component.h"
#include "transform.h"


class GameObject
{
private:
	static int nextID;
	int gameID;
	bool isQueuedForRemoval;
	std::unordered_map<ComponentType, Component*> components;

public:
	Transform* transform;

public:
	GameObject();
	~GameObject();

	void awake();
	void start();
	void earlyUpdate();
	void update();
	void lateUpdate();
	void render(sf::RenderWindow* window);
	
	void addComponent(Component* newComponent);
	void removeComponent(ComponentType componentType);
	Component* getComponent(ComponentType componentType);

	bool hasComponent(ComponentType componentType);

	void queueForRemoval();
	bool getQueuedForRemoval() { return this->isQueuedForRemoval; }
	
	int getID() { return gameID; };
};