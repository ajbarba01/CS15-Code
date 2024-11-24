#pragma once

#include "enum.h"
#include "collider.h"
#include "gameObject.h"

#include <unordered_map>


class Collision
{
private:
	std::unordered_map<CollisionLayer, std::unordered_map<int, GameObject*>> objects;
	std::vector<GameObject*> overlappingObjects;

public:
	Collision();

	void addObject(GameObject* gameObject);
	void removeObject(GameObject* gameObject);
	void clear();

	void processRemovals();
	void update();
	void resolve();
	void search(Collider* collider);
};