#include "collision.h"


std::vector<CollisionLayer> COLLISION_LAYERS = { CollisionLayer::Default, CollisionLayer::Terrain, };


Collision::Collision()
{
	this->clear();
}

void Collision::addObject(GameObject* gameObject)
{
	CollisionLayer objectLayer = static_cast<Collider*>(gameObject->getComponent(ComponentType::T_Collider))->getLayer();
	this->objects[objectLayer][gameObject->getID()] = gameObject;
}

void Collision::removeObject(GameObject* gameObject)
{
	if (gameObject->hasComponent(ComponentType::T_Collider))
	{
		CollisionLayer objectLayer = static_cast<Collider*>(gameObject->getComponent(ComponentType::T_Collider))->getLayer();
		this->objects[objectLayer].erase(gameObject->getID());
	}
}

void Collision::clear()
{
	for (CollisionLayer layer : COLLISION_LAYERS)
	{
		this->objects[layer] = std::unordered_map<int, GameObject*>();
	}
}

void Collision::processRemovals()
{
	for (auto& layerPair : this->objects) {
		auto& objectMap = layerPair.second;
		for (auto it = objectMap.begin(); it != objectMap.end(); ) {
			if (!it->second || it->second->getQueuedForRemoval()) {
				it = objectMap.erase(it);
			}
			else {
				++it;
			}
		}
	}
}

void Collision::update()
{
	this->resolve();
}

void Collision::resolve()
{
	for (const auto& layerPair : this->objects)
	{
		CollisionLayer layer = layerPair.first;

		for (const auto& objectPair : layerPair.second)
		{
			GameObject* object = objectPair.second;
			Collider* collider = static_cast<Collider*>(object->getComponent(ComponentType::T_Collider));
			collider->resetManifold();

			if (object->transform->getStatic())
			{
				continue;
			}

			this->search(collider);
			for (GameObject* overlappingObject : this->overlappingObjects)
			{
				Collider* otherCollider = static_cast<Collider*>(overlappingObject->getComponent(ComponentType::T_Collider));
				if (otherCollider->isTrigger)
				{
					otherCollider->setManifold(true, collider);
					continue;
				}

				Manifold manifold = collider->intersects(otherCollider);
				if (manifold.colliding)
				{
					// std::cout << "COLLIDING\n";
					collider->resolveOverlap(manifold);
					collider->resetManifold();
				}
			}
		}
	}
}

void Collision::search(Collider* collider)
{
	this->overlappingObjects.clear();
	for (CollisionLayer layer : collider->getCollideLayers())
	{
		for (const auto& objectPair : this->objects[layer])
		{
			Collider* other = static_cast<Collider*>(objectPair.second->getComponent(ComponentType::T_Collider));

			if (collider == other)
			{
				continue;
			}

			if (other->getRect().intersects(collider->getRect()))
			{
				this->overlappingObjects.push_back(objectPair.second);
			}
		}
	}
}




