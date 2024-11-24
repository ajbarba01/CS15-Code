#pragma once

#include <iostream>
#include <vector>

#include "gameObject.h"
#include "collision.h"

using namespace std;

class ObjectCollection
{
private:
	vector<GameObject*> objects;
	vector<GameObject*> newObjects;

	Collision* collisionSystem;

public:
	ObjectCollection();

	void earlyUpdate();
	void update();
	void lateUpdate();
	void render(sf::RenderWindow* window);
	void processNewObjects();
	void processRemovals();
	void clean();

	void setCollisionSystem(Collision* collisionSystem) { this->collisionSystem = collisionSystem; }
	void addObject(GameObject* toAdd);
	void addObject(GameObject* toAdd[], int numObjects);
};