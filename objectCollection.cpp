#include <iostream>
#include <algorithm>

#include "objectCollection.h"


ObjectCollection::ObjectCollection()
{
	this->objects = vector<GameObject*>();
	this->newObjects = vector<GameObject*>();
	this->collisionSystem = nullptr;
}

void ObjectCollection::earlyUpdate()
{
	for (GameObject* obj : this->objects)
	{
		obj->earlyUpdate();
	}
}

void ObjectCollection::update()
{
	this->processRemovals();
	this->processNewObjects();

	for (GameObject* obj : this->objects)
	{
		obj->update();
	}
}

void ObjectCollection::lateUpdate()
{
	for (GameObject* obj : this->objects)
	{
		obj->lateUpdate();
	}
}

void ObjectCollection::render(sf::RenderWindow* window)
{
	for (GameObject* obj : this->objects)
	{
		obj->render(window);
	}
}

void ObjectCollection::processNewObjects()
{
	if (this->newObjects.size() > 0)
	{
		for (GameObject* obj : this->newObjects)
		{
			obj->awake();
		}

		for (GameObject* obj : this->newObjects)
		{
			obj->start();
			
			if (this->collisionSystem)
			{
				if (obj->hasComponent(ComponentType::T_Collider))
				{
					this->collisionSystem->addObject(obj);
				}
			}
		}

		this->objects.insert(this->objects.end(), this->newObjects.begin(), this->newObjects.end());
		this->newObjects.clear();
		
	}
}

void ObjectCollection::processRemovals()
{

	for (auto it = objects.begin(); it != objects.end();) {
		GameObject* obj = *it;
		if (obj->getQueuedForRemoval()) {
			this->collisionSystem->removeObject(obj);
			delete obj;
			it = objects.erase(it);
		}
		else {
			++it;
		}
	}
}

void ObjectCollection::clean()
{
	this->processNewObjects();
	for (GameObject* obj : this->objects)
	{
		obj->queueForRemoval();
	}
	this->processRemovals();
}

void ObjectCollection::addObject(GameObject* toAdd)
{
	this->newObjects.push_back(toAdd);
}

void ObjectCollection::addObject(GameObject* toAdd[], int numObjects)
{
	for (int i = 0; i < numObjects; i++)
	{
		this->newObjects.push_back(toAdd[i]);
	}
}


